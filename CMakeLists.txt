cmake_minimum_required(VERSION 3.20)

# Load version configuration
include(VERSION.cmake)

project(croupier-cpp-sdk
    VERSION ${CROUPIER_SDK_VERSION}
    DESCRIPTION "${CROUPIER_SDK_DESCRIPTION}"
    HOMEPAGE_URL "${CROUPIER_SDK_HOMEPAGE_URL}"
    LANGUAGES CXX
)

# Verify build tools are available after project setup
# Note: Changed to WARNING to support vcpkg toolchain initialization
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if(NOT CMAKE_MAKE_PROGRAM)
        message(WARNING "CMAKE_MAKE_PROGRAM is not set. Build may fail if build tools are not installed.")
    else()
        message(STATUS "Make program: ${CMAKE_MAKE_PROGRAM}")
    endif()
    if(NOT CMAKE_CXX_COMPILER)
        message(WARNING "C++ compiler is not available. Build may fail if g++ is not installed.")
    else()
        message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
    endif()
endif()

# ========== Project Configuration ==========
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable position independent code for shared libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ========== Build Options ==========
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_STATIC_LIBS "Build static libraries" ON)
option(BUILD_EXAMPLES "Build example programs" ON)
option(BUILD_TESTS "Build unit tests" OFF)
option(ENABLE_VCPKG "Enable vcpkg package management" ON)
option(CROUPIER_CI_BUILD "Enable CI build with proto generation" OFF)

# ========== Standalone Build Options ==========
option(CROUPIER_STANDALONE_BUILD "Enable standalone build mode" OFF)
option(CROUPIER_PREBUILT_PROTO "Use prebuilt proto files" OFF)
option(CROUPIER_ONLINE_BUILD "Enable online proto download" OFF)
option(USE_SYSTEM_PACKAGES "Use system packages instead of vcpkg" OFF)
set(CROUPIER_PROTO_DIR "${CMAKE_CURRENT_SOURCE_DIR}/downloaded_proto" CACHE STRING "Proto files directory for online build")

# ========== Proto Generation Module ==========
include(cmake/ProtoGeneration.cmake)

# Setup build type with enhanced logic for standalone builds
if(CROUPIER_STANDALONE_BUILD)
    setup_standalone_build()
else()
    setup_ci_build()
endif()

# Set gRPC enable flag based on CI build result
if(CROUPIER_SDK_ENABLE_GRPC)
    message(STATUS "Building with real gRPC implementation")
    set(ENABLE_GRPC ON)
else()
    message(STATUS "Building with mock gRPC implementation")
    set(ENABLE_GRPC OFF)
endif()

# ========== vcpkg Integration ==========
if(ENABLE_VCPKG)
    # Set vcpkg toolchain file if not already set
    if(NOT CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{VCPKG_ROOT})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "Vcpkg toolchain file")
    endif()

    # vcpkg triplet configuration
    if(NOT VCPKG_TARGET_TRIPLET)
        if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
            if(CMAKE_GENERATOR_PLATFORM STREQUAL "x64" OR CMAKE_SIZEOF_VOID_P EQUAL 8)
                set(VCPKG_TARGET_TRIPLET "x64-windows")
            else()
                set(VCPKG_TARGET_TRIPLET "x86-windows")
            endif()
        elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
            if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
                set(VCPKG_TARGET_TRIPLET "arm64-osx")
            else()
                set(VCPKG_TARGET_TRIPLET "x64-osx")
            endif()
        elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
            if(CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
                set(VCPKG_TARGET_TRIPLET "arm64-linux")
            else()
                set(VCPKG_TARGET_TRIPLET "x64-linux")
            endif()
        endif()
    endif()

    message(STATUS "Using vcpkg triplet: ${VCPKG_TARGET_TRIPLET}")
endif()

# ========== Dependencies ==========
find_package(Threads REQUIRED)

# gRPC and Protobuf for real implementation
if(ENABLE_GRPC)
    find_package(gRPC CONFIG REQUIRED)
    find_package(Protobuf CONFIG QUIET)
    if(NOT Protobuf_FOUND)
        find_package(Protobuf MODULE REQUIRED)
    endif()
    find_package(ZLIB REQUIRED)

    message(STATUS "Found gRPC: ${gRPC_VERSION}")
    message(STATUS "Found Protobuf: ${Protobuf_VERSION}")

    set(GRPC_LIBRARIES
        gRPC::grpc++
        gRPC::grpc++_reflection
        gRPC::gpr
        protobuf::libprotobuf
    )
endif()

# JSON library for better JSON support (via vcpkg)
find_package(nlohmann_json CONFIG)
if(nlohmann_json_FOUND)
    message(STATUS "Found nlohmann_json: ${nlohmann_json_VERSION}")
    set(JSON_LIBRARY nlohmann_json::nlohmann_json)
else()
    message(STATUS "nlohmann_json not found, using built-in JSON utilities")
    set(JSON_LIBRARY "")
endif()

# ========== Compiler Settings ==========
if(MSVC)
    # MSVC specific settings
    # Use /W4 for SDK code but disable warnings-as-errors for specific warnings
    # from protobuf generated code
    add_compile_options(/W4)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    # Disable C4100 (unreferenced parameter) and C4267 (size_t to int conversion)
    # for generated protobuf code - these are common in generated code
    add_compile_options(/wd4100 /wd4267)
    # Keep WX for most code, but these warnings are unavoidable in generated code
    # Note: We rely on CI to catch real errors, generated code warnings are acceptable
else()
    # GCC/Clang settings
    add_compile_options(-Wall -Wextra -Werror)

    # Suppress warnings from third-party libraries (protobuf, gRPC)
    add_compile_options(
        -Wno-deprecated-declarations    # Suppress protobuf deprecated API warnings
        -Wno-unused-parameter           # Suppress gRPC unused parameter warnings
    )

    # Enable debug info in release builds for better profiling
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-g)
    endif()
endif()

# ========== Generated Proto Files ==========
# `cmake/ProtoGeneration.cmake` populates:
# - `GENERATED_PROTO_SOURCES` / `GENERATED_PROTO_HEADERS`
# - `PROTO_GENERATED_DIR`
#
# Keep a minimal fallback for older/alternate layouts only if nothing was configured.
if(ENABLE_GRPC AND NOT GENERATED_PROTO_SOURCES)
    message(STATUS "⚠️ No generated proto sources were configured; attempting fallback discovery")

    set(MONOREPO_GEN_DIR "${PROJECT_ROOT_DIR}/gen")
    if(EXISTS "${MONOREPO_GEN_DIR}/croupier")
        file(GLOB_RECURSE GENERATED_PROTO_SOURCES "${MONOREPO_GEN_DIR}/**/*.cc")
        file(GLOB_RECURSE GENERATED_PROTO_HEADERS "${MONOREPO_GEN_DIR}/**/*.h")
        if(GENERATED_PROTO_SOURCES)
            set(PROTO_GENERATED_DIR "${MONOREPO_GEN_DIR}")
        endif()
    endif()

    if(NOT GENERATED_PROTO_SOURCES)
        set(SDK_GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/generated")
        if(EXISTS "${SDK_GENERATED_DIR}/croupier")
            file(GLOB_RECURSE GENERATED_PROTO_SOURCES "${SDK_GENERATED_DIR}/**/*.cc")
            file(GLOB_RECURSE GENERATED_PROTO_HEADERS "${SDK_GENERATED_DIR}/**/*.h")
            if(GENERATED_PROTO_SOURCES)
                set(PROTO_GENERATED_DIR "${SDK_GENERATED_DIR}")
            endif()
        endif()
    endif()

    if(NOT GENERATED_PROTO_SOURCES)
        message(STATUS "🔧 No proto files found, using mock gRPC implementation")
        set(ENABLE_GRPC OFF)
    endif()
endif()

# ========== Source Files ==========
# SDK source and header files
set(SDK_SOURCES
    src/croupier_client.cpp
    src/grpc_service.cpp
    src/config_driven_loader.cpp
    src/utils/json_utils.cpp
    src/utils/file_utils.cpp
    src/config/client_config_loader.cpp
    src/plugin/dynamic_loader.cpp
)

set(SDK_HEADERS
    include/croupier/sdk/croupier_client.h
    include/croupier/sdk/grpc_service.h
    include/croupier/sdk/config_driven_loader.h
    include/croupier/sdk/utils/json_utils.h
    include/croupier/sdk/utils/file_utils.h
    include/croupier/sdk/config/client_config_loader.h
    include/croupier/sdk/plugin/dynamic_loader.h
)

# Add generated proto files if gRPC is enabled AND proto files exist
if(ENABLE_GRPC)
    if(GENERATED_PROTO_SOURCES)
        list(APPEND SDK_SOURCES ${GENERATED_PROTO_SOURCES})
        list(APPEND SDK_HEADERS ${GENERATED_PROTO_HEADERS})
        message(STATUS "Added generated proto files to build")
    else()
        message(STATUS "Building without generated proto files (using mock implementation)")
    endif()
endif()

# ========== Library Targets ==========

# Shared Library
if(BUILD_SHARED_LIBS)
    add_library(croupier-sdk-shared SHARED ${SDK_SOURCES} ${SDK_HEADERS})
    set_target_properties(croupier-sdk-shared PROPERTIES
        OUTPUT_NAME "croupier-sdk"
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        EXPORT_NAME "croupier-sdk"
    )

    # Set output directories for the shared library
    # On Windows: .dll goes to bin/, .lib (import library) stays in build root for linking
    set_target_properties(croupier-sdk-shared PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        # Keep import library in build root so linker can find it directly
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )

    target_include_directories(croupier-sdk-shared
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<$<AND:$<BOOL:${ENABLE_GRPC}>,$<BOOL:${PROTO_GENERATED_DIR}>>:$<BUILD_INTERFACE:${PROTO_GENERATED_DIR}>>
            $<INSTALL_INTERFACE:include>
    )

    target_link_libraries(croupier-sdk-shared
        PUBLIC
            Threads::Threads
    )

    if(ENABLE_GRPC)
        target_link_libraries(croupier-sdk-shared
            PUBLIC
                ${GRPC_LIBRARIES}
                ZLIB::ZLIB
        )
        target_compile_definitions(croupier-sdk-shared
            PUBLIC
                CROUPIER_SDK_ENABLE_GRPC
                PROTOBUF_NONNULL=
                PROTOBUF_NULLABLE=
        )
    endif()

    if(JSON_LIBRARY)
        target_link_libraries(croupier-sdk-shared
            PUBLIC
                ${JSON_LIBRARY}
        )
        target_compile_definitions(croupier-sdk-shared
            PUBLIC
                CROUPIER_SDK_ENABLE_JSON
        )
    endif()

    target_compile_definitions(croupier-sdk-shared
        PRIVATE
            CROUPIER_SDK_BUILDING_DLL
        PUBLIC
            CROUPIER_SDK_SHARED
    )

    # Alias for easier usage
    add_library(croupier::sdk-shared ALIAS croupier-sdk-shared)
endif()

# Static Library
if(BUILD_STATIC_LIBS)
    add_library(croupier-sdk-static STATIC ${SDK_SOURCES} ${SDK_HEADERS})
    set_target_properties(croupier-sdk-static PROPERTIES
        OUTPUT_NAME "croupier-sdk-static"
        EXPORT_NAME "croupier-sdk-static"
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )

    target_include_directories(croupier-sdk-static
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<$<AND:$<BOOL:${ENABLE_GRPC}>,$<BOOL:${PROTO_GENERATED_DIR}>>:$<BUILD_INTERFACE:${PROTO_GENERATED_DIR}>>
            $<INSTALL_INTERFACE:include>
    )

    target_link_libraries(croupier-sdk-static
        PUBLIC
            Threads::Threads
    )

    if(ENABLE_GRPC)
        target_link_libraries(croupier-sdk-static
            PUBLIC
                ${GRPC_LIBRARIES}
                ZLIB::ZLIB
        )
        target_compile_definitions(croupier-sdk-static
            PUBLIC
                CROUPIER_SDK_ENABLE_GRPC
                PROTOBUF_NONNULL=
                PROTOBUF_NULLABLE=
        )
    endif()

    if(JSON_LIBRARY)
        target_link_libraries(croupier-sdk-static
            PUBLIC
                ${JSON_LIBRARY}
        )
        target_compile_definitions(croupier-sdk-static
            PUBLIC
                CROUPIER_SDK_ENABLE_JSON
        )
    endif()

    target_compile_definitions(croupier-sdk-static
        PUBLIC
            CROUPIER_SDK_STATIC
    )

    # Alias for easier usage
    add_library(croupier::sdk-static ALIAS croupier-sdk-static)
endif()

# Default library target (shared if available, otherwise static)
if(BUILD_SHARED_LIBS)
    add_library(croupier::sdk ALIAS croupier-sdk-shared)
elseif(BUILD_STATIC_LIBS)
    add_library(croupier::sdk ALIAS croupier-sdk-static)
endif()

# ========== Example Programs ==========
if(BUILD_EXAMPLES)
    # Basic example
    add_executable(croupier-example examples/example.cpp)
    target_link_libraries(croupier-example
        PRIVATE
            croupier::sdk
    )

    # Virtual Object Demo
    add_executable(croupier-virtual-object-demo examples/virtual_object_demo.cpp)
    target_link_libraries(croupier-virtual-object-demo
        PRIVATE
            croupier::sdk
    )

    # Complete Example with gRPC
    add_executable(croupier-complete-example examples/complete_example.cpp)
    target_link_libraries(croupier-complete-example
        PRIVATE
            croupier::sdk
    )

    # Advanced Configuration Example
    add_executable(croupier-config-example examples/config_example.cpp)
    target_link_libraries(croupier-config-example
        PRIVATE
            croupier::sdk
    )

    # Plugin System Demo
    add_executable(croupier-plugin-demo examples/plugin_demo.cpp)
    target_link_libraries(croupier-plugin-demo
        PRIVATE
            croupier::sdk
    )

    # Comprehensive Demo - Shows ALL SDK interfaces
    add_executable(croupier-comprehensive-demo examples/comprehensive_demo.cpp)
    target_link_libraries(croupier-comprehensive-demo
        PRIVATE
            croupier::sdk
    )

    # Example Plugin (shared library)
    add_library(example_plugin SHARED examples/plugins/example_plugin.cpp)
    target_include_directories(example_plugin
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    # Platform-specific settings for plugin
    if(WIN32)
        # Windows DLL export settings
        target_compile_definitions(example_plugin PRIVATE BUILDING_PLUGIN_DLL)
        set_target_properties(example_plugin PROPERTIES
            PREFIX ""
            SUFFIX ".dll"
        )
    elseif(APPLE)
        # macOS dylib settings
        set_target_properties(example_plugin PROPERTIES
            PREFIX "lib"
            SUFFIX ".dylib"
        )
    else()
        # Linux shared library settings
        set_target_properties(example_plugin PROPERTIES
            PREFIX "lib"
            SUFFIX ".so"
        )
    endif()

    # Set output directory for plugins
    set_target_properties(example_plugin PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
    )

    # Set output directory for examples
    set_target_properties(croupier-example croupier-virtual-object-demo croupier-complete-example croupier-config-example croupier-plugin-demo croupier-comprehensive-demo PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )
endif()

# ========== Unit Tests ==========
if(BUILD_TESTS)
    enable_testing()

    find_package(GTest CONFIG QUIET)
    if(NOT GTest_FOUND)
        include(FetchContent)

        # Keep this minimal: only used when GTest isn't provided by vcpkg/system packages.
        # Pin to a stable tag to avoid test flakiness from upstream changes.
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.15.2
        )

        set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()

    # Targets are available either from `find_package(GTest)` (vcpkg/system) or FetchContent.
    if(TARGET GTest::gtest_main OR TARGET gtest_main)
        add_executable(croupier-sdk-tests
            tests/test_virtual_objects.cpp
            tests/test_utils.cpp
            tests/test_integration.cpp
            tests/test_invoker.cpp
        )

        if(TARGET GTest::gtest_main)
            set(_croupier_gtest_main GTest::gtest_main)
        else()
            set(_croupier_gtest_main gtest_main)
        endif()

        target_link_libraries(croupier-sdk-tests
            PRIVATE
                croupier::sdk
                ${_croupier_gtest_main}
        )

        add_test(NAME CroupierSDKTests COMMAND croupier-sdk-tests)
    else()
        message(WARNING "BUILD_TESTS=ON but GTest is unavailable; skipping croupier-sdk-tests target")
    endif()
endif()

# ========== Install Rules ==========
include(GNUInstallDirs)

# Public SDK headers
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

# Generated proto headers are part of the public API surface (grpc_service.h includes them).
if(ENABLE_GRPC AND PROTO_GENERATED_DIR AND EXISTS "${PROTO_GENERATED_DIR}/croupier")
    install(DIRECTORY "${PROTO_GENERATED_DIR}/croupier/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/croupier"
        FILES_MATCHING PATTERN "*.h"
    )
endif()

if(BUILD_SHARED_LIBS)
    install(TARGETS croupier-sdk-shared
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
endif()

if(BUILD_STATIC_LIBS)
    install(TARGETS croupier-sdk-static
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )
endif()

# ========== Package Information ==========
set(CPACK_PACKAGE_NAME "croupier-cpp-sdk")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Croupier C++ SDK for Virtual Object Registration")
set(CPACK_PACKAGE_VENDOR "Croupier Project")
set(CPACK_PACKAGE_CONTACT "support@croupier.dev")

# Platform-specific package settings
if(WIN32)
    set(CPACK_GENERATOR "ZIP;NSIS")
elseif(APPLE)
    set(CPACK_GENERATOR "TGZ;DragNDrop")
else()
    set(CPACK_GENERATOR "TGZ;DEB;RPM")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Croupier Project <support@croupier.dev>")
    set(CPACK_RPM_PACKAGE_LICENSE "MIT")
endif()

include(CPack)

# ========== Summary ==========
message(STATUS "")
message(STATUS "========== Build Configuration Summary ==========")
message(STATUS "Project Name:    ${PROJECT_NAME}")
message(STATUS "Version:         ${PROJECT_VERSION}")
message(STATUS "Build Type:      ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard:    ${CMAKE_CXX_STANDARD}")
message(STATUS "")
message(STATUS "Options:")
message(STATUS "  BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")
message(STATUS "  BUILD_STATIC_LIBS: ${BUILD_STATIC_LIBS}")
message(STATUS "  BUILD_EXAMPLES:    ${BUILD_EXAMPLES}")
message(STATUS "  BUILD_TESTS:       ${BUILD_TESTS}")
message(STATUS "  ENABLE_VCPKG:      ${ENABLE_VCPKG}")
message(STATUS "  ENABLE_GRPC:       ${ENABLE_GRPC}")
if(ENABLE_VCPKG)
message(STATUS "  VCPKG_TRIPLET:     ${VCPKG_TARGET_TRIPLET}")
endif()
message(STATUS "")
message(STATUS "Dependencies:")
if(ENABLE_GRPC)
message(STATUS "  gRPC:            Found")
message(STATUS "  Protobuf:        Found")
endif()
if(nlohmann_json_FOUND)
message(STATUS "  nlohmann_json:   Found")
endif()
message(STATUS "=================================================")
message(STATUS "")

cmake_minimum_required(VERSION 3.15)
project(croupier-sdk-cpp VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(croupier_sdk
    src/croupier_client.cpp
)
target_include_directories(croupier_sdk PUBLIC include)

option(CROUPIER_BUILD_EXAMPLES "Build examples" ON)
if(CROUPIER_BUILD_EXAMPLES)
    add_executable(croupier_example examples/example.cpp)
    target_link_libraries(croupier_example PRIVATE croupier_sdk)
endif()


include("${VCPKG_ROOT_DIR}/triplets/arm64-osx.cmake")

# Apple Clang injects `/usr/local/include` into the header search path. This can
# cause vcpkg port builds to accidentally pick up Homebrew headers instead of
# the vcpkg-installed ones. Chainload a wrapper toolchain that prefers vcpkg
# headers and enforces C++17.
set(VCPKG_CHAINLOAD_TOOLCHAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/../../cmake/vcpkg-chainload-osx.cmake")


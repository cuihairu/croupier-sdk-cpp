# Croupier SDK vcpkg bootstrap toolchain
#
# Why this exists:
# - CMake Tools (VS Code) needs a toolchain file at first configure time.
# - When developers don't have vcpkg yet, pointing directly to
#   `./vcpkg/scripts/buildsystems/vcpkg.cmake` fails before CMake can do anything.
# - This toolchain auto-clones + bootstraps vcpkg into `./vcpkg` (once), then
#   delegates to the official vcpkg toolchain.

cmake_minimum_required(VERSION 3.20)

get_filename_component(_CROUPIER_REPO_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
set(_CROUPIER_VCPKG_ROOT "${_CROUPIER_REPO_ROOT}/vcpkg")
set(_CROUPIER_VCPKG_TOOLCHAIN "${_CROUPIER_VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
if(WIN32)
  set(_CROUPIER_VCPKG_BOOTSTRAP "${_CROUPIER_VCPKG_ROOT}/bootstrap-vcpkg.bat")
else()
  set(_CROUPIER_VCPKG_BOOTSTRAP "${_CROUPIER_VCPKG_ROOT}/bootstrap-vcpkg.sh")
endif()

if(NOT DEFINED CROUPIER_BOOTSTRAP_VCPKG)
  set(CROUPIER_BOOTSTRAP_VCPKG ON CACHE BOOL "Auto-clone and bootstrap vcpkg into ./vcpkg when missing" )
endif()

if(NOT EXISTS "${_CROUPIER_VCPKG_TOOLCHAIN}")
  if(NOT CROUPIER_BOOTSTRAP_VCPKG)
    message(FATAL_ERROR
      "vcpkg toolchain not found at: ${_CROUPIER_VCPKG_TOOLCHAIN}\n"
      "Either clone vcpkg into ${_CROUPIER_VCPKG_ROOT} or set CROUPIER_BOOTSTRAP_VCPKG=ON.")
  endif()

  message(STATUS "vcpkg not found, bootstrapping into: ${_CROUPIER_VCPKG_ROOT}")

  # If we have a half-cloned directory (e.g. interrupted clone), wipe it and retry.
  if(EXISTS "${_CROUPIER_VCPKG_ROOT}/.git" AND NOT EXISTS "${_CROUPIER_VCPKG_BOOTSTRAP}")
    message(WARNING "Detected incomplete vcpkg checkout at ${_CROUPIER_VCPKG_ROOT}; re-cloning.")
    file(REMOVE_RECURSE "${_CROUPIER_VCPKG_ROOT}")
  endif()

  if(NOT EXISTS "${_CROUPIER_VCPKG_ROOT}/.git")
    execute_process(
      COMMAND git clone https://github.com/microsoft/vcpkg "${_CROUPIER_VCPKG_ROOT}"
      WORKING_DIRECTORY "${_CROUPIER_REPO_ROOT}"
      RESULT_VARIABLE _git_rc
    )
    if(NOT _git_rc EQUAL 0)
      message(FATAL_ERROR "Failed to clone vcpkg (git exit code: ${_git_rc})")
    endif()
  endif()

  if(NOT EXISTS "${_CROUPIER_VCPKG_BOOTSTRAP}")
    message(FATAL_ERROR "vcpkg clone completed but bootstrap script is missing: ${_CROUPIER_VCPKG_BOOTSTRAP}")
  endif()

  if(WIN32)
    execute_process(
      COMMAND cmd /c bootstrap-vcpkg.bat -disableMetrics
      WORKING_DIRECTORY "${_CROUPIER_VCPKG_ROOT}"
      RESULT_VARIABLE _bootstrap_rc
    )
  else()
    execute_process(
      COMMAND sh ./bootstrap-vcpkg.sh -disableMetrics
      WORKING_DIRECTORY "${_CROUPIER_VCPKG_ROOT}"
      RESULT_VARIABLE _bootstrap_rc
    )
  endif()

  if(NOT _bootstrap_rc EQUAL 0)
    message(FATAL_ERROR "Failed to bootstrap vcpkg (exit code: ${_bootstrap_rc})")
  endif()
endif()

# Help downstream tooling/ports.
set(ENV{VCPKG_ROOT} "${_CROUPIER_VCPKG_ROOT}")

include("${_CROUPIER_VCPKG_TOOLCHAIN}")

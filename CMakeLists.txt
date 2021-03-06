cmake_minimum_required(VERSION 3.17)
project(weder LANGUAGES CXX)
set(VERSION_NUMBER 0.2.0-dev)

# Require C++20 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate version.h that contains project information
configure_file(${CMAKE_SOURCE_DIR}/cmake/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/version.h)

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(
        REQUIRES
        doctest/2.4.6
        fmt/8.0.1
        cpp-httplib/0.9.0
        nlohmann_json/3.9.1
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
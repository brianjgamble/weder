cmake_minimum_required(VERSION 3.17)
project(weder VERSION 0.0.1 LANGUAGES CXX)

# Require C++20 and disable extensions for all targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate version.h that contains project information
configure_file(${CMAKE_SOURCE_DIR}/cmake/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/version.h)

# Download automatically, you can also just copy the conan.cmake file
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(
        REQUIRES
        doctest/[>=2.4.0]
        fmt/7.1.2
        cpp-httplib/0.7.12
        nlohmann_json/3.9.1
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
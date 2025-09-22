cmake_minimum_required(VERSION 3.21)

# Define the Bit Utilities library
project(bitutil
        VERSION 1.0.4.0
        DESCRIPTION "Bit-Oriented Utilities Library"
        LANGUAGES CXX)

# Tests are built by default when this is a top-level project
if(PROJECT_IS_TOP_LEVEL)
    # Option to control whether tests are built
    option(bitutil_BUILD_TESTS "Build Tests for the Bit Utilities Library" ON)
else()
    # Option to control whether tests are built
    option(bitutil_BUILD_TESTS "Build Tests for the Bit Utilities Library" OFF)
endif()

# Option to control ability to install the library
option(bitutil_INSTALL "Install the Bit-Oriented Utilities Library" ON)

# Determine whether clang-tidy will be performed
option(bitutil_CLANG_TIDY "Use clang-tidy to perform linting during build" OFF)

# Ensure testing is enabled to surface tests in dependencies
include(CTest)

add_subdirectory(dependencies)
add_subdirectory(src)

if(BUILD_TESTING AND bitutil_BUILD_TESTS)
    add_subdirectory(test)
endif()

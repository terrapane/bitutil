# Include standard installation directory variables
include(GNUInstallDirs)

# Create the library
add_library(bitutil STATIC byte_order.cpp)
add_library(Terra::bitutil ALIAS bitutil)

# Specify the internal and public include directories
target_include_directories(bitutil
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Specify the C++ standard to observe
set_target_properties(bitutil
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF)

# If requesting clang-tidy, try to look for it
if(bitutil_CLANG_TIDY)
    find_program(CLANG_TIDY_COMMAND NAMES "clang-tidy")
    if(CLANG_TIDY_COMMAND)
        set_target_properties(bitutil PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
    else()
        message(WARNING "Could not find clang-tidy")
    endif()
endif()

# Use the following compile options
target_compile_options(bitutil
    PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wpedantic -Wextra -Wall -Werror>
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /Zc:__cplusplus>)

# Install target and associated include files
if(bitutil_INSTALL)
    install(TARGETS bitutil EXPORT bitutilTargets ARCHIVE)
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ TYPE INCLUDE)
    install(EXPORT bitutilTargets
            FILE bitutilConfig.cmake
            NAMESPACE Terra::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/bitutil)
endif()

add_executable(test_significant_bit test_significant_bit.cpp)

target_link_libraries(test_significant_bit Terra::bitutil Terra::stf)

# Specify the C++ standard to observe
set_target_properties(test_significant_bit
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF)

target_compile_options(test_significant_bit PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>: -Wpedantic -Wextra -Wall>
    $<$<CXX_COMPILER_ID:MSVC>: /Zc:__cplusplus>)

add_test(NAME test_significant_bit
         COMMAND test_significant_bit)

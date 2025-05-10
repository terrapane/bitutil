add_executable(test_bit_shift test_bit_shift.cpp)

target_link_libraries(test_bit_shift Terra::bitutil Terra::stf)

# Specify the C++ standard to observe
set_target_properties(test_bit_shift
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF)

target_compile_options(test_bit_shift
    PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wpedantic -Wextra -Wall>
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /Zc:__cplusplus>)

add_test(NAME test_bit_shift
         COMMAND test_bit_shift)

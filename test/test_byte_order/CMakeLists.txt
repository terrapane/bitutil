add_executable(test_byte_order test_byte_order.cpp)

target_link_libraries(test_byte_order Terra::bitutil Terra::stf)

# Specify the C++ standard to observe
set_target_properties(test_byte_order
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF)

target_compile_options(test_byte_order
    PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wpedantic -Wextra -Wall>
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /Zc:__cplusplus>)

add_test(NAME test_byte_order
         COMMAND test_byte_order)

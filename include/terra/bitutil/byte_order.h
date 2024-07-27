/*
 *  byte_order.h
 *
 *  Copyright (C) 2024
 *  Terrapane Corporation
 *  All Rights Reserved
 *
 *  Author:
 *      Paul E. Jones <paulej@packetizer.com>
 *
 *  Description:
 *      This header contains function declarations for routines to indicate
 *      the byte order (endianness) of the underlying hardware and to convert
 *      values between network and host byte order.
 *
 *      A big endian machine has the same byte ordering as network byte order.
 *      Therefore, the functions to perform byte ordering have no effect when
 *      called on a Big Endian platform.
 *
 *  Portability Issues:
 *      C++20 is recommended to utilize most of the functions in this file.
 *      However, functions are declared with `static line` if using older
 *      versions of C++.  The following `#if` checks are performed:
 *          __cplusplus >= 202002L => Looks for C++20
 *          __cpp_lib_endian >= 201907L => Support for std::endian
 */

#pragma once

#include <cstdint>

// This header is only available with C++20 (MSVC does not set __cplusplus
// correctly unless compiling with compiler flag `/Zc:__cplusplus`, so
// also check for the `__cpp_lib_endian` feature)
#if (__cplusplus >= 202002L) || (__cpp_lib_endian >= 201907L)
#include <bit>
#endif

namespace Terra::BitUtil
{

// Enumeration representing some known machine endian forms
enum class EndianClassification : std::uint32_t
{
    Big_Endian          = 0x00010203,
    PDP_Endian          = 0x01000302,
    Honeywell_Endian    = 0x02030001,
    Little_Endian       = 0x03020100
};

/*
 *  GetMachineEndian()
 *
 *  Description:
 *      This function will return value representing the machine byte order.
 *
 *  Parameters:
 *      None.
 *
 *  Returns:
 *      A value representing the machine's byte order.  If this is an unknown
 *      machine architecture, the result may be something other than one of
 *      the currently defined enumeration values.
 *
 *  Comments:
 *      None.
 */
EndianClassification GetMachineEndian();

/*
 *  IsLittleEndian()
 *
 *  Description:
 *      This function will return true if the host machine is little endian.
 *
 *  Parameters:
 *      None.
 *
 *  Returns:
 *      True for little endian, false if not.
 *
 *  Comments:
 *      This is constexpr function under C++20, but not C++17 or earlier.
 */
#if __cpp_lib_endian >= 201907L
constexpr bool IsLittleEndian()
{
    return std::endian::native == std::endian::little;
}
#else
static inline bool IsLittleEndian()
{
    return GetMachineEndian() == EndianClassification::Little_Endian;
}
#endif

/*
 *  IsBigEndian()
 *
 *  Description:
 *      This function will return true if the host machine is big endian.
 *
 *  Parameters:
 *      None.
 *
 *  Returns:
 *      True for big endian, false if not.
 *
 *  Comments:
 *      This is constexpr function under C++20, but not C++17 or earlier.
 */
#if __cpp_lib_endian >= 201907L
constexpr bool IsBigEndian()
{
    return std::endian::native == std::endian::big;
}
#else
static inline bool IsBigEndian()
{
    return GetMachineEndian() == EndianClassification::Big_Endian;
}
#endif

/*
 *  IsLittleOrBigEndian()
 *
 *  Description:
 *      This function will return true if the host machine is either little
 *      endian or big endian.
 *
 *  Parameters:
 *      None.
 *
 *  Returns:
 *      True for if the machine architecture is either big or little endian.
 *
 *  Comments:
 *      This is constexpr function under C++20, but not C++17 or earlier.
 *      While this could be reduced to a single return statement, MSVC
 *      generated a warning.
 */
#if __cpp_lib_endian >= 201907L
constexpr bool IsLittleOrBigEndian()
{
    if (std::endian::native == std::endian::little) return true;
    if (std::endian::native == std::endian::big) return true;

    return false;
}
#else
static inline bool IsLittleOrBigEndian()
{
    return (GetMachineEndian() == EndianClassification::Little_Endian) ||
           (GetMachineEndian() == EndianClassification::Big_Endian);
}
#endif

/*
 *  NetworkByteOrder()
 *
 *  Description:
 *      This function will convert a 64-bit value between network byte order
 *      and host byte order.
 *
 *  Parameters:
 *      value [in]
 *          The value to convert between network and host byte order.
 *
 *  Returns:
 *      The converted value.
 *
 *  Comments:
 *      This is constexpr function under C++20, but not C++17 or earlier.
 *      This function assumes the machine is either big or little endian.
 */
#if __cpp_lib_endian >= 201907L
constexpr std::uint64_t NetworkByteOrder(std::uint64_t value)
{
    // Big endian machines just return the value passed in
    static_assert(IsLittleOrBigEndian());
    if constexpr (IsBigEndian()) return value;
#else
static inline std::uint64_t NetworkByteOrder(std::uint64_t value)
{
    // Big endian machines just return the value passed in
    if (IsBigEndian()) return value;
#endif

    // Little endian machines need to reverse the octet order
    return ((value >> 56) & 0x00000000000000ff) |
           ((value >> 40) & 0x000000000000ff00) |
           ((value >> 24) & 0x0000000000ff0000) |
           ((value >>  8) & 0x00000000ff000000) |
           ((value <<  8) & 0x000000ff00000000) |
           ((value << 24) & 0x0000ff0000000000) |
           ((value << 40) & 0x00ff000000000000) |
           ((value << 56) & 0xff00000000000000);
}

/*
 *  NetworkByteOrder()
 *
 *  Description:
 *      This function will convert a 32-bit value between network byte order
 *      and host byte order.
 *
 *  Parameters:
 *      value [in]
 *          The value to convert between network and host byte order.
 *
 *  Returns:
 *      The converted value.
 *
 *  Comments:
 *      This is constexpr function under C++20, but not C++17 or earlier.
 *      This function assumes the machine is either big or little endian.
 */
#if __cpp_lib_endian >= 201907L
constexpr std::uint32_t NetworkByteOrder(std::uint32_t value)
{
    // Big endian machines just return the value passed in
    static_assert(IsLittleOrBigEndian());
    if constexpr (IsBigEndian()) return value;
#else
static inline std::uint32_t NetworkByteOrder(std::uint32_t value)
{
    // Big endian machines just return the value passed in
    if (IsBigEndian()) return value;
#endif

    // Little endian machines need to reverse the octet order
    return ((value >> 24) & 0x000000ff) | ((value >>  8) & 0x0000ff00) |
           ((value <<  8) & 0x00ff0000) | ((value << 24) & 0xff000000);
}

/*
 *  NetworkByteOrder()
 *
 *  Description:
 *      This function will convert a 16-bit value between network byte order
 *      and host byte order.
 *
 *  Parameters:
 *      value [in]
 *          The value to convert between network and host byte order.
 *
 *  Returns:
 *      The converted value.
 *
 *  Comments:
 *      This is constexpr function under C++20, but not C++17 or earlier.
 *      This function assumes the machine is either big or little endian.
 */
#if __cpp_lib_endian >= 201907L
constexpr std::uint16_t NetworkByteOrder(std::uint16_t value)
{
    // Big endian machines just return the value passed in
    static_assert(IsLittleOrBigEndian());
    if constexpr (IsBigEndian()) return value;
#else
static inline std::uint16_t NetworkByteOrder(std::uint16_t value)
{
    // Big endian machines just return the value passed in
    if (IsBigEndian()) return value;
#endif

    // Little endian machines need to reverse the octet order
    return ((value >> 8) & 0x00ff) | ((value << 8) & 0xff00);
}

} // namespace Terra::BitUtil

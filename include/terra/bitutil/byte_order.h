/*
 *  byte_order.h
 *
 *  Copyright (C) 2024, 2026
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
 *      versions of C++.
 */

#pragma once

#include <cstdint>

// MSVC does not set __cplusplus correctly unless compiling with the flag
// /Zc:__cplusplus, so also check _MSVC_LANG
#if (__cplusplus >= 202002L) || (_MSVC_LANG >= 202002L)
#include <version>
#include <bit>
#endif

namespace Terra::BitUtil
{

// Enumeration representing some known machine endian forms
enum class EndianClassification : std::uint32_t
{
    Unknown             = 0x00000000U,
    Big_Endian          = 0x00010203U,
    PDP_Endian          = 0x01000302U,
    Honeywell_Endian    = 0x02030001U,
    Little_Endian       = 0x03020100U
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
consteval bool IsLittleEndian()
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
consteval bool IsBigEndian()
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
consteval bool IsLittleOrBigEndian()
{
    return (std::endian::native == std::endian::little) !=
           (std::endian::native == std::endian::big);
}
#else
static inline bool IsLittleOrBigEndian()
{
    return (GetMachineEndian() == EndianClassification::Little_Endian) !=
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

    // Little endian machines need to reverse the octet order
    return ((value >> 56U) & 0x00000000000000ffULL) |
           ((value >> 40U) & 0x000000000000ff00ULL) |
           ((value >> 24U) & 0x0000000000ff0000ULL) |
           ((value >>  8U) & 0x00000000ff000000ULL) |
           ((value <<  8U) & 0x000000ff00000000ULL) |
           ((value << 24U) & 0x0000ff0000000000ULL) |
           ((value << 40U) & 0x00ff000000000000ULL) |
           ((value << 56U) & 0xff00000000000000ULL);
}
#else
static inline std::uint64_t NetworkByteOrder(std::uint64_t value)
{
    // Big endian machines just return the value passed in
    if (IsBigEndian()) return value;

    // Little endian machines need to reverse the octet order
    return ((value >> 56U) & 0x00000000000000ffULL) |
           ((value >> 40U) & 0x000000000000ff00ULL) |
           ((value >> 24U) & 0x0000000000ff0000ULL) |
           ((value >>  8U) & 0x00000000ff000000ULL) |
           ((value <<  8U) & 0x000000ff00000000ULL) |
           ((value << 24U) & 0x0000ff0000000000ULL) |
           ((value << 40U) & 0x00ff000000000000ULL) |
           ((value << 56U) & 0xff00000000000000ULL);
}
#endif

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

    // Little endian machines need to reverse the octet order
    return ((value >> 24U) & 0x000000ffU) | ((value >>  8U) & 0x0000ff00U) |
           ((value <<  8U) & 0x00ff0000U) | ((value << 24U) & 0xff000000U);
}
#else
static inline std::uint32_t NetworkByteOrder(std::uint32_t value)
{
    // Big endian machines just return the value passed in
    if (IsBigEndian()) return value;

    // Little endian machines need to reverse the octet order
    return ((value >> 24U) & 0x000000ffU) | ((value >>  8U) & 0x0000ff00U) |
           ((value <<  8U) & 0x00ff0000U) | ((value << 24U) & 0xff000000U);
}
#endif


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

    // Little endian machines need to reverse the octet order
    return ((static_cast<unsigned>(value) >> 8U) & 0x00ffU) |
           ((static_cast<unsigned>(value) << 8U) & 0xff00U);
}
#else
static inline std::uint16_t NetworkByteOrder(std::uint16_t value)
{
    // Big endian machines just return the value passed in
    if (IsBigEndian()) return value;

    // Little endian machines need to reverse the octet order
    return ((value >> 8U) & 0x00ffU) | ((value << 8U) & 0xff00U);
}
#endif

} // namespace Terra::BitUtil

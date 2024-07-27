/*
 *  bit_shift.h
 *
 *  Copyright (C) 2024
 *  Terrapane Corporation
 *  All Rights Reserved
 *
 *  Author:
 *      Paul E. Jones <paulej@packetizer.com>
 *
 *  Description:
 *      This header file contains constexpr functions to perform bit shifts.
 *      These are commonly used in security-related algorithms, like SHA-2 and
 *      AES.
 *
 *  Portability Issues:
 *      None.
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <limits>

namespace Terra::BitUtil
{

/*
 *  ShiftLeft()
 *
 *  Description:
 *      This function will shift the bits of the given integer to the left
 *      the specified number of bits.
 *
 *  Parameters:
 *      value [in]
 *          The original integer value before bit shifting is performed.
 *
 *      bits [in]
 *          The number of bits to shift left.  Note that no error checking is
 *          performed, so specifying a number of bits greater than the number
 *          of bits in the given type for "value" will produce a zero result.
 *
 *      mask [in]
 *          The bit mask to apply to the result.  This is necessary since types
 *          like std::uint_fast32_t may actually be larger than 32-bits.
 *          For fixed-width integer types, this will default to the correct
 *          mask.
 *
 *  Returns:
 *      The value after the bit shift is performed.
 *
 *  Comments:
 *      None.
 */
template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
constexpr T ShiftLeft(const T value,
                      const std::size_t bits,
                      const T mask = std::numeric_limits<T>::max())
{
    return (value << bits) & mask;
}

/*
 *  ShiftRight()
 *
 *  Description:
 *      This function will shift the bits of the given integer to the right
 *      the specified number of bits.
 *
 *  Parameters:
 *      value [in]
 *          The original integer value before bit shifting is performed.
 *
 *      bits [in]
 *          The number of bits to shift right.  Note that no error checking is
 *          performed, so specifying a number of bits greater than the number
 *          of bits in the given type for "value" will produce a zero result.
 *
 *      mask [in]
 *          The bit mask to apply to the result.  This is necessary since types
 *          like std::uint_fast32_t may actually be larger than 32-bits.
 *          For fixed-width integer types, this will default to the correct
 *          mask.
 *
 *  Returns:
 *      The value after the bit shift is performed.
 *
 *  Comments:
 *      None.
 */
template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
constexpr T ShiftRight(const T value,
                       const std::size_t bits,
                       const T mask = std::numeric_limits<T>::max())
{
    return ((value & mask) >> bits);
}

} // namespace Terra::BitUtil

/*
 *  bit_rotation.h
 *
 *  Copyright (C) 2024
 *  Terrapane Corporation
 *  All Rights Reserved
 *
 *  Author:
 *      Paul E. Jones <paulej@packetizer.com>
 *
 *  Description:
 *      This header file contains constexpr functions to perform bit
 *      rotation.  These are commonly used in security-related
 *      algorithms, like SHA-2 and AES.
 *
 *  Portability Issues:
 *      None.
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <climits>
#include <limits>

namespace Terra::BitUtil
{

/*
 *  RotateLeft()
 *
 *  Description:
 *      This function will rotate the bits of the given integer to the left
 *      the specified number of bits.
 *
 *  Parameters:
 *      value [in]
 *          The original integer value before bit rotation is performed.
 *
 *      bits [in]
 *          The number of bits to rotate left.  Note that no error checking is
 *          performed, so specifying a number of bits greater than the number
 *          of bits in the given type for "value" will produce an undefined
 *          result.
 *
 *      width [in]
 *          The width of the value in bits.  This is necessary since types
 *          like std::uint_fast32_t may be larger than 32-bits. For fixed-width
 *          integer types, this will default to the correct width.
 *
 *      mask [in]
 *          The bit mask to apply to the result.  This is necessary since types
 *          like std::uint_fast32_t may actually be larger than 32-bits.
 *          For fixed-width integer types, this will default to the correct
 *          mask.
 *
 *  Returns:
 *      The value after the bit rotation is performed.
 *
 *  Comments:
 *      None.
 */
template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
constexpr T RotateLeft(const T value,
                       const std::size_t bits,
                       const std::size_t width = sizeof(T) * CHAR_BIT,
                       const T mask = std::numeric_limits<T>::max())
{
    return ((value << bits) | ((value & mask) >> (width - bits))) & mask;
}

/*
 *  RotateRight()
 *
 *  Description:
 *      This function will rotate the bits of the given integer to the right
 *      the specified number of bits.
 *
 *  Parameters:
 *      value [in]
 *          The original integer value before bit rotation is performed.
 *
 *      bits [in]
 *          The number of bits to rotate right.  Note that no error checking is
 *          performed, so specifying a number of bits greater than the number
 *          of bits in the given type for "value" will produce an undefined
 *          result.
 *
 *      width [in]
 *          The width of the value in bits.  This is necessary since types
 *          like std::uint_fast32_t may be larger than 32-bits. For fixed-width
 *          integer types, this will default to the correct width.
 *
 *      mask [in]
 *          The bit mask to apply to the result.  This is necessary since types
 *          like std::uint_fast32_t may actually be larger than 32-bits.
 *          For fixed-width integer types, this will default to the correct
 *          mask.
 *
 *  Returns:
 *      The value after the bit rotation is performed.
 *
 *  Comments:
 *      None.
 */
template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
constexpr T RotateRight(const T value,
                        const std::size_t bits,
                        const std::size_t width = sizeof(T) * CHAR_BIT,
                        const T mask = std::numeric_limits<T>::max())
{
    return (((value & mask) >> bits) | (value << (width - bits))) & mask;
}

} // namespace Terra::BitUtil

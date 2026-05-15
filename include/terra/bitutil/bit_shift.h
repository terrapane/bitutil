/*
 *  bit_shift.h
 *
 *  Copyright (C) 2024, 2026
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
#include <limits>
#include <type_traits>
#include <concepts>

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
template<typename T>
    requires std::integral<T>
constexpr T ShiftLeft(const T value,
                      const std::size_t bits,
                      const T mask = std::numeric_limits<T>::max())
{
    // Define a type for readability
    using U = std::make_unsigned_t<T>;

    // Shift the bits left
    const U shifted_result =  static_cast<U>(value) << bits;

    // Apply the mask and return the result
    return static_cast<T>(shifted_result & static_cast<U>(mask));
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
template<typename T>
    requires std::integral<T>
constexpr T ShiftRight(const T value,
                       const std::size_t bits,
                       const T mask = std::numeric_limits<T>::max())
{
    // Define a type for readability
    using U = std::make_unsigned_t<T>;

    // Mask the value
    const U masked_value = static_cast<U>(value) & static_cast<U>(mask);

    // Shift the bits and return the result
    return static_cast<T>(masked_value >> bits);
}

} // namespace Terra::BitUtil

/*
 *  significant_bit.h
 *
 *  Copyright (C) 2024, 2026
 *  Terrapane Corporation
 *  All Rights Reserved
 *
 *  Author:
 *      Paul E. Jones <paulej@packetizer.com>
 *
 *  Description:
 *      This file defines functions that will determine the most significant
 *      bit position in a given signed or unsigned integer.
 *
 *  Portability Issues:
 *      None.
 */

#pragma once

#include <cstdint>
#include <cstddef>

namespace Terra::BitUtil
{

/*
 *  FindMSb()
 *
 *  Description:
 *      This function will find the most significant bit in the given integer,
 *      with a value in the range of 0 to n, where n is the number of bits
 *      in the integer.  If the value of the integer is 0, the MSb value
 *      returned is 0.  It is the caller's responsibility to check that the
 *      integer has a non-zero value.
 *
 *  Parameters:
 *      v [in]
 *          The value for which the most significant bit position is sought.
 *
 *  Returns:
 *      The bit position having the most significant bit set to 1, with the
 *      range being 0 to n, where n is the number of bits in the integer.
 *      If the integer has a 0 value, this function will return 0.
 *
 *  Comments:
 *      None.
 */
constexpr std::size_t FindMSb(std::uint8_t v)
{
    // Assume position 0
    std::size_t p = 0;

    // Find the most significant bit position
    if (v >= static_cast<std::uint8_t>(1) << 4U) p += 4, v >>= 4U;
    if (v >= static_cast<std::uint8_t>(1) << 2U) p += 2, v >>= 2U;
    if (v >= static_cast<std::uint8_t>(1) << 1U) p += 1;

    return p;
}

/*
 *  FindMSb()
 *
 *  Description:
 *      This function will find the most significant bit in the given integer.
 *      This function operates on signed integers and behaves differently
 *      than the parallel function that operates on unsigned integers.  If
 *      the integer value is non-negative, it will locate the bit postion having
 *      the most significant bit value 1.  If the integer is negative, however,
 *      it will seek the bit position having the most significant bit position
 *      set to 0.  To understand why, consider that -1 is all 1s and -2 is all
 *      1s, except for bit position 0, which would contain a 0.  The value -3
 *      would be all 1s, except for bit position 1 having a 0.  This function is
 *      not seeking the "biggest value", but the "most significant" bit, and for
 *      negative numbers that is indicated by a 0 value bit.
 *
 *  Parameters:
 *      v [in]
 *          The value for which the most significant bit position is sought.
 *
 *  Returns:
 *      The bit position having the most significant bit set to 0 or 1,
 *      depending on whether the integer is negative or non-negative.  A
 *      value of -1, 0, or 1 will all return 0.
 *
 *  Comments:
 *      None.
 */
constexpr std::size_t FindMSb(std::int8_t v)
{
    if (v >= 0) return FindMSb(static_cast<std::uint8_t>(v));

    return FindMSb(static_cast<std::uint8_t>(~static_cast<std::uint8_t>(v)));
}

/*
 *  FindMSb()
 *
 *  Description:
 *      This function will find the most significant bit in the given integer,
 *      with a value in the range of 0 to n, where n is the number of bits
 *      in the integer.  If the value of the integer is 0, the MSb value
 *      returned is 0.  It is the caller's responsibility to check that the
 *      integer has a non-zero value.
 *
 *  Parameters:
 *      v [in]
 *          The value for which the most significant bit position is sought.
 *
 *  Returns:
 *      The bit position having the most significant bit set to 1, with the
 *      range being 0 to n, where n is the number of bits in the integer.
 *      If the integer has a 0 value, this function will return 0.
 *
 *  Comments:
 *      None.
 */
constexpr std::size_t FindMSb(std::uint16_t v)
{
    // Assume position 0
    std::size_t p = 0;

    // Find the most significant bit position
    if (v >= static_cast<std::uint16_t>(1) << 8U) p += 8U, v >>= 8U;
    if (v >= static_cast<std::uint16_t>(1) << 4U) p += 4U, v >>= 4U;
    if (v >= static_cast<std::uint16_t>(1) << 2U) p += 2U, v >>= 2U;
    if (v >= static_cast<std::uint16_t>(1) << 1U) p += 1U;

    return p;
}

/*
 *  FindMSb()
 *
 *  Description:
 *      This function will find the most significant bit in the given integer.
 *      This function operates on signed integers and behaves differently
 *      than the parallel function that operates on unsigned integers.  If
 *      the integer value is non-negative, it will locate the bit postion having
 *      the most significant bit value 1.  If the integer is negative, however,
 *      it will seek the bit position having the most significant bit position
 *      set to 0.  To understand why, consider that -1 is all 1s and -2 is all
 *      1s, except for bit position 0, which would contain a 0.  The value -3
 *      would be all 1s, except for bit position 1 having a 0.  This function is
 *      not seeking the "biggest value", but the "most significant" bit, and for
 *      negative numbers that is indicated by a 0 value bit.
 *
 *  Parameters:
 *      v [in]
 *          The value for which the most significant bit position is sought.
 *
 *  Returns:
 *      The bit position having the most significant bit set to 0 or 1,
 *      depending on whether the integer is negative or non-negative.  A
 *      value of -1, 0, or 1 will all return 0.
 *
 *  Comments:
 *      None.
 */
constexpr std::size_t FindMSb(std::int16_t v)
{
    if (v >= 0) return FindMSb(static_cast<std::uint16_t>(v));

    return FindMSb(static_cast<std::uint16_t>(~static_cast<std::uint16_t>(v)));
}

/*
 *  FindMSb()
 *
 *  Description:
 *      This function will find the most significant bit in the given integer,
 *      with a value in the range of 0 to n, where n is the number of bits
 *      in the integer.  If the value of the integer is 0, the MSb value
 *      returned is 0.  It is the caller's responsibility to check that the
 *      integer has a non-zero value.
 *
 *  Parameters:
 *      v [in]
 *          The value for which the most significant bit position is sought.
 *
 *  Returns:
 *      The bit position having the most significant bit set to 1, with the
 *      range being 0 to n, where n is the number of bits in the integer.
 *      If the integer has a 0 value, this function will return 0.
 *
 *  Comments:
 *      None.
 */
constexpr std::size_t FindMSb(std::uint32_t v)
{
    // Assume position 0
    std::size_t p = 0;

    // Find the most significant bit position
    if (v >= static_cast<std::uint32_t>(1) << 16U) p += 16U, v >>= 16U;
    if (v >= static_cast<std::uint32_t>(1) <<  8U) p +=  8U, v >>=  8U;
    if (v >= static_cast<std::uint32_t>(1) <<  4U) p +=  4U, v >>=  4U;
    if (v >= static_cast<std::uint32_t>(1) <<  2U) p +=  2U, v >>=  2U;
    if (v >= static_cast<std::uint32_t>(1) <<  1U) p +=  1U;

    return p;
}

/*
 *  FindMSb()
 *
 *  Description:
 *      This function will find the most significant bit in the given integer.
 *      This function operates on signed integers and behaves differently
 *      than the parallel function that operates on unsigned integers.  If
 *      the integer value is non-negative, it will locate the bit postion having
 *      the most significant bit value 1.  If the integer is negative, however,
 *      it will seek the bit position having the most significant bit position
 *      set to 0.  To understand why, consider that -1 is all 1s and -2 is all
 *      1s, except for bit position 0, which would contain a 0.  The value -3
 *      would be all 1s, except for bit position 1 having a 0.  This function is
 *      not seeking the "biggest value", but the "most significant" bit, and for
 *      negative numbers that is indicated by a 0 value bit.
 *
 *  Parameters:
 *      v [in]
 *          The value for which the most significant bit position is sought.
 *
 *  Returns:
 *      The bit position having the most significant bit set to 0 or 1,
 *      depending on whether the integer is negative or non-negative.  A
 *      value of -1, 0, or 1 will all return 0.
 *
 *  Comments:
 *      None.
 */
constexpr std::size_t FindMSb(std::int32_t v)
{
    if (v >= 0) return FindMSb(static_cast<std::uint32_t>(v));

    return FindMSb(static_cast<std::uint32_t>(~static_cast<std::uint32_t>(v)));
}

/*
 *  FindMSb()
 *
 *  Description:
 *      This function will find the most significant bit in the given integer,
 *      with a value in the range of 0 to n, where n is the number of bits
 *      in the integer.  If the value of the integer is 0, the MSb value
 *      returned is 0.  It is the caller's responsibility to check that the
 *      integer has a non-zero value.
 *
 *  Parameters:
 *      v [in]
 *          The value for which the most significant bit position is sought.
 *
 *  Returns:
 *      The bit position having the most significant bit set to 1, with the
 *      range being 0 to n, where n is the number of bits in the integer.
 *      If the integer has a 0 value, this function will return 0.
 *
 *  Comments:
 *      None.
 */
constexpr std::size_t FindMSb(std::uint64_t v)
{
    // Assume position 0
    std::size_t p = 0;

    // Find the most significant bit position
    if (v >= static_cast<std::uint64_t>(1) << 32U) p += 32U, v >>= 32U;
    if (v >= static_cast<std::uint64_t>(1) << 16U) p += 16U, v >>= 16U;
    if (v >= static_cast<std::uint64_t>(1) <<  8U) p +=  8U, v >>=  8U;
    if (v >= static_cast<std::uint64_t>(1) <<  4U) p +=  4U, v >>=  4U;
    if (v >= static_cast<std::uint64_t>(1) <<  2U) p +=  2U, v >>=  2U;
    if (v >= static_cast<std::uint64_t>(1) <<  1U) p +=  1U, v >>=  1U;

    return p;
}

/*
 *  FindMSb()
 *
 *  Description:
 *      This function will find the most significant bit in the given integer.
 *      This function operates on signed integers and behaves differently
 *      than the parallel function that operates on unsigned integers.  If
 *      the integer value is non-negative, it will locate the bit postion having
 *      the most significant bit value 1.  If the integer is negative, however,
 *      it will seek the bit position having the most significant bit position
 *      set to 0.  To understand why, consider that -1 is all 1s and -2 is all
 *      1s, except for bit position 0, which would contain a 0.  The value -3
 *      would be all 1s, except for bit position 1 having a 0.  This function is
 *      not seeking the "biggest value", but the "most significant" bit, and for
 *      negative numbers that is indicated by a 0 value bit.
 *
 *  Parameters:
 *      v [in]
 *          The value for which the most significant bit position is sought.
 *
 *  Returns:
 *      The bit position having the most significant bit set to 0 or 1,
 *      depending on whether the integer is negative or non-negative.  A
 *      value of -1, 0, or 1 will all return 0.
 *
 *  Comments:
 *      None.
 */
constexpr std::size_t FindMSb(std::int64_t v)
{
    if (v >= 0) return FindMSb(static_cast<std::uint64_t>(v));

    return FindMSb(static_cast<std::uint64_t>(~static_cast<std::uint64_t>(v)));
}

} // namespace Terra::BitUtil

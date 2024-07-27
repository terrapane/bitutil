/*
 *  test_bit_shift.cpp
 *
 *  Copyright (C) 2024
 *  Terrapane Corporation
 *  All Rights Reserved
 *
 *  Author:
 *      Paul E. Jones <paulej@packetizer.com>
 *
 *  Description:
 *      This module contains tests for bit shift functions.
 *
 *  Portability Issues:
 *      None.
 */

#include <terra/stf/stf.h>
#include <terra/bitutil/bit_shift.h>

using namespace Terra;

STF_TEST(BitShift, TestShiftLeft1)
{
    std::uint32_t expected = 2;
    std::uint32_t value = 1;
    std::uint32_t result;

    result = BitUtil::ShiftLeft(value, 1);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftLeft2)
{
    std::uint32_t expected = 0xFFFF0000;
    std::uint32_t value = 0x0000FFFF;
    std::uint32_t result;

    result = BitUtil::ShiftLeft(value, 16);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftLeft3)
{
    std::uint32_t expected = 0x000FFFF0;
    std::uint32_t value = 0x0000FFFF;
    std::uint32_t result;

    result = BitUtil::ShiftLeft(value, 4);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftLeft4)
{
    std::size_t expected = 0x000FFFF0;
    std::size_t value = 0x0000FFFF;
    std::size_t result;

    result = BitUtil::ShiftLeft(value, 4);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftLeft5)
{
    std::uint8_t expected = 0b0000'1100;
    std::uint8_t value = 0b0000'0011;
    std::uint8_t result;

    result = BitUtil::ShiftLeft(value, 2);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftLeft6)
{
    std::int32_t expected = 0x000FFFF0;
    std::int32_t value = 0x0000FFFF;
    std::int32_t result;

    result = BitUtil::ShiftLeft(value, 4);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftLeft7)
{
    std::uint64_t expected = 0x00FF'FF00'0000'0000;
    std::uint64_t value = 0x0000'0000'0000'FFFF;
    std::uint64_t result;

    result = BitUtil::ShiftLeft(value, 40);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftLeft8)
{
    std::uint_fast32_t expected = 0x0d0e0f00;
    std::uint_fast32_t value = 0x0c0d0e0f;
    std::uint_fast32_t result;

    // This type may be longer than 32-bits, so we explicitly pass in the
    // width and mask values
    result = BitUtil::ShiftLeft(value, 8, std::uint_fast32_t(0xffffffff));

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftLeft9)
{
    std::uint32_t expected = 0xFFF00000;
    std::uint32_t value = 0xFFFF0000;
    std::uint32_t result;

    result = BitUtil::ShiftLeft(value, 4);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftRight1)
{
    std::uint32_t expected = 1;
    std::uint32_t value = 2;
    std::uint32_t result;

    result = BitUtil::ShiftRight(value, 1);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftRight2)
{
    std::uint32_t expected = 0x0000FFFF;
    std::uint32_t value = 0xFFFF0000;
    std::uint32_t result;

    result = BitUtil::ShiftRight(value, 16);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftRight3)
{
    std::uint32_t expected = 0x0000FFFF;
    std::uint32_t value = 0x000FFFF0;
    std::uint32_t result;

    result = BitUtil::ShiftRight(value, 4);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftRight4)
{
    std::size_t expected = 0x0000FFFF;
    std::size_t value = 0x000FFFF0;
    std::size_t result;

    result = BitUtil::ShiftRight(value, 4);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftRight5)
{
    std::uint8_t expected = 0b0000'0011;
    std::uint8_t value = 0b0000'1101;
    std::uint8_t result;

    result = BitUtil::ShiftRight(value, 2);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftRight6)
{
    std::int32_t expected = 0x0000FFFF;
    std::int32_t value = 0x000FFFF0;
    std::int32_t result;

    result = BitUtil::ShiftRight(value, 4);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftRight7)
{
    std::uint64_t expected = 0x0000'0000'0000'FFFF;
    std::uint64_t value = 0x00FF'FF00'0000'0000;
    std::uint64_t result;

    result = BitUtil::ShiftRight(value, 40);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftRight8)
{
    std::uint_fast32_t expected = 0x000d0e0f;
    std::uint_fast32_t value = 0x0d0e0f0c;
    std::uint_fast32_t result;

    // This type may be longer than 32-bits, so we explicitly pass in the
    // width and mask values
    result = BitUtil::ShiftRight(value, 8, std::uint_fast32_t(0xffffffff));

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitShift, TestShiftRight9)
{
    std::uint32_t expected = 0x00000FFF;
    std::uint32_t value = 0x0000FFFF;
    std::uint32_t result;

    result = BitUtil::ShiftRight(value, 4);

    STF_ASSERT_EQ(expected, result);
}


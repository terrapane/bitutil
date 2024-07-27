/*
 *  test_bit_rotation.cpp
 *
 *  Copyright (C) 2024
 *  Terrapane Corporation
 *  All Rights Reserved
 *
 *  Author:
 *      Paul E. Jones <paulej@packetizer.com>
 *
 *  Description:
 *      This module contains tests for bit rotation functions.
 *
 *  Portability Issues:
 *      None.
 */

#include <terra/stf/stf.h>
#include <terra/bitutil/bit_rotation.h>

using namespace Terra;

STF_TEST(BitRotation, TestRotateLeft1)
{
    std::uint32_t expected = 2;
    std::uint32_t value = 1;
    std::uint32_t result;

    result = BitUtil::RotateLeft(value, 1);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateLeft2)
{
    std::uint32_t expected = 0xFFFF0000;
    std::uint32_t value = 0x0000FFFF;
    std::uint32_t result;

    result = BitUtil::RotateLeft(value, 16);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateLeft3)
{
    std::uint32_t expected = 0x000FFFF0;
    std::uint32_t value = 0x0000FFFF;
    std::uint32_t result;

    result = BitUtil::RotateLeft(value, 4);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateLeft4)
{
    std::size_t expected = 0x000FFFF0;
    std::size_t value = 0x0000FFFF;
    std::size_t result;

    result = BitUtil::RotateLeft(value, 4);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateLeft5)
{
    std::uint8_t expected = 0b0000'1110;
    std::uint8_t value = 0b1000'0011;
    std::uint8_t result;

    result = BitUtil::RotateLeft(value, 2);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateLeft6)
{
    std::int32_t expected = 0x000FFFF0;
    std::int32_t value = 0x0000FFFF;
    std::int32_t result;

    result = BitUtil::RotateLeft(value, 4);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateLeft7)
{
    std::uint64_t expected = 0x00FF'FF00'0000'0000;
    std::uint64_t value = 0x0000'0000'0000'FFFF;
    std::uint64_t result;

    result = BitUtil::RotateLeft(value, 40);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateLeft8)
{
    std::uint_fast32_t expected = 0x0d0e0f0c;
    std::uint_fast32_t value = 0x0c0d0e0f;
    std::uint_fast32_t result;

    // This type may be longer than 32-bits, so we explicitly pass in the
    // width and mask values
    result = BitUtil::RotateLeft(value, 8, 32, std::uint_fast32_t(0xffffffff));

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateLeft9)
{
    std::uint32_t expected = 0xFFF0000F;
    std::uint32_t value = 0xFFFF0000;
    std::uint32_t result;

    result = BitUtil::RotateLeft(value, 4);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateRight1)
{
    std::uint32_t expected = 1;
    std::uint32_t value = 2;
    std::uint32_t result;

    result = BitUtil::RotateRight(value, 1);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateRight2)
{
    std::uint32_t expected = 0x0000FFFF;
    std::uint32_t value = 0xFFFF0000;
    std::uint32_t result;

    result = BitUtil::RotateRight(value, 16);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateRight3)
{
    std::uint32_t expected = 0x0000FFFF;
    std::uint32_t value = 0x000FFFF0;
    std::uint32_t result;

    result = BitUtil::RotateRight(value, 4);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateRight4)
{
    std::size_t expected = 0x0000FFFF;
    std::size_t value = 0x000FFFF0;
    std::size_t result;

    result = BitUtil::RotateRight(value, 4);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateRight5)
{
    std::uint8_t expected = 0b0100'0011;
    std::uint8_t value = 0b0000'1101;
    std::uint8_t result;

    result = BitUtil::RotateRight(value, 2);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateRight6)
{
    std::int32_t expected = 0x0000FFFF;
    std::int32_t value = 0x000FFFF0;
    std::int32_t result;

    result = BitUtil::RotateRight(value, 4);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateRight7)
{
    std::uint64_t expected = 0x0000'0000'0000'FFFF;
    std::uint64_t value = 0x00FF'FF00'0000'0000;
    std::uint64_t result;

    result = BitUtil::RotateRight(value, 40);

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateRight8)
{
    std::uint_fast32_t expected = 0x0c0d0e0f;
    std::uint_fast32_t value = 0x0d0e0f0c;
    std::uint_fast32_t result;

    // This type may be longer than 32-bits, so we explicitly pass in the
    // width and mask values
    result = BitUtil::RotateRight(value, 8, 32, std::uint_fast32_t(0xffffffff));

    STF_ASSERT_EQ(expected, result);
}

STF_TEST(BitRotation, TestRotateRight9)
{
    std::uint32_t expected = 0xF0000FFF;
    std::uint32_t value = 0x0000FFFF;
    std::uint32_t result;

    result = BitUtil::RotateRight(value, 4);

    STF_ASSERT_EQ(expected, result);
}


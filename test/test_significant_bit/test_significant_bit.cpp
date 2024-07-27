/*
 *  test_significant_bit.cpp
 *
 *  Copyright (C) 2024
 *  Terrapane Corporation
 *  All Rights Reserved
 *
 *  Author:
 *      Paul E. Jones <paulej@packetizer.com>
 *
 *  Description:
 *      This module contains tests for significant bit functions.
 *
 *  Portability Issues:
 *      None.
 */

#include <terra/stf/stf.h>
#include <terra/bitutil/significant_bit.h>

using namespace Terra;

STF_TEST(SignificantBit, TestSignificantBitUint8)
{
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::uint8_t(0)));
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::uint8_t(1)));
    STF_ASSERT_EQ(1, BitUtil::FindMSb(std::uint8_t(2)));
    STF_ASSERT_EQ(4, BitUtil::FindMSb(std::uint8_t(16)));
    STF_ASSERT_EQ(6, BitUtil::FindMSb(std::uint8_t(64)));
}

STF_TEST(SignificantBit, TestSignificantBitInt8)
{
    // Non-negative integers
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::int8_t(0)));
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::int8_t(1)));
    STF_ASSERT_EQ(1, BitUtil::FindMSb(std::int8_t(2)));
    STF_ASSERT_EQ(4, BitUtil::FindMSb(std::int8_t(16)));
    STF_ASSERT_EQ(6, BitUtil::FindMSb(std::int8_t(64)));

    // Negative integers
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::int8_t(-1)));
    STF_ASSERT_EQ(6, BitUtil::FindMSb(std::int8_t(-65)));
}

STF_TEST(SignificantBit, TestSignificantBitUint16)
{
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::uint16_t(0)));
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::uint16_t(1)));
    STF_ASSERT_EQ(1, BitUtil::FindMSb(std::uint16_t(2)));
    STF_ASSERT_EQ(4, BitUtil::FindMSb(std::uint16_t(16)));
    STF_ASSERT_EQ(13, BitUtil::FindMSb(std::uint16_t(0x2000)));
}

STF_TEST(SignificantBit, TestSignificantBitInt16)
{
    // Non-negative integers
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::int16_t(0)));
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::int16_t(1)));
    STF_ASSERT_EQ(1, BitUtil::FindMSb(std::int16_t(2)));
    STF_ASSERT_EQ(4, BitUtil::FindMSb(std::int16_t(16)));
    STF_ASSERT_EQ(6, BitUtil::FindMSb(std::int16_t(0x40)));
    STF_ASSERT_EQ(7, BitUtil::FindMSb(std::int16_t(0x80)));
    STF_ASSERT_EQ(13, BitUtil::FindMSb(std::int16_t(0x2000)));

    // Negative integers
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::int16_t(-1)));
    STF_ASSERT_EQ(7, BitUtil::FindMSb(std::int16_t(-129)));
    STF_ASSERT_EQ(14, BitUtil::FindMSb(std::int16_t(-16385)));
}

STF_TEST(SignificantBit, TestSignificantBitUint32)
{
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::uint32_t(0)));
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::uint32_t(1)));
    STF_ASSERT_EQ(1, BitUtil::FindMSb(std::uint32_t(2)));
    STF_ASSERT_EQ(4, BitUtil::FindMSb(std::uint32_t(16)));
    STF_ASSERT_EQ(13, BitUtil::FindMSb(std::uint32_t(0x2000)));
    STF_ASSERT_EQ(31, BitUtil::FindMSb(std::uint32_t(0x80000000L)));
}

STF_TEST(SignificantBit, TestSignificantBitInt32)
{
    // Non-negative integers
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::int32_t(0)));
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::int32_t(1)));
    STF_ASSERT_EQ(1, BitUtil::FindMSb(std::int32_t(2)));
    STF_ASSERT_EQ(4, BitUtil::FindMSb(std::int32_t(16)));
    STF_ASSERT_EQ(6, BitUtil::FindMSb(std::int32_t(0x40)));
    STF_ASSERT_EQ(7, BitUtil::FindMSb(std::int32_t(0x80)));
    STF_ASSERT_EQ(13, BitUtil::FindMSb(std::int32_t(0x2000)));
    STF_ASSERT_EQ(14, BitUtil::FindMSb(std::int32_t(0x4000)));
    STF_ASSERT_EQ(30, BitUtil::FindMSb(std::int32_t(0x40000000L)));

    // Negative integers
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::int32_t(-1)));
    STF_ASSERT_EQ(7, BitUtil::FindMSb(std::int32_t(-129)));
    STF_ASSERT_EQ(14, BitUtil::FindMSb(std::int32_t(-16385)));
    STF_ASSERT_EQ(30, BitUtil::FindMSb(std::int32_t(-1073741825L)));
}

STF_TEST(SignificantBit, TestSignificantBitUint64)
{
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::uint64_t(0)));
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::uint64_t(1)));
    STF_ASSERT_EQ(1, BitUtil::FindMSb(std::uint64_t(2)));
    STF_ASSERT_EQ(4, BitUtil::FindMSb(std::uint64_t(16)));
    STF_ASSERT_EQ(13, BitUtil::FindMSb(std::uint64_t(0x2000)));
    STF_ASSERT_EQ(31, BitUtil::FindMSb(std::uint64_t(0x80000000LL)));
    STF_ASSERT_EQ(42, BitUtil::FindMSb(std::uint64_t(0x40000000000LL)));
    STF_ASSERT_EQ(63, BitUtil::FindMSb(std::uint64_t(0x8000000000000000LL)));
}

STF_TEST(SignificantBit, TestSignificantBitInt64)
{
    // Non-negative integers
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::int64_t(0)));
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::int64_t(1)));
    STF_ASSERT_EQ(1, BitUtil::FindMSb(std::int64_t(2)));
    STF_ASSERT_EQ(4, BitUtil::FindMSb(std::int64_t(16)));
    STF_ASSERT_EQ(6, BitUtil::FindMSb(std::int64_t(0x40)));
    STF_ASSERT_EQ(7, BitUtil::FindMSb(std::int64_t(0x80)));
    STF_ASSERT_EQ(13, BitUtil::FindMSb(std::int64_t(0x2000)));
    STF_ASSERT_EQ(15, BitUtil::FindMSb(std::int64_t(0x8000)));
    STF_ASSERT_EQ(31, BitUtil::FindMSb(std::int64_t(0x80000000LL)));
    STF_ASSERT_EQ(42, BitUtil::FindMSb(std::int64_t(0x40000000000LL)));
    STF_ASSERT_EQ(61, BitUtil::FindMSb(std::int64_t(0x2000000000000000LL)));

    // Negative integers
    STF_ASSERT_EQ(0, BitUtil::FindMSb(std::int64_t(-1)));
    STF_ASSERT_EQ(7, BitUtil::FindMSb(std::int64_t(-129)));
    STF_ASSERT_EQ(15, BitUtil::FindMSb(std::int64_t(-32769)));
    STF_ASSERT_EQ(31, BitUtil::FindMSb(std::int64_t(-2147483649LL)));
    STF_ASSERT_EQ(43, BitUtil::FindMSb(std::int64_t(-8796093022209LL)));
    STF_ASSERT_EQ(62, BitUtil::FindMSb(std::int64_t(0xA000000000000000LL)));
}

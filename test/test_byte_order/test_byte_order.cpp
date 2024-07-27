/*
 *  test_byte_order.cpp
 *
 *  Copyright (C) 2024
 *  Terrapane Corporation
 *  All Rights Reserved
 *
 *  Author:
 *      Paul E. Jones <paulej@packetizer.com>
 *
 *  Description:
 *      This module contains tests for endianness functions.
 *
 *  Portability Issues:
 *      These tests assume the machine architecture is either big endian
 *      or little endian.  Additional tests could be added to check
 *      for other architectures, but there has been no demonstrable need.
 */

#include <cstdint>
#include <terra/stf/stf.h>
#include <terra/bitutil/byte_order.h>

using namespace Terra;

// Ensures this is either a big or little endian architecture, as others are
// not supported
STF_TEST(Endianness, LittleOrBigEndian)
{
    STF_ASSERT_NE(BitUtil::IsLittleEndian(), BitUtil::IsBigEndian());
    STF_ASSERT_TRUE(BitUtil::IsLittleOrBigEndian());
}

STF_TEST(Endianness, GetMachineEndian)
{
    BitUtil::EndianClassification endian = BitUtil::GetMachineEndian();

    // Ensure the value is as expected
    if (BitUtil::IsLittleEndian())
    {
        STF_ASSERT_EQ(endian, BitUtil::EndianClassification::Little_Endian);
    }
    if (BitUtil::IsBigEndian())
    {
        STF_ASSERT_EQ(endian, BitUtil::EndianClassification::Big_Endian);
    }
}

STF_TEST(Endianness, VerifyExpectations)
{
    std::uint32_t value = 0x01020304;
    std::uint8_t *p = reinterpret_cast<std::uint8_t *>(&value);

    if (BitUtil::IsBigEndian())
    {
        STF_ASSERT_EQ(*p++, std::uint8_t(0x01));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x02));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x03));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x04));
    }
    else
    {
        STF_ASSERT_EQ(*p++, std::uint8_t(0x04));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x03));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x02));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x01));
    }
}

STF_TEST(Endianness, NetworkByteOrder_64)
{
    std::uint64_t value = 0x123456789abcdef0;
    std::uint64_t result = BitUtil::NetworkByteOrder(value);
    std::uint8_t *p = reinterpret_cast<std::uint8_t *>(&result);

    // The resulting output should always be the following
    STF_ASSERT_EQ(*p++, std::uint8_t(0x12));
    STF_ASSERT_EQ(*p++, std::uint8_t(0x34));
    STF_ASSERT_EQ(*p++, std::uint8_t(0x56));
    STF_ASSERT_EQ(*p++, std::uint8_t(0x78));
    STF_ASSERT_EQ(*p++, std::uint8_t(0x9a));
    STF_ASSERT_EQ(*p++, std::uint8_t(0xbc));
    STF_ASSERT_EQ(*p++, std::uint8_t(0xde));
    STF_ASSERT_EQ(*p++, std::uint8_t(0xf0));

    // A second call would put them back into host order, but this should
    // only have an actual effect on the order on Little Endian machines
    result = BitUtil::NetworkByteOrder(result);
    p = reinterpret_cast<std::uint8_t *>(&result);
    if (BitUtil::IsLittleEndian())
    {
        STF_ASSERT_EQ(*p++, std::uint8_t(0xf0));
        STF_ASSERT_EQ(*p++, std::uint8_t(0xde));
        STF_ASSERT_EQ(*p++, std::uint8_t(0xbc));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x9a));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x78));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x56));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x34));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x12));
    }
    else
    {
        STF_ASSERT_EQ(*p++, std::uint8_t(0x12));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x34));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x56));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x78));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x9a));
        STF_ASSERT_EQ(*p++, std::uint8_t(0xbc));
        STF_ASSERT_EQ(*p++, std::uint8_t(0xde));
        STF_ASSERT_EQ(*p++, std::uint8_t(0xf0));
    }
}

STF_TEST(Endianness, NetworkByteOrder_32)
{
    std::uint32_t value = 0x12345678;
    std::uint32_t result = BitUtil::NetworkByteOrder(value);
    std::uint8_t *p = reinterpret_cast<std::uint8_t *>(&result);

    // The resulting output should always be the following
    STF_ASSERT_EQ(*p++, std::uint8_t(0x12));
    STF_ASSERT_EQ(*p++, std::uint8_t(0x34));
    STF_ASSERT_EQ(*p++, std::uint8_t(0x56));
    STF_ASSERT_EQ(*p++, std::uint8_t(0x78));

    // A second call would put them back into host order, but this should
    // only have an actual effect on the order on Little Endian machines
    result = BitUtil::NetworkByteOrder(result);
    p = reinterpret_cast<std::uint8_t *>(&result);
    if (BitUtil::IsLittleEndian())
    {
        STF_ASSERT_EQ(*p++, std::uint8_t(0x78));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x56));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x34));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x12));
    }
    else
    {
        STF_ASSERT_EQ(*p++, std::uint8_t(0x12));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x34));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x56));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x78));
    }
}

STF_TEST(Endianness, NetworkByteOrder_16)
{
    std::uint16_t value = 0x1234;
    std::uint16_t result = BitUtil::NetworkByteOrder(value);
    std::uint8_t *p = reinterpret_cast<std::uint8_t *>(&result);

    // The resulting output should always be the following
    STF_ASSERT_EQ(*p++, std::uint8_t(0x12));
    STF_ASSERT_EQ(*p++, std::uint8_t(0x34));

    // A second call would put them back into host order, but this should
    // only have an actual effect on the order on Little Endian machines
    result = BitUtil::NetworkByteOrder(result);
    p = reinterpret_cast<std::uint8_t *>(&result);
    if (BitUtil::IsLittleEndian())
    {
        STF_ASSERT_EQ(*p++, std::uint8_t(0x34));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x12));
    }
    else
    {
        STF_ASSERT_EQ(*p++, std::uint8_t(0x12));
        STF_ASSERT_EQ(*p++, std::uint8_t(0x34));
    }
}

STF_TEST(Endianness, NetworkByteOrder_64_Twice)
{
    std::uint64_t value = 0x123456789abcdef0;

    // Convert to network byte order
    std::uint64_t result = BitUtil::NetworkByteOrder(value);

    // Depending on the machine architecture, result should be...
    if (BitUtil::IsBigEndian())
    {
        STF_ASSERT_EQ(value, result);
    }
    else
    {
        STF_ASSERT_NE(value, result);
    }

    // Convert back to host byte order
    result = BitUtil::NetworkByteOrder(result);

    // Verify original value
    STF_ASSERT_EQ(value, result);
}

STF_TEST(Endianness, NetworkByteOrder_32_Twice)
{
    std::uint32_t value = 0x12345678;

    // Convert to network byte order
    std::uint32_t result = BitUtil::NetworkByteOrder(value);

    // Depending on the machine architecture, result should be...
    if (BitUtil::IsBigEndian())
    {
        STF_ASSERT_EQ(value, result);
    }
    else
    {
        STF_ASSERT_NE(value, result);
    }

    // Convert back to host byte order
    result = BitUtil::NetworkByteOrder(result);

    // Verify original value
    STF_ASSERT_EQ(value, result);
}

STF_TEST(Endianness, NetworkByteOrder_16_Twice)
{
    std::uint16_t value = 0x1234;

    // Convert to network byte order
    std::uint16_t result = BitUtil::NetworkByteOrder(value);

    // Depending on the machine architecture, result should be...
    if (BitUtil::IsBigEndian())
    {
        STF_ASSERT_EQ(value, result);
    }
    else
    {
        STF_ASSERT_NE(value, result);
    }

    // Convert back to host byte order
    result = BitUtil::NetworkByteOrder(result);

    // Verify original value
    STF_ASSERT_EQ(value, result);
}

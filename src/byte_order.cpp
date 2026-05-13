/*
 *  byte_order.cpp
 *
 *  Copyright (C) 2024, 2026
 *  Terrapane Corporation
 *  All Rights Reserved
 *
 *  Author:
 *      Paul E. Jones <paulej@packetizer.com>
 *
 *  Description:
 *      This module contains code to indicate the byte order (endianness) of
 *      the underlying hardware and to convert values between network and
 *      host byte order.
 *
 *  Portability Issues:
 *      None.
 */

#include <climits>
#include <cstdint>
#include <terra/bitutil/byte_order.h>

namespace Terra::BitUtil
{

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
EndianClassification GetMachineEndian()
{
    static_assert(CHAR_BIT == 8, "Unsupported byte size");

    // Populate a union to facilitate detection of byte order
    static const union
    {
        unsigned char octets[4]; // NOLINT(*-avoid-c-arrays)
        std::uint32_t endian;
    } observed_endianness = {{0, 1, 2, 3}};

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-union-access)
    return static_cast<EndianClassification>(observed_endianness.endian);
}

} // namespace Terra::BitUtil

/*
 *  byte_order.cpp
 *
 *  Copyright (C) 2024
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
#include <terra/bitutil/byte_order.h>

namespace Terra::BitUtil
{

namespace
{

// Populate a union to facilitate detection of byte order
const union
{
    unsigned char octets[4];
    std::uint32_t endian;
} Observed_Endianness = {{0, 1, 2, 3}};

/*
 *  DetermineMachineEndian()
 *
 *  Description:
 *      This function will determine the endianness of the machine and return
 *      the value representing the endianness.
 *
 *  Parameters:
 *      None.
 *
 *  Returns:
 *      A value representing the machine's endianness.  If this is an unknown
 *      machine architecture, the result may be something other than one of
 *      the currently defined enumeration values.
 *
 *  Comments:
 *      None.
 */
EndianClassification DetermineMachineEndian() noexcept
{
    static_assert(CHAR_BIT == 8, "Unsupported byte size");

    return static_cast<EndianClassification>(Observed_Endianness.endian);
}

// Initialize the endian flags
const EndianClassification Machine_Endian = DetermineMachineEndian();

} // namespace

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
    return Machine_Endian;
}

} // namespace Terra::BitUtil

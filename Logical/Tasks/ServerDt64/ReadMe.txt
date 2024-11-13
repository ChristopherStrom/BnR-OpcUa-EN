The largest integer data types natively supported on the PLC under IEC are UDINT (Uint32) and DINT (Int32). 
However, larger data types are sometimes needed as counters (e.g., in Companion Specifications).

This example demonstrates the use of 64-bit data types such as Uint64 (ULINT) and Int64 (LINT) under OpcUa.
The required structures and functions for this are implemented in the base library BrbLib as of version V5.02.
Descriptions and notes on this can be found in the library's help documentation. Special attention should be given to the note on consistency!

The task defines a Uint64 (variable nUint64) and an Int64 (variable nInt64).
Both are cyclically changed to demonstrate their handling. In particular, underflows and overflows are shown:

**Uint64:**
- Range: 0..18446744073709551615
- Initial value: 0
- The value is incremented up to 5. Then the count direction is set to negative. 
  When decremented by 1 at 0 (lowest value), an underflow occurs, resulting in the value 18446744073709551615 (highest value).
- It continues counting down to 18446744073709551610, after which the count direction is set back to positive.
  When incremented by 1 at 18446744073709551615 (highest value), an overflow occurs, resetting the value to 0 (lowest value). 
- Counting then starts over.
- The underflow/overflow logic is the same as for an unsigned value with fewer bits (e.g., a UINT).
- To make the 64-bit value human-readable on the PLC, it is cyclically converted to text showing the actual number (variable sUint64).

**Int64:**
- Range: -9223372036854775808..+9223372036854775807
- Initial value: +9223372036854775802
- The value is incremented up to +9223372036854775807 (highest value). Incrementing by 1 again results in an overflow, setting the value to -9223372036854775808 (lowest value).
- Counting continues up to -9223372036854775803, after which the count direction is set to negative.
  When decremented by 1 at -9223372036854775808 (lowest value), an underflow occurs, setting the value to +9223372036854775807 (highest value). 
- Counting continues down to +9223372036854775802, and the count direction is set back to positive. 
  Counting then starts over.
- The underflow/overflow logic is the same as for a signed value with fewer bits (e.g., an INT).
- To make the 64-bit value human-readable on the PLC, it is cyclically converted to text showing the actual number (variable sInt64).

**Publishing as 64-bit value on the OpcUa server:**
- On the PLC, 64-bit values are structured (BrbUint64_TYP or BrbInt64_TYP).
- To configure the server to publish this structure as Uint64 or Int64, a simple configuration is required. 
  This must be done in the file 'OpcUaMap.uad' (see ConfigurationView/Connectivity/OpcUa), specifically in the 'UA Datatype' column of the structure variable (the sub-elements of the structure should not be released). 
  Here, an OpcUa data type NodeId can optionally be specified:
    - Uint64: ns=0;i=9
    - Int64: ns=0;i=8
- The server will then publish the variable value as the specified OpcUa data type.
- However, this works only if the PLC variable has the byte length required by the specified OpcUa type.
  The OpcUa data types Uint64 and Int64 each require 8 bytes, which are provided by the instances of the structures 'BrbUint64_TYP' and 'BrbInt64_TYP'.

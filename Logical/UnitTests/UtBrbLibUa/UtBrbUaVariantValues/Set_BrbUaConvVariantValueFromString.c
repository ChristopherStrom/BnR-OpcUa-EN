#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
_TEST BrbUaConvVariantValueFromString_NulPtr(void)
{
	dwordOut = BrbUaConvVariantValueFromString(0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, 0);
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_Boolean(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Boolean;
	strcpy(stringIn0, "xxx");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Boolean, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_BOOL(0, variantIn0.Boolean);

	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Boolean;
	strcpy(stringIn0, "0");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Boolean, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_BOOL(0, variantIn0.Boolean);

	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Boolean;
	strcpy(stringIn0, "False");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Boolean, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_BOOL(0, variantIn0.Boolean);

	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Boolean;
	strcpy(stringIn0, "false");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Boolean, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_BOOL(0, variantIn0.Boolean);

	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Boolean;
	strcpy(stringIn0, "1");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Boolean, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_BOOL(1, variantIn0.Boolean);

	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Boolean;
	strcpy(stringIn0, "True");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Boolean, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_BOOL(1, variantIn0.Boolean);

	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Boolean;
	strcpy(stringIn0, "true");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Boolean, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_BOOL(1, variantIn0.Boolean);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_SByte(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_SByte;
	strcpy(stringIn0, "-128");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_SByte, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_DINT(-128, (DINT)variantIn0.SByte);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_Byte(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Byte;
	strcpy(stringIn0, "127");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Byte, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(127, (UDINT)variantIn0.Byte);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_Int16(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Int16;
	strcpy(stringIn0, "-32768");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Int16, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_DINT(-32768, (DINT)variantIn0.Int16);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_Uint16(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_UInt16;
	strcpy(stringIn0, "65535");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_UInt16, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(65535, (UDINT)variantIn0.UInt16);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_Int32(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Int32;
	strcpy(stringIn0, "-2147483648");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Int32, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_DINT(-2147483648, (DINT)variantIn0.Int32);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_Uint32(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_UInt32;
	strcpy(stringIn0, "4294967295");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_UInt32, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(4294967295, variantIn0.UInt32);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_Int64(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Int64;
	strcpy(stringIn0, "-2147483648");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Int64, (DINT)variantIn0.VariantType);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_Uint64(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_UInt64;
	strcpy(stringIn0, "4294967295");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	BRB_ASSERT_EQUAL_DINT(UAVariantType_UInt64, (DINT)variantIn0.VariantType);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_Float(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Float;
	strcpy(stringIn0, "-1.23");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Float, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_REAL(-1.23, variantIn0.Float);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_Double(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Double;
	strcpy(stringIn0, "-2.34");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Double, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_LREAL((LREAL)-2.3399999141693115, variantIn0.Double);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_String(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_String;
	strcpy(stringIn0, "Hallo");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_String, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("Hallo", variantIn0.String);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_DateTime(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_DateTime;
	strcpy(stringIn0, "2106.02.07 06:28:15:000:000");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_DateTime, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(4294967295, (UDINT)variantIn0.DateTime);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_Guid(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Guid;
	strcpy(stringIn0, "12345678-1234-5678-9ABC-123456789ABC");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Guid, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("12345678-1234-5678-9ABC-123456789ABC", variantIn0.String);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_ByteString(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_ByteString;
	strcpy(stringIn0, "123456789ABC");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	BRB_ASSERT_EQUAL_DINT(UAVariantType_ByteString, (DINT)variantIn0.VariantType);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_XmlElement(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_XmlElement;
	strcpy(stringIn0, "<Hallo >");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	BRB_ASSERT_EQUAL_DINT(UAVariantType_XmlElement, (DINT)variantIn0.VariantType);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_NodeId(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_NodeId;
	strcpy(stringIn0, "ns=34");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x80330000 , dwordOut); // = Bad_NodeIdInvalid
	BRB_ASSERT_EQUAL_DINT(UAVariantType_NodeId, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(34, (UDINT)variantIn0.NodeId.NamespaceIndex);
	//BRB_ASSERT_EQUAL_DINT(UAIdentifierType_Numeric, variantIn0.NodeId.IdentifierType);
	TEST_ASSERT_EQUAL_STRING("", variantIn0.NodeId.Identifier);
	
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_NodeId;
	strcpy(stringIn0, "ns=56;");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x80330000 , dwordOut); // = Bad_NodeIdInvalid
	BRB_ASSERT_EQUAL_DINT(UAVariantType_NodeId, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(56, (UDINT)variantIn0.NodeId.NamespaceIndex);
	//BRB_ASSERT_EQUAL_DINT(UAIdentifierType_Numeric, variantIn0.NodeId.IdentifierType);
	TEST_ASSERT_EQUAL_STRING("", variantIn0.NodeId.Identifier);
	
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_NodeId;
	strcpy(stringIn0, "ns=123;v=Hallo");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x80330000 , dwordOut); // = Bad_NodeIdInvalid
	BRB_ASSERT_EQUAL_DINT(UAVariantType_NodeId, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(123, (UDINT)variantIn0.NodeId.NamespaceIndex);
	//BRB_ASSERT_EQUAL_DINT(UAIdentifierType_Numeric, variantIn0.NodeId.IdentifierType);
	TEST_ASSERT_EQUAL_STRING("", variantIn0.NodeId.Identifier);
	
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_NodeId;
	strcpy(stringIn0, "i=1234");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_NodeId, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)variantIn0.NodeId.NamespaceIndex);
	BRB_ASSERT_EQUAL_DINT(UAIdentifierType_Numeric, (DINT)variantIn0.NodeId.IdentifierType);
	TEST_ASSERT_EQUAL_STRING("1234", variantIn0.NodeId.Identifier);
	
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_NodeId;
	strcpy(stringIn0, "ns=21;i=2345");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_NodeId, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(21, (UDINT)variantIn0.NodeId.NamespaceIndex);
	BRB_ASSERT_EQUAL_DINT(UAIdentifierType_Numeric, (DINT)variantIn0.NodeId.IdentifierType);
	TEST_ASSERT_EQUAL_STRING("2345", variantIn0.NodeId.Identifier);
	
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_NodeId;
	strcpy(stringIn0, "s=Hallo");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_NodeId, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)variantIn0.NodeId.NamespaceIndex);
	BRB_ASSERT_EQUAL_DINT(UAIdentifierType_String, (DINT)variantIn0.NodeId.IdentifierType);
	TEST_ASSERT_EQUAL_STRING("Hallo", variantIn0.NodeId.Identifier);
	
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_NodeId;
	strcpy(stringIn0, "ns=22;s=Hello");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_NodeId, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(22, (UDINT)variantIn0.NodeId.NamespaceIndex);
	BRB_ASSERT_EQUAL_DINT(UAIdentifierType_String, (DINT)variantIn0.NodeId.IdentifierType);
	TEST_ASSERT_EQUAL_STRING("Hello", variantIn0.NodeId.Identifier);
	
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_NodeId;
	strcpy(stringIn0, "g=7fdf25f9-7815-e783-488b-a4247f55b88e");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_NodeId, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)variantIn0.NodeId.NamespaceIndex);
	BRB_ASSERT_EQUAL_DINT(UAIdentifierType_GUID, (DINT)variantIn0.NodeId.IdentifierType);
	TEST_ASSERT_EQUAL_STRING("7fdf25f9-7815-e783-488b-a4247f55b88e", variantIn0.NodeId.Identifier);
	
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_NodeId;
	strcpy(stringIn0, "ns=23;g=80e0360a-7815-e783-488b-a4247f55b88e");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_NodeId, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(23, (UDINT)variantIn0.NodeId.NamespaceIndex);
	BRB_ASSERT_EQUAL_DINT(UAIdentifierType_GUID, (DINT)variantIn0.NodeId.IdentifierType);
	TEST_ASSERT_EQUAL_STRING("80e0360a-7815-e783-488b-a4247f55b88e", variantIn0.NodeId.Identifier);
	
	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_ExpandedNodeId(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_ExpandedNodeId;
	strcpy(stringIn0, "xxxyyy");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	BRB_ASSERT_EQUAL_DINT(UAVariantType_ExpandedNodeId, (DINT)variantIn0.VariantType);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_StatusCode(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_StatusCode;
	strcpy(stringIn0, "32987");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_StatusCode, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(32987, variantIn0.UInt32);

	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_StatusCode;
	strcpy(stringIn0, "0xA0150000");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_StatusCode, (DINT)variantIn0.VariantType);
	BRB_ASSERT_EQUAL_UDINT(2685730816, variantIn0.UInt32);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_QualifiedName(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_QualifiedName;
	strcpy(stringIn0, "xxxyyy");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	BRB_ASSERT_EQUAL_DINT(UAVariantType_QualifiedName, (DINT)variantIn0.VariantType);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueFromString_LocalizedText(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_LocalizedText;
	strcpy(stringIn0, "xxxyyy");
	dwordOut = BrbUaConvVariantValueFromString(&variantIn0, stringIn0);
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	BRB_ASSERT_EQUAL_DINT(UAVariantType_LocalizedText, (DINT)variantIn0.VariantType);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-05-04 13:01:25Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaConvVariantValueFromString_NulPtr", BrbUaConvVariantValueFromString_NulPtr), 
	new_TestFixture("BrbUaConvVariantValueFromString_Boolean", BrbUaConvVariantValueFromString_Boolean), 
	new_TestFixture("BrbUaConvVariantValueFromString_SByte", BrbUaConvVariantValueFromString_SByte), 
	new_TestFixture("BrbUaConvVariantValueFromString_Byte", BrbUaConvVariantValueFromString_Byte), 
	new_TestFixture("BrbUaConvVariantValueFromString_Int16", BrbUaConvVariantValueFromString_Int16), 
	new_TestFixture("BrbUaConvVariantValueFromString_Uint16", BrbUaConvVariantValueFromString_Uint16), 
	new_TestFixture("BrbUaConvVariantValueFromString_Int32", BrbUaConvVariantValueFromString_Int32), 
	new_TestFixture("BrbUaConvVariantValueFromString_Uint32", BrbUaConvVariantValueFromString_Uint32), 
	new_TestFixture("BrbUaConvVariantValueFromString_Int64", BrbUaConvVariantValueFromString_Int64), 
	new_TestFixture("BrbUaConvVariantValueFromString_Uint64", BrbUaConvVariantValueFromString_Uint64), 
	new_TestFixture("BrbUaConvVariantValueFromString_Float", BrbUaConvVariantValueFromString_Float), 
	new_TestFixture("BrbUaConvVariantValueFromString_Double", BrbUaConvVariantValueFromString_Double), 
	new_TestFixture("BrbUaConvVariantValueFromString_String", BrbUaConvVariantValueFromString_String), 
	new_TestFixture("BrbUaConvVariantValueFromString_DateTime", BrbUaConvVariantValueFromString_DateTime), 
	new_TestFixture("BrbUaConvVariantValueFromString_Guid", BrbUaConvVariantValueFromString_Guid), 
	new_TestFixture("BrbUaConvVariantValueFromString_ByteString", BrbUaConvVariantValueFromString_ByteString), 
	new_TestFixture("BrbUaConvVariantValueFromString_XmlElement", BrbUaConvVariantValueFromString_XmlElement), 
	new_TestFixture("BrbUaConvVariantValueFromString_NodeId", BrbUaConvVariantValueFromString_NodeId), 
	new_TestFixture("BrbUaConvVariantValueFromString_ExpandedNodeId", BrbUaConvVariantValueFromString_ExpandedNodeId), 
	new_TestFixture("BrbUaConvVariantValueFromString_StatusCode", BrbUaConvVariantValueFromString_StatusCode), 
	new_TestFixture("BrbUaConvVariantValueFromString_QualifiedName", BrbUaConvVariantValueFromString_QualifiedName), 
	new_TestFixture("BrbUaConvVariantValueFromString_LocalizedText", BrbUaConvVariantValueFromString_LocalizedText), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaConvVariantValueFromString, "Set_BrbUaConvVariantValueFromString", 0, 0, fixtures, 0, 0, 0);


#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
_TEST BrbUaConvVariantValueToString_NulPtr(void)
{
	dwordOut = BrbUaConvVariantValueToString(0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	dwordOut = BrbUaConvVariantValueToString(&variantIn0, 0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_Bool(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Boolean;
	variantIn0.Boolean = 0;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Boolean, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("False", stringIn0);

	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Boolean;
	variantIn0.Boolean = 1;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Boolean, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("True", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_SByte(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_SByte;
	variantIn0.SByte = -128;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_SByte, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("-128", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_Byte(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));

	variantIn0.VariantType = UAVariantType_Byte;
	variantIn0.Byte = 255;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Byte, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("255", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_Int16(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Int16;
	variantIn0.Int16 = -32768;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Int16, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("-32768", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_UInt16(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_UInt16;
	variantIn0.UInt16 = 65535;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_UInt16, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("65535", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_Int32(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Int32;
	variantIn0.Int32 = -2147483648;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Int32, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("-2147483648", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_UInt32(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_UInt32;
	strcpy(stringIn0, "4294967295");
	variantIn0.UInt32 = 4294967295;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_UInt32, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("4294967295", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_Int64(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Int64;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Int64, (DINT)variantIn0.VariantType);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_UInt64(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_UInt64;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	BRB_ASSERT_EQUAL_DINT(UAVariantType_UInt64, (DINT)variantIn0.VariantType);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_Float(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Float;
	variantIn0.Float = -1.23f;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Float, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("-1.23", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_Double(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Double;
	variantIn0.Double = (LREAL)-2.34;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Double, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("-2.34", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_String(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_String;
	strcpy(variantIn0.String, "Hallo");
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_String, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("Hallo", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_DateTime(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_DateTime;
	variantIn0.DateTime = BrbSetDt(2106, 02, 07, 06, 28, 15);
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_DateTime, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("2106-02-07 06:28:15", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_Guid(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Guid;
	strcpy(variantIn0.String, "12345678-1234-5678-9ABC-123456789ABC");
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Guid, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("12345678-1234-5678-9ABC-123456789ABC", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_ByteString(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_ByteString;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	BRB_ASSERT_EQUAL_DINT(UAVariantType_ByteString, (DINT)variantIn0.VariantType);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_XmlElement(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_XmlElement;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	BRB_ASSERT_EQUAL_DINT(UAVariantType_XmlElement, (DINT)variantIn0.VariantType);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_NodeId(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_NodeId;
	BrbUaSetNodeId(&variantIn0.NodeId, "VarX", 0);
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_NodeId, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("ns=0;s=VarX", stringIn0);

	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_NodeId;
	BrbUaSetNodeId(&variantIn0.NodeId, "1234", 1);
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_NodeId, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("ns=1;i=1234", stringIn0);

	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_NodeId;
	variantIn0.NodeId.IdentifierType = UAIdentifierType_GUID;
	strcpy(variantIn0.NodeId.Identifier, "12345678-1234-5678-9ABC-123456789ABC");
	variantIn0.NodeId.NamespaceIndex = 2;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_NodeId, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("ns=2;g=12345678-1234-5678-9ABC-123456789ABC", stringIn0);

	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_NodeId;
	variantIn0.NodeId.IdentifierType = UAIdentifierType_Opaque;
	strcpy(variantIn0.NodeId.Identifier, "");
	variantIn0.NodeId.NamespaceIndex = 2;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	BRB_ASSERT_EQUAL_DINT(UAVariantType_NodeId, (DINT)variantIn0.VariantType);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_ExpandedNodeId(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_ExpandedNodeId;
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	BRB_ASSERT_EQUAL_DINT(UAVariantType_ExpandedNodeId, (DINT)variantIn0.VariantType);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_StatusCode(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_StatusCode;
	variantIn0.UInt32 = 0x800D0000; // = Bad_ServerNotConnected
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_StatusCode, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("0x800D0000 = Bad_ServerNotConnected", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_QualifiedName(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_QualifiedName;
	BrbUaSetQualifedName(&variantIn0.QualifiedName, 1, "VarX");
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_QualifiedName, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("1:VarX", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaConvVariantValueToString_LocalizedText(void)
{
	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_LocalizedText;
	BrbUaSetLocalizedText(&variantIn0.LocalizedText, "", "VarX");
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_LocalizedText, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("VarX", stringIn0);

	memset(&variantIn0, 0, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_LocalizedText;
	BrbUaSetLocalizedText(&variantIn0.LocalizedText, "de", "VarX");
	dwordOut = BrbUaConvVariantValueToString(&variantIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_LocalizedText, (DINT)variantIn0.VariantType);
	TEST_ASSERT_EQUAL_STRING("de:VarX", stringIn0);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-05-05 10:56:29Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaConvVariantValueToString_NulPtr", BrbUaConvVariantValueToString_NulPtr), 
	new_TestFixture("BrbUaConvVariantValueToString_Bool", BrbUaConvVariantValueToString_Bool), 
	new_TestFixture("BrbUaConvVariantValueToString_SByte", BrbUaConvVariantValueToString_SByte), 
	new_TestFixture("BrbUaConvVariantValueToString_Byte", BrbUaConvVariantValueToString_Byte), 
	new_TestFixture("BrbUaConvVariantValueToString_Int16", BrbUaConvVariantValueToString_Int16), 
	new_TestFixture("BrbUaConvVariantValueToString_UInt16", BrbUaConvVariantValueToString_UInt16), 
	new_TestFixture("BrbUaConvVariantValueToString_Int32", BrbUaConvVariantValueToString_Int32), 
	new_TestFixture("BrbUaConvVariantValueToString_UInt32", BrbUaConvVariantValueToString_UInt32), 
	new_TestFixture("BrbUaConvVariantValueToString_Int64", BrbUaConvVariantValueToString_Int64), 
	new_TestFixture("BrbUaConvVariantValueToString_UInt64", BrbUaConvVariantValueToString_UInt64), 
	new_TestFixture("BrbUaConvVariantValueToString_Float", BrbUaConvVariantValueToString_Float), 
	new_TestFixture("BrbUaConvVariantValueToString_Double", BrbUaConvVariantValueToString_Double), 
	new_TestFixture("BrbUaConvVariantValueToString_String", BrbUaConvVariantValueToString_String), 
	new_TestFixture("BrbUaConvVariantValueToString_DateTime", BrbUaConvVariantValueToString_DateTime), 
	new_TestFixture("BrbUaConvVariantValueToString_Guid", BrbUaConvVariantValueToString_Guid), 
	new_TestFixture("BrbUaConvVariantValueToString_ByteString", BrbUaConvVariantValueToString_ByteString), 
	new_TestFixture("BrbUaConvVariantValueToString_XmlElement", BrbUaConvVariantValueToString_XmlElement), 
	new_TestFixture("BrbUaConvVariantValueToString_NodeId", BrbUaConvVariantValueToString_NodeId), 
	new_TestFixture("BrbUaConvVariantValueToString_ExpandedNodeId", BrbUaConvVariantValueToString_ExpandedNodeId), 
	new_TestFixture("BrbUaConvVariantValueToString_StatusCode", BrbUaConvVariantValueToString_StatusCode), 
	new_TestFixture("BrbUaConvVariantValueToString_QualifiedName", BrbUaConvVariantValueToString_QualifiedName), 
	new_TestFixture("BrbUaConvVariantValueToString_LocalizedText", BrbUaConvVariantValueToString_LocalizedText), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaConvVariantValueToString, "Set_BrbUaConvVariantValueToString", 0, 0, fixtures, 0, 0, 0);


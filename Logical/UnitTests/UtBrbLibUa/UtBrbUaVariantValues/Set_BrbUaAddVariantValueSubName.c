#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

_TEST BrbUaAddVariantValueSubName_NulPtr(void)
{
	dwordOut = BrbUaAddVariantValueSubName(0, 0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaAddVariantValueSubName_Add(void)
{
	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_Null, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_Boolean, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.Boolean", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_SByte, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.SByte", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_Byte, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.Byte", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_Int16, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.Int16", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_UInt16, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.UInt16", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_Int32, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.Int32", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_UInt32, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.UInt32", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_Int64, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.Int64", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_UInt64, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.UInt64", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_Float, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.Float", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_Double, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.Double", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_String, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.String", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_DateTime, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.DateTime", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_Guid, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.String", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_ByteString, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.String", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_XmlElement, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_NodeId, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.NodeId", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_ExpandedNodeId, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.ExpandedNodeId", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_StatusCode, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.StatusCode", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_QualifiedName, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.QualifiedName", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_Boolean, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.Boolean", stringIn0);

	strcpy(stringIn0, "Var");
	dwordOut = BrbUaAddVariantValueSubName(UAVariantType_LocalizedText, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Var.LocalizedText", stringIn0);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 12:30:26Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaAddVariantValueSubName_NulPtr", BrbUaAddVariantValueSubName_NulPtr), 
	new_TestFixture("BrbUaAddVariantValueSubName_Add", BrbUaAddVariantValueSubName_Add), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaAddVariantValueSubName, "Set_BrbUaAddVariantValueSubName", 0, 0, fixtures, 0, 0, 0);


#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

_TEST BrbUaAddNodeIdText_NulPtr(void)
{
	dwordOut = BrbUaAddNodeIdText(0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	dwordOut = BrbUaAddNodeIdText(&nodeIdIn0, 0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaAddNodeIdText_Add(void)
{
	strcpy(stringIn0, "Test ");
	BrbUaSetNodeId(&nodeIdIn0, "1234", 0);
	dwordOut = BrbUaAddNodeIdText(&nodeIdIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test ns=0;i=1234", stringIn0);

	strcpy(stringIn0, "Test ");
	BrbUaSetNodeId(&nodeIdIn0, "VarX", 12);
	dwordOut = BrbUaAddNodeIdText(&nodeIdIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test ns=12;s=VarX", stringIn0);

	strcpy(stringIn0, "Test ");
	nodeIdIn0.IdentifierType = UAIdentifierType_GUID;
	strcpy(nodeIdIn0.Identifier, "12345678-1234-5678-9ABC-123456789ABC");
	nodeIdIn0.NamespaceIndex = 4;
	dwordOut = BrbUaAddNodeIdText(&nodeIdIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test ns=4;g=12345678-1234-5678-9ABC-123456789ABC", stringIn0);

	strcpy(stringIn0, "Test ");
	nodeIdIn0.IdentifierType = UAIdentifierType_Opaque;
	strcpy(nodeIdIn0.Identifier, "123456789ABCDEF01234");
	nodeIdIn0.NamespaceIndex = 6;
	dwordOut = BrbUaAddNodeIdText(&nodeIdIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test ns=6;o=123456789ABCDEF01234", stringIn0);

	strcpy(stringIn0, "Test ");
	nodeIdIn0.IdentifierType = 0; // NOLINT(clang-diagnostic-assign-enum)
	strcpy(nodeIdIn0.Identifier, "UnknownIdentifierType");
	nodeIdIn0.NamespaceIndex = 8;
	dwordOut = BrbUaAddNodeIdText(&nodeIdIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test ns=8;?=UnknownIdentifierType", stringIn0);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 08:30:07Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaAddNodeIdText_NulPtr", BrbUaAddNodeIdText_NulPtr), 
	new_TestFixture("BrbUaAddNodeIdText_Add", BrbUaAddNodeIdText_Add), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaAddNodeIdText, "Set_BrbUaAddNodeIdText", 0, 0, fixtures, 0, 0, 0);


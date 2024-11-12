#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

_TEST BrbUaSetNodeId_NulPtr(void)
{
	memset(&stringIn0, 0, sizeof(stringIn0));
	uintIn0 = 0;
	dwordOut = BrbUaSetNodeId(0, stringIn0, uintIn0);
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaSetNodeId_Set(void)
{
	strcpy(stringIn0, "VarX");
	uintIn0 = 1;
	dwordOut = BrbUaSetNodeId(&nodeIdIn0, stringIn0, uintIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_INT(UAIdentifierType_String, nodeIdIn0.IdentifierType);
	TEST_ASSERT_EQUAL_STRING(stringIn0, nodeIdIn0.Identifier);
	TEST_ASSERT_EQUAL_INT(uintIn0, nodeIdIn0.NamespaceIndex);

	strcpy(stringIn0, "1234");
	uintIn0 = 1;
	dwordOut = BrbUaSetNodeId(&nodeIdIn0, stringIn0, uintIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_INT(UAIdentifierType_Numeric, nodeIdIn0.IdentifierType);
	TEST_ASSERT_EQUAL_STRING(stringIn0, nodeIdIn0.Identifier);
	TEST_ASSERT_EQUAL_INT(uintIn0, nodeIdIn0.NamespaceIndex);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 08:00:09Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaSetNodeId_NulPtr", BrbUaSetNodeId_NulPtr), 
	new_TestFixture("BrbUaSetNodeId_Set", BrbUaSetNodeId_Set), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaSetNodeId, "Set_BrbUaSetNodeId", 0, 0, fixtures, 0, 0, 0);


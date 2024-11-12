#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

_TEST BrbUaSetNodeIdNum_NulPtr(void)
{
	udintIn0 = 0;
	uintIn0 = 0;
	dwordOut = BrbUaSetNodeIdNum(0, udintIn0, uintIn0);
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaSetNodeId_Set(void)
{
	udintIn0 = 1234;
	uintIn0 = 1;
	dwordOut = BrbUaSetNodeIdNum(&nodeIdIn0, udintIn0, uintIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_INT(UAIdentifierType_Numeric, nodeIdIn0.IdentifierType);
	TEST_ASSERT_EQUAL_STRING("1234", nodeIdIn0.Identifier);
	TEST_ASSERT_EQUAL_INT(uintIn0, nodeIdIn0.NamespaceIndex);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 08:08:20Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaSetNodeIdNum_NulPtr", BrbUaSetNodeIdNum_NulPtr), 
	new_TestFixture("BrbUaSetNodeId_Set", BrbUaSetNodeId_Set), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaSetNodeIdNum, "Set_BrbUaSetNodeIdNum", 0, 0, fixtures, 0, 0, 0);


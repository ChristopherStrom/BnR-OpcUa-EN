#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

_TEST BrbUaGetRandomNodeId_NulPtr(void)
{
	udintIn0 = 0;
	uintIn0 = 0;
	dwordOut = BrbUaGetRandomNodeId(0, UAIdentifierType_Numeric);
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaGetRandomNodeId_Get(void)
{
	dwordOut = BrbUaGetRandomNodeId(&nodeIdIn0, UAIdentifierType_Numeric);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_INT(UAIdentifierType_Numeric, nodeIdIn0.IdentifierType);

	dwordOut = BrbUaGetRandomNodeId(&nodeIdIn0, UAIdentifierType_String);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_INT(UAIdentifierType_String, nodeIdIn0.IdentifierType);

	dwordOut = BrbUaGetRandomNodeId(&nodeIdIn0, UAIdentifierType_GUID);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_INT(UAIdentifierType_GUID, nodeIdIn0.IdentifierType);

	dwordOut = BrbUaGetRandomNodeId(&nodeIdIn0, UAIdentifierType_Opaque);
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	TEST_ASSERT_EQUAL_INT(UAIdentifierType_Opaque, nodeIdIn0.IdentifierType);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 08:12:57Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaGetRandomNodeId_NulPtr", BrbUaGetRandomNodeId_NulPtr), 
	new_TestFixture("BrbUaGetRandomNodeId_Get", BrbUaGetRandomNodeId_Get), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaGetRandomNodeId, "Set_BrbUaGetRandomNodeId", 0, 0, fixtures, 0, 0, 0);


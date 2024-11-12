#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

_TEST BrbUaAreNodeIdsEqual_NulPtr(void)
{
	boolOut = BrbUaAreNodeIdsEqual(0, &nodeIdIn1);
	BRB_ASSERT_EQUAL_BOOL(0, boolOut);

	boolOut = BrbUaAreNodeIdsEqual(&nodeIdIn0, 0);
	BRB_ASSERT_EQUAL_BOOL(0, boolOut);

	// Finished
	TEST_DONE;
}

_TEST BrbUaAreNodeIdsEqual_Compare(void)
{

	BrbUaSetNodeId(&nodeIdIn0, "1234", 12);
	BrbUaSetNodeId(&nodeIdIn1, "1234", 12);
	boolOut = BrbUaAreNodeIdsEqual(&nodeIdIn0, &nodeIdIn1);
	BRB_ASSERT_EQUAL_BOOL(1, boolOut);

	BrbUaSetNodeId(&nodeIdIn0, "1234", 12);
	BrbUaSetNodeId(&nodeIdIn1, "1234", 16);
	boolOut = BrbUaAreNodeIdsEqual(&nodeIdIn0, &nodeIdIn1);
	BRB_ASSERT_EQUAL_BOOL(0, boolOut);

	BrbUaSetNodeId(&nodeIdIn0, "1234", 12);
	BrbUaSetNodeId(&nodeIdIn1, "1235", 12);
	boolOut = BrbUaAreNodeIdsEqual(&nodeIdIn0, &nodeIdIn1);
	BRB_ASSERT_EQUAL_BOOL(0, boolOut);

	BrbUaSetNodeId(&nodeIdIn0, "1234", 12);
	BrbUaSetNodeId(&nodeIdIn1, "1235", 16);
	boolOut = BrbUaAreNodeIdsEqual(&nodeIdIn0, &nodeIdIn1);
	BRB_ASSERT_EQUAL_BOOL(0, boolOut);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 08:16:35Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaAreNodeIdsEqual_NulPtr", BrbUaAreNodeIdsEqual_NulPtr), 
	new_TestFixture("BrbUaAreNodeIdsEqual_Compare", BrbUaAreNodeIdsEqual_Compare), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaAreNodeIdsEqual, "Set_BrbUaAreNodeIdsEqual", 0, 0, fixtures, 0, 0, 0);


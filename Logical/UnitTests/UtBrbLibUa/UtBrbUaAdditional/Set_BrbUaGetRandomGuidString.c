#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
_TEST BrbUaGetRandomGuidString_NulPtr(void)
{
	dwordOut = BrbUaGetRandomGuidString(0, sizeof(guidStringIn), 1);
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaGetRandomGuidString_WithSep(void)
{
	dwordOut = BrbUaGetRandomGuidString(&guidStringIn, sizeof(guidStringIn), 1);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_UDINT(36, strlen((STRING*)&guidStringIn));
	BRB_ASSERT_EQUAL_UDINT(4, BrbStringCountText(guidStringIn, "-", sizeof(guidStringIn)));
	TEST_ASSERT_EQUAL_INT('-', guidStringIn[8]);
	TEST_ASSERT_EQUAL_INT('-', guidStringIn[13]);
	TEST_ASSERT_EQUAL_INT('-', guidStringIn[18]);
	TEST_ASSERT_EQUAL_INT('-', guidStringIn[23]);

	// Finished
	TEST_DONE;
}

_TEST BrbUaGetRandomGuidString_WithoutSep(void)
{
	dwordOut = BrbUaGetRandomGuidString(&guidStringIn, sizeof(guidStringIn), 0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_UDINT(32, strlen((STRING*)&guidStringIn));
	BRB_ASSERT_EQUAL_UDINT(0, BrbStringCountText(guidStringIn, "-", sizeof(guidStringIn)));

	// Finished
	TEST_DONE;
}
// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-05-04 06:45:07Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaGetRandomGuidString_NulPtr", BrbUaGetRandomGuidString_NulPtr), 
	new_TestFixture("BrbUaGetRandomGuidString_WithSep", BrbUaGetRandomGuidString_WithSep), 
	new_TestFixture("BrbUaGetRandomGuidString_WithoutSep", BrbUaGetRandomGuidString_WithoutSep), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaGetRandomGuidString, "Set_BrbUaGetRandomGuidString", 0, 0, fixtures, 0, 0, 0);


#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
_TEST BrbUaGetStatusCodeText_NulPtr(void)
{
	statusCodeIn0 = 0x00000000;
	memset(&stringIn0, 0, sizeof(stringIn0));
	dwordOut = BrbUaGetStatusCodeText(statusCodeIn0, 0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing
	TEST_ASSERT_EQUAL_STRING("", stringIn0);

	// Finished
	TEST_DONE;
}

_TEST BrbUaGetStatusCodeText_Status(void)
{
	statusCodeIn0 = 0x00000000;
	dwordOut = BrbUaGetStatusCodeText(statusCodeIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("0x00000000 = Good", stringIn0);

	statusCodeIn0 = 0xFFFFFFFF;
	dwordOut = BrbUaGetStatusCodeText(statusCodeIn0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x803D0000, dwordOut); // = Bad_NotSupported
	TEST_ASSERT_EQUAL_STRING("0xFFFFFFFF", stringIn0);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 07:23:16Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaGetStatusCodeText_NulPtr", BrbUaGetStatusCodeText_NulPtr), 
	new_TestFixture("BrbUaGetStatusCodeText_Status", BrbUaGetStatusCodeText_Status), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaGetStatusCodeText, "Set_BrbUaGetStatusCodeText", 0, 0, fixtures, 0, 0, 0);


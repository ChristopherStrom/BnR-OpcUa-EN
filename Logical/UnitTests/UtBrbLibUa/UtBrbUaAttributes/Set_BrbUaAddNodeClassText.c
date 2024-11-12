#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

_TEST BrbUaAddNodeClassText_NulPtr(void)
{
	dwordOut = BrbUaAddNodeClassText(UANodeClass_None, 0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaAddNodeClassText_Add(void)
{
	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddNodeClassText(UANodeClass_None, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test None", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddNodeClassText(UANodeClass_Object, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test Object", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddNodeClassText(UANodeClass_Variable, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test Variable", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddNodeClassText(UANodeClass_Method, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test Method", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddNodeClassText(254, stringIn0, sizeof(stringIn0)); // NOLINT(clang-diagnostic-assign-enum)
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test Unknown", stringIn0);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 09:05:44Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaAddNodeClassText_NulPtr", BrbUaAddNodeClassText_NulPtr), 
	new_TestFixture("BrbUaAddNodeClassText_Add", BrbUaAddNodeClassText_Add), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaAddNodeClassText, "Set_BrbUaAddNodeClassText", 0, 0, fixtures, 0, 0, 0);


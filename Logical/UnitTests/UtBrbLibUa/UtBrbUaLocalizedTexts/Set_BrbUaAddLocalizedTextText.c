#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
_TEST BrbUaAddLocalizedTextText_NulPtr(void)
{
	dwordOut = BrbUaAddLocalizedTextText(0, stringIn, sizeof(stringIn));
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	dwordOut = BrbUaAddLocalizedTextText(&localizedTextIn, 0, sizeof(stringIn));
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaAddLocalizedTextText_Add(void)
{
	strcpy(stringIn, "Test ");
	BrbUaSetLocalizedText(&localizedTextIn, "de", "Hello");
	dwordOut = BrbUaAddLocalizedTextText(&localizedTextIn, stringIn, sizeof(stringIn));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test de:Hello", stringIn);

	strcpy(stringIn, "Test ");
	BrbUaSetLocalizedText(&localizedTextIn, "", "Hello");
	dwordOut = BrbUaAddLocalizedTextText(&localizedTextIn, stringIn, sizeof(stringIn));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test Hello", stringIn);

	strcpy(stringIn, "Test ");
	BrbUaSetLocalizedText(&localizedTextIn, "en", "");
	dwordOut = BrbUaAddLocalizedTextText(&localizedTextIn, stringIn, sizeof(stringIn));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test en:", stringIn);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-25 07:20:13Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaAddLocalizedTextText_NulPtr", BrbUaAddLocalizedTextText_NulPtr), 
	new_TestFixture("BrbUaAddLocalizedTextText_Add", BrbUaAddLocalizedTextText_Add), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaAddLocalizedTextText, "Set_BrbUaAddLocalizedTextText", 0, 0, fixtures, 0, 0, 0);


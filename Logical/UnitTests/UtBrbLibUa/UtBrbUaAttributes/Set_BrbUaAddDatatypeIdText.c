#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

_TEST BrbUaAddDatatypeIdText_NulPtr(void)
{
	dwordOut = BrbUaAddDatatypeIdText(0, 0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaAddDatatypeIdText_Add(void)
{
	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddDatatypeIdText(1, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 1=Boolean", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddDatatypeIdText(4, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 4=Int16", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddDatatypeIdText(8, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 8=Int64", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddDatatypeIdText(12, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 12=String", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddDatatypeIdText(15, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 15=ByteString", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddDatatypeIdText(17, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 17=NodeId", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddDatatypeIdText(22, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 22=Structure", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddDatatypeIdText(0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 0", stringIn0);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 09:10:48Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaAddDatatypeIdText_NulPtr", BrbUaAddDatatypeIdText_NulPtr), 
	new_TestFixture("BrbUaAddDatatypeIdText_Add", BrbUaAddDatatypeIdText_Add), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaAddDatatypeIdText, "Set_BrbUaAddDatatypeIdText", 0, 0, fixtures, 0, 0, 0);


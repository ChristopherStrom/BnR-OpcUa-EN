#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

_TEST BrbUaAddAccessLevelText_NulPtr(void)
{
	dwordOut = BrbUaAddAccessLevelText(0, 0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaAddAccessLevelText_Add(void)
{
	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 0= None", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(1, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 1= Read", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(2, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 2= Write", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(3, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 3= Read, Write", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(4, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 4= HistoryRead", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(5, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 5= Read, HistoryRead", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(6, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 6= Write, HistoryRead", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(7, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 7= Read, Write, HistoryRead", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(8, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 8= HistoryWrite", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(9, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 9= Read, HistoryWrite", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(10, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 10= Write, HistoryWrite", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(11, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 11= Read, Write, HistoryWrite", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(12, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 12= HistoryRead, HistoryWrite", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(13, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 13= Read, HistoryRead, HistoryWrite", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(14, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 14= Write, HistoryRead, HistoryWrite", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddAccessLevelText(15, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 15= Read, Write, HistoryRead, HistoryWrite", stringIn0);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 09:38:10Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaAddAccessLevelText_NulPtr", BrbUaAddAccessLevelText_NulPtr), 
	new_TestFixture("BrbUaAddAccessLevelText_Add", BrbUaAddAccessLevelText_Add), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaAddAccessLevelText, "Set_BrbUaAddAccessLevelText", 0, 0, fixtures, 0, 0, 0);


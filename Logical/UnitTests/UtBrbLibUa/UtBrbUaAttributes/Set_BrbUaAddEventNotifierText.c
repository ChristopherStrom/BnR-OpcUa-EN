#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

_TEST BrbUaAddEventNotifierText_NulPtr(void)
{
	dwordOut = BrbUaAddEventNotifierText(0, 0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaAddEventNotifierText_Add(void)
{
	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 0= None", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(1, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 1= Subscribe", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(2, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 2=", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(3, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 3= Subscribe", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(4, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 4= HistoryRead", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(5, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 5= Subscribe, HistoryRead", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(6, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 6= HistoryRead", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(7, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 7= Subscribe, HistoryRead", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(8, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 8= HistoryWrite", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(9, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 9= Subscribe, HistoryWrite", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(10, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 10= HistoryWrite", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(11, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 11= Subscribe, HistoryWrite", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(12, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 12= HistoryRead, HistoryWrite", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(13, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 13= Subscribe, HistoryRead, HistoryWrite", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(14, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 14= HistoryRead, HistoryWrite", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddEventNotifierText(15, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 15= Subscribe, HistoryRead, HistoryWrite", stringIn0);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 09:47:06Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaAddEventNotifierText_NulPtr", BrbUaAddEventNotifierText_NulPtr), 
	new_TestFixture("BrbUaAddEventNotifierText_Add", BrbUaAddEventNotifierText_Add), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaAddEventNotifierText, "Set_BrbUaAddEventNotifierText", 0, 0, fixtures, 0, 0, 0);


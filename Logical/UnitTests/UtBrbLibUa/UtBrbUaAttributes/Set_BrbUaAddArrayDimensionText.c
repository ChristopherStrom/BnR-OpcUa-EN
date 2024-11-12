#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

_TEST BrbUaAddArrayDimensionText_NulPtr(void)
{
	dwordOut = BrbUaAddArrayDimensionText(0, nARRAY_DIMENSION_INDEX_MAX, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	dwordOut = BrbUaAddArrayDimensionText((UDINT*)&anArrayDimensions, nARRAY_DIMENSION_INDEX_MAX, 0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaAddArrayDimensionText_Add(void)
{
	anArrayDimensions[0] = 1;
	anArrayDimensions[1] = 2;
	anArrayDimensions[2] = 3;
	anArrayDimensions[3] = 4;
	anArrayDimensions[4] = 5;
	anArrayDimensions[5] = 6;

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddArrayDimensionText((UDINT*)&anArrayDimensions, 0, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x800F0000 , dwordOut); // = Bad_NothingToDo
	TEST_ASSERT_EQUAL_STRING("Test ", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddArrayDimensionText((UDINT*)&anArrayDimensions, 1, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 1", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddArrayDimensionText((UDINT*)&anArrayDimensions, 3, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 1;2;3", stringIn0);

	strcpy(stringIn0, "Test ");
	dwordOut = BrbUaAddArrayDimensionText((UDINT*)&anArrayDimensions, 6, stringIn0, sizeof(stringIn0));
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	TEST_ASSERT_EQUAL_STRING("Test 1;2;3;4;5;6", stringIn0);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 09:18:31Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaAddArrayDimensionText_NulPtr", BrbUaAddArrayDimensionText_NulPtr), 
	new_TestFixture("BrbUaAddArrayDimensionText_Add", BrbUaAddArrayDimensionText_Add), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaAddArrayDimensionText, "Set_BrbUaAddArrayDimensionText", 0, 0, fixtures, 0, 0, 0);


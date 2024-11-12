#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
_TEST BrbUaIncByteString_NulPtr(void)
{
	dwordOut = BrbUaIncByteString(0, 0);
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaIncByteString_Inc(void)
{
	memset(&byteStringIn, 1, sizeof(byteStringIn));
	dwordOut = BrbUaIncByteString((USINT*)&byteStringIn, 0);
	TEST_ASSERT_EQUAL_INT(0x803C0000, dwordOut); // = Bad_OutOfRange

	memset(&byteStringIn, 0, sizeof(byteStringIn));
	dwordOut = BrbUaIncByteString((USINT*)&byteStringIn, nBYTE_STRING_INDEX_MAX+1);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[0]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[1]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[2]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[3]);
	BRB_ASSERT_EQUAL_UDINT(1, (UDINT)byteStringIn[4]);

	dwordOut = BrbUaIncByteString((USINT*)&byteStringIn, nBYTE_STRING_INDEX_MAX+1);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[0]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[1]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[2]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[3]);
	BRB_ASSERT_EQUAL_UDINT(2, (UDINT)byteStringIn[4]);

	byteStringIn[0] = 0;
	byteStringIn[1] = 0;
	byteStringIn[2] = 0;
	byteStringIn[3] = 0;
	byteStringIn[4] = 255;
	dwordOut = BrbUaIncByteString((USINT*)&byteStringIn, nBYTE_STRING_INDEX_MAX+1);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[0]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[1]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[2]);
	BRB_ASSERT_EQUAL_UDINT(1, (UDINT)byteStringIn[3]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[4]);

	byteStringIn[0] = 0;
	byteStringIn[1] = 0;
	byteStringIn[2] = 0;
	byteStringIn[3] = 255;
	byteStringIn[4] = 255;
	dwordOut = BrbUaIncByteString((USINT*)&byteStringIn, nBYTE_STRING_INDEX_MAX+1);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[0]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[1]);
	BRB_ASSERT_EQUAL_UDINT(1, (UDINT)byteStringIn[2]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[3]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[4]);

	byteStringIn[0] = 0;
	byteStringIn[1] = 0;
	byteStringIn[2] = 255;
	byteStringIn[3] = 255;
	byteStringIn[4] = 255;
	dwordOut = BrbUaIncByteString((USINT*)&byteStringIn, nBYTE_STRING_INDEX_MAX+1);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[0]);
	BRB_ASSERT_EQUAL_UDINT(1, (UDINT)byteStringIn[1]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[2]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[3]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[4]);

	byteStringIn[0] = 0;
	byteStringIn[1] = 255;
	byteStringIn[2] = 255;
	byteStringIn[3] = 255;
	byteStringIn[4] = 255;
	dwordOut = BrbUaIncByteString((USINT*)&byteStringIn, nBYTE_STRING_INDEX_MAX+1);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_UDINT(1, (UDINT)byteStringIn[0]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[1]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[2]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[3]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[4]);

	byteStringIn[0] = 255;
	byteStringIn[1] = 255;
	byteStringIn[2] = 255;
	byteStringIn[3] = 255;
	byteStringIn[4] = 255;
	dwordOut = BrbUaIncByteString((USINT*)&byteStringIn, nBYTE_STRING_INDEX_MAX+1);
	TEST_ASSERT_EQUAL_INT(0xB00C0000, dwordOut); // = PlcOpen_BadElementCount
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[0]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[1]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[2]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[3]);
	BRB_ASSERT_EQUAL_UDINT(0, (UDINT)byteStringIn[4]);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 12:39:56Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaIncByteString_NulPtr", BrbUaIncByteString_NulPtr), 
	new_TestFixture("BrbUaIncByteString_Inc", BrbUaIncByteString_Inc), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaIncByteString, "Set_BrbUaIncByteString", 0, 0, fixtures, 0, 0, 0);


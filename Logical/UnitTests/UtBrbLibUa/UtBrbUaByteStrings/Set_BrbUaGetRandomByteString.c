#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
_TEST BrbUaGetRandomByteString_NulPtr(void)
{
	dwordOut = BrbUaGetRandomByteString(0, 0);
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaGetRandomByteString_Random(void)
{
	dwordOut = BrbUaGetRandomByteString((USINT*)&byteStringIn, 0);
	TEST_ASSERT_EQUAL_INT(0x803C0000, dwordOut); // = Bad_OutOfRange

	dwordOut = BrbUaGetRandomByteString((USINT*)&byteStringIn, nBYTE_STRING_INDEX_MAX+1);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-25 07:04:32Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaGetRandomByteString_NulPtr", BrbUaGetRandomByteString_NulPtr), 
	new_TestFixture("BrbUaGetRandomByteString_Random", BrbUaGetRandomByteString_Random), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaGetRandomByteString, "Set_BrbUaGetRandomByteString", 0, 0, fixtures, 0, 0, 0);


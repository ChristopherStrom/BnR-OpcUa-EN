#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
_TEST BrbUaGetRandomXmlElement_NulPtr(void)
{
	dwordOut = BrbUaGetRandomXmlElement(0);
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaGetRandomXmlElement_Status(void)
{
	dwordOut = BrbUaGetRandomXmlElement(&xmlElementIn);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-25 10:50:15Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaGetRandomXmlElement_NulPtr", BrbUaGetRandomXmlElement_NulPtr), 
	new_TestFixture("BrbUaGetRandomXmlElement_Status", BrbUaGetRandomXmlElement_Status), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaGetRandomXmlElement, "Set_BrbUaGetRandomXmlElement", 0, 0, fixtures, 0, 0, 0);


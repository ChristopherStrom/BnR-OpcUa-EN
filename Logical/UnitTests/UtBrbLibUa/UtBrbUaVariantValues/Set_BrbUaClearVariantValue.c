#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
_TEST BrbUaClearVariantValue_NulPtr(void)
{
	dwordOut = BrbUaClearVariantValue(0);
	TEST_ASSERT_EQUAL_INT(0x80460000, dwordOut); // = Bad_StructureMissing

	// Finished
	TEST_DONE;
}

_TEST BrbUaClearVariantValue_Clear(void)
{
	memset(&variantIn0, 1, sizeof(variantIn0));
	variantIn0.VariantType = UAVariantType_Byte;
	dwordOut = BrbUaClearVariantValue(&variantIn0);
	TEST_ASSERT_EQUAL_INT(0x00000000, dwordOut); // = Good
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Byte, (DINT)variantIn0.VariantType);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 10:55:13Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaClearVariantValue_NulPtr", BrbUaClearVariantValue_NulPtr), 
	new_TestFixture("BrbUaClearVariantValue_Clear", BrbUaClearVariantValue_Clear), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaClearVariantValue, "Set_BrbUaClearVariantValue", 0, 0, fixtures, 0, 0, 0);


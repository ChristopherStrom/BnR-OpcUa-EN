#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
_TEST BrbUaSrvDateTimeToDtStruct_NulPtr(void)
{
	uintOut = BrbUaSrvDateTimeToDtStruct(0, &srvDateTimeIn);
	TEST_ASSERT_EQUAL_INT(eBRB_ERR_NULL_POINTER, uintOut);

	uintOut = BrbUaSrvDateTimeToDtStruct(&dtStructIn, 0);
	TEST_ASSERT_EQUAL_INT(eBRB_ERR_NULL_POINTER, uintOut);

	// Finished
	TEST_DONE;
}

_TEST BrbUaSrvDateTimeToDtStruct_Convert(void)
{
	srvDateTimeIn.DateTime = BrbSetDt(2023, 1, 2, 3, 4, 5);
	srvDateTimeIn.NanoSeconds = 6007123;
	uintOut = BrbUaSrvDateTimeToDtStruct(&dtStructIn, &srvDateTimeIn);
	TEST_ASSERT_EQUAL_INT(eBRB_ERR_OK, uintOut);
	BRB_ASSERT_EQUAL_DTSTRUCT(2023, 1, 2, eBRB_WD_MONDAY, 3, 4, 5, 6, 7, &dtStructIn);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-25 07:49:47Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaSrvDateTimeToDtStruct_NulPtr", BrbUaSrvDateTimeToDtStruct_NulPtr), 
	new_TestFixture("BrbUaSrvDateTimeToDtStruct_Convert", BrbUaSrvDateTimeToDtStruct_Convert), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaSrvDateTimeToDtStruct, "Set_BrbUaSrvDateTimeToDtStruct", 0, 0, fixtures, 0, 0, 0);


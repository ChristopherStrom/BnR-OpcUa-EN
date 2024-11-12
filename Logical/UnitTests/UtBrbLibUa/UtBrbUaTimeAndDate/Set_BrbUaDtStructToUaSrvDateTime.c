#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
_TEST BrbUaDtStructToUaSrvDateTime_NulPtr(void)
{
	uintOut = BrbUaDtStructToUaSrvDateTime(0, &dtStructIn, 123);
	TEST_ASSERT_EQUAL_INT(eBRB_ERR_NULL_POINTER, uintOut);

	uintOut = BrbUaDtStructToUaSrvDateTime(&srvDateTimeIn, 0, 123);
	TEST_ASSERT_EQUAL_INT(eBRB_ERR_NULL_POINTER, uintOut);

	// Finished
	TEST_DONE;
}

_TEST BrbUaDtStructToUaSrvDateTime_Convert(void)
{
	dtStructIn.year = 2023;
	dtStructIn.month = 01;
	dtStructIn.day = 02;
	dtStructIn.hour = 03;
	dtStructIn.minute = 04;
	dtStructIn.second = 05;
	dtStructIn.millisec = 006;
	dtStructIn.microsec = 007;
	uintOut = BrbUaDtStructToUaSrvDateTime(&srvDateTimeIn, &dtStructIn, 123);
	TEST_ASSERT_EQUAL_INT(eBRB_ERR_OK, uintOut);
	TEST_ASSERT_EQUAL_INT(1672628645, srvDateTimeIn.DateTime);
	TEST_ASSERT_EQUAL_INT(6007123, srvDateTimeIn.NanoSeconds);

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
	new_TestFixture("BrbUaDtStructToUaSrvDateTime_NulPtr", BrbUaDtStructToUaSrvDateTime_NulPtr), 
	new_TestFixture("BrbUaDtStructToUaSrvDateTime_Convert", BrbUaDtStructToUaSrvDateTime_Convert), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaDtStructToUaSrvDateTime, "Set_BrbUaDtStructToUaSrvDateTime", 0, 0, fixtures, 0, 0, 0);


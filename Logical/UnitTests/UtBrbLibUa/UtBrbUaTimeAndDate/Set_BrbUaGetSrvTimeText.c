#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
_TEST BrbUaGetSrvTimeText_NulPtr(void)
{
	uintOut = BrbUaGetSrvTimeText(0, stringIn0, sizeof(stringIn0), 0, stringIn1);
	TEST_ASSERT_EQUAL_INT(eBRB_ERR_NULL_POINTER, uintOut);

	uintOut = BrbUaGetSrvTimeText(&srvDateTimeIn, 0, sizeof(stringIn0), 0, stringIn1);
	TEST_ASSERT_EQUAL_INT(eBRB_ERR_NULL_POINTER, uintOut);

	uintOut = BrbUaGetSrvTimeText(&srvDateTimeIn, stringIn0, 0, 0, stringIn1);
	TEST_ASSERT_EQUAL_INT(eBRB_ERR_INVALID_PARAMETER , uintOut);

	uintOut = BrbUaGetSrvTimeText(&srvDateTimeIn, stringIn0, sizeof(stringIn0), 0, 0);
	TEST_ASSERT_EQUAL_INT(eBRB_ERR_NULL_POINTER, uintOut);

	// Finished
	TEST_DONE;
}

_TEST BrbUaGetSrvTimeText_Get(void)
{
	srvDateTimeIn.DateTime = BrbSetDt(2023, 1, 2, 3, 4, 5);
	srvDateTimeIn.NanoSeconds = 6007823;
	strcpy(stringIn1, "yyyy-mm-dd hh:MM:ss:milms:micus:nanns");
	uintOut = BrbUaGetSrvTimeText(&srvDateTimeIn, stringIn0, sizeof(stringIn0), 0, stringIn1);
	TEST_ASSERT_EQUAL_INT(eBRB_ERR_OK, uintOut);
	TEST_ASSERT_EQUAL_STRING("2023-01-02 03:04:05:006ms:007us:823ns", stringIn0);

	srvDateTimeIn.DateTime = BrbSetDt(2023, 1, 2, 3, 4, 5);
	srvDateTimeIn.NanoSeconds = 6007823;
	strcpy(stringIn1, "yyyy-mm-dd hh:MM:ss:milms:micus:nanns");
	uintOut = BrbUaGetSrvTimeText(&srvDateTimeIn, stringIn0, sizeof(stringIn0), 60, stringIn1);
	TEST_ASSERT_EQUAL_INT(eBRB_ERR_OK, uintOut);
	TEST_ASSERT_EQUAL_STRING("2023-01-02 04:04:05:006ms:007us:823ns", stringIn0);

	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-25 07:55:27Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaGetSrvTimeText_NulPtr", BrbUaGetSrvTimeText_NulPtr), 
	new_TestFixture("BrbUaGetSrvTimeText_Get", BrbUaGetSrvTimeText_Get), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaGetSrvTimeText, "Set_BrbUaGetSrvTimeText", 0, 0, fixtures, 0, 0, 0);


#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

_TEST BrbUaGetAttributeIdDatatype_Get(void)
{

	varianTypeOut = BrbUaGetAttributeIdDatatype(UAAI_Default);
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Null, (DINT)varianTypeOut);
	
	varianTypeOut = BrbUaGetAttributeIdDatatype(UAAI_NodeId);
	BRB_ASSERT_EQUAL_DINT(UAVariantType_NodeId, (DINT)varianTypeOut);
	
	varianTypeOut = BrbUaGetAttributeIdDatatype(UAAI_UserExecutable);
	BRB_ASSERT_EQUAL_DINT(UAVariantType_Boolean, (DINT)varianTypeOut);
	
	// Finished
	TEST_DONE;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2023-04-20 08:53:32Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbUaGetAttributeIdDatatype_Get", BrbUaGetAttributeIdDatatype_Get), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbUaGetAttributeIdDatatype, "Set_BrbUaGetAttributeIdDatatype", 0, 0, fixtures, 0, 0, 0);


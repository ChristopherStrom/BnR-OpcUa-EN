/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (List of TestSets).
LastUpdated: 2023-04-25 10:34:46Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
#include "UnitTest.h"



UNITTEST_TESTSET_DECLARATION  Set_BrbUaDtStructToUaSrvDateTime;
UNITTEST_TESTSET_DECLARATION  Set_BrbUaSrvDateTimeToDtStruct;
UNITTEST_TESTSET_DECLARATION  Set_BrbUaGetSrvTimeText;
UNITTEST_TESTSET_DECLARATION  Set_BrbUaGetRandomTimeZone;



UNITTEST_TESTSET_FIXTURES(utTestSets)
{
	new_TestSet(Set_BrbUaDtStructToUaSrvDateTime),
	new_TestSet(Set_BrbUaSrvDateTimeToDtStruct),
	new_TestSet(Set_BrbUaGetSrvTimeText),
	new_TestSet(Set_BrbUaGetRandomTimeZone),
};
UNTITTEST_TESTSET_HANDLER();


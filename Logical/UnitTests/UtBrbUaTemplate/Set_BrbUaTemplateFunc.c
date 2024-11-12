#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include "BrbAsserts.h"
#include <string.h>

_TEST BrbXXX(void)
{
	// Init
	//memset(&xxx, 0, sizeof(xxx));
	//strcpy(stringIn0, "");
	
	// Call
	uintOut0 = 0;//BrbXXX();
	
	// Assert
	//TEST_ASSERT_EQUAL_INT(eBRB_ERR_NULL_POINTER, uintOut0);
	//TEST_ASSERT_EQUAL_STRING("", stringIn0);

	// Finished
	TEST_DONE;
}

/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2021-05-03 06:15:16Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("BrbXXX", BrbXXX), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_BrbTemplateFunc, "Set_BrbTemplateFunc", 0, 0, fixtures, 0, 0, 0);


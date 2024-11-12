/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbAsserts
 * File: Equal_Udint.h
 * Author: Rainer Niedermeier
 *******************************************************************/

#include <bur/plctypes.h>
#include "UnitTest.h"
#include "AsTime.h" // NOLINT(clang-diagnostic-nonportable-system-include-path)

#ifdef __cplusplus
extern "C"
{
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*, readability-avoid-const-params-in-decls)

/* Dummies for smart edit autocompletion.
See below for the real macros used by the compiler  */
#ifdef _SMART_EDIT_DUMMY_
	/* Returns true if they are equal. */
	BOOL BRB_ASSERT_EQUAL_DTSTRUCT(const UINT expectedYear, const USINT expectedMonth, const USINT expectedDay, const USINT expectedWeekday, const USINT expectedHour, const USINT expectedMinute, const USINT expectedSecond, const USINT expectedMilliSecond, const USINT expectedMicroSecond, const DTStructure* actual);
#endif

/* Prototyping of functions.
These declaration of functions are used by the compiler to check number and type of arguments. */
BOOL brb_assertEqualDtStruct(const UINT expectedYear, const USINT expectedMonth, const USINT expectedDay, const USINT expectedWeekday, const USINT expectedHour, const USINT expectedMinute, const USINT expectedSecond, const UINT expectedMilliSecond, const UINT expectedMicroSecond, const DTStructure* actual, unsigned long line, const char *file);

/* Macros used in the test implementation.
The macro passes the location information to the implemented assert. */
#define BRB_ASSERT_EQUAL_DTSTRUCT(expectedYear, expectedMonth, expectedDay, expectedWeekday, expectedHour, expectedMinute, expectedSecond, expectedMilliSecond, expectedMicroSecond, actual) brb_assertEqualDtStruct(expectedYear, expectedMonth, expectedDay, expectedWeekday, expectedHour, expectedMinute, expectedSecond, expectedMilliSecond, expectedMicroSecond, actual, (unsigned long) __LINE__, __FILE__)

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*, readability-avoid-const-params-in-decls)

#ifdef __cplusplus
};
#endif


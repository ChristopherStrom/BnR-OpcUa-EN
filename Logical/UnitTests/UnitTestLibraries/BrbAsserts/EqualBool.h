/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbAsserts
 * File: EqualBool.c
 * Author: Rainer Niedermeier
 *******************************************************************/

#include <bur/plctypes.h>
#include "UnitTest.h"

#ifdef __cplusplus
extern "C"
{
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*, readability-avoid-const-params-in-decls)

/* Dummies for smart edit autocompletion.
See below for the real macros used by the compiler  */
#ifdef _SMART_EDIT_DUMMY_
	/* Returns true if they are equal. */
	BOOL BRB_ASSERT_EQUAL_BOOL(const BOOL expected, const BOOL actual);
#endif

/* Prototyping of functions.
These declaration of functions are used by the compiler to check number and type of arguments. */
BOOL brb_assertEqualBool(const BOOL expected, const BOOL actual, unsigned long line, const char *file);

/* Macros used in the test implementation.
The macro passes the location information to the implemented assert. */
#define BRB_ASSERT_EQUAL_BOOL(expected, actual) brb_assertEqualBool(expected, actual, (unsigned long) __LINE__, __FILE__)

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*, readability-avoid-const-params-in-decls)

#ifdef __cplusplus
};
#endif


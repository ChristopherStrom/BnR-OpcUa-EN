/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbAsserts
 * File: EqualBool.c
 * Author: Rainer Niedermeier
 *******************************************************************/

#include <bur/plctypes.h>
#include "BrbAsserts.h"
#include "AsBrStr.h"
#include "BrbLib.h"

#define TRUE 1
#define FALSE 0

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
BOOL brb_assertEqualBool(const BOOL expected, const BOOL actual,
	unsigned long line, const char *file)
{
	STRING buffer[100];
	STRING numbuf[15];
	BOOL result = TRUE;
	if(expected == actual)
	{
		addPassed("", line, file);
	}
	else
	{
		brsstrcpy((unsigned long) buffer, (unsigned long) "expected bool ");
		brsitoa((DINT)expected, (UDINT)&numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) " was ");
		brsitoa((DINT)actual, (UDINT)&numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		addFailure(buffer, line, file);
		result = FALSE;
	}
	return result;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbAsserts
 * File: Equal_Udint.c
 * Author: Rainer Niedermeier
 *******************************************************************/

#include <bur/plctypes.h>
#include "AsBrStr.h"
#include "BrbLib.h"
#include "WithinUdint.h"

#define TRUE 1
#define FALSE 0

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
BOOL brb_assertWithinUdint(const UDINT min, const UDINT max, const UDINT actual,
                         		unsigned long line, const char *file)
{
	STRING buffer[100];
	STRING numbuf[15];
	BOOL result = TRUE;
	if(actual >= min && actual <= max)
	{
		addPassed("", line, file);
	}
	else
	{
		brsstrcpy((unsigned long) buffer, (unsigned long) "expected udint ");
		BrbUdintToAscii(actual, numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) " was outside range (min=");
		BrbUdintToAscii(min, numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) ", max=");
		BrbUdintToAscii(max, numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) ")");
		addFailure(buffer, line, file);
		result = FALSE;
	}
	return result;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

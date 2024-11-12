/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbAsserts
 * File: StringEndContent.c
 * Author: Rainer Niedermeier
 *******************************************************************/

#include <bur/plctypes.h>
#include "AsBrStr.h"
#include "BrbLib.h"
#include "WithinDint.h"

#define TRUE 1
#define FALSE 0

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
BOOL brb_assertStringEndContent(const UDINT mem, const USINT content, const UDINT size, const UDINT start,
                         		unsigned long line, const char *file)
{
	STRING buffer[100];
	STRING numbuf[15];
	BOOL result = TRUE;
	UDINT index = 0;
	for(index=0; index<size; index++)
	{
		if(index>=start)
		{
			USINT* pointer = ((USINT*)mem) + index;
			USINT value = *pointer;
			if(value != content)
			{
				brsstrcpy((unsigned long) buffer, (unsigned long) "expected string end content [");
				brsitoa((int)index, (unsigned long)numbuf);
				brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
				brsstrcat((unsigned long) buffer, (unsigned long) "] is ");
				brsitoa((int)value, (unsigned long)numbuf);
				brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
				brsstrcat((unsigned long) buffer, (unsigned long) ", not ");
				brsitoa((int)content, (unsigned long)numbuf);
				brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
				addFailure(buffer, line, file);
				result = FALSE;
			}
		}
	}
	if(result == TRUE)
	{
		addPassed("", line, file);
	}
	return result;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

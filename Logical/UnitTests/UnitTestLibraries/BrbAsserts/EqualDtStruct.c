/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbAsserts
 * File: Equal_Udint.c
 * Author: Rainer Niedermeier
 *******************************************************************/

#include <bur/plctypes.h>
#include "AsBrStr.h"
#include "EqualDtStruct.h"

#define TRUE 1
#define FALSE 0

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)
BOOL brb_assertEqualDtStruct(const UINT expectedYear, const USINT expectedMonth, const USINT expectedDay, const USINT expectedWeekday, 
														const USINT expectedHour, const USINT expectedMinute, const USINT expectedSecond, 
														const UINT expectedMilliSecond, const UINT expectedMicroSecond,
														const DTStructure* actual,
                         		unsigned long line, const char *file)
{
	STRING buffer[100];
	STRING numbuf[15];
	BOOL result = TRUE;
	// year
	if(expectedYear == actual->year)
	{
		addPassed("", line, file);
	}
	else
	{
		brsstrcpy((unsigned long) buffer, (unsigned long) "expected year ");
		brsitoa((int)expectedYear, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) " was ");
		brsitoa((int)actual->year, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		addFailure(buffer, line, file);
		result = FALSE;
	}
	// month
	if(expectedMonth == actual->month)
	{
		addPassed("", line, file);
	}
	else
	{
		brsstrcpy((unsigned long) buffer, (unsigned long) "expected month ");
		brsitoa((int)expectedMonth, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) " was ");
		brsitoa((int)actual->month, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		addFailure(buffer, line, file);
		result = FALSE;
	}
	// day
	if(expectedDay == actual->day)
	{
		addPassed("", line, file);
	}
	else
	{
		brsstrcpy((unsigned long) buffer, (unsigned long) "expected day ");
		brsitoa((int)expectedDay, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) " was ");
		brsitoa((int)actual->day, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		addFailure(buffer, line, file);
		result = FALSE;
	}
	// weekday
	if(expectedWeekday == actual->wday)
	{
		addPassed("", line, file);
	}
	else
	{
		brsstrcpy((unsigned long) buffer, (unsigned long) "expected weekday ");
		brsitoa((int)expectedWeekday, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) " was ");
		brsitoa((int)actual->wday, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		addFailure(buffer, line, file);
		result = FALSE;
	}
	// hour
	if(expectedHour == actual->hour)
	{
		addPassed("", line, file);
	}
	else
	{
		brsstrcpy((unsigned long) buffer, (unsigned long) "expected hour ");
		brsitoa((int)expectedHour, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) " was ");
		brsitoa((int)actual->hour, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		addFailure(buffer, line, file);
		result = FALSE;
	}
	// minute
	if(expectedMinute == actual->minute)
	{
		addPassed("", line, file);
	}
	else
	{
		brsstrcpy((unsigned long) buffer, (unsigned long) "expected minute ");
		brsitoa((int)expectedMinute, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) " was ");
		brsitoa((int)actual->minute, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		addFailure(buffer, line, file);
		result = FALSE;
	}
	// second
	if(expectedSecond == actual->second)
	{
		addPassed("", line, file);
	}
	else
	{
		brsstrcpy((unsigned long) buffer, (unsigned long) "expected second ");
		brsitoa((int)expectedSecond, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) " was ");
		brsitoa((int)actual->second, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		addFailure(buffer, line, file);
		result = FALSE;
	}
	// millisecond
	if(expectedMilliSecond == actual->millisec)
	{
		addPassed("", line, file);
	}
	else
	{
		brsstrcpy((unsigned long) buffer, (unsigned long) "expected millisecond ");
		brsitoa((int)expectedMilliSecond, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) " was ");
		brsitoa((int)actual->millisec, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		addFailure(buffer, line, file);
		result = FALSE;
	}
	// microsecond
	if(expectedMicroSecond == actual->microsec)
	{
		addPassed("", line, file);
	}
	else
	{
		brsstrcpy((unsigned long) buffer, (unsigned long) "expected microsecond ");
		brsitoa((int)expectedMicroSecond, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) " was ");
		brsitoa((int)actual->microsec, (unsigned long)numbuf);
		brsstrcat((unsigned long) buffer, (unsigned long) numbuf);
		addFailure(buffer, line, file);
		result = FALSE;
	}
	return result;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

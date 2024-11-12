/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbSetTimespan.c
 * Author: niedermeierr
 * Created: May 18, 2021
 ********************************************************************
 * Implementation of library BrbLib
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLib.h"

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Setzt eine TIME-Zeitspanne */
plctime BrbSetTimespan(signed char nSign, unsigned long nDays, unsigned long nHours, unsigned long nMinutes, unsigned long nSeconds, unsigned long nMilliseconds)
{
	TIME tTime = nBRB_DINT_MAX; // Bei Überschreitung positiven Höchstwert zurückgeben
	UDINT nTime = 0;
	nTime += nMilliseconds;
	nTime += nSeconds * (DINT)nBRB_MILLISECONDS_PER_SECOND;
	nTime += nMinutes * (DINT)nBRB_SECONDS_PER_MINUTE * (DINT)nBRB_MILLISECONDS_PER_SECOND;
	nTime += nHours * (DINT)nBRB_MINUTES_PER_HOUR * (DINT)nBRB_SECONDS_PER_MINUTE * (DINT)nBRB_MILLISECONDS_PER_SECOND;
	nTime += nDays * (DINT)nBRB_HOURS_PER_DAY * (DINT)nBRB_MINUTES_PER_HOUR * (DINT)nBRB_SECONDS_PER_MINUTE * (DINT)nBRB_MILLISECONDS_PER_SECOND;
	if(nSign >= 0)
	{
		if(nTime <= (UDINT)nBRB_DINT_MAX)
		{
			tTime = (DINT)nTime;
		}
	}
	else
	{
		if(nTime <= (UDINT)nBRB_DINT_MAX)
		{
			LREAL rTime = (LREAL)nTime * -1.0;
			tTime = (DINT)rTime;
		}
		else
		{
			tTime = (TIME)(-2147483647 - 1);	// Bei Unterschreitung negativen Höchstwert zurückgeben
		}
	}
	return tTime;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

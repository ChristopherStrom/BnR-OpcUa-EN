/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbGetTimeTextMs.c
 * Author: niedermeierr
 * Created: April 29, 2016
 ********************************************************************
 * Implementation of library BrbLib
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLib.h"
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Gibt die angebenene Millisekunden-Zeit als Text zurück */
unsigned short BrbGetTimeTextMs(signed long nMilliseconds, plcstring* pText, unsigned long nTextSize, plcstring* pFormat, plcbit bClip) // NOLINT(readability-function-cognitive-complexity)
{
	// Prüfung der Parameter
	if(pText == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	if(nTextSize == 0)
	{
		return eBRB_ERR_INVALID_PARAMETER;
	}
	if(pFormat == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	// Text ermitteln
	BrbStringCopy(pText, pFormat, nTextSize);
	STRING sItoA[20];
	memset((USINT*)sItoA, 0, sizeof(sItoA));
	if(BrbStringGetAdrOf(pText, "dd", 0) != 0)
	{
		DINT nDays = nMilliseconds / (DINT)nBRB_MILLISECONDS_PER_DAY;
		nMilliseconds -= nDays * (DINT)nBRB_MILLISECONDS_PER_DAY;
		brsitoa(nDays, (UDINT)&sItoA);
		if(nDays < 10)
		{
			BrbStringInsert(sItoA, 0, "0");
		}
		BrbStringReplace(pText, "dd", sItoA);
	}
	else if(BrbStringGetAdrOf(pText, "d", 0) != 0)
	{
		DINT nDays = nMilliseconds / (DINT)nBRB_MILLISECONDS_PER_DAY;
		nMilliseconds -= nDays * (DINT)nBRB_MILLISECONDS_PER_DAY;
		brsitoa(nDays, (UDINT)&sItoA);
		BrbStringReplace(pText, "d", sItoA);
	}
	else if(bClip == 1)
	{
		DINT nDays = nMilliseconds / (DINT)nBRB_MILLISECONDS_PER_DAY;
		nMilliseconds -= nDays * (DINT)nBRB_MILLISECONDS_PER_DAY;
	}
	if(BrbStringGetAdrOf(pText, "hh", 0) != 0)
	{
		DINT nHours = nMilliseconds / (DINT)nBRB_MILLISECONDS_PER_HOUR;
		nMilliseconds -= nHours * (DINT)nBRB_MILLISECONDS_PER_HOUR;
		brsitoa(nHours, (UDINT)&sItoA);
		if(nHours < 10)
		{
			BrbStringInsert(sItoA, 0, "0");
		}
		BrbStringReplace(pText, "hh", sItoA);
	}
	else if(BrbStringGetAdrOf(pText, "h", 0) != 0)
	{
		DINT nHours = nMilliseconds / (DINT)nBRB_MILLISECONDS_PER_HOUR;
		nMilliseconds -= nHours * (DINT)nBRB_MILLISECONDS_PER_HOUR;
		brsitoa(nHours, (UDINT)&sItoA);
		BrbStringReplace(pText, "h", sItoA);
	}
	else if(bClip == 1)
	{
		DINT nHours = nMilliseconds / (DINT)nBRB_MILLISECONDS_PER_HOUR;
		nMilliseconds -= nHours * (DINT)nBRB_MILLISECONDS_PER_HOUR;
	}
	if(BrbStringGetAdrOf(pText, "MM", 0) != 0)
	{
		DINT nMinutes = nMilliseconds / (DINT)nBRB_MILLISECONDS_PER_MINUTE;
		nMilliseconds -= nMinutes * (DINT)nBRB_MILLISECONDS_PER_MINUTE;
		brsitoa(nMinutes, (UDINT)&sItoA);
		if(nMinutes < 10)
		{
			BrbStringInsert(sItoA, 0, "0");
		}
		BrbStringReplace(pText, "MM", sItoA);
	}
	else if(BrbStringGetAdrOf(pText, "M", 0) != 0)
	{
		DINT nMinutes = nMilliseconds / (DINT)nBRB_MILLISECONDS_PER_MINUTE;
		nMilliseconds -= nMinutes * (DINT)nBRB_MILLISECONDS_PER_MINUTE;
		brsitoa(nMinutes, (UDINT)&sItoA);
		BrbStringReplace(pText, "M", sItoA);
	}
	else if(bClip == 1)
	{
		DINT nMinutes = nMilliseconds / (DINT)nBRB_MILLISECONDS_PER_MINUTE;
		nMilliseconds -= nMinutes * (DINT)nBRB_MILLISECONDS_PER_MINUTE;
	}
	if(BrbStringGetAdrOf(pText, "ss", 0) != 0)
	{
		DINT nSeconds = nMilliseconds / (DINT)nBRB_MILLISECONDS_PER_SECOND;
		nMilliseconds -= nSeconds * (DINT)nBRB_MILLISECONDS_PER_SECOND;
		brsitoa(nSeconds, (UDINT)&sItoA);
		if(nSeconds < 10)
		{
			BrbStringInsert(sItoA, 0, "0");
		}
		BrbStringReplace(pText, "ss", sItoA);
	}
	else if(BrbStringGetAdrOf(pText, "s", 0) != 0)
	{
		DINT nSeconds = nMilliseconds / (DINT)nBRB_MILLISECONDS_PER_SECOND;
		nMilliseconds -= nSeconds * (DINT)nBRB_MILLISECONDS_PER_SECOND;
		brsitoa((DINT)nSeconds, (UDINT)&sItoA);
		BrbStringReplace(pText, "s", sItoA);
	}
	else if(bClip == 1)
	{
		DINT nSeconds = nMilliseconds / (DINT)nBRB_MILLISECONDS_PER_SECOND;
		nMilliseconds -= nSeconds * (DINT)nBRB_MILLISECONDS_PER_SECOND;
	}
	if(BrbStringGetAdrOf(pText, "mil", 0) != 0)
	{
		brsitoa(nMilliseconds, (UDINT)&sItoA);
		if(nMilliseconds < 10)
		{
			BrbStringInsert(sItoA, 0, "00");
		}
		else if(nMilliseconds < 100)
		{
			BrbStringInsert(sItoA, 0, "0");
		}
		BrbStringReplace(pText, "mil", sItoA);
	}
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

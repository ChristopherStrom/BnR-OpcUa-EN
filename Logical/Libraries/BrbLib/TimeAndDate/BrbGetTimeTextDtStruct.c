/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbGetTimeTextDtStruct.c
 * Author: niedermeierr
 * Created: June 11, 2013
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

/* Gibt die angegebene DtStruct-Zeit als Text zurück */
unsigned short BrbGetTimeTextDtStruct(struct DTStructure* pTime, plcstring* pText, unsigned long nTextSize, plcstring* pFormat)
{
	// Prüfung der Parameter
	if(pTime == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
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
	RTCtime_typ RtcTime;
	RtcTime.year = pTime->year;
	RtcTime.month = pTime->month;
	RtcTime.day = pTime->day;
	RtcTime.hour = pTime->hour;
	RtcTime.minute = pTime->minute;
	RtcTime.second = pTime->second;
	RtcTime.millisec = pTime->millisec;
	RtcTime.microsec = pTime->microsec;
	return BrbGetTimeText(&RtcTime, pText, nTextSize, pFormat);
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbStopStopWatch.c
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
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Stoppt eine Stoppuhr */
unsigned long BrbStopStopWatch(struct BrbStopWatch_TYP* pStopWatch)
{
	// Stoppuhr stoppen
	pStopWatch->tStopTime = clock_ms();
	pStopWatch->nTimeDiff = DiffT(pStopWatch->tStopTime, pStopWatch->tStartTime);
	memset(pStopWatch->sTimeDiff, 0, sizeof(pStopWatch->sTimeDiff));
	TIMEStructure TimeDiff;
	TIME_TO_TIMEStructure((TIME)pStopWatch->nTimeDiff, (UDINT)&TimeDiff);
	STRING sItoA[20];
	memset(sItoA, 0, sizeof(sItoA));
	if(TimeDiff.day < 10)
	{
		BrbStringCat((STRING*)pStopWatch->sTimeDiff, "0", sizeof(pStopWatch->sTimeDiff));
	}
	brsitoa((DINT)TimeDiff.day, (UDINT)&sItoA);
	BrbStringCat((STRING*)pStopWatch->sTimeDiff, sItoA, sizeof(pStopWatch->sTimeDiff));
	BrbStringCat((STRING*)pStopWatch->sTimeDiff, "d_", sizeof(pStopWatch->sTimeDiff));
	if(TimeDiff.hour < 10)
	{
		BrbStringCat((STRING*)pStopWatch->sTimeDiff, "0", sizeof(pStopWatch->sTimeDiff));
	}
	brsitoa((DINT)TimeDiff.hour, (UDINT)&sItoA);
	BrbStringCat((STRING*)pStopWatch->sTimeDiff, sItoA, sizeof(pStopWatch->sTimeDiff));
	BrbStringCat((STRING*)pStopWatch->sTimeDiff, "h_", sizeof(pStopWatch->sTimeDiff));
	if(TimeDiff.minute < 10)
	{
		BrbStringCat((STRING*)pStopWatch->sTimeDiff, "0", sizeof(pStopWatch->sTimeDiff));
	}
	brsitoa((DINT)TimeDiff.minute, (UDINT)&sItoA);
	BrbStringCat((STRING*)pStopWatch->sTimeDiff, sItoA, sizeof(pStopWatch->sTimeDiff));
	BrbStringCat((STRING*)pStopWatch->sTimeDiff, "m_", sizeof(pStopWatch->sTimeDiff));
	if(TimeDiff.second < 10)
	{
		BrbStringCat((STRING*)pStopWatch->sTimeDiff, "0", sizeof(pStopWatch->sTimeDiff));
	}
	brsitoa((DINT)TimeDiff.second, (UDINT)&sItoA);
	BrbStringCat((STRING*)pStopWatch->sTimeDiff, sItoA, sizeof(pStopWatch->sTimeDiff));
	BrbStringCat((STRING*)pStopWatch->sTimeDiff, "s_", sizeof(pStopWatch->sTimeDiff));
	if(TimeDiff.millisec < 10)
	{
		BrbStringCat((STRING*)pStopWatch->sTimeDiff, "00", sizeof(pStopWatch->sTimeDiff));
	}
	else if(TimeDiff.millisec < 100)
	{
		BrbStringCat((STRING*)pStopWatch->sTimeDiff, "0", sizeof(pStopWatch->sTimeDiff));
	}
	brsitoa((DINT)TimeDiff.millisec, (UDINT)&sItoA);
	BrbStringCat((STRING*)pStopWatch->sTimeDiff, sItoA, sizeof(pStopWatch->sTimeDiff));
	BrbStringCat((STRING*)pStopWatch->sTimeDiff, "ms", sizeof(pStopWatch->sTimeDiff));
	return pStopWatch->nTimeDiff;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

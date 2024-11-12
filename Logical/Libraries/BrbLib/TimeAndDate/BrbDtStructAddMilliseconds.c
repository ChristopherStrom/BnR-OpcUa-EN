/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbDtStructAddMilliseconds.c
 * Author: niedermeierr
 * Created: December 11, 2013
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

/* Addiert zu einer DTStructure die angegebenen Millisekunden */
plcdt BrbDtStructAddMilliseconds(struct DTStructure* pDtStruct, signed long nMilliseconds)
{
	// Prüfung der Parameter
	if(pDtStruct == 0)
	{
		return 0;
	}
	// Addieren
	DINT nMilliSecondsBefore = (DINT)pDtStruct->millisec;
	UINT nMicroSecondsBefore = pDtStruct->microsec;
	DATE_AND_TIME dtTime = DTStructure_TO_DT((UDINT)pDtStruct);
	DINT nSeconds = (DINT)((REAL)nMilliseconds / (REAL)nBRB_MILLISECONDS_PER_SECOND);
	if(nSeconds < 0)
	{
		dtTime = dtTime - (UDINT)(nSeconds * -1);
	}
	else
	{
		dtTime = dtTime + (UDINT)nSeconds;
	}
	DINT nMillisecondsLeft = nMilliseconds - nSeconds * (DINT)nBRB_MILLISECONDS_PER_SECOND;
	if(nMilliSecondsBefore + nMillisecondsLeft >= (DINT)nBRB_MILLISECONDS_PER_SECOND)
	{
		dtTime += 1;
		nMillisecondsLeft -= (DINT)nBRB_MILLISECONDS_PER_SECOND;
	}
	else if(nMilliSecondsBefore + nMillisecondsLeft < 0)
	{
		dtTime -= 1;
		nMillisecondsLeft += (DINT)nBRB_MILLISECONDS_PER_SECOND;
	}
	DT_TO_DTStructure(dtTime, (UDINT)pDtStruct);
	pDtStruct->millisec = (UINT)(nMilliSecondsBefore + nMillisecondsLeft);
	pDtStruct->microsec = nMicroSecondsBefore;
	return dtTime;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

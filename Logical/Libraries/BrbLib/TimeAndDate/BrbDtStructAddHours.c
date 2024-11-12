/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbDtStructAddSeconds.c
 * Author: niedermeierr
 * Created: September 08, 2021
 ********************************************************************
 * Implementation of library BrbLib
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLib.h"
#include <AnsiCFunc.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Addiert zu einer DTStructure die angegebenen Sekunden */
plcdt BrbDtStructAddHours(struct DTStructure* pDtStruct, signed long nHours)
{
	// Prüfung der Parameter
	if(pDtStruct == 0)
	{
		return 0;
	}
	// Addieren
	UINT nMilliSecondsBefore = pDtStruct->millisec;
	UINT nMicroSecondsBefore = pDtStruct->microsec;
	DATE_AND_TIME dtTime = DTStructure_TO_DT((UDINT)pDtStruct);
	// Es müssen Sekunden addiert werden. Durch eine Multiplikation der Stunden mit 60s*60m = 3600s könnte der Bereich eines Dint nicht mehr ausreichen
	// Daher wird eine Schleife durchlaufen.
	UDINT nLoop = 0;
	if(nHours < 0)
	{
		for(nLoop=0; nLoop<(UDINT)abs(nHours); nLoop++)
		{
			dtTime = dtTime - nBRB_SECONDS_PER_HOUR;
		}
	}
	else
	{
		for(nLoop=0; nLoop<(UDINT)abs(nHours); nLoop++)
		{
			dtTime = dtTime + nBRB_SECONDS_PER_HOUR;
		}
	}
	DT_TO_DTStructure(dtTime, (UDINT)pDtStruct);
	pDtStruct->millisec = nMilliSecondsBefore;
	pDtStruct->microsec = nMicroSecondsBefore;
	return dtTime;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

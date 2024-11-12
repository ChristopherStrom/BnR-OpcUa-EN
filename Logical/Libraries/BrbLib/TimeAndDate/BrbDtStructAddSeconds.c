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

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Addiert zu einer DTStructure die angegebenen Sekunden */
plcdt BrbDtStructAddSeconds(struct DTStructure* pDtStruct, signed long nSeconds)
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
	if(nSeconds < 0)
	{
		dtTime = dtTime - (UDINT)(nSeconds * -1);
	}
	else
	{
		dtTime = dtTime + (UDINT)nSeconds;
	}
	DT_TO_DTStructure(dtTime, (UDINT)pDtStruct);
	pDtStruct->millisec = nMilliSecondsBefore;
	pDtStruct->microsec = nMicroSecondsBefore;
	return dtTime;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

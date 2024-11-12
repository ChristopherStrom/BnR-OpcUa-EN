/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbDtStructAddMillisecondsLReal.c
 * Author: niedermeierr
 * Created: September 10, 2021
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
plcdt BrbDtStructAddMillisecondsLReal(struct DTStructure* pDtStruct, double rMilliseconds)
{
	// Prüfung der Parameter
	if(pDtStruct == 0)
	{
		return 0;
	}
	// Addieren
	LREAL rDays = rMilliseconds / (LREAL)nBRB_MILLISECONDS_PER_DAY; // [ms/day]
	DINT nDays = (DINT)rDays; // Nachkomma-Stellen werden abgeschnitten
	BrbDtStructAddDays(pDtStruct, nDays);
	rMilliseconds -= (LREAL)nDays * (LREAL)nBRB_MILLISECONDS_PER_DAY;
	DINT nMilliseconds = (DINT)rMilliseconds;
	BrbDtStructAddMilliseconds(pDtStruct, nMilliseconds);
	DATE_AND_TIME dtTime = DTStructure_TO_DT((UDINT)pDtStruct);
	return dtTime;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

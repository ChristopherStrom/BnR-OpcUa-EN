/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbGetTimeDiffMsDtStruct.c
 * Author: niedermeierr
 * Created: February 13, 2017
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

/* Gibt die Zeit-Differenz zweier DtStruct-Zeiten in [ms] zurück */
signed long BrbGetTimeDiffMsDtStruct(struct DTStructure* pTimeStampBase, struct DTStructure* pTimeStampCompare)
{
	// Prüfung der Parameter
	if(pTimeStampBase == 0)
	{
		return 0;
	}
	if(pTimeStampCompare == 0)
	{
		return 0;
	}
	// Diff
	DINT nDiffMs = 0;
	DATE_AND_TIME dtTimeBase = DTStructure_TO_DT((UDINT)pTimeStampBase);
	DATE_AND_TIME dtTimeCompare = DTStructure_TO_DT((UDINT)pTimeStampCompare);
	UDINT nDiffS = 0;
	if(dtTimeBase >= dtTimeCompare)
	{
		nDiffS = DiffDT(dtTimeBase, dtTimeCompare);
		nDiffMs = (DINT)(pTimeStampCompare->millisec - pTimeStampBase->millisec);
		nDiffMs += (DINT)nDiffS * -(DINT)nBRB_MILLISECONDS_PER_SECOND;
	}
	else
	{
		nDiffS = DiffDT(dtTimeCompare, dtTimeBase);
		nDiffMs = (DINT)(pTimeStampCompare->millisec - pTimeStampBase->millisec);
		nDiffMs += (DINT)nDiffS * (DINT)nBRB_MILLISECONDS_PER_SECOND;
	}
	return nDiffMs;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbStringCutFromLastSeparator.c
 * Author: niedermeierr
 * Created: October 21, 2014
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

/* Schneidet die Zeichenfolge ab dem letzten Trennzeichen in einem Text ab */
unsigned long BrbStringCutFromLastSeparator(plcstring* pText, plcstring* pSeparator, plcstring* pCut)
{
	UDINT nResult = 0;
	UDINT nTextLen = strlen(pText);
	STRING* pSeparatorStart = BrbStringGetLastAdrOf(pText, pSeparator, nTextLen);
	if(pSeparatorStart != 0)
	{
		UDINT nCutIndex = (UDINT)(pSeparatorStart - pText);
		UDINT nCutLen = nTextLen - nCutIndex;
		BrbStringCut(pText, nCutIndex, nCutLen, pCut);
		nResult = nCutLen;
	}
	return nResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

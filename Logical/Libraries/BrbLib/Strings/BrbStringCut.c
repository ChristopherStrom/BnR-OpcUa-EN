/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbStringCut.c
 * Author: niedermeierr
 * Created: July 05, 2013
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

/* Schneidet eine Zeichenfolge aus einem Text heraus */
plcstring* BrbStringCut(plcstring* pText, unsigned long nCutIndex, unsigned long nCutLen, plcstring* pCut)
{
	STRING* pResult = 0;
	UDINT nTextLen = strlen(pText);
	if(nCutIndex+nCutLen > nTextLen)
	{
		nCutLen = nTextLen-nCutIndex;
	}
	UDINT nRestLen = nTextLen - nCutIndex - nCutLen + 1;
	if(pCut != 0)
	{
		// Herauszuschneidenden String kopieren
		memcpy(pCut, (pText + nCutIndex), nCutLen);
		*(pCut + nCutLen) = 0;
	}
	// Zeichen nach dem Cut nach vorne ziehen
	memmove((pText + nCutIndex), (pText + nCutIndex + nCutLen), nRestLen);
	pResult = pText + nCutIndex + nCutLen;
	return pResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbWcStringPadRight.c
 * Author: niedermeierr
 * Created: May 03, 2016
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

/* Füllt einen String auf der rechten Seite mit einem Füllzeichen auf eine bestimme Länge */
plcbit BrbWcStringPadRight(plcwstring* pText, plcwstring* pFillChar, unsigned long nLen)
{
	BOOL bResult = 0;
	UDINT nTextLen = brwcslen(pText);
	DINT nFillLen = (DINT)nLen - (DINT)nTextLen;
	UINT* pChar = (UINT*)pText + nTextLen;
	if(nFillLen > 0)
	{
		// Füllzeichen einsetzen
		while(pChar < (UINT*)(pText+nLen))
		{
			*pChar = *pFillChar;
			pChar++;
		}
		bResult = 1;
	}
	// Terminierung
	*pChar = 0;
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

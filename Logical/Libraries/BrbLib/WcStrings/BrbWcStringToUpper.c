/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbWcStringToUpper.c
 * Author: niedermeierr
 * Created: May 04, 2016
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

/* Konvertiert einen WcString zu Groﬂbuchstaben */
plcbit BrbWcStringToUpper(plcwstring* pText)
{
	BOOL bResult = 0;
	UDINT nTextLen = brwcslen(pText);
	UDINT nIndex = 0;
	UINT* pChar = 0;
	for(nIndex=0; nIndex<nTextLen; nIndex++)
	{
		pChar = (UINT*)(pText + nIndex);
		if(*pChar >= 97 && *pChar <= 122)
		{
			*pChar = *pChar - 32;
			bResult = 1;
		}
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

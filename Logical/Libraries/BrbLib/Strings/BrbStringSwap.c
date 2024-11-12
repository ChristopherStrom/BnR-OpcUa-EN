/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbStringSwap.c
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

/* Dreht die Reihenfolge der Zeichen in einem Text */
plcbit BrbStringSwap(plcstring* pText, plcstring* pSwapped, unsigned long nSwappedSize)
{
	BOOL bResult = 0;
	memset(pSwapped, 0, nSwappedSize);
	UDINT nIndex = 0;
	USINT* pCharText = 0;
	USINT* pCharSwapped = 0;
	UDINT nTextLen = strlen(pText);
	if(nTextLen <= nSwappedSize)
	{
		for(nIndex=0; nIndex<nTextLen; nIndex++)
		{
			pCharText = (USINT*)(pText + nIndex);
			pCharSwapped = (USINT*)(pSwapped + nTextLen - nIndex - 1);
			*pCharSwapped = *pCharText;
		}
		bResult = 1;
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

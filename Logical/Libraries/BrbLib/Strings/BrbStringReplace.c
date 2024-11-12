/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbStringReplace.c
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

/* Ersetzt eine Zeichenfolge in einem Text durch eine andere */
unsigned long BrbStringReplace(plcstring* pText, plcstring* pFind, plcstring* pReplace)
{
	UDINT nResult = 0;
	UDINT nTextLen = strlen(pText);
	UDINT nFindLen = strlen(pFind);
	UDINT nReplaceLen = strlen(pReplace);
	DINT nDiff = (DINT)nReplaceLen - (DINT)nFindLen;
	UDINT nCharIndex = 0;
	// Text von vorne nach hinten durchsuchen
	while(1==1)
	{
		// Textstelle vergleichen
		if(memcmp((pText + nCharIndex), pFind, nFindLen) == 0)
		{
			// Text gefunden
			if(nDiff > 0)
			{
				// Replace ist länger
				UDINT nRestLen = nTextLen - nCharIndex + 1;
				memmove((pText + nCharIndex + nDiff), (pText + nCharIndex), nRestLen);
				memcpy((pText + nCharIndex), pReplace, nReplaceLen);
				nTextLen += (UDINT)nDiff;
				nCharIndex += nReplaceLen;
				nResult += 1;
			}
			else if(nDiff < 0)
			{
				// Replace ist kürzer
				UDINT nRestLen = (UDINT)((DINT)nTextLen - (DINT)nCharIndex + nDiff + 1);
				memmove((pText + nCharIndex), (pText + nCharIndex - nDiff), nRestLen);
				memcpy((pText + nCharIndex), pReplace, nReplaceLen);
				nTextLen = (UDINT)((DINT)nTextLen + nDiff);
				nCharIndex += nReplaceLen;
				nResult += 1;
			}
			else
			{
				// Zeichenfolgen sind gleich lang
				memcpy((pText + nCharIndex), pReplace, nReplaceLen);
				nCharIndex += nReplaceLen;
				nResult += 1;
			}
		}
		else
		{
			nCharIndex += 1;
		}
		if(nCharIndex>=nTextLen)
		{
			break;
		}
	}
	return nResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

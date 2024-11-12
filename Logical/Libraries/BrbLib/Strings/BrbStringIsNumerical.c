/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbStringIsNumerical.c
 * Author: niedermeierr
 * Created: March 18, 2015
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

/* Gibt zur�ck, ob ein Text eine Nummer enth�lt */
plcbit BrbStringIsNumerical(plcstring* pText) // NOLINT(readability-function-cognitive-complexity)
{
	BOOL bResult = 1;
	UDINT nTextLen = strlen(pText);
	if(nTextLen == 0)
	{
		bResult = 0;
	}
	else
	{
		UDINT nIndex = 0;
		USINT* pChar = 0;
		UINT nCountSeparator = 0;
		DINT nIndexExp = -1;
		for(nIndex=0; nIndex<nTextLen; nIndex++)
		{
			pChar = (USINT*)(pText + nIndex);
			// NOLINTBEGIN(bugprone-branch-clone)
			if(*pChar == 43)
			{
				// Plus
				if(nIndex != 0 && nIndexExp != (DINT)nIndex-1)
				{
					// Nicht am Anfang oder nach "e"
					bResult = 0;
					break;
				}
			}
			else if(*pChar == 45)
			{
				// Minus
				if(nIndex != 0 && nIndexExp != (DINT)nIndex-1)
				{
					// Nicht am Anfang oder nach "e"
					bResult = 0;
					break;
				}
			}
			else if(*pChar == 44)
			{
				// Komma
				nCountSeparator++;
				if(nCountSeparator > 1)
				{
					// Mehr als 1 Separartor
					bResult = 0;
					break;
				}
			}
			else if(*pChar == 46)
			{
				// Punkt
				nCountSeparator++;
				if(nCountSeparator > 1)
				{
					// Mehr als 1 Separartor
					bResult = 0;
					break;
				}
			}
			else if(*pChar == 101)
			{
				// e
				if(nIndexExp == -1)
				{
					nIndexExp = (DINT)nIndex;
					if(nIndex >= nTextLen-1)
					{
						// Nach "e" folgt nichts
						bResult = 0;
						break;
					}
				}
				else
				{
					// Zweites "e"
					bResult = 0;
					break;
				}
			}
			else if(!(*pChar >= 48 && *pChar <= 57))
			{
				bResult = 0;
				break;
			}
			// NOLINTEND(bugprone-branch-clone)
		}
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

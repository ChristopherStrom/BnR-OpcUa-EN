/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbWcStringIsHex.c
 * Author: niedermeierr
 * Created: January 17, 2017
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

/* Gibt zurück, ob ein Text eine hexadezimale Nummer enthält */
plcbit BrbWcStringIsHex(plcwstring* pText, plcbit bLowCaseAllowed)
{
	BOOL bResult = 1;
	UDINT nTextLen = brwcslen(pText);
	if(nTextLen == 0)
	{
		bResult = 0;
	}
	else
	{
		UDINT nIndex = 0;
		UINT* pChar = 0;
		for(nIndex=0; nIndex<nTextLen; nIndex++)
		{
			pChar = (UINT*)(pText + nIndex);
			// NOLINTBEGIN(bugprone-branch-clone)
			if((*pChar >= 48 && *pChar <= 57)) // 0..9
			{
			}
			else if((*pChar >= 65 && *pChar <= 70)) // A..F
			{
			}
			else if((*pChar >= 97 && *pChar <= 102) && bLowCaseAllowed == 1) // a..f
			{
			}
			else
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

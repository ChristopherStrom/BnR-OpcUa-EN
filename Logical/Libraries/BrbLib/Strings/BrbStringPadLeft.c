/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbStringPadLeft.c
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

/* F�llt einen String auf der linken Seite mit einem F�llzeichen auf eine bestimme L�nge */
plcbit BrbStringPadLeft(plcstring* pText, plcstring* pFillChar, unsigned long nLen)
{
	BOOL bResult = 0;
	UDINT nTextLen = strlen(pText);
	DINT nFillLen = (DINT)nLen - (DINT)nTextLen;
	USINT* pChar = (USINT*)pText;
	if(nFillLen > 0)
	{
		// Text nach rechts schieben
		memmove(pText+nFillLen, pText, nTextLen+1);
		// F�llzeichen einsetzen
		while(pChar < (USINT*)(pText+nFillLen))
		{
			*pChar = (USINT)*pFillChar;
			pChar++;
		}
		bResult = 1;
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

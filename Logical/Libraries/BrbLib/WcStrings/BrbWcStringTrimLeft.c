/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbWcStringTrimLeft.c
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

/* Schneidet eine Zeichenfolge auf der linken Seite eines Textes heraus */
plcbit BrbWcStringTrimLeft(plcwstring* pText, plcwstring* pTrim)
{
	BOOL bResult = 0;
	UDINT nTrimLen = brwcslen(pTrim);
	BOOL bLeave = 0;
	do
	{
		if(BrbWcStringStartsWith(pText, pTrim) == 1)
		{
			BrbWcStringCut(pText, 0, nTrimLen, 0);
			bResult = 1;
		}
		else
		{
			bLeave = 1;
		}
	} while(bLeave == 0);
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

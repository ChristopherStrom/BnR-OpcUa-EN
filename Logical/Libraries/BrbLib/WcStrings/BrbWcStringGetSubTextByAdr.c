/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbWcStringGetSubTextByAdr.c
 * Author: niedermeierr
 * Created: May 02, 2016
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

/* Gibt eine Zeichenfolge innerhalb eines Textes zurück */
unsigned long BrbWcStringGetSubTextByAdr(plcwstring* pStart, plcwstring* pEnd, plcwstring* pSubText)
{
	UDINT nResult = 0;
	if(pEnd > pStart)
	{
		UDINT nLen = (UDINT)(pEnd - pStart);
		nResult = BrbWcStringGetSubTextByLen(pStart, nLen, pSubText);
	}
	return nResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbStringGetSubTextByAdr.c
 * Author: niedermeierr
 * Created: June 17, 2013
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
plcstring* BrbStringGetSubTextByAdr(plcstring* pStart, plcstring* pEnd, plcstring* pSubText)
{
	STRING* pResult = 0;
	if(pEnd > pStart)
	{
		UDINT nLen = (UDINT)pEnd - (UDINT)pStart;
		pResult = BrbStringGetSubTextByLen(pStart, nLen, pSubText);
	}
	return pResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

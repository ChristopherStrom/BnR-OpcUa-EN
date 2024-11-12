/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbXmlGetNextTag.c
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

/* Gibt die Adresse nach einem Xml-Tag zurück */
unsigned long BrbXmlGetNextTag(plcstring* pTag, unsigned long pStart, unsigned long pEnd)
{
	UDINT nResult = 0;
	// Start-Tag suchen
	STRING* pStartTagAdr = 0;
	if(pStart > 0 && pEnd > 0 && pEnd > pStart)
	{
		UDINT nSearchLen = pEnd - pStart;
		pStartTagAdr = BrbStringGetAdrOf((STRING*)pStart, pTag, nSearchLen);
		if(pStartTagAdr != 0)
		{
			// Start-Tag gefunden
			UDINT nStartTagLen = strlen(pTag);
			nResult = (UDINT)(pStartTagAdr + nStartTagLen);
		}
	}
	return nResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbWcStringGetAdrOf.c
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

/* Gibt die erste Adresse eines zu suchenden Textes zur�ck */
unsigned long BrbWcStringGetAdrOf(plcwstring* pText, plcwstring* pFind, unsigned long nTextLen)
{
	UDINT nResult = 0;
	// Wenn die L�nge bekannt ist, kann sie �bergeben werden
	// Damit entf�llt das Aufrufen von strlen, welches bei langen Texten Zeit braucht
	UDINT nLenText = nTextLen;
	if(nTextLen == 0)
	{
		nLenText = brwcslen(pText);
	}
	UDINT nByteLenFind = brwcslen(pFind) * 2;
	UDINT nCharIndex = 0;
	// Text von vorne nach hinten durchsuchen
	for(nCharIndex=0; nCharIndex<nLenText; nCharIndex++)
	{
		// Textstelle vergleichen
		if(memcmp((pText + nCharIndex), pFind, nByteLenFind) == 0)
		{
			// Text gefunden
			nResult = (UDINT)(pText + nCharIndex);
			break;
		}
	}
	return nResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

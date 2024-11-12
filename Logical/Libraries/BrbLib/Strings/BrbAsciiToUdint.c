/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbAsciiToUdint.c
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

/* Wandelt einen String zu einem UDINT-Wert */
unsigned long BrbAsciiToUdint(plcstring* pText)
{
	UDINT nFuncRetVal = 0;
	UDINT nCharCount = strlen((STRING*)pText )-1;
	STRING* pChar = 0;
	UDINT nDiff = 1; // Wertigkeit
	UDINT nDigitVal = 0; // Wert der Stelle als Einer-Wertigkeit
	while(1 == 1)
	{
		// Zeichen von hinten nach vorne durchlaufen
		pChar = (STRING*)pText+nCharCount;
		if(*pChar >= '0' && *pChar <= '9')
		{
			// Zeichen ist eine Nummer
			nDigitVal = (UDINT)(*pChar-'0'); // Wert als Einer-Stelle
			LREAL rResult = (LREAL)nFuncRetVal + ((LREAL)nDigitVal * (LREAL)nDiff);
			if(rResult > (LREAL)nBRB_UDINT_MAX)
			{
				// Ergebnis zu groß für UDINT
				nFuncRetVal = nBRB_UDINT_MAX; // Maximalen Wert zurückgeben
				break;
			}
			nFuncRetVal += nDigitVal * nDiff; // Wert als tatsächliche Wertigkeit zum Udint addieren
			nDiff *= 10; // Nächste Wertigkeit (Einer->Zehner->Hunderter->usw.)
		}
		else
		{
			// Zeichen ist keine Nummer -> Abbrechen
			break;
		}
		if(nCharCount > 0)
		{
			// Vorheriges Zeichen
			nCharCount--;
		}
		else
		{
			// Alle Zeichen durchlaufen
			break;
		}
	}
	return nFuncRetVal;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

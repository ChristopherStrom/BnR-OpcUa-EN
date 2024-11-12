/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbStringSplitEmpty.c
 * Author: niedermeierr
 * Created: May 17, 2021
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

/* Spaltet einen Text in mehrere Strings aufgrund eines Trennzeichens (inkl. Leer-Strings) */
unsigned long BrbStringSplitEmpty(plcstring* pText, plcstring* pSep, unsigned long pSplitArray, unsigned long nArrayIndexMax, unsigned long nEntrySize)
{
	if(nEntrySize <= 1)
	{
		// String-Grösse zu klein
		return 0;
	}
	UDINT nResult = 0;
	UDINT nLenText = strlen(pText);
	UDINT nLenSep = strlen(pSep);
	// Der Einfachkeit halber wird das Array in einer MemList verwaltet
	BrbMemListManagement_Typ ListMan;
	ListMan.pList = pSplitArray;
	ListMan.nIndexMax = nArrayIndexMax;
	ListMan.nEntryLength = nEntrySize;
	BrbMemListClear(&ListMan);
	// Text von vorne nach hinten nach Trennzeichen durchsuchen
	STRING* pEntryTextStart = pText;
	STRING* pEntryTextEnd = 0;
	UDINT nCharIndex = 0;
	do
	{
		// Trennzeichen vergleichen
		if((memcmp((pText + nCharIndex), pSep, nLenSep) == 0) || nCharIndex == nLenText-1)
		{
			// Trennzeichen gefunden -> Splittext holen und in Array eintragen
			if((memcmp((pText + nCharIndex), pSep, nLenSep) != 0) && nCharIndex == nLenText-1)
			{
				// Kein Trennzeichen am Ende
				pEntryTextEnd = pText + nCharIndex + 1;
			}
			else
			{
				pEntryTextEnd = pText + nCharIndex;
			}
			STRING sEntryText[nEntrySize];
			memset(sEntryText, 0, sizeof(sEntryText));
			DINT nNeededEntrySize = (DINT)pEntryTextEnd - (DINT)pEntryTextStart + 1;
			if((DINT)nEntrySize < nNeededEntrySize)
			{
				pEntryTextEnd = pEntryTextStart + nEntrySize - 1;
			}
			BrbStringGetSubTextByAdr(pEntryTextStart, pEntryTextEnd, sEntryText);
			if(strcmp(sEntryText, pSep) == 0)
			{
				memset(sEntryText, 0, sizeof(sEntryText));
			}
			BrbMemListIn(&ListMan, ListMan.nEntryCount, (UDINT)&sEntryText);
			nResult += 1;
			// Weitermachen mit Text nach Trennzeichen
			nCharIndex += nLenSep;
			pEntryTextStart = pText + nCharIndex;
		}
		else
		{
			nCharIndex += 1;
		}
	} while(nCharIndex<nLenText);
	if(pEntryTextEnd != 0)
	{
		if(BrbStringEndsWith(pEntryTextEnd, pSep) == 1)
		{
			// Text endet mit Trennzeichen -> noch einen leeren Eintrag hinzufügen
			STRING sEntryText[nEntrySize];
			memset(sEntryText, 0, sizeof(sEntryText));
			BrbMemListIn(&ListMan, ListMan.nEntryCount, (UDINT)&sEntryText);
			nResult += 1;
		}
	}
	return nResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

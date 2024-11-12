
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

/* Addiert zwei Integer-Strings */
signed long BrbIntegerStringAdd(plcstring* pIntegerString1, plcstring* pIntegerString2, unsigned long nSize1)
{
	if(pIntegerString1 == 0 || pIntegerString2 == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	UDINT nLen1 = strlen(pIntegerString1);
	UDINT nLen2 = strlen(pIntegerString2);
	UDINT nLenMax = nLen1;
	if(nLen2 > nLen1)
	{
		nLenMax = nLen2;
	}
	// Temporärer Ergebnis-String
	STRING sResult[nSize1];
	memset((USINT*)&sResult, 0 ,sizeof(sResult));
	BrbStringPadRight(sResult, "0", nSize1-1);
	// Stellen des längsten Strings von hinten nach vorne durchgehen
	UDINT nDigit = 0; // Stelle von hinten
	BOOL bDigitOverflow = 0;
	for(nDigit=0; nDigit<nLenMax+1; nDigit++) // nLenMax+1, damit der Überlauf der letzten Stelle auch berücksichtigt wird
	{
		// Stellenwert von String1 ermitteln
		USINT nValue1 = 0;
		if(nDigit < nLen1)
		{
			USINT* pChar1 = (USINT*)pIntegerString1 + nLen1 - nDigit - 1;
			nValue1 = *pChar1 - '0';
		}
		// Stellenwert von String2 ermitteln
		USINT nValue2 = 0;
		if(nDigit < nLen2)
		{
			USINT* pChar2 = (USINT*)pIntegerString2 + nLen2 - nDigit - 1;
			nValue2 = *pChar2 - '0';
		}
		// Summe ermitteln
		USINT nSum = nValue1 + nValue2;
		if(bDigitOverflow == 1)
		{
			// Überlauf aus vorherigem Durchgang berücksichtigen
			nSum += 1;
			bDigitOverflow = 0;
		}
		// Überlauf ermitteln
		if(nSum >= 10)
		{
			nSum -= 10;
			bDigitOverflow = 1;
		}
		if(nDigit < nSize1)
		{
			// Summe in Ergebnis besetzen
			USINT* pCharResult = (USINT*)&sResult + nSize1 - nDigit - 2;
			*pCharResult = '0' + nSum;
		}
		else
		{
			// Ergebnis-String ist zu Ende -> Schleife verlassen
			break;
		}
	}
	// Ergebnis auf String1 übernehmen
	BrbStringTrimLeft(sResult, "0");
	if(strlen(sResult) == 0)
	{
		BrbStringCopy(sResult, "0", nSize1);
	}
	BrbStringCopy(pIntegerString1, sResult, nSize1);
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

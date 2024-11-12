/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbRoundDint.c
 * Author: niedermeierr
 * Created: November 19, 2015
 ********************************************************************
 * Implementation of library BrbLib
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLib.h"
#include <math.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Rundet einen Dint */
signed long BrbRoundDint(signed long nValue, enum BrbRound_ENUM eRound, unsigned char nDigits) // NOLINT(readability-function-cognitive-complexity)
{
	DINT nResult = nValue;
	if(nValue != 0)
	{
		if(nDigits < 1)
		{
			nDigits = 1;
		}
		BOOL bMinus = 0;
		if(nValue < 0)
		{
			bMinus = 1;
			nResult = nResult * -1;
			if(eRound == eBRB_ROUND_UP)
			{
				eRound = eBRB_ROUND_DOWN;
			}
			else if(eRound == eBRB_ROUND_DOWN)
			{
				eRound = eBRB_ROUND_UP;
			}
		}
		if(eRound == eBRB_ROUND_UP)
		{
			// Jede Stelle f�r sich runden
			USINT nDigit = 0;
			for(nDigit=1; nDigit<=nDigits; nDigit++)
			{
				DINT nDigitFactor = (DINT)pow(10, nDigit); // NOLINT(clang-diagnostic-bad-function-cast)
				DINT nNum0 = (DINT)((nResult / nDigitFactor) * nDigitFactor);
				DINT nRest = nResult - nNum0;
				if(nRest > 0)
				{
					nResult = nResult + (nDigitFactor - nRest);
				}
			}
		}
		else if(eRound == eBRB_ROUND_DOWN)
		{
			// Alle Rundungs-Stellen auf 0 setzen
			DINT nDigitFactor = (DINT)pow(10, nDigits); // NOLINT(clang-diagnostic-bad-function-cast)
			DINT nNum0 = (DINT)((nResult / nDigitFactor) * nDigitFactor);
			DINT nRest = nResult - nNum0;
			nResult = nResult - nRest;
		}
		else
		{
			DINT nDigitFactor = (DINT)pow(10.0, nDigits); // NOLINT(clang-diagnostic-bad-function-cast)
			DINT nNum0 = (DINT)(nResult / nDigitFactor);
			DINT nNum1 = nNum0 * nDigitFactor;
			DINT nRest = nResult - nNum1; // Rundungs-Stelle feststellen
			if(nRest >= 5 * (DINT)(nDigitFactor / 10.0))
			{
				nResult = BrbRoundDint(nResult, eBRB_ROUND_UP, nDigits);
			}
			else
			{
				nResult = BrbRoundDint(nResult, eBRB_ROUND_DOWN, nDigits);
			}
		}
		if(bMinus == 1)
		{
			nResult = nResult * -1;
		}
	}
	return nResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

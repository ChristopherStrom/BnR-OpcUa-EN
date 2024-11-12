/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbStringFormatFractionDigits.c
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

/* Formatiert einen Real-String-Wert auf Nachkommastellen */
unsigned short  BrbStringFormatFractionDigits(plcstring* pValue, unsigned long nValueSize, unsigned short nFractionsDigits)
{
	STRING sTemp[nValueSize+1];
	BrbStringConvertRealFromExp(pValue, sTemp, sizeof(sTemp));
	brsstrcpy((UDINT)pValue, (UDINT)&sTemp);
	UDINT nValueLen = strlen(pValue);
	STRING* pDot = BrbStringGetAdrOf(pValue, ".", nValueLen);
	if(pDot > pValue)
	{
		// Punkt gefunden
		UDINT nLenAfterDot = ((UDINT)pValue + nValueLen) - (UDINT)pDot - 1;
		if(nLenAfterDot > nFractionsDigits)
		{
			if(nFractionsDigits > 0)
			{
				*(pDot + nFractionsDigits + 1) = 0;
			}
			else
			{
				*pDot = 0;
			}
		}
		else if(nLenAfterDot < nFractionsDigits)
		{
			UDINT nMissingDigits = nFractionsDigits - nLenAfterDot;
			UDINT nMissingChars = 0;
			for(nMissingChars=0; nMissingChars<nMissingDigits; nMissingChars++)
			{
				BrbStringCat(pValue, "0", nValueSize);
			}
		}
	}
	else
	{
		// Punkt nicht gefunden
		if(nFractionsDigits > 0)
		{
			BrbStringCat(pValue, ".", nValueSize);
			UDINT nMissingChars = 0;
			for(nMissingChars=0; nMissingChars<nFractionsDigits; nMissingChars++)
			{
				BrbStringCat(pValue, "0", nValueSize);
			}
		}
	}
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

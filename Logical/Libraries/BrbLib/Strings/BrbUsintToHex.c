/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbUdintToHex.c
 * Author: niedermeierr
 * Created: July 14, 2021
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
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Wandelt einen Usint in einen Hex-String */
unsigned short BrbUsintToHex(unsigned char nValue, plcstring* pHex, unsigned long nHexSize, plcbit bWithPraefix)
{
	memset(pHex, 0, nHexSize);
	if(bWithPraefix == 1)
	{
		BrbStringCat(pHex, "0x", nHexSize);
	}
	DINT nDigit = 0;
	for(nDigit=1; nDigit>=0; nDigit--)
	{
		UDINT nHelp1 = (UDINT)0xF << (UDINT)nDigit * 4; // NOLINT(hicpp-signed-bitwise)
		UDINT nHelp2 = nValue & nHelp1;
		UDINT nHelp3 = nHelp2 >> (UDINT)nDigit * 4;
		
		if(nHelp3 <= 9)
		{
			STRING sChar[2];
			sChar[0] = (char)(48 + nHelp3);
			sChar[1] = 0;
			BrbStringCat(pHex, sChar, nHexSize);
		}
		else
		{
			STRING sChar[2];
			sChar[0] = (char)(65 + nHelp3 - 10);
			sChar[1] = 0;
			BrbStringCat(pHex, sChar, nHexSize);
		}
	}
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

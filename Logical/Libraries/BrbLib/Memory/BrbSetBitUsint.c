/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbSetBitUsint.c
 * Author: niedermeierr
 * Created: June 25, 2013
 ********************************************************************
 * Implementation of library BrbLib
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLib.h"

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Setzt ein Bit in einem Usint */
plcbit BrbSetBitUsint(unsigned char* pValue, unsigned short nBitNumber, plcbit bBit)
{
	BOOL bResult = 0;
	if(nBitNumber <= 7)
	{
		bResult = BrbGetBitUsint(*pValue, nBitNumber);
		if(bBit == 1)
		{
			*pValue = *pValue | (USINT)((USINT)1 << nBitNumber); // NOLINT(hicpp-signed-bitwise)
		}
		else
		{
			*pValue = *pValue & ~(USINT)((USINT)1 << nBitNumber); // NOLINT(hicpp-signed-bitwise)
		}
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

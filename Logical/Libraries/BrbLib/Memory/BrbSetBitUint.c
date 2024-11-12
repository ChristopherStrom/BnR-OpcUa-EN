/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbSetBitUint.c
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

/* Setzt oder löscht ein Bit in einem Uint */
plcbit BrbSetBitUint(unsigned short* pValue, unsigned short nBitNumber, plcbit bBit)
{
	BOOL bResult = 0;
	if(nBitNumber <= 15)
	{
		bResult = BrbGetBitUint(*pValue, nBitNumber);
		if(bBit == 1)
		{
			*pValue = (UINT)(*pValue | ((UINT)1 << nBitNumber)); // NOLINT(hicpp-signed-bitwise)
		}
		else
		{
			*pValue = (UINT)(*pValue & ~((UINT)1 << nBitNumber)); // NOLINT(hicpp-signed-bitwise)
		}
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

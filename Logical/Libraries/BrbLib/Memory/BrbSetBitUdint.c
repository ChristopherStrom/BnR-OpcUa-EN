/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbSetBitUdint.c
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

/* Setzt oder löscht ein Bit in einem Udint */
plcbit BrbSetBitUdint(unsigned long* pValue, unsigned short nBitNumber, plcbit bBit)
{
	BOOL bResult = 0;
	if(nBitNumber <= 31)
	{
		bResult = BrbGetBitUdint(*pValue, nBitNumber);
		if(bBit == 1)
		{
			*pValue = *pValue | ((UDINT)1 << nBitNumber);
		}
		else
		{
			*pValue = *pValue & ~((UDINT)1 << nBitNumber);
		}
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

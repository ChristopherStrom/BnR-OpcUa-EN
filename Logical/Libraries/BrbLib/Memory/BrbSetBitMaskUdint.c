/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbSetBitMaskUdint.c
 * Author: niedermeierr
 * Created: May 16, 2014
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

/* Setzt oder l�scht eine Bitmaske in einem Udint */
plcbit BrbSetBitMaskUdint(unsigned long* pValue, unsigned long nBitMask, plcbit bSet)
{
	BOOL bResult = 0;
	bResult = BrbGetBitMaskUdint(*pValue, nBitMask);
	if(bSet == 1)
	{
		*pValue = *pValue | nBitMask;
	}
	else
	{
		*pValue = *pValue & ~nBitMask;
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

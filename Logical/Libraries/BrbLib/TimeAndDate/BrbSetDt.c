/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbSetDtStruct.c
 * Author: niedermeierr
 * Created: May 18, 2021
 ********************************************************************
 * Implementation of library BrbLib
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLib.h"
#include "AsTime.h" // NOLINT(clang-diagnostic-nonportable-system-include-path)

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Setzt eine DATE_AND_TIME-Zeit */
plcdt BrbSetDt(unsigned short nYear, unsigned char nMonth, unsigned char nDay, unsigned char nHour, unsigned char nMinute, unsigned char nSecond)
{
	DTStructure dtStruct;
	DATE_AND_TIME dtTime = BrbSetDtStruct(&dtStruct, nYear, nMonth, nDay, nHour, nMinute, nSecond, 0, 0);
	return dtTime;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

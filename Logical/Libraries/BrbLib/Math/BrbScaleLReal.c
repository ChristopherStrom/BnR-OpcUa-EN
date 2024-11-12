/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbScaleLReal.c
 * Author: niedermeierr
 * Created: October 11, 2021
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

/* Skaliert ein analoges Signal linear */
double BrbScaleLReal(double rRaw, double rRawMin, double rRawMax, double rScaledMin, double rScaledMax, double rFactor, double rOffset)
{
	LREAL rResult = 0.0;
	LREAL rRawDiff = rRawMax - rRawMin;
	if(rRawDiff != 0.0) // Division durch 0 vermeiden
	{
		rResult = ((rScaledMin + ((rScaledMax - rScaledMin) / rRawDiff * (rRaw - rRawMin))) * rFactor) + rOffset;
	}
	return rResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbScaleAnalogInput.c
 * Author: niedermeierr
 * Created: April 22, 2016
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

/* Skaliert ein analoges Eingangssignal linear auf einen Einheitswert */
float BrbScaleAnalogInput(signed short nRaw, signed short nRawMin, signed short nRawMax, float rScaledMin, float rScaledMax, float rFactor, float rOffset)
{
	REAL rResult = 0.0f;
	DINT nRawDiff = nRawMax - nRawMin;
	if(nRawDiff != 0) // Division durch 0 vermeiden
	{
		rResult = ((rScaledMin + ((rScaledMax - rScaledMin) / (REAL)nRawDiff * (REAL)(nRaw - nRawMin))) * rFactor) + rOffset;
	}
	return rResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

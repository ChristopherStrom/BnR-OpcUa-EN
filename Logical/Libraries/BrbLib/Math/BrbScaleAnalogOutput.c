/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbScaleAnalogOutput.c
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

/* Skaliert ein analoges Ausgangssignal von einem Einheitswert */
signed short BrbScaleAnalogOutput(float rScaled, signed short nRawMin, signed short nRawMax, float rScaledMin, float rScaledMax, float rFactor, float rOffset)
{
	INT nResult = 0;
	REAL rScaleDiff = (rScaledMax - rScaledMin);
	if(rFactor != 0.0f && rScaleDiff != 0.0f) // Division durch 0 vermeiden // NOLINT(clang-diagnostic-float-equal)
	{
		REAL rRawMin = (REAL)nRawMin;
		REAL rRawMax = (REAL)nRawMax;
		REAL rValue = ((((rScaled - rOffset) / rFactor) - rScaledMin) * (rRawMax - rRawMin) / rScaleDiff) + rRawMin;
		if(rValue < rRawMin)
		{
			nResult = nRawMin;
		}
		else if(rValue > rRawMax)
		{
			nResult = nRawMax;
		}
		else
		{
			nResult = (INT)rValue;
		}
	}
	return nResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

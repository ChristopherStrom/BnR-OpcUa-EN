/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbNormalizeAngleDeg.c
 * Author: niedermeierr
 * Created: September 05, 2014
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

/* Normalisiert einen Grad-Winkel in den Bereich 0..360° */
float BrbNormalizeAngleDeg(float rAngleDeg, plcbit bKeep360)
{
	REAL rResult = rBRB_DEGREE_0;
	if(bKeep360 == 1 && rAngleDeg == rBRB_DEGREE_360)
	{
		// 360.0° ist eigentlich 0°. Diese Korrektur kann hier verhindert werden.
		rResult = rBRB_DEGREE_360;
	}
	else
	{
		DINT nMod = (DINT)(rAngleDeg / rBRB_DEGREE_360);
		rResult = rAngleDeg - ((REAL)nMod * rBRB_DEGREE_360);
		if(rResult < rBRB_DEGREE_0)
		{
			rResult += rBRB_DEGREE_360;
		}
	}
	return rResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

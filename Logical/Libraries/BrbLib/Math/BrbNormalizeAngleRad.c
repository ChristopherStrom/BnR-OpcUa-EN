/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbNormalizeAngleRad.c
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
#include <AnsiCFunc.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Normalisiert einen Bogenmass-Winkel in den Bereich 0..2Pi */
float BrbNormalizeAngleRad(float rAngleRad)
{
	REAL rResult = 0.0f;
	DINT nMod = (DINT)(rAngleRad / 6.283185307179586476925286766559f);
	rResult = rAngleRad - ((REAL)nMod * 6.283185307179586476925286766559f);
	if(BrbIsNearlyZeroReal(rResult, 0.00017453292519943f))
	{
		// ~= 0.0
		rResult = 0.0f;
	}
	else if(rResult < 0.0f)
	{
		rResult += 6.283185307179586476925286766559f;
	}
	return rResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

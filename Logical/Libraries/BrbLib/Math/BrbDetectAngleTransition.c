
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

/* Erkennt den Übergang einer bestimmten Position bei einer 360°-Rundachse */
plcbit BrbDetectAngleTransition(double rTransPosition, plcbit bDirection, double rPosAct, double rPosOld)
{
	BOOL bResult = 0;
	// Richtung feststellen
	LREAL rDir =  rPosAct - rPosOld;
	if(rPosAct >= rBRB_DEGREE_0 && rPosAct <= rBRB_DEGREE_90 && rPosOld >= rBRB_DEGREE_270 && rPosOld <= rBRB_DEGREE_360)
	{
		// Übergang von 360° auf 0°
		rDir = +1.0;
	}
	else if(rPosAct >= rBRB_DEGREE_270 && rPosAct <= rBRB_DEGREE_360 && rPosOld >= rBRB_DEGREE_0 && rPosOld <= rBRB_DEGREE_90)
	{
		// Übergang von 0° auf 360°
		rDir = -1.0;
	}
	if(rTransPosition <= rBRB_DEGREE_90)
	{
		// Positionen um 90° nach positiv verschieben, um Übergang von 360° auf 0° zu vermeiden
		rTransPosition = (LREAL)BrbNormalizeAngleDeg((REAL)rTransPosition + rBRB_DEGREE_90, 0);
		rPosAct = (LREAL)BrbNormalizeAngleDeg((REAL)rPosAct + rBRB_DEGREE_90, 0);
		rPosOld = (LREAL)BrbNormalizeAngleDeg((REAL)rPosOld + rBRB_DEGREE_90, 0);
	}
	else if(rTransPosition >= rBRB_DEGREE_270)
	{
		// Positionen um 90° nach negativ verschieben, um Übergang von 360° auf 0° zu vermeiden
		rTransPosition = (LREAL)BrbNormalizeAngleDeg((REAL)rTransPosition - rBRB_DEGREE_90, 0);
		rPosAct = (LREAL)BrbNormalizeAngleDeg((REAL)rPosAct - rBRB_DEGREE_90, 0);
		rPosOld = (LREAL)BrbNormalizeAngleDeg((REAL)rPosOld - rBRB_DEGREE_90, 0);
	}
	// NOLINTBEGIN(bugprone-branch-clone)
	if(bDirection == 0 && rDir < rBRB_DEGREE_0)
	{
		// Negative Richtung
		if(rPosOld > rTransPosition && rPosAct <= rTransPosition)
		{
			bResult = 1;
		}
		else if(rPosOld >= rTransPosition && rPosAct < rTransPosition)
		{
			bResult = 1;
		}
	}
	else if(bDirection == 1 && rDir > rBRB_DEGREE_0)
	{
		// Positive Richtung
		if(rPosOld < rTransPosition && rPosAct >= rTransPosition)
		{
			bResult = 1;
		}
		else if(rPosOld <= rTransPosition && rPosAct > rTransPosition)
		{
			bResult = 1;
		}
	}
	// NOLINTEND(bugprone-branch-clone)
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

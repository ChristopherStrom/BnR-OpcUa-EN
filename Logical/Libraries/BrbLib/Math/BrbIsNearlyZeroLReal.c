
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

/* Gibt zurück, ob ein LREAL-Wert annähernd 0 ist */
plcbit BrbIsNearlyZeroLReal(double rValue, double rTolerance)
{
	BOOL bResult = 0;
	if(rTolerance < 0.0)
	{
		rTolerance = rTolerance*(LREAL)-1.00000000000000000000;
	}
	LREAL rMin = -rTolerance;
	LREAL rMax = rTolerance;
	if(rValue >= rMin && rValue <= rMax)
	{
		bResult = 1;
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)


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

/* Gibt zurück, ob sich ein Winkel innerhalb eines Bereichs befindet */
plcbit BrbIsWithinRangeAngle(double rAngleAct, double rAngleStart, double rAngleEnd)
{
	BOOL bResult = 0;
	if(rAngleStart <= rAngleEnd)
	{
		if(rAngleAct >= rAngleStart && rAngleAct <= rAngleEnd)
		{
			bResult = 1;
		}
	}
	else
	{
		if(rAngleAct >= rAngleStart || rAngleAct <= rAngleEnd)
		{
			bResult = 1;
		}
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

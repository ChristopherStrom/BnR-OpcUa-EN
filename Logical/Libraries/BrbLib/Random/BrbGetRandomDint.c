/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbGetRandomDint.c
 * Author: niedermeierr
 * Created: June 11, 2013
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

/* Erzeugt eine Zufallszahl zwischen nMin und nMax */
signed long BrbGetRandomDint(signed long nMin, signed long nMax)
{
	DINT nRandom = 0;
	if(nMin >= 0 && nMax >= 0)
	{
		nRandom = (DINT)BrbGetRandomUdint((UDINT)nMin, (UDINT)nMax);
	}
	else if(nMin < 0 && nMax < 0)
	{
		nRandom = (DINT)BrbGetRandomUdint((UDINT)abs(nMax), (UDINT)abs(nMin));
		nRandom = nRandom * -1;
	}
	else
	{
		// Eigentlich ohne +2.0, aber dann ist es sehr unwahrscheinlich, dass sich der Max-Wert ergibt (RandomPercent muss 1.0 sein).
		// Das +2.0 erhöht die Chance dazu, muss dann aber korrigiert werden.
		LREAL rRange = (LREAL)nMax - (LREAL)nMin + (LREAL)2.0;
		REAL rRangeRandom = BrbGetRandomPercent() * (REAL)rRange;
		LREAL rRandom = (LREAL)rRangeRandom + (LREAL)nMin - (LREAL)1.0;
		nRandom = (DINT)rRandom;
		// NOLINTBEGIN(bugprone-branch-clone)
		if(nRandom > nMax)
		{
			nRandom = nMax;
		}
		else if(nMin > 0 && nMax == nBRB_DINT_MAX && nRandom == 0)
		{
			nRandom = nMax;
		}
		else if(nRandom < nMin)
		{
			nRandom = nMin;
		}
		// NOLINTEND(bugprone-branch-clone)
	}
	return nRandom;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

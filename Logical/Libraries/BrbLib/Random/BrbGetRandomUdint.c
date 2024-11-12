/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbGetRandomUdint.c
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

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Erzeugt eine Zufallszahl zwischen nMin und nMax */
unsigned long BrbGetRandomUdint(unsigned long nMin, unsigned long nMax)
{
	UDINT nRandom = 0;
	if(nMin == 0 && nMax == nBRB_UDINT_MAX)
	{
		nRandom = (UDINT)(BrbGetRandomPercent() * (REAL)nMax);
	}
	else
	{
		// Eigentlich ohne +1, aber dann ist es sehr unwahrscheinlich, dass sich der Max-Wert ergibt (RandomPercent muss 1.0 sein).
		// Das +1 erhöht die Chance dazu, muss dann aber korrigiert werden.
		nRandom = (UDINT)(BrbGetRandomPercent()*(REAL)(nMax-nMin+1))+nMin;
		if(nRandom > nMax)
		{
			nRandom = nMax;
		}
		else if(nMin > 0 && nMax == nBRB_UDINT_MAX && nRandom == 0)
		{
			nRandom = nBRB_UDINT_MAX;
		}
	}
	return nRandom;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

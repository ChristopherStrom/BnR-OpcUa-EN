/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbHexToDint.c
 * Author: niedermeierr
 * Created: January 19, 2017
 ********************************************************************
 * Implementation of library BrbLib
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLib.h"
#include <math.h>
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Wandelt einen Hex-String in einen Dint */
signed long BrbHexToDint(plcstring* pHex)
{
	DINT nResult = 0;
	UDINT nHexLen = strlen(pHex);
	UDINT nValueUdint = BrbHexToUdint(pHex);
	if(nHexLen < 8)
	{
		UDINT nMaxValuePositive = (UDINT)pow(2, nHexLen*4) - 1; // NOLINT(clang-diagnostic-bad-function-cast)
		UDINT nPolarityLimit = ((nMaxValuePositive+1) / 2) - 1;
		if(nValueUdint > nPolarityLimit)
		{
			// Zahl ist negativ
			nResult = (DINT)(nValueUdint - nMaxValuePositive - 1);
		}
		else
		{
			// Zahl ist positiv
			nResult = (DINT)nValueUdint;
		}
	}
	else
	{
		// Sonderbehandlung, weil die Berechnungen sonst durch Überlauf falsch wären
		if(nValueUdint > nBRB_DINT_MAX)
		{
			// Zahl ist negativ
			nResult = (DINT)(nValueUdint - nBRB_UDINT_MAX - 1);
		}
		else
		{
			// Zahl ist positiv
			nResult = (DINT)nValueUdint;
		}
	}
	return nResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

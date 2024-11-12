/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbStartStepTimeout.c
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

/* Startet den Timeout-Zähler für eine Schrittkette */
unsigned short BrbStartStepTimeout(struct BrbStepHandling_TYP* pStepHandling, unsigned long nTimeout, signed long nContinueStep)
{
	// Prüfen, ob Timer schon abgelaufen ist
	if(pStepHandling->Intern.fbTimeout.Q == 0)
	{
		// Timer setzen und starten
		pStepHandling->Intern.fbTimeout.PT = (TIME)nTimeout;
		pStepHandling->Current.nTimeoutContinueStep = nContinueStep;
		pStepHandling->Intern.fbTimeout.IN = 1;
	}
	return 0;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

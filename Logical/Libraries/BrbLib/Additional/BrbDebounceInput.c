/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbDebounceInput.c
 * Author: niedermeierr
 * Created: April 15, 2015
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

/* Entprellt einen Eingang */
void BrbDebounceInput(struct BrbDebounceInput* inst)
{
	inst->bOutput = 0;
	inst->fbDebounce.PT = (TIME)inst->nDebounceTime;
	TON(&inst->fbDebounce);
	if(inst->fbDebounce.Q == 1)
	{
		inst->fbDebounce.IN = 0;
		TON(&inst->fbDebounce);
	}
	if(inst->bInput == 1 && inst->fbDebounce.IN == 0)
	{
		inst->bOutput = 1;
		inst->fbDebounce.IN = 1;
		TON(&inst->fbDebounce);
	}
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

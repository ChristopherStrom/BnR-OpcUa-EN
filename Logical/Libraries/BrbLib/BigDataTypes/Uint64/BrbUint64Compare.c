
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

/* Vergleicht zwei Uint64 auf kleiner, größer oder gleich */
signed char BrbUint64Compare(struct BrbUint64_TYP* pOperand0, struct BrbUint64_TYP* pOperand1)
{
	if(pOperand0 == 0 || pOperand1 == 0)
	{
		return 0;
	}
	SINT nResult = 0;
	// NOLINTBEGIN(bugprone-branch-clone)
	if(pOperand0->nHigh > pOperand1->nHigh)
	{
		nResult = 1;
	}
	else if(pOperand0->nHigh < pOperand1->nHigh)
	{
		nResult = -1;
	}
	else if(pOperand0->nLow > pOperand1->nLow)
	{
		nResult = 1;
	}
	else if(pOperand0->nLow < pOperand1->nLow)
	{
		nResult = -1;
	}
	// NOLINTEND(bugprone-branch-clone)
	return nResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

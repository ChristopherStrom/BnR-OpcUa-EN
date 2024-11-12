
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

/* Vergleicht zwei Int64 auf kleiner, größer oder gleich */
signed char BrbInt64Compare(struct BrbInt64_TYP* pOperand0, struct BrbInt64_TYP* pOperand1)
{
	if(pOperand0 == 0 || pOperand1 == 0)
	{
		return 0;
	}
	SINT nResult = 0;
	BOOL bNegativeBit0 = (pOperand0->nHigh & 0x80000000) == 0x80000000;
	BOOL bNegativeBit1 = (pOperand1->nHigh & 0x80000000) == 0x80000000;
	if(bNegativeBit0 == 0 && bNegativeBit1 == 1)
	{
		// 0=Positiv, 1=Negativ
		nResult = 1;
	}
	else if(bNegativeBit0 == 1 && bNegativeBit1 == 0)
	{
		// 0=Negativ, 1=Positiv
		nResult = -1;
	}
	else
	{
		// Beide positiv oder beide negativ
		UDINT nHigh0 = pOperand0->nHigh & 0x7FFFFFFF; // NOLINT(hicpp-signed-bitwise)
		UDINT nHigh1 = pOperand1->nHigh & 0x7FFFFFFF; // NOLINT(hicpp-signed-bitwise)
		// NOLINTBEGIN(bugprone-branch-clone)
		if(nHigh0 > nHigh1)
		{
			nResult = 1;
		}
		else if(nHigh0 < nHigh1)
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
	}
	return nResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)


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

/* Dekrementiert einen Uint64-Wert um 1 */
signed long BrbUint64Dec(struct BrbUint64_TYP* pUint64)
{
	if(pUint64 == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	BrbUint64_TYP nOperand;
	nOperand.nLow = 1;
	nOperand.nHigh = 0;
	return BrbUint64Calculate(pUint64, &nOperand, eBRB_DT64_OPERATOR_SUBTRACT);
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

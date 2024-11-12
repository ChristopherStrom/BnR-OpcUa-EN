
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

/* Inkrementiert einen Int64-Wert um 1 */
signed long BrbInt64Inc(struct BrbInt64_TYP* pInt64)
{
	if(pInt64 == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	BrbInt64_TYP nOperand;
	nOperand.nLow = 1;
	nOperand.nHigh = 0;
	return BrbInt64Calculate(pInt64, &nOperand, eBRB_DT64_OPERATOR_ADD);
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

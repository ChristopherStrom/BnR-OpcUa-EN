
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

/* Rechnet mit zwei Uint64 */
signed long BrbUint64Calculate(struct BrbUint64_TYP* pOperand0, struct BrbUint64_TYP* pOperand1, enum BrbDt64Operator_ENUM eOperator)
{
	if(pOperand0 == 0 || pOperand1 == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	unsigned long long* pUlintOperand0 = (unsigned long long*)pOperand0;
	unsigned long long* pUlintOperand1 = (unsigned long long*)pOperand1;
	switch(eOperator) // NOLINT(hicpp-multiway-paths-covered)
	{
		case eBRB_DT64_OPERATOR_ADD:
			*pUlintOperand0 = *pUlintOperand0 + *pUlintOperand1;
			break;

		case eBRB_DT64_OPERATOR_SUBTRACT:
			*pUlintOperand0 = *pUlintOperand0 - *pUlintOperand1;
			break;

		case eBRB_DT64_OPERATOR_MULTIPLY:
			*pUlintOperand0 = *pUlintOperand0 * *pUlintOperand1;
			break;

		case eBRB_DT64_OPERATOR_DIVIDE:
			if(*pUlintOperand1 == 0)
			{
				return eBRB_ERR_DIVISION_BY_0;
			}
			*pUlintOperand0 = *pUlintOperand0 / *pUlintOperand1;
			break;

	}
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)


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

/* Rechnet mit zwei Int64 */
signed long BrbInt64Calculate(struct BrbInt64_TYP* pOperand0, struct BrbInt64_TYP* pOperand1, enum BrbDt64Operator_ENUM eOperator)
{
	if(pOperand0 == 0 || pOperand1 == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	signed long long* pLintOperand0 = (signed long long*)pOperand0;
	signed long long* pLintOperand1 = (signed long long*)pOperand1;
	switch(eOperator) // NOLINT(hicpp-multiway-paths-covered)
	{
		case eBRB_DT64_OPERATOR_ADD:
			*pLintOperand0 = *pLintOperand0 + *pLintOperand1;
			break;

		case eBRB_DT64_OPERATOR_SUBTRACT:
			*pLintOperand0 = *pLintOperand0 - *pLintOperand1;
			break;

		case eBRB_DT64_OPERATOR_MULTIPLY:
			*pLintOperand0 = *pLintOperand0 * *pLintOperand1;
			break;

		case eBRB_DT64_OPERATOR_DIVIDE:
			if(*pLintOperand1 == 0)
			{
				return eBRB_ERR_DIVISION_BY_0;
			}
			*pLintOperand0 = *pLintOperand0 / *pLintOperand1;
			break;

	}
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

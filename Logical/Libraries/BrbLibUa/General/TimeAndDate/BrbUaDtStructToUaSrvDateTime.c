#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLibUa.h"
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Wandelt eine DtStruct-Zeit in eine UaSrvDateTime-Zeit */
unsigned short BrbUaDtStructToUaSrvDateTime(struct UaSrv_DateTimeType* pUaSrvDateTime, struct DTStructure* pDtStruct, unsigned short nNanoSeconds)
{
	if(pUaSrvDateTime == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	if(pDtStruct == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	memset(pUaSrvDateTime, 0, sizeof(UaSrv_DateTimeType));
	pUaSrvDateTime->DateTime = DTStructure_TO_DT((UDINT)pDtStruct);
	pUaSrvDateTime->NanoSeconds = pDtStruct->millisec * 1000000 + pDtStruct->microsec * 1000 + nNanoSeconds;
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

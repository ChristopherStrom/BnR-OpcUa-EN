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

/* Wandelt eine UaSrvDateTime-Zeit in eine DtStruct-Zeit */
unsigned short BrbUaSrvDateTimeToDtStruct(struct DTStructure* pDtStruct, struct UaSrv_DateTimeType* pUaSrvDateTime)
{
	if(pDtStruct == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	if(pUaSrvDateTime == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	memset(pDtStruct, 0, sizeof(DTStructure));
	DT_TO_DTStructure(pUaSrvDateTime->DateTime, (UDINT)pDtStruct);
	UDINT nTotalNanoSeconds = pUaSrvDateTime->NanoSeconds;
	pDtStruct->millisec = (UINT)(nTotalNanoSeconds / 1000000);
	nTotalNanoSeconds -= pDtStruct->millisec * 1000000;
	pDtStruct->microsec = (UINT)(nTotalNanoSeconds / 1000);
	BrbGetWeekdayDtStruct(pDtStruct);
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

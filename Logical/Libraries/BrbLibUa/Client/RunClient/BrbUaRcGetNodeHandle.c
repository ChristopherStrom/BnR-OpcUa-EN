#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLibUa.h"
#include <string.h>
#include <AnsiCFunc.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Gibt einen ermittelten NodeHandle zurück */
unsigned short BrbUaRcGetNodeHandle(struct BrbUaRunClient_TYP* pRunClient, unsigned short nNodeHandleIndex, struct BrbUaRcNodeHandle_TYP* pNodeHandle)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunClient != 0 && pNodeHandle != 0)
	{
		memset(pNodeHandle, 0, sizeof(BrbUaRcNodeHandle_TYP));
		nStatus = eBRB_ERR_UA_NO_ELEMENTS;
		if(pRunClient->NodeHandles.nNodeHandleCount > 0 && pRunClient->NodeHandles.pDatObjNamespaceIndices != 0 && pRunClient->NodeHandles.pNodeIds != 0 && pRunClient->NodeHandles.pNodeHandleErrorIds != 0 && pRunClient->NodeHandles.pNodeHandles != 0)
		{
			nStatus = eBRB_ERR_UA_INVALID_INDEX;
			if(nNodeHandleIndex < pRunClient->NodeHandles.nNodeHandleCount)
			{
				nStatus = eBRB_ERR_OK;
				pNodeHandle->nDatObjNamespaceIndex = *(((UINT*)pRunClient->NodeHandles.pDatObjNamespaceIndices) + nNodeHandleIndex);
				memcpy(&pNodeHandle->NodeId, (USINT*)(((UANodeID*)pRunClient->NodeHandles.pNodeIds) + nNodeHandleIndex), sizeof(UANodeID));
				pNodeHandle->nErrorId = *(((DWORD*)pRunClient->NodeHandles.pNodeHandleErrorIds) + nNodeHandleIndex);
				pNodeHandle->nNodeHandle = *(((DWORD*)pRunClient->NodeHandles.pNodeHandles) + nNodeHandleIndex);
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

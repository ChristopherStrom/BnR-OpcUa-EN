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

/* Gibt ein ermitteltes ReadItem zurück */
unsigned short BrbUaRcGetReadItem(struct BrbUaRunClient_TYP* pRunClient, unsigned short nReadBlockIndex, unsigned short nReadItemIndex, struct BrbUaRcReadItem_TYP* pReadItem)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunClient != 0 && pReadItem != 0)
	{
		memset(pReadItem, 0, sizeof(BrbUaRcReadItem_TYP));
		nStatus = eBRB_ERR_UA_NO_ELEMENTS;
		if(pRunClient->ReadBlocks.nBlockCount > 0 && pRunClient->ReadBlocks.pBlocks != 0)
		{
			nStatus = eBRB_ERR_UA_INVALID_INDEX;
			if(nReadBlockIndex < pRunClient->ReadBlocks.nBlockCount)
			{
				nStatus = eBRB_ERR_UA_NO_ELEMENTS;
				BrbUaRcReadBlockIntern_TYP* pReadBlock = ((BrbUaRcReadBlockIntern_TYP*)pRunClient->ReadBlocks.pBlocks) + nReadBlockIndex;
				if(pReadBlock->nReadItemCount > 0 && 
					pReadBlock->pRiDatObjNamespaceIndices != 0 && pReadBlock->pRiNodeIds != 0 && 
					pReadBlock->pRiNodeAddInfos != 0 && pReadBlock->pRiVariables != 0 && 
					pReadBlock->pRiNodeErrorIds != 0 && pReadBlock->pRiTimestamps != 0 
					)
				{
					nStatus = eBRB_ERR_UA_INVALID_INDEX;
					if(nReadItemIndex < pReadBlock->nReadItemCount)
					{
						nStatus = eBRB_ERR_OK;
						pReadItem->nDatObjNamespaceIndex = *(((UINT*)pReadBlock->pRiDatObjNamespaceIndices) + nReadItemIndex);
						memcpy(&pReadItem->NodeId, ((UANodeID*)pReadBlock->pRiNodeIds) + nReadItemIndex, sizeof(UANodeID));
						UANodeAdditionalInfo* pNodeAddInfo = ((UANodeAdditionalInfo*)pReadBlock->pRiNodeAddInfos) + nReadItemIndex;
						memcpy(&pReadItem->AddInfo, pNodeAddInfo, sizeof(UANodeAdditionalInfo));
						STRING sVarName[nBRBUA_VARNAME_TEXT_CHAR_MAX+1];
						STRING* pVar = (STRING*)((USINT*)pReadBlock->pRiVariables) + (nReadItemIndex * sizeof(sVarName));
						BrbStringCopy(pReadItem->sVar, pVar, sizeof(pReadItem->sVar));
						pReadItem->dtTimestamp = *(((DATE_AND_TIME*)pReadBlock->pRiTimestamps) + nReadItemIndex);
						pReadItem->nErrorId = *(((DWORD*)pReadBlock->pRiNodeErrorIds) + nReadItemIndex);
					}
				}
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

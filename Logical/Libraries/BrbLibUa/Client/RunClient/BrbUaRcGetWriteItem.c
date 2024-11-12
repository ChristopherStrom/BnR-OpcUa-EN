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

/* Gibt ein ermitteltes WriteItem zurück */
unsigned short BrbUaRcGetWriteItem(struct BrbUaRunClient_TYP* pRunClient, unsigned short nWriteBlockIndex, unsigned short nWriteItemIndex, struct BrbUaRcWriteItem_TYP* pWriteItem)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunClient != 0 && pWriteItem != 0)
	{
		memset(pWriteItem, 0, sizeof(BrbUaRcWriteItem_TYP));
		nStatus = eBRB_ERR_UA_NO_ELEMENTS;
		if(pRunClient->WriteBlocks.nBlockCount > 0 && pRunClient->WriteBlocks.pBlocks != 0)
		{
			nStatus = eBRB_ERR_UA_INVALID_INDEX;
			if(nWriteBlockIndex < pRunClient->WriteBlocks.nBlockCount)
			{
				nStatus = eBRB_ERR_UA_NO_ELEMENTS;
				BrbUaRcWriteBlockIntern_TYP* pWriteBlock = ((BrbUaRcWriteBlockIntern_TYP*)pRunClient->WriteBlocks.pBlocks) + nWriteBlockIndex;
				if(pWriteBlock->nWriteItemCount > 0 && 
					pWriteBlock->pWiDatObjNamespaceIndices != 0 && pWriteBlock->pWiNodeIds != 0 && 
					pWriteBlock->pWiNodeAddInfos != 0 && pWriteBlock->pWiVariables != 0 && 
					pWriteBlock->pWiNodeErrorIds != 0 
					)
				{
					nStatus = eBRB_ERR_UA_INVALID_INDEX;
					if(nWriteItemIndex < pWriteBlock->nWriteItemCount)
					{
						nStatus = eBRB_ERR_OK;
						pWriteItem->nDatObjNamespaceIndex = *(((UINT*)pWriteBlock->pWiDatObjNamespaceIndices) + nWriteItemIndex);
						memcpy(&pWriteItem->NodeId, ((UANodeID*)pWriteBlock->pWiNodeIds) + nWriteItemIndex, sizeof(UANodeID));
						UANodeAdditionalInfo* pNodeAddInfo = ((UANodeAdditionalInfo*)pWriteBlock->pWiNodeAddInfos) + nWriteItemIndex;
						memcpy(&pWriteItem->AddInfo, pNodeAddInfo, sizeof(UANodeAdditionalInfo));
						STRING sVarName[nBRBUA_VARNAME_TEXT_CHAR_MAX+1];
						STRING* pVar = (STRING*)((USINT*)pWriteBlock->pWiVariables) + (nWriteItemIndex * sizeof(sVarName));
						BrbStringCopy(pWriteItem->sVar, pVar, sizeof(pWriteItem->sVar));
						pWriteItem->nErrorId = *(((DWORD*)pWriteBlock->pWiNodeErrorIds) + nWriteItemIndex);
					}
				}
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

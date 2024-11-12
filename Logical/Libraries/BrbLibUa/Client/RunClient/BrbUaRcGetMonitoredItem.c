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

/* Gibt ein ermitteltes MonitoredItem zurück */
unsigned short BrbUaRcGetMonitoredItem(struct BrbUaRunClient_TYP* pRunClient, unsigned short nSubscriptionIndex, unsigned short nMonitoredItemIndex, struct BrbUaRcMonitoredItem_TYP* pMonitoredItem)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunClient != 0 && pMonitoredItem != 0)
	{
		memset(pMonitoredItem, 0, sizeof(BrbUaRcMonitoredItem_TYP));
		nStatus = eBRB_ERR_UA_NO_ELEMENTS;
		if(pRunClient->Subscriptions.nSubscriptionCount > 0 && pRunClient->Subscriptions.pSubscriptions != 0)
		{
			nStatus = eBRB_ERR_UA_INVALID_INDEX;
			if(nSubscriptionIndex < pRunClient->Subscriptions.nSubscriptionCount)
			{
				nStatus = eBRB_ERR_UA_NO_ELEMENTS;
				BrbUaRcSubscriptionIntern_TYP* pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)pRunClient->Subscriptions.pSubscriptions) + nSubscriptionIndex;
				if(pSubscription->nMonitoredItemCount > 0 && 
					pSubscription->pMiDatObjNamespaceIndices != 0 && pSubscription->pMiNodeIds != 0 && 
					pSubscription->pMiNodeHandleErrorIds != 0 && pSubscription->pMiNodeHandles != 0 && 
					pSubscription->pMiNodeAddInfos != 0 && pSubscription->pMiVariables != 0 && 
					pSubscription->pMiQueueSizeOri != 0 && pSubscription->pMiMonitorSettings != 0 &&
					pSubscription->pMiValuesChanged != 0 && pSubscription->pMiRemainingValueCounts != 0 &&
					pSubscription->pMiTimestamps != 0 && pSubscription->pMiNodeQualityIds != 0 &&
					pSubscription->pMiMonitoredItemErrorIds != 0 && pSubscription->pMiMonitoredItemHandles != 0
					)
				{
					nStatus = eBRB_ERR_UA_INVALID_INDEX;
					if(nMonitoredItemIndex < pSubscription->nMonitoredItemCount)
					{
						nStatus = eBRB_ERR_OK;
						pMonitoredItem->nDatObjNamespaceIndex = *(((UINT*)pSubscription->pMiDatObjNamespaceIndices) + nMonitoredItemIndex);
						memcpy(&pMonitoredItem->NodeId, ((UANodeID*)pSubscription->pMiNodeIds) + nMonitoredItemIndex, sizeof(UANodeID));
						pMonitoredItem->nNodeHandleErrorId = *(((DWORD*)pSubscription->pMiNodeHandleErrorIds) + nMonitoredItemIndex);
						pMonitoredItem->nNodeHandle = *(((DWORD*)pSubscription->pMiNodeHandles) + nMonitoredItemIndex);
						UANodeAdditionalInfo* pNodeAddInfo = ((UANodeAdditionalInfo*)pSubscription->pMiNodeAddInfos) + nMonitoredItemIndex;
						memcpy(&pMonitoredItem->AddInfo, pNodeAddInfo, sizeof(UANodeAdditionalInfo));
						STRING sVarName[nBRBUA_VARNAME_TEXT_CHAR_MAX+1];
						STRING* pVar = (STRING*)((USINT*)pSubscription->pMiVariables) + (nMonitoredItemIndex * sizeof(sVarName));
						BrbStringCopy(pMonitoredItem->sVar, pVar, sizeof(pMonitoredItem->sVar));
						pMonitoredItem->nQueueSizeOri = *(((UINT*)pSubscription->pMiQueueSizeOri) + nMonitoredItemIndex);
						UAMonitoringParameters* pMonitoringSetting = ((UAMonitoringParameters*)pSubscription->pMiMonitorSettings) + nMonitoredItemIndex;
						memcpy(&pMonitoredItem->MonitorSettings, pMonitoringSetting, sizeof(UAMonitoringParameters));
						pMonitoredItem->bValueChanged = *(((BOOL*)pSubscription->pMiValuesChanged) + nMonitoredItemIndex);
						pMonitoredItem->nRemainingValueCount = *(((UINT*)pSubscription->pMiRemainingValueCounts) + nMonitoredItemIndex);
						pMonitoredItem->dtTimestamp = *(((DT*)pSubscription->pMiTimestamps) + nMonitoredItemIndex);
						pMonitoredItem->nNodeQualityId = *(((DWORD*)pSubscription->pMiNodeQualityIds) + nMonitoredItemIndex);
						pMonitoredItem->nMonitoredItemErrorId = *(((DWORD*)pSubscription->pMiMonitoredItemErrorIds) + nMonitoredItemIndex);
						pMonitoredItem->nMonitoredItemHandle = *(((DWORD*)pSubscription->pMiMonitoredItemHandles) + nMonitoredItemIndex);
					}
				}
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

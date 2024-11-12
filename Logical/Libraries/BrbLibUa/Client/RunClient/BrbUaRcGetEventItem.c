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

/* Gibt ein ermitteltes EventItem zurück */
unsigned short BrbUaRcGetEventItem(struct BrbUaRunClient_TYP* pRunClient, unsigned short nSubscriptionIndex, unsigned short nEventItemIndex, struct BrbUaRcEventItem_TYP* pEventItem, struct BrbUaRcEventItemIntern_TYP* pEventItemIntern)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunClient != 0 && pEventItem != 0)
	{
		memset(pEventItem, 0, sizeof(BrbUaRcEventItem_TYP));
		nStatus = eBRB_ERR_UA_NO_ELEMENTS;
		if(pRunClient->Subscriptions.nSubscriptionCount > 0 && pRunClient->Subscriptions.pSubscriptions != 0)
		{
			nStatus = eBRB_ERR_UA_INVALID_INDEX;
			if(nSubscriptionIndex < pRunClient->Subscriptions.nSubscriptionCount)
			{
				nStatus = eBRB_ERR_UA_NO_ELEMENTS;
				BrbUaRcSubscriptionIntern_TYP* pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)pRunClient->Subscriptions.pSubscriptions) + nSubscriptionIndex;
				if(pSubscription->nEventItemCount > 0 && pSubscription->pEventItems != 0)
				{
					nStatus = eBRB_ERR_UA_INVALID_INDEX;
					if(nEventItemIndex < pSubscription->nEventItemCount)
					{
						nStatus = eBRB_ERR_OK;
						BrbUaRcEventItemIntern_TYP* pEventItemInternOri = ((BrbUaRcEventItemIntern_TYP*)pSubscription->pEventItems) + nEventItemIndex;
						pEventItem->nEventDatObjNamespaceIndex = pEventItemInternOri->nEventDatObjNamespaceIndex;
						memcpy(&pEventItem->EventNodeId, &pEventItemInternOri->EventNodeId, sizeof(UANodeID));
						pEventItem->nEventNodeHandleErrorId = pEventItemInternOri->nEventNodeHandleErrorId;
						pEventItem->nEventNodeHandle = pEventItemInternOri->nEventNodeHandle;
						pEventItem->nTypeDatObjNamespaceIndex = pEventItemInternOri->nTypeDatObjNamespaceIndex;
						memcpy(&pEventItem->TypeNodeId, &pEventItemInternOri->TypeNodeId, sizeof(UANodeID));
						pEventItem->nEventItemErrorId = pEventItemInternOri->nEventItemErrorId;
						pEventItem->nEventItemHandle = pEventItemInternOri->nEventItemHandle;
						pEventItem->tTimeout = pEventItemInternOri->tTimeout;
						pEventItem->bCallOperate = pEventItemInternOri->bCallOperate;
						pEventItem->nEventFieldCount = pEventItemInternOri->nEventFieldCount;
						pEventItem->nReceiveCount = pEventItemInternOri->nReceiveCount;
						pEventItem->bEventReceived = pEventItemInternOri->bEventReceived;
						if(pEventItemIntern != 0)
						{
							memcpy(pEventItemIntern, pEventItemInternOri, sizeof(BrbUaRcEventItemIntern_TYP));
						}
					}
				}
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

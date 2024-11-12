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

/* Gibt das ValueChanged-Flag eines MonitoredItems zurück und löscht es optional */
plcbit BrbUaRcGetMiValueChanged(struct BrbUaRunClient_TYP* pRunClient, unsigned short nSubscriptionIndex, unsigned short nMonitoredItemIndex, plcbit bClear)
{
	BOOL bResult = 0;
	if(pRunClient != 0)
	{
		if(pRunClient->State.eClientState == eBRB_RCCLTSTATE_CONNECTED)
		{
			if(pRunClient->Subscriptions.nSubscriptionCount > 0 &&pRunClient->Subscriptions.pSubscriptions != 0)
			{
				if(nSubscriptionIndex < pRunClient->Subscriptions.nSubscriptionCount)
				{
					BrbUaRcSubscriptionIntern_TYP* pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)pRunClient->Subscriptions.pSubscriptions) + nSubscriptionIndex;
					if(pSubscription->nMonitoredItemCount > 0 && 
						pSubscription->pMiDatObjNamespaceIndices != 0 && pSubscription->pMiNodeIds != 0 && 
						pSubscription->pMiNodeHandleErrorIds != 0 && pSubscription->pMiNodeHandles != 0 && 
						pSubscription->pMiNodeAddInfos != 0 && pSubscription->pMiVariables != 0 && 
						pSubscription->pMiQueueSizeOri != 0 && pSubscription->pMiMonitorSettings != 0 &&
						pSubscription->pMiValuesChanged != 0 && pSubscription->pMiRemainingValueCounts != 0 &&
						pSubscription->pMiTimestamps != 0 && pSubscription->pMiNodeQualityIds != 0 &&
						pSubscription->pMiMonitoredItemErrorIds != 0 && pSubscription->pMiMonitoredItemHandles != 0)
					{
						if(nMonitoredItemIndex < pSubscription->nMonitoredItemCount)
						{
							bResult = *(((BOOL*)pSubscription->pMiValuesChanged) + nMonitoredItemIndex);
							if(bClear == 1)
							{
								*(((BOOL*)pSubscription->pMiValuesChanged) + nMonitoredItemIndex) = 0;
							}
						}
					}
				}
			}
		}
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

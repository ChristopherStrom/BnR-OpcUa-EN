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

/* Gibt eine ermittelte Subscription zurück */
unsigned short BrbUaRcGetSubscription(struct BrbUaRunClient_TYP* pRunClient, unsigned short nSubscriptionIndex, struct BrbUaRcSubscription_TYP* pSubscription, struct BrbUaRcSubscriptionIntern_TYP* pSubscriptionIntern)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunClient != 0 && pSubscription != 0)
	{
		memset(pSubscription, 0, sizeof(BrbUaRcSubscription_TYP));
		nStatus = eBRB_ERR_UA_NO_ELEMENTS;
		if(pRunClient->Subscriptions.nSubscriptionCount > 0 && pRunClient->Subscriptions.pSubscriptions != 0)
		{
			nStatus = eBRB_ERR_UA_INVALID_INDEX;
			if(nSubscriptionIndex < pRunClient->Subscriptions.nSubscriptionCount)
			{
				nStatus = eBRB_ERR_OK;
				BrbUaRcSubscriptionIntern_TYP* pSubscriptionInternOri = ((BrbUaRcSubscriptionIntern_TYP*)pRunClient->Subscriptions.pSubscriptions) + nSubscriptionIndex;
				pSubscription->bPublishingEnable = pSubscriptionInternOri->bPublishingEnable;
				pSubscription->nPriority = pSubscriptionInternOri->nPriority;
				pSubscription->tPublishingInterval = pSubscriptionInternOri->tPublishingInterval;
				pSubscription->nMonitoredItemCount = pSubscriptionInternOri->nMonitoredItemCount;
				pSubscription->nEventItemCount = pSubscriptionInternOri->nEventItemCount;
				pSubscription->nErrorId = pSubscriptionInternOri->nErrorId;
				pSubscription->nSubscriptionHandle = pSubscriptionInternOri->nSubscriptionHandle;
				if(pSubscriptionIntern != 0)
				{
					memcpy(pSubscriptionIntern, pSubscriptionInternOri, sizeof(BrbUaRcSubscriptionIntern_TYP));
				}
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

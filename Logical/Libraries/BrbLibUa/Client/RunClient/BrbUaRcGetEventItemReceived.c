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

/* Gibt zurück, ob ein Event empfangen wurde */
plcbit BrbUaRcGetEventItemReceived(struct BrbUaRunClient_TYP* pRunClient, unsigned short nSubscriptionIndex, unsigned short nEventItemIndex)
{
	BOOL bResult = 0;
	if(pRunClient != 0)
	{
		if(pRunClient->State.eClientState == eBRB_RCCLTSTATE_CONNECTED)
		{
			if(pRunClient->Subscriptions.nSubscriptionCount > 0 && pRunClient->Subscriptions.pSubscriptions != 0)
			{
				if(nSubscriptionIndex < pRunClient->Subscriptions.nSubscriptionCount)
				{
					BrbUaRcSubscriptionIntern_TYP* pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)pRunClient->Subscriptions.pSubscriptions) + nSubscriptionIndex;
					if(pSubscription->nEventItemCount > 0 && pSubscription->pEventItems != 0)
					{
						if(nEventItemIndex < pSubscription->nEventItemCount)
						{
							BrbUaRcEventItemIntern_TYP* pEventItemInternOri = ((BrbUaRcEventItemIntern_TYP*)pSubscription->pEventItems) + nEventItemIndex;
							bResult = pEventItemInternOri->bEventReceived;
						}
					}
				}
			}
		}
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

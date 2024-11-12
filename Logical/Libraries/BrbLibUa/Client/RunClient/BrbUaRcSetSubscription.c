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

// Eigene Enums und Typen
enum Steps_ENUM
{
	eSTEP_INIT,
	eSTEP_OPERATE,
	eSTEP_OPERATE_WAIT,
};

/* Ändert die Parameter einer Subscription */
void BrbUaRcSetSubscription(struct BrbUaRcSetSubscription* inst)
{
	switch(inst->eStep)
	{
		case eSTEP_INIT:
			// Fub initialisieren
			inst->nStatus =  eBRB_ERR_BUSY;
			inst->bPublished = 0;
			inst->nErrorId = 0x00000000; // Good
			BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
			memset(&inst->fbUA_SubscriptionOperate, 0, sizeof(inst->fbUA_SubscriptionOperate));
			// Parameter prüfen
			if(inst->pRunClient != 0 && inst->pSubscription != 0)
			{
				if(inst->pRunClient->State.eClientState == eBRB_RCCLTSTATE_CONNECTED && inst->pRunClient->Connection.nConnectionHandle != 0)
				{
					if(inst->pRunClient->Subscriptions.nSubscriptionCount > 0 && inst->pRunClient->Subscriptions.pSubscriptions != 0)
					{
						if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount)
						{
							inst->eStep = eSTEP_OPERATE;
						}
						else
						{
							inst->nStatus = eBRB_ERR_UA_INVALID_INDEX;
						}
					}
					else
					{
						inst->nStatus = eBRB_ERR_UA_NO_ELEMENTS;
					}
				}
				else
				{
					inst->nStatus = eBRB_ERR_UA_NOT_CONNECTED;
				}
			}
			else
			{
				inst->nStatus = eBRB_ERR_NULL_POINTER;
			}
			break;

		case eSTEP_OPERATE:
			// Subscription ändern
			inst->nStatus  = eBRB_ERR_BUSY;
			{
				BrbUaRcSubscriptionIntern_TYP* pSubscriptionIntern = ((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex;
				inst->fbUA_SubscriptionOperate.Execute = 1;
				inst->fbUA_SubscriptionOperate.SubscriptionHdl = pSubscriptionIntern->nSubscriptionHandle;
				inst->fbUA_SubscriptionOperate.PublishingEnable = inst->pSubscription->bPublishingEnable;
				inst->fbUA_SubscriptionOperate.Priority = inst->pSubscription->nPriority;
				inst->fbUA_SubscriptionOperate.Timeout = inst->pRunClient->Cfg.tAccessTimeout;
				inst->tPublishingInterval = inst->pSubscription->tPublishingInterval;
				inst->fbUA_SubscriptionOperate.PublishingInterval = &inst->tPublishingInterval;
			}
			inst->eStep = eSTEP_OPERATE_WAIT;
			break;

		case eSTEP_OPERATE_WAIT:
			// Warten, bis Subscription geändert wurde
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->fbUA_SubscriptionOperate.Done == 1)
			{
				inst->fbUA_SubscriptionOperate.Execute = 0;
				// Geänderte Werte in interne Daten übernehmen
				BrbUaRcSubscriptionIntern_TYP* pSubscriptionIntern = ((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex;
				pSubscriptionIntern->bPublishingEnable = inst->pSubscription->bPublishingEnable;
				pSubscriptionIntern->nPriority = inst->pSubscription->nPriority;
				pSubscriptionIntern->tPublishingInterval = inst->pSubscription->tPublishingInterval = inst->tPublishingInterval;
				inst->nStatus  = eBRB_ERR_OK;
				inst->bPublished = inst->fbUA_SubscriptionOperate.Published;
				inst->nErrorId = inst->fbUA_SubscriptionOperate.ErrorID;
				BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
				inst->eStep = eSTEP_INIT;
			}
			else if(inst->fbUA_SubscriptionOperate.Error == 1)
			{
				inst->fbUA_SubscriptionOperate.Execute = 0;
				inst->nStatus  = eBRB_ERR_UA_ERROR;
				inst->nErrorId = inst->fbUA_SubscriptionOperate.ErrorID;
				BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
				inst->eStep = eSTEP_INIT;
			}
			break;

	}

	// Aufruf aller FB's
	UA_SubscriptionOperate(&inst->fbUA_SubscriptionOperate);
	
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

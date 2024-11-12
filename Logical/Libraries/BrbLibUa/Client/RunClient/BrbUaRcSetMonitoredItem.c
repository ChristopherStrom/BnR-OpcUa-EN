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

/* Ändert die Parameter eines MonitoredItems */
void BrbUaRcSetMonitoredItem(struct BrbUaRcSetMonitoredItem* inst)
{
	switch(inst->eStep)
	{
		case eSTEP_INIT:
			// Fub initialisieren
			inst->nStatus =  eBRB_ERR_BUSY;
			inst->bValueChanged = 0;
			inst->dtTimestamp = 0;
			inst->nErrorId = 0x00000000; // Good
			BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
			memset(&inst->fbUA_MonitoredItemOperate, 0, sizeof(inst->fbUA_MonitoredItemOperate));
			// Parameter prüfen
			if(inst->pRunClient != 0 && inst->pMonitoringSettings != 0)
			{
				if(inst->pRunClient->State.eClientState == eBRB_RCCLTSTATE_CONNECTED && inst->pRunClient->Connection.nConnectionHandle != 0)
				{
					if(inst->pRunClient->Subscriptions.nSubscriptionCount > 0 && inst->pRunClient->Subscriptions.pSubscriptions != 0)
					{
						if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount)
						{
							BrbUaRcSubscriptionIntern_TYP* pSubscriptionIntern = ((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex;
							if(pSubscriptionIntern->nMonitoredItemCount > 0 && 
								pSubscriptionIntern->pMiDatObjNamespaceIndices != 0 && pSubscriptionIntern->pMiNodeIds != 0 && 
								pSubscriptionIntern->pMiNodeHandleErrorIds != 0 && pSubscriptionIntern->pMiNodeHandles != 0 && 
								pSubscriptionIntern->pMiNodeAddInfos != 0 && pSubscriptionIntern->pMiVariables != 0 && 
								pSubscriptionIntern->pMiQueueSizeOri != 0 && pSubscriptionIntern->pMiMonitorSettings != 0 &&
								pSubscriptionIntern->pMiValuesChanged != 0 && pSubscriptionIntern->pMiRemainingValueCounts != 0 &&
								pSubscriptionIntern->pMiTimestamps != 0 && pSubscriptionIntern->pMiNodeQualityIds != 0 &&
								pSubscriptionIntern->pMiMonitoredItemErrorIds != 0 && pSubscriptionIntern->pMiMonitoredItemHandles != 0)
							{
								if(inst->nMonitoredItemIndex < pSubscriptionIntern->nMonitoredItemCount)
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
			// MonitoredItem ändern
			inst->nStatus  = eBRB_ERR_BUSY;
			BrbUaRcGetMonitoredItem(inst->pRunClient, inst->nSubscriptionIndex, inst->nMonitoredItemIndex, &inst->MonitoredItemIntern);
			inst->fbUA_MonitoredItemOperate.Execute = 1;
			inst->fbUA_MonitoredItemOperate.MonitoredItemHdl = inst->MonitoredItemIntern.nMonitoredItemHandle;
			inst->fbUA_MonitoredItemOperate.Timeout = inst->pRunClient->Cfg.tAccessTimeout;
			inst->fbUA_MonitoredItemOperate.MonitoringSettings = inst->pMonitoringSettings;
			inst->eStep = eSTEP_OPERATE_WAIT;
			break;

		case eSTEP_OPERATE_WAIT:
			// Warten, bis MonitoredItem geändert wurde
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->fbUA_MonitoredItemOperate.Done == 1)
			{
				inst->fbUA_MonitoredItemOperate.Execute = 0;
				// Geänderte Werte in interne Daten übernehmen
				BrbUaRcSubscriptionIntern_TYP* pSubscriptionIntern = ((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex;
				UAMonitoringParameters* pMonitoringSettingIntern = ((UAMonitoringParameters*)pSubscriptionIntern->pMiMonitorSettings) + inst->nMonitoredItemIndex;
				pMonitoringSettingIntern->SamplingInterval = inst->pMonitoringSettings->SamplingInterval;
				pMonitoringSettingIntern->DeadbandType = inst->pMonitoringSettings->DeadbandType;
				pMonitoringSettingIntern->Deadband = inst->pMonitoringSettings->Deadband;
				inst->nStatus  = eBRB_ERR_OK;
				inst->bValueChanged = inst->fbUA_MonitoredItemOperate.ValueChanged;
				inst->dtTimestamp = inst->fbUA_MonitoredItemOperate.TimeStamp;
				inst->nErrorId = inst->fbUA_MonitoredItemOperate.ErrorID;
				BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
				inst->eStep = eSTEP_INIT;
			}
			else if(inst->fbUA_MonitoredItemOperate.Error == 1)
			{
				inst->fbUA_MonitoredItemOperate.Execute = 0;
				inst->nStatus  = eBRB_ERR_UA_ERROR;
				inst->nErrorId = inst->fbUA_MonitoredItemOperate.ErrorID;
				BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
				inst->eStep = eSTEP_INIT;
			}
			break;

	}

	// Aufruf aller FB's
	UA_MonitoredItemOperate(&inst->fbUA_MonitoredItemOperate);
	
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

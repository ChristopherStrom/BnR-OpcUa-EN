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

// Prototypen
BOOL GetNextEventItem(BrbUaRunClient_TYP* pRunClient, DINT* pSubscriptionIndex, DINT* pEventItemIndex);

// Eigene Enums und Typen
enum Steps_ENUM
{
	eSTEP_INIT,
	eSTEP_WAIT_FOR_CMD_CONNECT,
	eSTEP_CONNECT,
	eSTEP_CONNECTION_ERROR,
	eSTEP_GET_NAMESPACE,
	eSTEP_GET_NODE_HANDLES_NS,
	eSTEP_GET_NODE_HANDLE,
	eSTEP_GET_NODE_HANDLE_WAIT,
	eSTEP_GET_READITEMS_NS,
	eSTEP_GET_WRITEITEMS_NS,
	eSTEP_GET_METHOD_HANDLES_NS,
	eSTEP_GET_METHOD_HANDLE,
	eSTEP_CREATE_SUBSCRIPTION,
	eSTEP_GET_MI_NODE_HANDLE,
	eSTEP_GET_MI_NODE_HANDLE_WAIT,
	eSTEP_ADD_MI,
	eSTEP_ADD_MI_WAIT,
	eSTEP_GET_EI_NODE_HANDLE,
	eSTEP_ADD_EI,
	eSTEP_CONNECTED,
	eSTEP_DISCONNECT,
	eSTEP_CLEAR_EVENT_ITEM_HANDLES,
	eSTEP_CLEAR_MONITORED_ITEM_HANDLES,
	eSTEP_CLEAR_METHOD_HANDLES,
	eSTEP_CLEAR_NODE_HANDLES,
};

/* Behandelt eine Client-Instanz */
void BrbUaRunClientCyclic(struct BrbUaRunClientCyclic* inst) // NOLINT(hicpp-function-size, readability-function-size)
{
	switch(inst->eStep)
	{
		case eSTEP_INIT:
			// Fub initialisieren
			inst->nStatus = eBRB_ERR_OK;
			memset(&inst->fbUA_Connect, 0, sizeof(inst->fbUA_Connect));
			memset(&inst->fbUA_GetNamespaceIndex, 0, sizeof(inst->fbUA_GetNamespaceIndex));
			memset(&inst->fbUA_NodeGetHandleList, 0, sizeof(inst->fbUA_NodeGetHandleList));
			memset(&inst->fbUA_MethodGetHandle, 0, sizeof(inst->fbUA_MethodGetHandle));
			memset(&inst->fbUA_SubscriptionCreate, 0, sizeof(inst->fbUA_SubscriptionCreate));
			memset(&inst->fbUA_MonitoredItemAddList, 0, sizeof(inst->fbUA_MonitoredItemAddList));
			memset(&inst->fbUA_NodeGetHandle, 0, sizeof(inst->fbUA_NodeGetHandle));
			memset(&inst->fbUA_EventItemAdd, 0, sizeof(inst->fbUA_EventItemAdd));
			memset(&inst->fbUA_ConnectionGetStatus, 0, sizeof(inst->fbUA_ConnectionGetStatus));
			memset(&inst->fbUA_Disconnect, 0, sizeof(inst->fbUA_Disconnect));
			// Client-Pointer prüfen
			if(inst->pRunClient != 0)
			{
				inst->pRunClient->State.nClientErroId = 0;
				if(inst->pRunClient->State.eClientState == eBRB_RCCLTSTATE_INIT_DONE)
				{
					inst->eStep = eSTEP_WAIT_FOR_CMD_CONNECT;
				}
				else
				{
					inst->nStatus = eBRB_ERR_INVALID_PARAMETER;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Cyclic error: Init not done");
				}
			}
			else
			{
				inst->nStatus = eBRB_ERR_NULL_POINTER;
			}
			break;

		case eSTEP_WAIT_FOR_CMD_CONNECT:
			// Warten auf Kommando Connect
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_WAIT_FOR_CONNECT;
			inst->pRunClient->Connection.nInterruptedCount = 0;
			if(inst->pRunClient->eCmd == eBRB_RCCLTCMD_CONNECT)
			{
				inst->pRunClient->eCmd = eBRB_RCCLTCMD_NONE;
				inst->bEventItemFound = 0;
				inst->pEventItemReceived = 0;
				// Timeouts korrigieren
				if(inst->pRunClient->Cfg.SessionConnectInfo.SessionTimeout == 0)
				{
					inst->pRunClient->Cfg.SessionConnectInfo.SessionTimeout = 10000;
				}
				if(inst->pRunClient->Cfg.SessionConnectInfo.MonitorConnection == 0)
				{
					inst->pRunClient->Cfg.SessionConnectInfo.MonitorConnection = 2000;
				}
				if(inst->pRunClient->Cfg.tConnectTimeout == 0)
				{
					inst->pRunClient->Cfg.tConnectTimeout = 10000;
				}
				if(inst->pRunClient->Cfg.tAccessTimeout == 0)
				{
					inst->pRunClient->Cfg.tAccessTimeout = 5000;
				}
				inst->eStep = eSTEP_CONNECT;
			}
			break;

		case eSTEP_CONNECT:
			// Verbinden
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTING;
			inst->pRunClient->State.nClientErroId = 0x00000000;
			strcpy(inst->pRunClient->State.sClientErrorText, "");
			inst->fbUA_Connect.Execute = 1;
			BrbStringCopy(inst->fbUA_Connect.ServerEndpointUrl, inst->pRunClient->Cfg.sServerEndpointUrl, sizeof(inst->fbUA_Connect.ServerEndpointUrl));
			memcpy(&inst->fbUA_Connect.SessionConnectInfo, &inst->pRunClient->Cfg.SessionConnectInfo, sizeof(UASessionConnectInfo));
			inst->fbUA_Connect.Timeout = inst->pRunClient->Cfg.tConnectTimeout;
			if(inst->fbUA_Connect.Done == 1)
			{
				inst->fbUA_Connect.Execute = 0;
				inst->pRunClient->Connection.nConnectionHandle = inst->fbUA_Connect.ConnectionHdl;
				inst->fbUA_ConnectionGetStatus.ConnectionHdl = inst->fbUA_Connect.ConnectionHdl;
				inst->fbUA_ConnectionGetStatus.Timeout = inst->pRunClient->Cfg.tAccessTimeout;
				inst->pRunClient->Connection.nConnectTries++;
				inst->pRunClient->Connection.nInterruptedCount = 0;
				inst->nNamespaceIndex = 0;
				inst->nNodeHandleIndex = 0;
				inst->nReadBlockIndex = 0;
				inst->nMethodIndex = 0;
				inst->nSubscriptionIndex = 0;
				inst->nMonItemIndex = 0;
				inst->eStep = eSTEP_GET_NAMESPACE;
			}
			else if(inst->fbUA_Connect.Error == 1)
			{
				inst->fbUA_Connect.Execute = 0;
				inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECT_ERROR;
				inst->pRunClient->Connection.nErrorId = inst->fbUA_Connect.ErrorID;
				inst->pRunClient->State.nClientErroId = inst->fbUA_Connect.ErrorID;
				strcpy(inst->pRunClient->State.sClientErrorText, "Error on connecting: ");
				STRING sHelp[64];
				BrbUaGetStatusCodeText(inst->pRunClient->State.nClientErroId, sHelp, sizeof(sHelp));
				BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
				inst->pRunClient->Connection.nConnectTries++;
				inst->eStep = eSTEP_CONNECTION_ERROR;
			}
			break;

		case eSTEP_CONNECTION_ERROR:
			// Verbindungs-Fehler
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECT_ERROR;
			if(inst->pRunClient->eCmd == eBRB_RCCLTCMD_CONNECT)
			{
				inst->eStep = eSTEP_WAIT_FOR_CMD_CONNECT;
			}
			break;

		case eSTEP_GET_NAMESPACE:
			// NamespaceIndex ermitteln
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTING;
			if(inst->pRunClient->Namespaces.nNamespaceCount > 0 && inst->pRunClient->Namespaces.pNamespaces != 0)
			{
				if(inst->nNamespaceIndex < inst->pRunClient->Namespaces.nNamespaceCount)
				{
					BrbUaRcNamespace_TYP* pNamespace = ((BrbUaRcNamespace_TYP*)inst->pRunClient->Namespaces.pNamespaces) + inst->nNamespaceIndex;
					inst->fbUA_GetNamespaceIndex.Execute = 1;
					inst->fbUA_GetNamespaceIndex.ConnectionHdl =  inst->pRunClient->Connection.nConnectionHandle;
					BrbStringCopy(inst->fbUA_GetNamespaceIndex.NamespaceUri, pNamespace->sNamespaceUri, sizeof(inst->fbUA_GetNamespaceIndex.NamespaceUri));
					inst->fbUA_GetNamespaceIndex.Timeout = inst->pRunClient->Cfg.tAccessTimeout;
					if(inst->fbUA_GetNamespaceIndex.Done == 1)
					{
						inst->fbUA_GetNamespaceIndex.Execute = 0;
						pNamespace->nNamespaceIndex = inst->fbUA_GetNamespaceIndex.NamespaceIndex;
						pNamespace->nErrorId = 0x00000000; // = Good
						inst->nNamespaceIndex += 1;
					}
					else if(inst->fbUA_GetNamespaceIndex.Error == 1)
					{
						inst->fbUA_GetNamespaceIndex.Execute = 0;
						pNamespace->nNamespaceIndex = 0;
						pNamespace->nErrorId = inst->fbUA_GetNamespaceIndex.ErrorID;
						inst->pRunClient->State.nClientErroId = inst->fbUA_GetNamespaceIndex.ErrorID;
						strcpy(inst->pRunClient->State.sClientErrorText, "Cyclic error on getting Namespace#");
						STRING sHelp[16];
						brsitoa(inst->nNamespaceIndex, (UDINT)&sHelp);
						BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
						inst->nNamespaceIndex += 1;
					}
				}
				else
				{
					inst->eStep = eSTEP_GET_NODE_HANDLES_NS;
				}
			}
			else
			{
				// Keine Namespaces: Andere Eintragungen mache keinen Sinn
				inst->nSubscriptionIndex = 0;
				inst->nEventItemIndex = -1;
				inst->eStep = eSTEP_CONNECTED;
			}
			break;

		case eSTEP_GET_NODE_HANDLES_NS:
			// Bei allen NodeHandles den ServerNamespaceIndex eintragen (in 64-Blöcken)
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_WAIT_FOR_CONNECT;
			if(inst->pRunClient->NodeHandles.nNodeHandleCount > 0 && inst->pRunClient->NodeHandles.pDatObjNamespaceIndices != 0 && inst->pRunClient->NodeHandles.pNodeIds != 0 && inst->pRunClient->NodeHandles.pNodeHandleErrorIds != 0 && inst->pRunClient->NodeHandles.pNodeHandles != 0)
			{
				DINT nRemainingItemsCount = inst->pRunClient->NodeHandles.nNodeHandleCount - inst->nNodeHandleIndex;
				if(nRemainingItemsCount > 0)
				{
					UINT nItemCount = (UINT)nRemainingItemsCount;
					if(nRemainingItemsCount > 64)
					{
						nItemCount = 64;
					}
					for(inst->nLoopIndex=0; inst->nLoopIndex < nItemCount; inst->nLoopIndex++)
					{
						// ServerNamespaceIndex aus geparsten DatObjNamespaceIndex für jedes NodeHandle ermitteln
						UINT nDatObjNamespaceIndex = *(((UINT*)(inst->pRunClient->NodeHandles.pDatObjNamespaceIndices)) + inst->nNodeHandleIndex + inst->nLoopIndex);
						UANodeID* pNodeId = ((UANodeID*)inst->pRunClient->NodeHandles.pNodeIds) + inst->nLoopIndex + inst->nNodeHandleIndex;
						pNodeId->NamespaceIndex = BrbUaRcGetSrvNamespace(inst->pRunClient, nDatObjNamespaceIndex, 0);
					}
					inst->nNodeHandleIndex += nItemCount;
				}
				else
				{
					inst->nNodeHandleIndex = 0;
					inst->eStep = eSTEP_GET_NODE_HANDLE;
				}
			}
			else
			{
				inst->eStep = eSTEP_GET_NODE_HANDLE;
			}
			break;

		case eSTEP_GET_NODE_HANDLE:
			// NodeHandle ermitteln (in 64-Blöcken)
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTING;
			if(inst->pRunClient->NodeHandles.nNodeHandleCount > 0 && inst->pRunClient->NodeHandles.pDatObjNamespaceIndices != 0 && inst->pRunClient->NodeHandles.pNodeIds != 0 && inst->pRunClient->NodeHandles.pNodeHandleErrorIds != 0 && inst->pRunClient->NodeHandles.pNodeHandles != 0)
			{
				if(inst->nNodeHandleIndex < inst->pRunClient->NodeHandles.nNodeHandleCount)
				{
					inst->fbUA_NodeGetHandleList.Execute = 1;
					inst->fbUA_NodeGetHandleList.ConnectionHdl = inst->pRunClient->Connection.nConnectionHandle;
					DINT nRemainingItemsCount = inst->pRunClient->NodeHandles.nNodeHandleCount - inst->nNodeHandleIndex;
					UINT nNodeCount = (UINT)nRemainingItemsCount;
					if(nRemainingItemsCount > 64)
					{
						nNodeCount = 64;
					}
					inst->fbUA_NodeGetHandleList.NodeIDCount = nNodeCount;
					memset(&inst->fbUA_NodeGetHandleList.NodeIDs, 0, sizeof(inst->fbUA_NodeGetHandleList.NodeIDs));
					memcpy(&inst->fbUA_NodeGetHandleList.NodeIDs, (USINT*)(((UANodeID*)inst->pRunClient->NodeHandles.pNodeIds) + inst->nNodeHandleIndex), nNodeCount * sizeof(UANodeID));
					memset(&inst->fbUA_NodeGetHandleList.NodeErrorIDs, 0, sizeof(inst->fbUA_NodeGetHandleList.NodeErrorIDs));
					inst->fbUA_NodeGetHandleList.Timeout = inst->pRunClient->Cfg.tAccessTimeout;
					inst->eStep = eSTEP_GET_NODE_HANDLE_WAIT;
				}
				else
				{
					inst->eStep = eSTEP_GET_READITEMS_NS;
				}
			}
			else
			{
				inst->eStep = eSTEP_GET_READITEMS_NS;
			}
			break;

		case eSTEP_GET_NODE_HANDLE_WAIT:
			// Warten, bis NodeHandle-Block ermittelt wurde
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTING;
			if(inst->fbUA_NodeGetHandleList.Done == 1)
			{
				inst->fbUA_NodeGetHandleList.Execute = 0;
				// Handles und NodeErrorId's aus dem FB holen
				for(inst->nLoopIndex=0; inst->nLoopIndex<inst->fbUA_NodeGetHandleList.NodeIDCount; inst->nLoopIndex++)
				{
					*(((DWORD*)inst->pRunClient->NodeHandles.pNodeHandles) + inst->nNodeHandleIndex + inst->nLoopIndex) = inst->fbUA_NodeGetHandleList.NodeHdls[inst->nLoopIndex];
					*(((DWORD*)inst->pRunClient->NodeHandles.pNodeHandleErrorIds) + inst->nNodeHandleIndex + inst->nLoopIndex) = inst->fbUA_NodeGetHandleList.NodeErrorIDs[inst->nLoopIndex];
				}
				// Nächsten Block
				inst->nNodeHandleIndex += inst->fbUA_NodeGetHandleList.NodeIDCount;
				inst->eStep = eSTEP_GET_NODE_HANDLE;
			}
			else if(inst->fbUA_NodeGetHandleList.Error == 1)
			{
				inst->fbUA_NodeGetHandleList.Execute = 0;
				// Handles und NodeErrorId's aus dem FB holen
				for(inst->nLoopIndex=0; inst->nLoopIndex<inst->fbUA_NodeGetHandleList.NodeIDCount; inst->nLoopIndex++)
				{
					*(((DWORD*)inst->pRunClient->NodeHandles.pNodeHandles) + inst->nNodeHandleIndex + inst->nLoopIndex) = inst->fbUA_NodeGetHandleList.NodeHdls[inst->nLoopIndex];
					*(((DWORD*)inst->pRunClient->NodeHandles.pNodeHandleErrorIds) + inst->nNodeHandleIndex + inst->nLoopIndex) = inst->fbUA_NodeGetHandleList.NodeErrorIDs[inst->nLoopIndex];
				}
				inst->pRunClient->State.nClientErroId = inst->fbUA_NodeGetHandleList.ErrorID;
				strcpy(inst->pRunClient->State.sClientErrorText, "Cyclic error on getting NodeHandles #");
				STRING sHelp[16];
				brsitoa(inst->nNodeHandleIndex, (UDINT)&sHelp);
				BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
				BrbStringCat(inst->pRunClient->State.sClientErrorText, " to #", sizeof(inst->pRunClient->State.sClientErrorText));
				brsitoa(inst->fbUA_NodeGetHandleList.NodeIDCount-1, (UDINT)&sHelp);
				BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
				// Nächsten Block
				inst->nNodeHandleIndex += inst->fbUA_NodeGetHandleList.NodeIDCount;
				inst->eStep = eSTEP_GET_NODE_HANDLE;
			}
			break;

		case eSTEP_GET_READITEMS_NS:
			// Bei allen ReadItems aller ReadBlocks den ServerNamespaceIndex eintragen
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTING;
			if(inst->pRunClient->ReadBlocks.nBlockCount > 0 && inst->pRunClient->ReadBlocks.pBlocks != 0)
			{
				if(inst->nReadBlockIndex < inst->pRunClient->ReadBlocks.nBlockCount)
				{
					BrbUaRcReadBlockIntern_TYP* pReadBlock = (((BrbUaRcReadBlockIntern_TYP*)inst->pRunClient->ReadBlocks.pBlocks)  + inst->nReadBlockIndex);
					for(inst->nLoopIndex=0; inst->nLoopIndex < pReadBlock->nReadItemCount; inst->nLoopIndex++)
					{
						UINT nDatObjNamespaceIndex = *(((UINT*)(pReadBlock->pRiDatObjNamespaceIndices)) + inst->nLoopIndex);
						UANodeID* pNodeId = ((UANodeID*)pReadBlock->pRiNodeIds) + inst->nLoopIndex;
						pNodeId->NamespaceIndex = BrbUaRcGetSrvNamespace(inst->pRunClient, nDatObjNamespaceIndex, 0);
					}
					inst->nReadBlockIndex += 1;
				}
				else
				{
					inst->nReadBlockIndex = 0;
					inst->eStep = eSTEP_GET_WRITEITEMS_NS;
				}
			}
			else
			{
				inst->eStep = eSTEP_GET_WRITEITEMS_NS;
			}
			break;
		
		case eSTEP_GET_WRITEITEMS_NS:
			// Bei allen WriteItems aller WriteBlocks den ServerNamespaceIndex eintragen
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTING;
			if(inst->pRunClient->WriteBlocks.nBlockCount > 0 && inst->pRunClient->WriteBlocks.pBlocks != 0)
			{
				if(inst->nWriteBlockIndex < inst->pRunClient->WriteBlocks.nBlockCount)
				{
					BrbUaRcWriteBlockIntern_TYP* pWriteBlock = (((BrbUaRcWriteBlockIntern_TYP*)inst->pRunClient->WriteBlocks.pBlocks)  + inst->nWriteBlockIndex);
					for(inst->nLoopIndex=0; inst->nLoopIndex < pWriteBlock->nWriteItemCount; inst->nLoopIndex++)
					{
						UINT nDatObjNamespaceIndex = *(((UINT*)(pWriteBlock->pWiDatObjNamespaceIndices)) + inst->nLoopIndex);
						UANodeID* pNodeId = ((UANodeID*)pWriteBlock->pWiNodeIds) + inst->nLoopIndex;
						pNodeId->NamespaceIndex = BrbUaRcGetSrvNamespace(inst->pRunClient, nDatObjNamespaceIndex, 0);
					}
					inst->nWriteBlockIndex += 1;
				}
				else
				{
					inst->nWriteBlockIndex = 0;
					inst->eStep = eSTEP_GET_METHOD_HANDLES_NS;
				}
			}
			else
			{
				inst->eStep = eSTEP_GET_METHOD_HANDLES_NS;
			}
			break;
		
		case eSTEP_GET_METHOD_HANDLES_NS:
			// Bei allen Methods den ServerNamespaceIndex eintragen (in 64-Blöcken)
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_WAIT_FOR_CONNECT;
			if(inst->pRunClient->Methods.nMethodCount > 0 && inst->pRunClient->Methods.pMethods != 0)
			{
				DINT nRemainingItemsCount = inst->pRunClient->Methods.nMethodCount - inst->nMethodIndex;
				if(nRemainingItemsCount > 0)
				{
					UINT nItemCount = (UINT)nRemainingItemsCount;
					if(nRemainingItemsCount > 64)
					{
						nItemCount = 64;
					}
					for(inst->nLoopIndex=0; inst->nLoopIndex < nItemCount; inst->nLoopIndex++)
					{
						// ServerNamespaceIndex aus geparsten DatObjNamespaceIndex für jedes NodeHandle ermitteln
						BrbUaRcMethodIntern_TYP* pMethod = (((BrbUaRcMethodIntern_TYP*)inst->pRunClient->Methods.pMethods)  + inst->nMethodIndex + inst->nLoopIndex);
						pMethod->ObjectNodeId.NamespaceIndex = BrbUaRcGetSrvNamespace(inst->pRunClient, pMethod->nDatObjNamespaceIndex, 0);
						pMethod->MethodNodeId.NamespaceIndex = pMethod->ObjectNodeId.NamespaceIndex;
					}
					inst->nMethodIndex += nItemCount;
				}
				else
				{
					inst->nMethodIndex = 0;
					inst->eStep = eSTEP_GET_METHOD_HANDLE;
				}
			}
			else
			{
				inst->eStep = eSTEP_GET_METHOD_HANDLE;
			}
			break;

		case eSTEP_GET_METHOD_HANDLE:
			// MethodHandle ermitteln
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTING;
			if(inst->pRunClient->Methods.nMethodCount > 0 && inst->pRunClient->Methods.pMethods != 0)
			{
				if(inst->nMethodIndex < inst->pRunClient->Methods.nMethodCount)
				{
					BrbUaRcMethodIntern_TYP* pMethod = (((BrbUaRcMethodIntern_TYP*)inst->pRunClient->Methods.pMethods)  + inst->nMethodIndex);
					inst->fbUA_MethodGetHandle.Execute = 1;
					inst->fbUA_MethodGetHandle.ConnectionHdl =  inst->pRunClient->Connection.nConnectionHandle;
					memcpy(&inst->fbUA_MethodGetHandle.MethodNodeID, &pMethod->MethodNodeId, sizeof(UANodeID));
					memcpy(&inst->fbUA_MethodGetHandle.ObjectNodeID, &pMethod->ObjectNodeId, sizeof(UANodeID));
					inst->fbUA_MethodGetHandle.Timeout = inst->pRunClient->Cfg.tAccessTimeout;
					if(inst->fbUA_MethodGetHandle.Done == 1)
					{
						inst->fbUA_MethodGetHandle.Execute = 0;
						pMethod->nMethodHandle = inst->fbUA_MethodGetHandle.MethodHdl;
						pMethod->nErrorId = 0x00000000; // = Good
						inst->nMethodIndex += 1;
					}
					else if(inst->fbUA_MethodGetHandle.Error == 1)
					{
						inst->fbUA_MethodGetHandle.Execute = 0;
						pMethod->nMethodHandle = 0;
						pMethod->nErrorId = inst->fbUA_MethodGetHandle.ErrorID;
						inst->pRunClient->State.nClientErroId = inst->fbUA_MethodGetHandle.ErrorID;
						strcpy(inst->pRunClient->State.sClientErrorText, "Cyclic error on getting MethodHandle#");
						STRING sHelp[16];
						brsitoa(inst->nMethodIndex, (UDINT)&sHelp);
						BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
						inst->nMethodIndex += 1;
					}
				}
				else
				{
					inst->eStep = eSTEP_CREATE_SUBSCRIPTION;
				}
			}
			else
			{
				inst->eStep = eSTEP_CREATE_SUBSCRIPTION;
			}
			break;

		case eSTEP_CREATE_SUBSCRIPTION:
			// Subscription erzeugen
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTING;
			if(inst->pRunClient->Subscriptions.nSubscriptionCount > 0 && inst->pRunClient->Subscriptions.pSubscriptions != 0)
			{
				if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount)
				{
					BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions)  + inst->nSubscriptionIndex);
					inst->fbUA_SubscriptionCreate.Execute = 1;
					inst->fbUA_SubscriptionCreate.ConnectionHdl =  inst->pRunClient->Connection.nConnectionHandle;
					inst->fbUA_SubscriptionCreate.PublishingEnable = pSubscription->bPublishingEnable;
					inst->fbUA_SubscriptionCreate.Priority = pSubscription->nPriority;
					inst->fbUA_SubscriptionCreate.Timeout = inst->pRunClient->Cfg.tAccessTimeout;
					inst->fbUA_SubscriptionCreate.PublishingInterval = &pSubscription->tPublishingInterval;
					if(inst->fbUA_SubscriptionCreate.Done == 1)
					{
						inst->fbUA_SubscriptionCreate.Execute = 0;
						pSubscription->nSubscriptionHandle = inst->fbUA_SubscriptionCreate.SubscriptionHdl;
						pSubscription->nErrorId = 0x00000000; // = Good
						// ServerNamespaceIndex aus geparsten DatObjNamespaceIndex für jedes MonitoredItem ermitteln
						for(inst->nLoopIndex=0; inst->nLoopIndex < pSubscription->nMonitoredItemCount; inst->nLoopIndex++)
						{
							UINT nDatObjNamespaceIndex = *(((UINT*)(pSubscription->pMiDatObjNamespaceIndices)) + inst->nLoopIndex);
							UANodeID* pNodeId = ((UANodeID*)pSubscription->pMiNodeIds) + inst->nLoopIndex;
							pNodeId->NamespaceIndex = BrbUaRcGetSrvNamespace(inst->pRunClient, nDatObjNamespaceIndex, 0);
						}
						// ServerNamespaceIndex aus geparsten DatObjNamespaceIndex für jedes EventField ermitteln
						for(inst->nEventItemIndex=0; inst->nEventItemIndex < pSubscription->nEventItemCount; inst->nEventItemIndex++)
						{
							BrbUaRcEventItemIntern_TYP* pEventItem = ((BrbUaRcEventItemIntern_TYP*)pSubscription->pEventItems) + inst->nEventItemIndex;
							for(inst->nEventFieldIndex=0; inst->nEventFieldIndex < pEventItem->nEventFieldCount; inst->nEventFieldIndex++)
							{
								UARelativePath* pSelection = ((UARelativePath*)pEventItem->pEfFieldSelections) + inst->nEventFieldIndex;
								UDINT nPathElementIndex = 0;
								for(nPathElementIndex=0; nPathElementIndex<pSelection->NoOfElements; nPathElementIndex++)
								{
									UARelativePathElement* pPathElement = &pSelection->Elements[nPathElementIndex];
									UINT nDatObjNamespaceIndex = *(((UINT*)(pEventItem->pEfDatObjNamespaceIndices)) + inst->nEventFieldIndex);
									pPathElement->TargetName.NamespaceIndex = BrbUaRcGetSrvNamespace(inst->pRunClient, nDatObjNamespaceIndex, 0);
								}
							}
						}
						inst->nSubscriptionIndex += 1;
					}
					else if(inst->fbUA_SubscriptionCreate.Error == 1)
					{
						inst->fbUA_SubscriptionCreate.Execute = 0;
						pSubscription->nSubscriptionHandle = 0;
						pSubscription->nErrorId = inst->fbUA_SubscriptionCreate.ErrorID;
						inst->pRunClient->State.nClientErroId = inst->fbUA_SubscriptionCreate.ErrorID;
						strcpy(inst->pRunClient->State.sClientErrorText, "Cyclic error on creating Subscription#");
						STRING sHelp[16];
						brsitoa(inst->nSubscriptionIndex, (UDINT)&sHelp);
						BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
						inst->nSubscriptionIndex += 1;
					}
				}
				else
				{
					inst->nSubscriptionIndex = 0;
					inst->nMonItemIndex = 0;
					inst->eStep = eSTEP_GET_MI_NODE_HANDLE;
				}
			}
			else
			{
				inst->nSubscriptionIndex = 0;
				inst->nEventItemIndex = -1;
				inst->eStep = eSTEP_CONNECTED;
			}
			break;
		
		case eSTEP_GET_MI_NODE_HANDLE:
			// NodeHandle für MonitoredItems ermitteln (in 64-Blöcken)
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTING;
			if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount)
			{
				BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex);
				if(pSubscription->nMonitoredItemCount > 0 && 
					pSubscription->pMiDatObjNamespaceIndices != 0 && pSubscription->pMiNodeIds != 0 && 
					pSubscription->pMiNodeHandleErrorIds != 0 && pSubscription->pMiNodeHandles != 0 && 
					pSubscription->pMiNodeAddInfos != 0 && pSubscription->pMiVariables != 0 && 
					pSubscription->pMiQueueSizeOri != 0 && pSubscription->pMiMonitorSettings != 0 &&
					pSubscription->pMiValuesChanged != 0 && pSubscription->pMiRemainingValueCounts != 0 &&
					pSubscription->pMiTimestamps != 0 && pSubscription->pMiNodeQualityIds != 0 &&
					pSubscription->pMiMonitoredItemErrorIds != 0 && pSubscription->pMiMonitoredItemHandles != 0)
				{
					if(inst->nMonItemIndex < pSubscription->nMonitoredItemCount)
					{
						inst->fbUA_NodeGetHandleList.Execute = 1;
						inst->fbUA_NodeGetHandleList.ConnectionHdl = inst->pRunClient->Connection.nConnectionHandle;
						DINT nRemainingItemsCount = pSubscription->nMonitoredItemCount - inst->nMonItemIndex;
						UINT nNodeCount = (UINT)nRemainingItemsCount;
						if(nRemainingItemsCount > 64)
						{
							nNodeCount = 64;
						}
						inst->fbUA_NodeGetHandleList.NodeIDCount = nNodeCount;
						memset(&inst->fbUA_NodeGetHandleList.NodeIDs, 0, sizeof(inst->fbUA_NodeGetHandleList.NodeIDs));
						memcpy(&inst->fbUA_NodeGetHandleList.NodeIDs, (USINT*)(((UANodeID*)pSubscription->pMiNodeIds) + inst->nMonItemIndex), nNodeCount * sizeof(UANodeID));
						memset(&inst->fbUA_NodeGetHandleList.NodeHdls, 0, sizeof(inst->fbUA_NodeGetHandleList.NodeHdls));
						memset(&inst->fbUA_NodeGetHandleList.NodeErrorIDs, 0, sizeof(inst->fbUA_NodeGetHandleList.NodeErrorIDs));
						inst->fbUA_NodeGetHandleList.Timeout = inst->pRunClient->Cfg.tAccessTimeout;
						inst->eStep = eSTEP_GET_MI_NODE_HANDLE_WAIT;
					}
					else
					{
						inst->nSubscriptionIndex++;
						inst->nMonItemIndex = 0;
					}
				}
				else
				{
					inst->nSubscriptionIndex++;
					inst->nMonItemIndex = 0;
				}
			}
			else
			{
				inst->nSubscriptionIndex = 0;
				inst->nMonItemIndex = 0;
				inst->eStep = eSTEP_ADD_MI;
			}
			break;

		case eSTEP_GET_MI_NODE_HANDLE_WAIT:
			// Warten, bis NodeHandle-Block ermittelt wurde
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTING;
			if(inst->fbUA_NodeGetHandleList.Done == 1)
			{
				inst->fbUA_NodeGetHandleList.Execute = 0;
				// Handles und NodeErrorId's aus dem FB holen
				BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex);
				for(inst->nLoopIndex=0; inst->nLoopIndex<inst->fbUA_NodeGetHandleList.NodeIDCount; inst->nLoopIndex++)
				{
					*(((DWORD*)pSubscription->pMiNodeHandles) + inst->nMonItemIndex + inst->nLoopIndex) = inst->fbUA_NodeGetHandleList.NodeHdls[inst->nLoopIndex];
					*(((DWORD*)pSubscription->pMiNodeHandleErrorIds) + inst->nMonItemIndex + inst->nLoopIndex) = inst->fbUA_NodeGetHandleList.NodeErrorIDs[inst->nLoopIndex];
					/*
						Ein Originalwert des QueueSize von 0 bedeutet Firmware-Sync-Mode, ein Wert von 1 bedeutet Controller-Sync-Mode auf Seiten des Clients.
						Auf Server-Seite wird der Wert 0 aber auf 1 korrigiert. Um den gewünschten Sync-Mode bei jedem Connect zu erhalten, muss das MonitoredItem
						wieder mit dem Originalwert angemeldet werden.
					*/
					pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex;
					UAMonitoringParameters* pMonitoringSetting = ((UAMonitoringParameters*)pSubscription->pMiMonitorSettings) + inst->nMonItemIndex + inst->nLoopIndex;
					pMonitoringSetting->QueueSize = *(((UINT*)pSubscription->pMiQueueSizeOri) + inst->nMonItemIndex);
				}
				// Nächsten Block
				inst->nMonItemIndex += inst->fbUA_NodeGetHandleList.NodeIDCount;
				inst->eStep = eSTEP_GET_MI_NODE_HANDLE;
			}
			else if(inst->fbUA_NodeGetHandleList.Error == 1)
			{
				inst->fbUA_NodeGetHandleList.Execute = 0;
				// Handles und NodeErrorId's aus dem FB holen
				BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex);
				for(inst->nLoopIndex=0; inst->nLoopIndex<inst->fbUA_NodeGetHandleList.NodeIDCount; inst->nLoopIndex++)
				{
					*(((DWORD*)pSubscription->pMiNodeHandles) + inst->nMonItemIndex + inst->nLoopIndex) = inst->fbUA_NodeGetHandleList.NodeHdls[inst->nLoopIndex];
					*(((DWORD*)pSubscription->pMiNodeHandleErrorIds) + inst->nMonItemIndex + inst->nLoopIndex) = inst->fbUA_NodeGetHandleList.NodeErrorIDs[inst->nLoopIndex];
				}
				inst->pRunClient->State.nClientErroId = inst->fbUA_NodeGetHandleList.ErrorID;
				strcpy(inst->pRunClient->State.sClientErrorText, "Cyclic error on getting MonitorItemHandle from Subscription#");
				STRING sHelp[16];
				brsitoa(inst->nSubscriptionIndex, (UDINT)&sHelp);
				BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
				BrbStringCat(inst->pRunClient->State.sClientErrorText, ", MonitorItems #", sizeof(inst->pRunClient->State.sClientErrorText));
				brsitoa(inst->nMonItemIndex, (UDINT)&sHelp);
				BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
				BrbStringCat(inst->pRunClient->State.sClientErrorText, " to #", sizeof(inst->pRunClient->State.sClientErrorText));
				brsitoa(inst->fbUA_NodeGetHandleList.NodeIDCount-1, (UDINT)&sHelp);
				BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
				// Nächsten Block
				inst->nMonItemIndex += inst->fbUA_NodeGetHandleList.NodeIDCount;
				inst->eStep = eSTEP_GET_MI_NODE_HANDLE;
			}
			break;

		case eSTEP_ADD_MI:
			// MonitoredItem hinzufügen (in 64-Blöcken)
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTING;
			if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount)
			{
				BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex);
				if(pSubscription->nMonitoredItemCount > 0 && 
					pSubscription->pMiDatObjNamespaceIndices != 0 && pSubscription->pMiNodeIds != 0 && 
					pSubscription->pMiNodeHandleErrorIds != 0 && pSubscription->pMiNodeHandles != 0 && 
					pSubscription->pMiNodeAddInfos != 0 && pSubscription->pMiVariables != 0 && 
					pSubscription->pMiQueueSizeOri != 0 && pSubscription->pMiMonitorSettings != 0 &&
					pSubscription->pMiValuesChanged != 0 && pSubscription->pMiRemainingValueCounts != 0 &&
					pSubscription->pMiTimestamps != 0 && pSubscription->pMiNodeQualityIds != 0 &&
					pSubscription->pMiMonitoredItemErrorIds != 0 && pSubscription->pMiMonitoredItemHandles != 0)
				{
					if(inst->nMonItemIndex < pSubscription->nMonitoredItemCount)
					{
						inst->fbUA_MonitoredItemAddList.Execute = 1;
						inst->fbUA_MonitoredItemAddList.SubscriptionHdl = pSubscription->nSubscriptionHandle;
						DINT nRemainingItemsCount = pSubscription->nMonitoredItemCount - inst->nMonItemIndex;
						UINT nNodeCount = (UINT)nRemainingItemsCount;
						if(nRemainingItemsCount > 64)
						{
							nNodeCount = 64;
						}
						inst->fbUA_MonitoredItemAddList.NodeHdlCount = nNodeCount;
						memset(&inst->fbUA_MonitoredItemAddList.NodeHdls, 0, sizeof(inst->fbUA_MonitoredItemAddList.NodeHdls));
						memcpy(&inst->fbUA_MonitoredItemAddList.NodeHdls, (USINT*)(((UANodeID*)pSubscription->pMiNodeHandles) + inst->nMonItemIndex), nNodeCount * sizeof(DWORD));
						memset(&inst->fbUA_MonitoredItemAddList.NodeAddInfos, 0, sizeof(inst->fbUA_MonitoredItemAddList.NodeAddInfos));
						memcpy(&inst->fbUA_MonitoredItemAddList.NodeAddInfos, (USINT*)(((UANodeID*)pSubscription->pMiNodeAddInfos) + inst->nMonItemIndex), nNodeCount * sizeof(UANodeAdditionalInfo));
						inst->fbUA_MonitoredItemAddList.Timeout = inst->pRunClient->Cfg.tAccessTimeout;
						memset(&inst->fbUA_MonitoredItemAddList.NodeErrorIDs, 0, sizeof(inst->fbUA_MonitoredItemAddList.NodeErrorIDs));
						memset(&inst->fbUA_MonitoredItemAddList.MonitoredItemHdls, 0, sizeof(inst->fbUA_MonitoredItemAddList.MonitoredItemHdls));
						inst->fbUA_MonitoredItemAddList.Variables = (void*)(((USINT*)pSubscription->pMiVariables) + ((UDINT)inst->nMonItemIndex * sizeof(inst->sVarName)));
						inst->fbUA_MonitoredItemAddList.MonitoringSettings = (void*)(((UAMonitoringParameters*)pSubscription->pMiMonitorSettings) + inst->nMonItemIndex);
						inst->fbUA_MonitoredItemAddList.ValuesChanged = (void*)(((BOOL*)pSubscription->pMiValuesChanged) + inst->nMonItemIndex);
						inst->fbUA_MonitoredItemAddList.RemainingValueCount = (void*)(((UINT*)pSubscription->pMiRemainingValueCounts) + inst->nMonItemIndex);
						inst->fbUA_MonitoredItemAddList.TimeStamps = (void*)(((DT*)pSubscription->pMiTimestamps) + inst->nMonItemIndex);
						inst->fbUA_MonitoredItemAddList.NodeQualityIDs = (void*)(((DWORD*)pSubscription->pMiNodeQualityIds) + inst->nMonItemIndex);
						inst->eStep = eSTEP_ADD_MI_WAIT;
					}
					else
					{
						inst->nSubscriptionIndex++;
						inst->nMonItemIndex = 0;
					}
				}
				else
				{
					inst->nSubscriptionIndex++;
					inst->nMonItemIndex = 0;
				}
			}
			else
			{
				inst->nSubscriptionIndex = 0;
				inst->nEventItemIndex = 0;
				inst->eStep = eSTEP_GET_EI_NODE_HANDLE;
			}
			break;

		case eSTEP_ADD_MI_WAIT:
			// Warten, bis NodeHandle-Block ermittelt wurde
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTING;
			if(inst->fbUA_MonitoredItemAddList.Done == 1)
			{
				inst->fbUA_MonitoredItemAddList.Execute = 0;
				// Handles und NodeErrorId's aus dem FB holen
				BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex);
				for(inst->nLoopIndex=0; inst->nLoopIndex<inst->fbUA_MonitoredItemAddList.NodeHdlCount; inst->nLoopIndex++)
				{
					*(((DWORD*)pSubscription->pMiMonitoredItemHandles) + inst->nMonItemIndex + inst->nLoopIndex) = inst->fbUA_MonitoredItemAddList.MonitoredItemHdls[inst->nLoopIndex];
					*(((DWORD*)pSubscription->pMiMonitoredItemErrorIds) + inst->nMonItemIndex + inst->nLoopIndex) = inst->fbUA_MonitoredItemAddList.NodeErrorIDs[inst->nLoopIndex];
				}
				// Nächsten Block
				inst->nMonItemIndex += inst->fbUA_MonitoredItemAddList.NodeHdlCount;
				inst->eStep = eSTEP_ADD_MI;
			}
			else if(inst->fbUA_MonitoredItemAddList.Error == 1)
			{
				inst->fbUA_MonitoredItemAddList.Execute = 0;
				// Handles und NodeErrorId's aus dem FB holen
				BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex);
				for(inst->nLoopIndex=0; inst->nLoopIndex<inst->fbUA_MonitoredItemAddList.NodeHdlCount; inst->nLoopIndex++)
				{
					*(((DWORD*)pSubscription->pMiMonitoredItemHandles) + inst->nMonItemIndex + inst->nLoopIndex) = inst->fbUA_MonitoredItemAddList.MonitoredItemHdls[inst->nLoopIndex];
					*(((DWORD*)pSubscription->pMiMonitoredItemErrorIds) + inst->nMonItemIndex + inst->nLoopIndex) = inst->fbUA_MonitoredItemAddList.NodeErrorIDs[inst->nLoopIndex];
				}
				inst->pRunClient->State.nClientErroId = inst->fbUA_MonitoredItemAddList.ErrorID;
				strcpy(inst->pRunClient->State.sClientErrorText, "Cyclic error on adding MonitorItems from Subscription#");
				STRING sHelp[16];
				brsitoa(inst->nSubscriptionIndex, (UDINT)&sHelp);
				BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
				BrbStringCat(inst->pRunClient->State.sClientErrorText, ", MonitorItems #", sizeof(inst->pRunClient->State.sClientErrorText));
				brsitoa(inst->nMonItemIndex, (UDINT)&sHelp);
				BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
				BrbStringCat(inst->pRunClient->State.sClientErrorText, " to #", sizeof(inst->pRunClient->State.sClientErrorText));
				brsitoa(inst->fbUA_MonitoredItemAddList.NodeHdlCount-1, (UDINT)&sHelp);
				BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
				// Nächsten Block
				inst->nMonItemIndex += inst->fbUA_MonitoredItemAddList.NodeHdlCount;
				inst->eStep = eSTEP_ADD_MI;
			}
			break;

		case eSTEP_GET_EI_NODE_HANDLE:
			// NodeHandle für EventItems ermitteln
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTING;
			if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount)
			{
				BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex);
				if(pSubscription->nEventItemCount > 0 && pSubscription->pEventItems != 0)
				{
					if(inst->nEventItemIndex < pSubscription->nEventItemCount)
					{
						BrbUaRcEventItemIntern_TYP* pEventItem = ((BrbUaRcEventItemIntern_TYP*)pSubscription->pEventItems) + inst->nEventItemIndex;
						// ReceiveCount zurücksetzen
						pEventItem->nReceiveCount = 0;
						// ServerNamespaceIndex aus geparsten DatObjNamespaceIndex für EventNode ermitteln
						pEventItem->EventNodeId.NamespaceIndex = BrbUaRcGetSrvNamespace(inst->pRunClient, pEventItem->nEventDatObjNamespaceIndex, 0);
						// ServerNamespaceIndex aus geparsten DatObjNamespaceIndex für TypeNode ermitteln
						pEventItem->TypeNodeId.NamespaceIndex = BrbUaRcGetSrvNamespace(inst->pRunClient, pEventItem->nTypeDatObjNamespaceIndex, 0);
						inst->fbUA_NodeGetHandle.Execute = 1;
						inst->fbUA_NodeGetHandle.ConnectionHdl = inst->pRunClient->Connection.nConnectionHandle;
						memcpy(&inst->fbUA_NodeGetHandle.NodeID, &pEventItem->EventNodeId, sizeof(UANodeID));
						inst->fbUA_NodeGetHandle.Timeout = inst->pRunClient->Cfg.tAccessTimeout;
						if(inst->fbUA_NodeGetHandle.Done == 1)
						{
							inst->fbUA_NodeGetHandle.Execute = 0;
							pEventItem->nEventNodeHandle = inst->fbUA_NodeGetHandle.NodeHdl;
							pEventItem->nEventNodeHandleErrorId = inst->fbUA_NodeGetHandle.ErrorID;
							inst->nEventItemIndex++;
						}
						else if(inst->fbUA_NodeGetHandle.Error == 1)
						{
							inst->fbUA_NodeGetHandle.Execute = 0;
							pEventItem->nEventNodeHandle = 0;
							pEventItem->nEventNodeHandleErrorId = inst->fbUA_NodeGetHandle.ErrorID;
							inst->pRunClient->State.nClientErroId = inst->fbUA_NodeGetHandle.ErrorID;
							strcpy(inst->pRunClient->State.sClientErrorText, "Cyclic error on getting event handle from Subscription#");
							STRING sHelp[16];
							brsitoa(inst->nSubscriptionIndex, (UDINT)&sHelp);
							BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
							BrbStringCat(inst->pRunClient->State.sClientErrorText, ", EventItem#", sizeof(inst->pRunClient->State.sClientErrorText));
							brsitoa(inst->nEventItemIndex, (UDINT)&sHelp);
							BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
							inst->nEventItemIndex++;
						}
					}
					else
					{
						inst->nSubscriptionIndex++;
						inst->nEventItemIndex = 0;
					}
				}
				else
				{
					inst->nSubscriptionIndex++;
					inst->nEventItemIndex = 0;
				}
			}
			else
			{
				inst->nSubscriptionIndex = 0;
				inst->nEventItemIndex = 0;
				inst->eStep = eSTEP_ADD_EI;
			}
			break;

		case eSTEP_ADD_EI:
			// EventItem hinzufügen
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTING;
			if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount)
			{
				BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex);
				if(pSubscription->nEventItemCount > 0 && pSubscription->pEventItems != 0)
				{
					if(inst->nEventItemIndex < pSubscription->nEventItemCount)
					{
						BrbUaRcEventItemIntern_TYP* pEventItem = ((BrbUaRcEventItemIntern_TYP*)pSubscription->pEventItems) + inst->nEventItemIndex;
						inst->fbUA_EventItemAdd.Execute = 1;
						inst->fbUA_EventItemAdd.SubscriptionHdl = pSubscription->nSubscriptionHandle;
						inst->fbUA_EventItemAdd.NodeHdl = pEventItem->nEventNodeHandle;
						memcpy(&inst->fbUA_EventItemAdd.EventType, &pEventItem->TypeNodeId, sizeof(UANodeID));
						inst->fbUA_EventItemAdd.EventFieldSelectionCount = pEventItem->nEventFieldCount;
						memcpy(&inst->fbUA_EventItemAdd.EventFieldSelections, (USINT*)pEventItem->pEfFieldSelections, pEventItem->nEventFieldCount * sizeof(UARelativePath));
						inst->fbUA_EventItemAdd.Timeout = pEventItem->tTimeout;
						inst->fbUA_EventItemAdd.EventFields = (void*)(((USINT*)pEventItem->pEfFieldVars) + ((UDINT)inst->nEventItemIndex * sizeof(inst->sVarName)));
						inst->fbUA_EventItemAdd.EventFields = (void*)pEventItem->pEfFieldVars;
						if(inst->fbUA_EventItemAdd.Done == 1)
						{
							inst->fbUA_EventItemAdd.Execute = 0;
							pEventItem->nEventItemHandle = inst->fbUA_EventItemAdd.EventItemHdl;
							pEventItem->nEventItemErrorId = inst->fbUA_EventItemAdd.ErrorID;
							inst->nEventItemIndex++;
						}
						else if(inst->fbUA_EventItemAdd.Error == 1)
						{
							inst->fbUA_EventItemAdd.Execute = 0;
							pEventItem->nEventItemHandle = inst->fbUA_EventItemAdd.EventItemHdl;
							pEventItem->nEventItemErrorId = inst->fbUA_EventItemAdd.ErrorID;
							inst->pRunClient->State.nClientErroId = inst->fbUA_EventItemAdd.ErrorID;
							strcpy(inst->pRunClient->State.sClientErrorText, "Cyclic error on adding EventItem from Subscription#");
							STRING sHelp[16];
							brsitoa(inst->nSubscriptionIndex, (UDINT)&sHelp);
							BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
							BrbStringCat(inst->pRunClient->State.sClientErrorText, ", EventItem#", sizeof(inst->pRunClient->State.sClientErrorText));
							brsitoa(inst->nEventItemIndex, (UDINT)&sHelp);
							BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
							inst->nEventItemIndex++;
						}
					}
					else
					{
						inst->nSubscriptionIndex++;
						inst->nEventItemIndex = 0;
					}
				}
				else
				{
					inst->nSubscriptionIndex++;
					inst->nEventItemIndex = 0;
				}
			}
			else
			{
				inst->nSubscriptionIndex = 0;
				inst->nEventItemIndex = -1;
				inst->eStep = eSTEP_CONNECTED;
			}
			break;

		case eSTEP_CONNECTED:
			// Verbindungs-Status abfragen und auswerten
			inst->fbUA_ConnectionGetStatus.Execute = 1;
			inst->pRunClient->State.ConnectionStatus.eConnectionStatus = inst->fbUA_ConnectionGetStatus.ConnectionStatus;
			inst->pRunClient->State.ConnectionStatus.eServerState = inst->fbUA_ConnectionGetStatus.ServerState;
			inst->pRunClient->State.ConnectionStatus.nServiceLevel = inst->fbUA_ConnectionGetStatus.ServiceLevel;
			if(inst->fbUA_ConnectionGetStatus.Done == 1)
			{
				inst->fbUA_ConnectionGetStatus.Execute = 0;
				if(inst->fbUA_ConnectionGetStatus.ConnectionStatus != UACS_Connected)
				{
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CON_INTERRUPTED;
				}
				else
				{
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_CONNECTED;
				}
			}
			else if(inst->fbUA_ConnectionGetStatus.Error == 1)
			{
				inst->fbUA_ConnectionGetStatus.Execute = 0;
			}
			// Verbindungs-Unterbrechungen zählen
			if(inst->pRunClient->State.eClientState == eBRB_RCCLTSTATE_CON_INTERRUPTED && inst->eClientStateOld == eBRB_RCCLTSTATE_CONNECTED)
			{
				inst->pRunClient->Connection.nInterruptedCount++;
			}
			inst->eClientStateOld = inst->pRunClient->State.eClientState;
			// Received-Flag aller Event-Items löschen (das Flag darf jeweils nur für 1 Zyklus gesetzt bleiben)
			{
				UINT nSubscriptionIndex = 0;
				for(nSubscriptionIndex=0; nSubscriptionIndex<inst->pRunClient->Subscriptions.nSubscriptionCount; nSubscriptionIndex++)
				{
					BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + nSubscriptionIndex);
					UINT nEventItemIndex = 0;
					for(nEventItemIndex=0; nEventItemIndex<pSubscription->nEventItemCount; nEventItemIndex++)
					{
						BrbUaRcEventItemIntern_TYP* pEventItem = ((BrbUaRcEventItemIntern_TYP*)pSubscription->pEventItems) + nEventItemIndex;
						if(pEventItem->bCallOperate == 1)
						{
							// Flag muss gelöscht werden
							pEventItem->bEventReceived = 0;
						}
					}
				}
			}
			// Nächstes EventItems für Operate suchen
			if(inst->bEventItemFound == 0 && inst->pRunClient->Subscriptions.nEventItemsCountTotal > 0)
			{
				BOOL bLeaveLoop = 0;
				UDINT nEventItemsCheckedCount = 0;
				do
				{
					BOOL bNextEventItemFound = GetNextEventItem(inst->pRunClient, &inst->nSubscriptionIndex, &inst->nEventItemIndex);
					if(bNextEventItemFound == 1)
					{
						nEventItemsCheckedCount++;
						BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex);
						BrbUaRcEventItemIntern_TYP* pEventItem = ((BrbUaRcEventItemIntern_TYP*)pSubscription->pEventItems) + inst->nEventItemIndex;
						if(pEventItem->bCallOperate == 1)
						{
							// EventItem für Operate gefunden
							inst->bEventItemFound = 1;
							bLeaveLoop = 1;
						}
						else if(nEventItemsCheckedCount >= inst->pRunClient->Subscriptions.nEventItemsCountTotal)
						{
							// Wieder beim zuletzt behandelten EventItem angelangt 
							bLeaveLoop = 1;
						}
					}
					else
					{
						bLeaveLoop = 1;
					}
				} while (bLeaveLoop == 0);
			}
			// Operate für EventItems aufrufen
			if(inst->pRunClient->State.eClientState == eBRB_RCCLTSTATE_CONNECTED)
			{
				if(inst->bEventItemFound == 1)
				{
					BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex);
					BrbUaRcEventItemIntern_TYP* pEventItem = ((BrbUaRcEventItemIntern_TYP*)pSubscription->pEventItems) + inst->nEventItemIndex;
					inst->fbUA_EventItemOperate.Execute = 1;
					inst->fbUA_EventItemOperate.SubscriptionHdl = pSubscription->nSubscriptionHandle;
					inst->fbUA_EventItemOperate.EventItemHdl = pEventItem->nEventItemHandle;
					inst->fbUA_EventItemOperate.Timeout = pEventItem->tTimeout;
					if(inst->fbUA_EventItemOperate.Done == 1)
					{
						inst->fbUA_EventItemOperate.Execute = 0;
						if(inst->fbUA_EventItemOperate.EventProcessed == 1)
						{
							pEventItem->nReceiveCount++;
						}
						inst->pEventItemReceived = &pEventItem->bEventReceived;
						*inst->pEventItemReceived = inst->fbUA_EventItemOperate.EventProcessed;
						inst->bEventItemFound = 0;
					}
					else if(inst->fbUA_EventItemOperate.Error == 1)
					{
						inst->fbUA_EventItemOperate.Execute = 0;
						inst->pEventItemReceived = &pEventItem->bEventReceived;
						*inst->pEventItemReceived = 0;
						inst->pRunClient->State.nClientErroId = inst->fbUA_EventItemOperate.ErrorID;
						strcpy(inst->pRunClient->State.sClientErrorText, "Cyclic error on operating EventItem from Subscription#");
						STRING sHelp[16];
						brsitoa(inst->nSubscriptionIndex, (UDINT)&sHelp);
						BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
						BrbStringCat(inst->pRunClient->State.sClientErrorText, ", EventItem#", sizeof(inst->pRunClient->State.sClientErrorText));
						brsitoa(inst->nEventItemIndex, (UDINT)&sHelp);
						BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
						inst->bEventItemFound = 0;
					}
				}
			}
			else
			{
				inst->fbUA_EventItemOperate.Execute = 0;
			}
			// Disconnect-Kommando prüfen
			if(inst->pRunClient->eCmd == eBRB_RCCLTCMD_DISCONNECT)
			{
				inst->fbUA_ConnectionGetStatus.Execute = 0;
				inst->fbUA_EventItemOperate.Execute = 0;
				inst->pRunClient->eCmd = eBRB_RCCLTCMD_NONE;
				inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_DISCONNECTING;
				inst->nSubscriptionIndex = 0;
				inst->nMonItemIndex = 0;
				inst->nMethodIndex = 0;
				inst->nNodeHandleIndex = 0;
				inst->nNamespaceIndex = 0;
				inst->eStep = eSTEP_DISCONNECT;
			}
			else
			{
				inst->pRunClient->eCmd = eBRB_RCCLTCMD_NONE;
			}
			break;

		//---------------------------------------------------------------------------------------------------------------------------------------------------------
		case eSTEP_DISCONNECT:
			// Verbindung trennen
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_DISCONNECTING;
			inst->pRunClient->Connection.nConnectTries = 0;
			inst->fbUA_Disconnect.Execute = 1;
			inst->fbUA_Disconnect.ConnectionHdl = inst->pRunClient->Connection.nConnectionHandle;
			inst->fbUA_Disconnect.Timeout = inst->pRunClient->Cfg.tConnectTimeout;
			if(inst->fbUA_Disconnect.Done == 1)
			{
				inst->fbUA_Disconnect.Execute = 0;
				inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_DISCONNECTED;
				inst->pRunClient->State.ConnectionStatus.eConnectionStatus = UACS_Shutdown;
				inst->pRunClient->State.ConnectionStatus.eServerState = UASS_Unknown;
				inst->pRunClient->State.ConnectionStatus.nServiceLevel = 0;
				inst->pRunClient->Connection.nConnectionHandle = 0;
				inst->eStep = eSTEP_CLEAR_EVENT_ITEM_HANDLES;
			}
			else if(inst->fbUA_Disconnect.Error == 1)
			{
				inst->fbUA_Disconnect.Execute = 0;
				inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_DISCONNECT_ERROR;
				inst->pRunClient->Connection.nErrorId = inst->fbUA_Disconnect.ErrorID;
				inst->pRunClient->State.nClientErroId = inst->fbUA_Disconnect.ErrorID;
				strcpy(inst->pRunClient->State.sClientErrorText, "Error on disconnecting: ");
				STRING sHelp[64];
				BrbUaGetStatusCodeText(inst->pRunClient->State.nClientErroId, sHelp, sizeof(sHelp));
				BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
				inst->eStep = eSTEP_CLEAR_EVENT_ITEM_HANDLES;
			}
			break;

		case eSTEP_CLEAR_EVENT_ITEM_HANDLES:
			// Bei allen EventItems aller Subscriptions den Handle auf 0 setzen (in 64-Blöcken)
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_DISCONNECTING;
			if(inst->pRunClient->Subscriptions.nSubscriptionCount > 0 && inst->pRunClient->Subscriptions.pSubscriptions != 0)
			{
				if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount)
				{
					BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex);
					if(pSubscription->nEventItemCount > 0 && pSubscription->pEventItems != 0)
					{
						if(inst->nEventItemIndex < pSubscription->nEventItemCount)
						{
							DINT nRemainingItemsCount = pSubscription->nEventItemCount - inst->nEventItemIndex;
							if(nRemainingItemsCount > 0)
							{
								UINT nItemCount = (UINT)nRemainingItemsCount;
								if(nRemainingItemsCount > 64)
								{
									nItemCount = 64;
								}
								for(inst->nLoopIndex=0; inst->nLoopIndex < nItemCount; inst->nLoopIndex++)
								{
									BrbUaRcEventItemIntern_TYP* pEventItem = ((BrbUaRcEventItemIntern_TYP*)pSubscription->pEventItems) + inst->nLoopIndex;
									pEventItem->nEventNodeHandle = 0;
									pEventItem->nEventItemHandle = 0;
									pEventItem->bEventReceived = 0;
									pEventItem->nReceiveCount = 0;
								}
								inst->nEventItemIndex += nItemCount;
							}
							else
							{
								inst->nSubscriptionIndex++;
								inst->nEventItemIndex = 0;
							}
						}
						else
						{
							inst->nSubscriptionIndex++;
							inst->nEventItemIndex = 0;
						}
					}
					else
					{
						inst->nSubscriptionIndex++;
						inst->nEventItemIndex = 0;
					}
				}
				else
				{
					inst->nSubscriptionIndex = 0;
					inst->nEventItemIndex = 0;
					inst->eStep = eSTEP_CLEAR_MONITORED_ITEM_HANDLES;
				}
			}
			else
			{
				inst->nSubscriptionIndex = 0;
				inst->nEventItemIndex = 0;
				inst->eStep = eSTEP_CLEAR_MONITORED_ITEM_HANDLES;
			}
			break;

		case eSTEP_CLEAR_MONITORED_ITEM_HANDLES:
			// Bei allen MonitoredItems aller Subscriptions den Handle auf 0 setzen (in 64-Blöcken)
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_DISCONNECTING;
			if(inst->pRunClient->Subscriptions.nSubscriptionCount > 0 && inst->pRunClient->Subscriptions.pSubscriptions != 0)
			{
				if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount)
				{
					BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex);
					pSubscription->nSubscriptionHandle = 0;
					if(pSubscription->nMonitoredItemCount > 0 && 
						pSubscription->pMiDatObjNamespaceIndices != 0 && pSubscription->pMiNodeIds != 0 && 
						pSubscription->pMiNodeHandleErrorIds != 0 && pSubscription->pMiNodeHandles != 0 && 
						pSubscription->pMiNodeAddInfos != 0 && pSubscription->pMiVariables != 0 && 
						pSubscription->pMiQueueSizeOri != 0 && pSubscription->pMiMonitorSettings != 0 &&
						pSubscription->pMiValuesChanged != 0 && pSubscription->pMiRemainingValueCounts != 0 &&
						pSubscription->pMiTimestamps != 0 && pSubscription->pMiNodeQualityIds != 0 &&
						pSubscription->pMiMonitoredItemErrorIds != 0 && pSubscription->pMiMonitoredItemHandles != 0)
					{
						if(inst->nMonItemIndex < pSubscription->nMonitoredItemCount)
						{
							DINT nRemainingItemsCount = pSubscription->nMonitoredItemCount - inst->nMonItemIndex;
							if(nRemainingItemsCount > 0)
							{
								UINT nItemCount = (UINT)nRemainingItemsCount;
								if(nRemainingItemsCount > 64)
								{
									nItemCount = 64;
								}
								for(inst->nLoopIndex=0; inst->nLoopIndex < nItemCount; inst->nLoopIndex++)
								{
									*(((DWORD*)pSubscription->pMiNodeHandles) + inst->nMonItemIndex + inst->nLoopIndex) = 0;
									*(((DWORD*)pSubscription->pMiMonitoredItemHandles) + inst->nMonItemIndex + inst->nLoopIndex) = 0;
								}
								inst->nMonItemIndex += nItemCount;
							}
							else
							{
								inst->nSubscriptionIndex++;
								inst->nMonItemIndex = 0;
							}
						}
						else
						{
							inst->nSubscriptionIndex++;
							inst->nMonItemIndex = 0;
						}
					}
					else
					{
						inst->nSubscriptionIndex++;
						inst->nMonItemIndex = 0;
					}
				}
				else
				{
					inst->nSubscriptionIndex = 0;
					inst->nMonItemIndex = 0;
					inst->eStep = eSTEP_CLEAR_METHOD_HANDLES;
				}
			}
			else
			{
				inst->nSubscriptionIndex = 0;
				inst->nMonItemIndex = 0;
				inst->eStep = eSTEP_CLEAR_METHOD_HANDLES;
			}
			break;

		case eSTEP_CLEAR_METHOD_HANDLES:
			// Bei allen Methods den Handle auf 0 setzen (in 64-Blöcken)
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_DISCONNECTING;
			if(inst->pRunClient->Methods.nMethodCount > 0 && inst->pRunClient->Methods.pMethods != 0)
			{
				DINT nRemainingItemsCount = inst->pRunClient->Methods.nMethodCount - inst->nMethodIndex;
				if(nRemainingItemsCount > 0)
				{
					UINT nItemCount = (UINT)nRemainingItemsCount;
					if(nRemainingItemsCount > 64)
					{
						nItemCount = 64;
					}
					for(inst->nLoopIndex=0; inst->nLoopIndex < nItemCount; inst->nLoopIndex++)
					{
						BrbUaRcMethodIntern_TYP* pMethod = (((BrbUaRcMethodIntern_TYP*)inst->pRunClient->Methods.pMethods)  + inst->nMethodIndex + inst->nLoopIndex);
						pMethod->nMethodHandle = 0;
					}
					inst->nMethodIndex += nItemCount;
				}
				else
				{
					inst->nMethodIndex = 0;
					inst->eStep = eSTEP_CLEAR_NODE_HANDLES;
				}
			}
			else
			{
				inst->nMethodIndex = 0;
				inst->eStep = eSTEP_CLEAR_NODE_HANDLES;
			}
			break;

		case eSTEP_CLEAR_NODE_HANDLES:
			// Bei allen NodeHandles den Handle auf 0 setzen (in 64-Blöcken)
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_DISCONNECTING;
			if(inst->pRunClient->NodeHandles.nNodeHandleCount > 0 && inst->pRunClient->NodeHandles.pDatObjNamespaceIndices != 0 && inst->pRunClient->NodeHandles.pNodeIds != 0 && inst->pRunClient->NodeHandles.pNodeHandleErrorIds != 0 && inst->pRunClient->NodeHandles.pNodeHandles != 0)
			{
				DINT nRemainingItemsCount = inst->pRunClient->NodeHandles.nNodeHandleCount - inst->nNodeHandleIndex;
				if(nRemainingItemsCount > 0)
				{
					UINT nItemCount = (UINT)nRemainingItemsCount;
					if(nRemainingItemsCount > 64)
					{
						nItemCount = 64;
					}
					for(inst->nLoopIndex=0; inst->nLoopIndex < nItemCount; inst->nLoopIndex++)
					{
						*(((DWORD*)inst->pRunClient->NodeHandles.pNodeHandles) + inst->nNodeHandleIndex + inst->nLoopIndex) = 0;
					}
					inst->nNodeHandleIndex += nItemCount;
				}
				else
				{
					inst->nNodeHandleIndex = 0;
					inst->eStep = eSTEP_WAIT_FOR_CMD_CONNECT;
				}
			}
			else
			{
				inst->nNodeHandleIndex = 0;
				inst->eStep = eSTEP_WAIT_FOR_CMD_CONNECT;
			}
			break;

	}

	// Rücksetzen des Kommandos (wird nicht in allen Schrittem ausgewertet)
	if(inst->eStep > eSTEP_WAIT_FOR_CMD_CONNECT )
	{
		inst->pRunClient->eCmd = eBRB_RCCLTCMD_NONE;
	}

	// Aufruf aller FB's
	UA_Connect(&inst->fbUA_Connect);
	UA_GetNamespaceIndex(&inst->fbUA_GetNamespaceIndex);
	UA_NodeGetHandleList(&inst->fbUA_NodeGetHandleList);
	UA_MethodGetHandle(&inst->fbUA_MethodGetHandle);
	UA_SubscriptionCreate(&inst->fbUA_SubscriptionCreate);
	UA_MonitoredItemAddList(&inst->fbUA_MonitoredItemAddList);
	UA_NodeGetHandle(&inst->fbUA_NodeGetHandle);
	UA_EventItemAdd(&inst->fbUA_EventItemAdd);
	UA_ConnectionGetStatus(&inst->fbUA_ConnectionGetStatus);
	UA_EventItemOperate(&inst->fbUA_EventItemOperate);
	UA_Disconnect(&inst->fbUA_Disconnect);
}

BOOL GetNextEventItem(BrbUaRunClient_TYP* pRunClient, DINT* pSubscriptionIndex, DINT* pEventItemIndex)
{
	BOOL bResult = 0;
	UDINT nEventItemsCheckedCount = 0;
	if(pRunClient->Subscriptions.nSubscriptionCount > 0)
	{
		// Beim angegebenen EventItem der angegebenen Subscription starten
		DINT nSubscriptionIndexLoop = *pSubscriptionIndex;
		DINT nEventItemIndexLoop = *pEventItemIndex;
		if(nSubscriptionIndexLoop < 0 || nSubscriptionIndexLoop>=pRunClient->Subscriptions.nSubscriptionCount)
		{	
			nSubscriptionIndexLoop = 0;
			nEventItemIndexLoop = -1;
		}
		if(nEventItemIndexLoop < 0)
		{	
			nEventItemIndexLoop = -1;
		}
		BOOL bLeaveLoop = 0;
		do
		{
			BrbUaRcSubscriptionIntern_TYP* pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)pRunClient->Subscriptions.pSubscriptions) + nSubscriptionIndexLoop;
			nEventItemIndexLoop++;
			if(nEventItemIndexLoop<pSubscription->nEventItemCount)
			{
				// EventItem gefunden
				nEventItemsCheckedCount++;
				*pSubscriptionIndex = nSubscriptionIndexLoop;
				*pEventItemIndex = nEventItemIndexLoop;
				bResult = 1;
				bLeaveLoop = 1;
			}
			else
			{
				// Nächste Subscription
				nSubscriptionIndexLoop++;
				if(nSubscriptionIndexLoop>=pRunClient->Subscriptions.nSubscriptionCount)
				{
					// Überlauf -> Subscription-Liste von vorne beginnen
					nSubscriptionIndexLoop = 0;
				}
				nEventItemIndexLoop = -1;
			}
			if(nEventItemsCheckedCount >= pRunClient->Subscriptions.nEventItemsCountTotal)
			{
				// Wieder beim zuerst geprüften EventItem angelangt -> Prüfen, ob es ein EventItem darstellen
				if(nSubscriptionIndexLoop<pRunClient->Subscriptions.nSubscriptionCount)
				{
					pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)pRunClient->Subscriptions.pSubscriptions) + nSubscriptionIndexLoop;
					if(nEventItemIndexLoop<pSubscription->nEventItemCount)
					{
						// Selbes EventItem gefunden
						*pSubscriptionIndex = nSubscriptionIndexLoop;
						*pEventItemIndex = nEventItemIndexLoop;
						bResult = 1;
					}
				}
				bLeaveLoop = 1;
			}
		} while (bLeaveLoop == 0);
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

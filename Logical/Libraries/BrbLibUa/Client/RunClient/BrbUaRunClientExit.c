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
	eSTEP_DISCONNECT,
	eSTEP_FREE_EVENT_FIELDS,
	eSTEP_FREE_EVENT_ITEMS,
	eSTEP_FREE_MONITORED_ITEMS,
	eSTEP_FREE_WRITE_ITEMS,
	eSTEP_FREE_READ_ITEMS,
	eSTEP_FREE_SUBSCRIPTIONS,
	eSTEP_FREE_METHODS,
	eSTEP_FREE_WRITEBLOCKS,
	eSTEP_FREE_READBLOCKS,
	eSTEP_FREE_NODEHANDLES,
	eSTEP_FREE_NAMESPACES,
	eSTEP_FINISHED,
};

/* Exilisiert eine Client-Instanz */
void BrbUaRunClientExit(struct BrbUaRunClientExit* inst)
{
	switch(inst->eStep)
	{
		case eSTEP_INIT:
			// Fub initialisieren
			inst->nStatus =  eBRB_ERR_BUSY;
			memset(&inst->fbUA_Disconnect, 0, sizeof(inst->fbUA_Disconnect));
			// Client-Pointer prüfen
			if(inst->pRunClient != 0)
			{
				inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_EXITING;
				inst->pRunClient->State.nClientErroId = 0x00000000;
				strcpy(inst->pRunClient->State.sClientErrorText, "");
				inst->nSubscriptionIndex = 0;
				inst->nReadBlockIndex = 0;
				inst->nWriteBlockIndex = 0;
				inst->eStep = eSTEP_DISCONNECT;
			}
			else
			{
				inst->nStatus = eBRB_ERR_NULL_POINTER;
				inst->eStep = eSTEP_INIT;
			}
			break;

		case eSTEP_DISCONNECT:
			// Verbindung trennen
			inst->nStatus  = eBRB_ERR_BUSY;
			inst->nReadBlockIndex = 0;
			inst->nWriteBlockIndex = 0;
			inst->nSubscriptionIndex = 0;
			inst->nEventItemIndex = 0;
			if(inst->pRunClient->Connection.nConnectionHandle != 0)
			{
				inst->fbUA_Disconnect.Execute = 1;
				inst->fbUA_Disconnect.ConnectionHdl = inst->pRunClient->Connection.nConnectionHandle;
				inst->fbUA_Disconnect.Timeout = inst->pRunClient->Cfg.tConnectTimeout;
				if(inst->fbUA_Disconnect.Done == 1)
				{
					inst->fbUA_Disconnect.Execute = 0;
					inst->pRunClient->State.ConnectionStatus.eConnectionStatus = UACS_Shutdown;
					inst->pRunClient->State.ConnectionStatus.eServerState = UASS_Unknown;
					inst->pRunClient->State.ConnectionStatus.nServiceLevel = 0;
					inst->pRunClient->Connection.nConnectionHandle = 0;
					inst->eStep = eSTEP_FREE_EVENT_FIELDS;
				}
				else if(inst->fbUA_Disconnect.Error == 1)
				{
					inst->fbUA_Disconnect.Execute = 0;
					inst->pRunClient->Connection.nErrorId = inst->fbUA_Disconnect.ErrorID;
					inst->pRunClient->State.nClientErroId = inst->fbUA_Disconnect.ErrorID;
					strcpy(inst->pRunClient->State.sClientErrorText, "Exit error on disconnect");
					inst->eStep = eSTEP_FREE_EVENT_FIELDS;
				}
			}
			else
			{
				inst->eStep = eSTEP_FREE_EVENT_FIELDS;
			}
			break;
		
		case eSTEP_FREE_EVENT_FIELDS:
			// Speicher für EventFields pro EventItems pro Subscription freigeben
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->Subscriptions.nSubscriptionCount > 0 && inst->pRunClient->Subscriptions.pSubscriptions != 0)
			{
				if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount)
				{
					BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions)  + inst->nSubscriptionIndex);
					if(pSubscription->nEventItemCount > 0 && pSubscription->pEventItems != 0)
					{
						if(inst->nEventItemIndex < pSubscription->nEventItemCount)
						{
							BrbUaRcEventItemIntern_TYP* pEventItem = ((BrbUaRcEventItemIntern_TYP*)pSubscription->pEventItems) + inst->nEventItemIndex;
							if(pEventItem->nEventFieldCount > 0 && pEventItem->pEfDatObjNamespaceIndices != 0 && pEventItem->pEfFieldSelections != 0 && pEventItem->pEfFieldVars != 0)
							{
								inst->nFreeStatus = TMP_free(pEventItem->nEfMemLen, (void*)pEventItem->pEfStart);
								if(inst->nFreeStatus == 0)
								{
									pEventItem->pEfStart = 0;
									pEventItem->pEfDatObjNamespaceIndices = 0;
									pEventItem->pEfFieldSelections = 0;
									pEventItem->pEfFieldVars = 0;
									pEventItem->nEfMemLen = 0;
									inst->nEventItemIndex++;
								}
								else
								{
									// Fehler
									inst->nStatus = inst->nFreeStatus;
									inst->pRunClient->State.nClientErroId = inst->nStatus;
									strcpy(inst->pRunClient->State.sClientErrorText, "Exit error on freeing memory for EventFields of Subscription#");
									STRING sHelp[16];
									brsitoa(inst->nSubscriptionIndex, (UDINT)&sHelp);
									BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
									strcpy(inst->pRunClient->State.sClientErrorText, "of EventItem#");
									brsitoa(inst->nEventItemIndex, (UDINT)&sHelp);
									BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
									inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_EXIT_ERROR;
									inst->eStep = eSTEP_INIT;
									break;
								}
							}
							else
							{
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
					inst->eStep = eSTEP_FREE_EVENT_ITEMS;
				}
			}
			else
			{
				// Keine Subscriptions angegeben
				inst->nSubscriptionIndex = 0;
				inst->nEventItemIndex = 0;
				inst->eStep = eSTEP_FREE_WRITE_ITEMS;
			}
			break;
		
		case eSTEP_FREE_EVENT_ITEMS:
			// Speicher für EventItems pro Subscription freigeben
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->Subscriptions.nSubscriptionCount > 0 && inst->pRunClient->Subscriptions.pSubscriptions != 0)
			{
				if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount)
				{
					BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions)  + inst->nSubscriptionIndex);
					if(pSubscription->nEventItemCount > 0 && pSubscription->pEventItems != 0)
					{
						inst->nFreeStatus = TMP_free(pSubscription->nEiMemLen, (void*)pSubscription->pEventItems);
						if(inst->nFreeStatus == 0)
						{
							pSubscription->pEventItems = 0;
							pSubscription->nEiMemLen = 0;
							inst->nSubscriptionIndex++;
						}
						else
						{
							// Fehler
							inst->nStatus = inst->nFreeStatus;
							inst->pRunClient->State.nClientErroId = inst->nStatus;
							strcpy(inst->pRunClient->State.sClientErrorText, "Exit error on freeing memory for EventItems of Subscription#");
							STRING sHelp[16];
							brsitoa(inst->nSubscriptionIndex, (UDINT)&sHelp);
							BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
							inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_EXIT_ERROR;
							inst->eStep = eSTEP_INIT;
							break;
						}
					}
					else
					{
						inst->nSubscriptionIndex++;
					}
				}
				else
				{
					inst->nSubscriptionIndex = 0;
					inst->eStep = eSTEP_FREE_MONITORED_ITEMS;
				}
			}
			else
			{
				// Keine Subscriptions angegeben
				inst->eStep = eSTEP_FREE_WRITE_ITEMS;
			}
			break;
		
		case eSTEP_FREE_MONITORED_ITEMS:
			// Speicher für MonitoredItems pro Subscription freigeben
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->Subscriptions.nSubscriptionCount > 0 && inst->pRunClient->Subscriptions.pSubscriptions != 0)
			{
				if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount)
				{
					BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions)  + inst->nSubscriptionIndex);
					if(pSubscription->nMonitoredItemCount > 0 && pSubscription->pMiStart != 0)
					{
						inst->nFreeStatus = TMP_free(pSubscription->nMiMemLen, (void*)pSubscription->pMiStart);
						if(inst->nFreeStatus == 0)
						{
							pSubscription->pMiStart = 0;
							pSubscription->pMiDatObjNamespaceIndices = 0;
							pSubscription->pMiNodeIds = 0;
							pSubscription->pMiNodeHandleErrorIds = 0;
							pSubscription->pMiNodeHandles = 0;
							pSubscription->pMiNodeAddInfos = 0;
							pSubscription->pMiVariables = 0;
							pSubscription->pMiQueueSizeOri = 0;
							pSubscription->pMiMonitorSettings = 0;
							pSubscription->pMiValuesChanged = 0;
							pSubscription->pMiRemainingValueCounts = 0;
							pSubscription->pMiTimestamps = 0;
							pSubscription->pMiNodeQualityIds = 0;
							pSubscription->pMiMonitoredItemErrorIds = 0;
							pSubscription->pMiMonitoredItemHandles = 0;
							pSubscription->nMiMemLen = 0;
							inst->nSubscriptionIndex++;
						}
						else
						{
							// Fehler
							inst->nStatus = inst->nFreeStatus;
							inst->pRunClient->State.nClientErroId = inst->nStatus;
							strcpy(inst->pRunClient->State.sClientErrorText, "Exit error on freeing memory for MonitoredItems of Subscription#");
							STRING sHelp[16];
							brsitoa(inst->nSubscriptionIndex, (UDINT)&sHelp);
							BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
							inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_EXIT_ERROR;
							inst->eStep = eSTEP_INIT;
							break;
						}
					}
					else
					{
						inst->nSubscriptionIndex++;
					}
				}
				else
				{
					inst->nSubscriptionIndex = 0;
					inst->eStep = eSTEP_FREE_WRITE_ITEMS;
				}
			}
			else
			{
				// Keine Subscriptions angegeben
				inst->eStep = eSTEP_FREE_WRITE_ITEMS;
			}
			break;
		
		case eSTEP_FREE_WRITE_ITEMS:
			// Speicher für WriteItems pro Block freigeben
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->WriteBlocks.nBlockCount > 0 && inst->pRunClient->WriteBlocks.pBlocks != 0)
			{
				if(inst->nWriteBlockIndex < inst->pRunClient->WriteBlocks.nBlockCount)
				{
					BrbUaRcWriteBlockIntern_TYP* pWriteBlock = (((BrbUaRcWriteBlockIntern_TYP*)inst->pRunClient->WriteBlocks.pBlocks)  + inst->nWriteBlockIndex);
					if(pWriteBlock->nWriteItemCount > 0 && pWriteBlock->pWiStart != 0)
					{
						inst->nFreeStatus = TMP_free(pWriteBlock->nMemLen, (void*)pWriteBlock->pWiStart);
						if(inst->nFreeStatus == 0)
						{
							pWriteBlock->pWiStart = 0;
							pWriteBlock->pWiDatObjNamespaceIndices = 0;
							pWriteBlock->pWiNodeIds = 0;
							pWriteBlock->pWiNodeAddInfos = 0;
							pWriteBlock->pWiVariables = 0;
							pWriteBlock->pWiNodeErrorIds = 0;
							pWriteBlock->nMemLen = 0;
							inst->nWriteBlockIndex++;
						}
						else
						{
							// Fehler
							inst->nStatus = inst->nFreeStatus;
							inst->pRunClient->State.nClientErroId = inst->nStatus;
							strcpy(inst->pRunClient->State.sClientErrorText, "Exit error on freeing memory for Items of WriteBlock#");
							STRING sHelp[16];
							brsitoa(inst->nWriteBlockIndex, (UDINT)&sHelp);
							BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
							inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_EXIT_ERROR;
							inst->eStep = eSTEP_INIT;
							break;
						}
					}
					else
					{
						inst->nWriteBlockIndex++;
					}
				}
				else
				{
					inst->nWriteBlockIndex = 0;
					inst->eStep = eSTEP_FREE_READ_ITEMS;
				}
			}
			else
			{
				// Keine WriteBlocks angegeben
				inst->eStep = eSTEP_FREE_READ_ITEMS;
			}
			break;
		
		case eSTEP_FREE_READ_ITEMS:
			// Speicher für ReadItems pro Block freigeben
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->ReadBlocks.nBlockCount > 0 && inst->pRunClient->ReadBlocks.pBlocks != 0)
			{
				if(inst->nReadBlockIndex < inst->pRunClient->ReadBlocks.nBlockCount)
				{
					BrbUaRcReadBlockIntern_TYP* pReadBlock = (((BrbUaRcReadBlockIntern_TYP*)inst->pRunClient->ReadBlocks.pBlocks)  + inst->nReadBlockIndex);
					if(pReadBlock->nReadItemCount > 0 && pReadBlock->pRiStart != 0)
					{
						inst->nFreeStatus = TMP_free(pReadBlock->nMemLen, (void*)pReadBlock->pRiStart);
						if(inst->nFreeStatus == 0)
						{
							pReadBlock->pRiStart = 0;
							pReadBlock->pRiDatObjNamespaceIndices = 0;
							pReadBlock->pRiNodeIds = 0;
							pReadBlock->pRiNodeAddInfos = 0;
							pReadBlock->pRiVariables = 0;
							pReadBlock->pRiNodeErrorIds = 0;
							pReadBlock->pRiTimestamps = 0;
							pReadBlock->nMemLen = 0;
							inst->nReadBlockIndex++;
						}
						else
						{
							// Fehler
							inst->nStatus = inst->nFreeStatus;
							inst->pRunClient->State.nClientErroId = inst->nStatus;
							strcpy(inst->pRunClient->State.sClientErrorText, "Exit error on freeing memory for Items of ReadBlock#");
							STRING sHelp[16];
							brsitoa(inst->nReadBlockIndex, (UDINT)&sHelp);
							BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
							inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_EXIT_ERROR;
							inst->eStep = eSTEP_INIT;
							break;
						}
					}
					else
					{
						inst->nReadBlockIndex++;
					}
				}
				else
				{
					inst->nReadBlockIndex = 0;
					inst->eStep = eSTEP_FREE_SUBSCRIPTIONS;
				}
			}
			else
			{
				// Keine ReadBlocks angegeben
				inst->eStep = eSTEP_FREE_SUBSCRIPTIONS;
			}
			break;
		
		case eSTEP_FREE_SUBSCRIPTIONS:
			// Speicher für alle Subscriptions freigeben
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->Subscriptions.nSubscriptionCount > 0 && inst->pRunClient->Subscriptions.pSubscriptions != 0 && inst->pRunClient->Subscriptions.nMemLen > 0)
			{
				inst->nFreeStatus = TMP_free(inst->pRunClient->Subscriptions.nMemLen, (void*)inst->pRunClient->Subscriptions.pSubscriptions);
				if(inst->nFreeStatus == 0)
				{
					inst->pRunClient->Subscriptions.nSubscriptionCount = 0;
					inst->pRunClient->Subscriptions.pSubscriptions = 0;
					inst->pRunClient->Subscriptions.nMemLen = 0;
					inst->eStep = eSTEP_FREE_METHODS;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nFreeStatus;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Exit error on freeing memory for subscriptions");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_EXIT_ERROR;
					inst->eStep = eSTEP_INIT;
				}
			}
			else
			{
				// Keine Subscriptions angegeben
				inst->eStep = eSTEP_FREE_METHODS;
			}
			break;

		case eSTEP_FREE_METHODS:
			// Speicher für alle Methods freigeben
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->Methods.nMethodCount > 0 && inst->pRunClient->Methods.pMethods != 0 && inst->pRunClient->Methods.nMemLen > 0)
			{
				inst->nFreeStatus = TMP_free(inst->pRunClient->Methods.nMemLen, (void*)inst->pRunClient->Methods.pMethods);
				if(inst->nFreeStatus == 0)
				{
					inst->pRunClient->Methods.nMethodCount = 0;
					inst->pRunClient->Methods.pMethods = 0;
					inst->pRunClient->Methods.nMemLen = 0;
					inst->eStep = eSTEP_FREE_WRITEBLOCKS;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nFreeStatus;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Exit error on freeing memory for methods");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_EXIT_ERROR;
					inst->eStep = eSTEP_INIT;
				}
			}
			else
			{
				// Keine Methods angegeben
				inst->eStep = eSTEP_FREE_WRITEBLOCKS;
			}
			break;

		case eSTEP_FREE_WRITEBLOCKS:
			// Speicher für alle WriteBlocks freigeben
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->WriteBlocks.nBlockCount > 0 && inst->pRunClient->WriteBlocks.pBlocks != 0 && inst->pRunClient->WriteBlocks.nMemLen > 0)
			{
				inst->nFreeStatus = TMP_free(inst->pRunClient->WriteBlocks.nMemLen, (void*)inst->pRunClient->WriteBlocks.pBlocks);
				if(inst->nFreeStatus == 0)
				{
					inst->pRunClient->WriteBlocks.nBlockCount = 0;
					inst->pRunClient->WriteBlocks.pBlocks = 0;
					inst->pRunClient->WriteBlocks.nMemLen = 0;
					inst->eStep = eSTEP_FREE_READBLOCKS;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nFreeStatus;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Exit error on freeing memory for write blocks");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_EXIT_ERROR;
					inst->eStep = eSTEP_INIT;
				}
			}
			else
			{
				// Keine WriteBlocks angegeben
				inst->eStep = eSTEP_FREE_READBLOCKS;
			}
			break;

		case eSTEP_FREE_READBLOCKS:
			// Speicher für alle ReadBlocks freigeben
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->ReadBlocks.nBlockCount > 0 && inst->pRunClient->ReadBlocks.pBlocks != 0 && inst->pRunClient->ReadBlocks.nMemLen > 0)
			{
				inst->nFreeStatus = TMP_free(inst->pRunClient->ReadBlocks.nMemLen, (void*)inst->pRunClient->ReadBlocks.pBlocks);
				if(inst->nFreeStatus == 0)
				{
					inst->pRunClient->ReadBlocks.nBlockCount = 0;
					inst->pRunClient->ReadBlocks.pBlocks = 0;
					inst->pRunClient->ReadBlocks.nMemLen = 0;
					inst->eStep = eSTEP_FREE_NODEHANDLES;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nFreeStatus;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Exit error on freeing memory for read blocks");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_EXIT_ERROR;
					inst->eStep = eSTEP_INIT;
				}
			}
			else
			{
				// Keine ReadBlocks angegeben
				inst->eStep = eSTEP_FREE_NODEHANDLES;
			}
			break;

		case eSTEP_FREE_NODEHANDLES:
			// Speicher für alle Nodehandles freigeben
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->NodeHandles.nNodeHandleCount > 0 && inst->pRunClient->NodeHandles.pStart != 0 && inst->pRunClient->Namespaces.nMemLen > 0)
			{
				inst->nFreeStatus = TMP_free(inst->pRunClient->NodeHandles.nMemLen, (void*)inst->pRunClient->NodeHandles.pStart);
				if(inst->nFreeStatus == 0)
				{
					inst->pRunClient->NodeHandles.nNodeHandleCount = 0;
					inst->pRunClient->NodeHandles.pStart = 0;
					inst->pRunClient->NodeHandles.pDatObjNamespaceIndices = 0;
					inst->pRunClient->NodeHandles.pNodeIds = 0;
					inst->pRunClient->NodeHandles.pNodeHandleErrorIds = 0;
					inst->pRunClient->NodeHandles.pNodeHandles = 0;
					inst->pRunClient->NodeHandles.nMemLen = 0;
					inst->eStep = eSTEP_FREE_NAMESPACES;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nFreeStatus;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Exit error on freeing memory for nodehandles");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_EXIT_ERROR;
					inst->eStep = eSTEP_INIT;
				}
			}
			else
			{
				// Keine NodeHandles angegeben
				inst->eStep = eSTEP_FREE_NAMESPACES;
			}
			break;

		case eSTEP_FREE_NAMESPACES:
			// Speicher für alle Namespaces freigeben
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->Namespaces.nNamespaceCount > 0 && inst->pRunClient->Namespaces.pNamespaces != 0 && inst->pRunClient->Namespaces.nMemLen > 0)
			{
				inst->nFreeStatus = TMP_free(inst->pRunClient->Namespaces.nMemLen, (void*)inst->pRunClient->Namespaces.pNamespaces);
				if(inst->nFreeStatus == 0)
				{
					inst->pRunClient->Namespaces.nNamespaceCount = 0;
					inst->pRunClient->Namespaces.pNamespaces = 0;
					inst->pRunClient->Namespaces.nMemLen = 0;
					inst->eStep = eSTEP_FINISHED;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nFreeStatus;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Exit error on freeing memory for namespaces");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_EXIT_ERROR;
					inst->eStep = eSTEP_INIT;
				}
			}
			else
			{
				// Keine Subscriptions angegeben
				inst->eStep = eSTEP_FINISHED;
			}
			break;

		case eSTEP_FINISHED:
			inst->nStatus = 0;
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_EXIT_DONE;
			inst->eStep = eSTEP_INIT;
			break;

	}

	// Aufruf aller FB's
	UA_Disconnect(&inst->fbUA_Disconnect);
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

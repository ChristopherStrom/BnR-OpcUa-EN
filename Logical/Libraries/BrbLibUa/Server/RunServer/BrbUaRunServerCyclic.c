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
	eSTEP_GET_NAMESPACE,
	eSTEP_GET_EVENT_NS,
	eSTEP_GET_EVENT_FIELD_NS,
	eSTEP_RUNNING,
};

/* Behandelt eine Server-Instanz */
void BrbUaRunServerCyclic(struct BrbUaRunServerCyclic* inst)
{
	switch(inst->eStep)
	{
		case eSTEP_INIT:
			// Fub initialisieren
			inst->nStatus = eBRB_ERR_OK;
			//memset(&inst->fbUaSrv_GetServerState, 0, sizeof(inst->fbUaSrv_GetServerState));
			// Server-Pointer prüfen
			if(inst->pRunServer != 0)
			{
				inst->pRunServer->State.nErroId = 0;
				if(inst->pRunServer->State.eState == eBRB_RSSTATE_INIT_DONE)
				{
					inst->nNamespaceIndex = 0;
					inst->nEventIndex = 0;
					inst->nEventFieldIndex = 0;
					inst->eStep = eSTEP_GET_NAMESPACE;
				}
				else
				{
					inst->nStatus = eBRB_ERR_INVALID_PARAMETER;
					inst->pRunServer->State.nErroId = inst->nStatus;
					strcpy(inst->pRunServer->State.sErrorText, "Cyclic error: Init not done");
				}
			}
			else
			{
				inst->nStatus = eBRB_ERR_NULL_POINTER;
			}
			break;

		case eSTEP_GET_NAMESPACE:
			// NamespaceIndex ermitteln
			inst->pRunServer->State.eState = eBRB_RSSTATE_DETECTING;
			if(inst->pRunServer->Namespaces.nNamespaceCount > 0 && inst->pRunServer->Namespaces.pNamespaces != 0)
			{
				if(inst->nNamespaceIndex < inst->pRunServer->Namespaces.nNamespaceCount)
				{
					BrbUaRsNamespace_TYP* pNamespace = ((BrbUaRsNamespace_TYP*)inst->pRunServer->Namespaces.pNamespaces) + inst->nNamespaceIndex;
					inst->fbUaSrv_GetNamespaceIndex.Execute = 1;
					BrbStringCopy(inst->fbUaSrv_GetNamespaceIndex.NamespaceUri, pNamespace->sNamespaceUri, sizeof(inst->fbUaSrv_GetNamespaceIndex.NamespaceUri));
					if(inst->fbUaSrv_GetNamespaceIndex.Done == 1)
					{
						inst->fbUaSrv_GetNamespaceIndex.Execute = 0;
						pNamespace->nNamespaceIndex = inst->fbUaSrv_GetNamespaceIndex.NamespaceIndex;
						pNamespace->nErrorId = 0x00000000; // = Good
						inst->nNamespaceIndex += 1;
					}
					else if(inst->fbUaSrv_GetNamespaceIndex.Error == 1)
					{
						inst->fbUaSrv_GetNamespaceIndex.Execute = 0;
						pNamespace->nNamespaceIndex = 0;
						pNamespace->nErrorId = inst->fbUaSrv_GetNamespaceIndex.ErrorID;
						inst->pRunServer->State.nErroId = inst->fbUaSrv_GetNamespaceIndex.ErrorID;
						strcpy(inst->pRunServer->State.sErrorText, "Cyclic error on getting Namespace#");
						STRING sHelp[16];
						brsitoa(inst->nNamespaceIndex, (UDINT)&sHelp);
						BrbStringCat(inst->pRunServer->State.sErrorText, sHelp, sizeof(inst->pRunServer->State.sErrorText));
						inst->nNamespaceIndex += 1;
					}
				}
				else
				{
					inst->eStep = eSTEP_GET_EVENT_NS;
				}
			}
			else
			{
				// Keine Namespaces: Andere Eintragungen mache keinen Sinn
				inst->eStep = eSTEP_RUNNING;
			}
			break;

		case eSTEP_GET_EVENT_NS:
			// Bei allen Events den ServerNamespaceIndex eintragen (in 64-Blöcken)
			inst->pRunServer->State.eState = eBRB_RSSTATE_DETECTING;
			if(inst->pRunServer->Events.nEventCount > 0 && inst->pRunServer->Events.pEvents != 0)
			{
				DINT nRemainingItemsCount = inst->pRunServer->Events.nEventCount - inst->nEventIndex;
				if(nRemainingItemsCount > 0)
				{
					UINT nItemCount = (UINT)nRemainingItemsCount;
					if(nRemainingItemsCount > 64)
					{
						nItemCount = 64;
					}
					for(inst->nLoopIndex=0; inst->nLoopIndex < nItemCount; inst->nLoopIndex++)
					{
						// ServerNamespaceIndex aus geparsten DatObj-Index für jedes Event ermitteln
						BrbUaRsEventIntern_TYP* pEvent = ((BrbUaRsEventIntern_TYP*)inst->pRunServer->Events.pEvents) + inst->nEventIndex + inst->nLoopIndex;
						pEvent->TypeNodeId.NamespaceIndex = BrbUaRsGetNamespace(inst->pRunServer, pEvent->nDatObjNamespaceIndex, 0);
					}
					inst->nEventIndex += nItemCount;
				}
				else
				{
					inst->nEventIndex = 0;
					inst->eStep = eSTEP_GET_EVENT_FIELD_NS;
				}
			}
			else
			{
				inst->eStep = eSTEP_RUNNING;
			}
			break;

		case eSTEP_GET_EVENT_FIELD_NS:
			// Bei allen EventFields den ServerNamespaceIndex eintragen (in 4-Blöcken)
			if(inst->pRunServer->Events.nEventCount > 0 && inst->pRunServer->Events.pEvents != 0)
			{
				// Events und deren Fields durchtickern
				UINT nEventFieldLoopCount = 0;
				BOOL bLeaveEventLoop = 0;
				do
				{
					if(inst->nEventIndex < inst->pRunServer->Events.nEventCount)
					{
						BrbUaRsEventIntern_TYP* pEvent = ((BrbUaRsEventIntern_TYP*)inst->pRunServer->Events.pEvents) + inst->nEventIndex;
						if(inst->nEventFieldIndex < pEvent->nFieldCount)
						{
							// ServerNamespaceIndex in jedem Element des Browse-Pfads ermitteln und austauschen
							UaSrv_FireEventFieldType* pEventField = ((UaSrv_FireEventFieldType*)pEvent->pFields) + inst->nEventFieldIndex;
							nEventFieldLoopCount += 1;
							UDINT nPathLen = brsstrlen((UDINT)&pEventField->BrowsePath);
							UINT nOffset = 0;
							BOOL bLeaveBrowsePathLoop = 0;
							do
							{
								// BrowsePath durchtickern
								if(nOffset < nPathLen)
								{
									// Nach / suchen
									DINT nStart = BrbStringGetIndexOf((STRING*)&pEventField->BrowsePath + nOffset, "/", 0);
									if(nStart > -1)
									{
										// Nach : suchen
										DINT nEnd = BrbStringGetIndexOf((STRING*)&pEventField->BrowsePath + nOffset + nStart + 1, ":", 0);
										if(nEnd > nStart)
										{
											// Zwischen / und : könnte ein NamespaceIndex liegen
											DINT nLen = nEnd - nStart;
											if(nLen > 0)
											{
												// Vermutlichen NamespaceIndex ermitteln
												STRING sOldNamespaceIndex[nLen+1];
												BrbStringGetSubTextByLen((STRING*)&pEventField->BrowsePath + nOffset + nStart + 1, (UDINT)nLen, (STRING*)&sOldNamespaceIndex);
												// Auf Nummer prüfen
												if(BrbStringIsNumerical(sOldNamespaceIndex) == 1)
												{
													// NamespaceIndex vorhanden
													UINT nOldNamespaceIndex = (UINT)BrbAsciiToUdint((STRING*)&sOldNamespaceIndex);
													UINT nNewNamespaceIndex = BrbUaRsGetNamespace(inst->pRunServer, nOldNamespaceIndex, 0);
													// Auf Unterschied prüfen
													if(nNewNamespaceIndex != nOldNamespaceIndex)
													{
														// Alten NamespaceIndex rausschneiden
														BrbStringCut((STRING*)&pEventField->BrowsePath + nOffset, (UDINT)nStart + 1, (UDINT)nLen, 0);
														// Neuen NamespaceIndex einfügen
														STRING sNewNamespaceIndex[12];
														brsitoa((DINT)nNewNamespaceIndex, (UDINT)&sNewNamespaceIndex);
														BrbStringInsert((STRING*)&pEventField->BrowsePath + nOffset, (UDINT)nStart + 1, (STRING*)sNewNamespaceIndex);
													}
												}
											}
											nOffset += nEnd;
										}
										else
										{
											inst->nEventFieldIndex += 1;
											bLeaveBrowsePathLoop = 1;
										}
									}
									else
									{
										inst->nEventFieldIndex += 1;
										bLeaveBrowsePathLoop = 1;
									}
								}
								else
								{
									inst->nEventFieldIndex += 1;
									bLeaveBrowsePathLoop = 1;
								}
							} while(bLeaveBrowsePathLoop == 0);
							if(nEventFieldLoopCount >= 4)
							{
								nEventFieldLoopCount = 0;
								bLeaveEventLoop = 1;
							}
						}
						else
						{
							// Nächstes Event
							inst->nEventFieldIndex = 0;
							inst->nEventIndex += 1;
						}
					}
					else
					{
						// Alle Events behandelt
						bLeaveEventLoop = 1;
						inst->eStep = eSTEP_RUNNING;
					}
				} while(bLeaveEventLoop == 0);
			}
			else
			{
				// Keine Events
				inst->eStep = eSTEP_RUNNING;
			}
			break;

		case eSTEP_RUNNING:
			inst->pRunServer->State.eState = eBRB_RSSTATE_RUNNING;
			// Server-Status abfragen
			inst->pRunServer->State.eServerState = UaSrv_GetServerState();
			break;

	}

	// Aufruf aller FB's
	UaSrv_GetNamespaceIndex(&inst->fbUaSrv_GetNamespaceIndex);
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

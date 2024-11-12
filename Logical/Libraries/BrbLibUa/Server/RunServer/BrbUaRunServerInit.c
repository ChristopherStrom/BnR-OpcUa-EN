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
BOOL ParseServerValue(STRING** ppStart, STRING* pPar, STRING* pValue);

// Eigene Enums und Typen
enum Steps_ENUM
{
	eSTEP_INIT,
	eSTEP_GET_DAT_INFO,
	eSTEP_COUNT_GENERAL,
	eSTEP_ALLOC_NAMESPACES,
	eSTEP_ALLOC_EVENTS,
	eSTEP_PARSE_GENERAL,
	eSTEP_ALLOC_EVENT_FIELDS,
	eSTEP_PARSE_EVENT_FIELDS,
	eSTEP_FINISHED,
};

/* Initialisiert eine Client-Instanz */
void BrbUaRunServerInit(struct BrbUaRunServerInit* inst)
{
	switch(inst->eStep)
	{
		case eSTEP_INIT:
			// Fub initialisieren
			inst->nStatus =  eBRB_ERR_BUSY;
			memset(&inst->fbDatObjInfo, 0, sizeof(inst->fbDatObjInfo));
			memset(&inst->fbDatObjRead, 0, sizeof(inst->fbDatObjRead));
			// Client-Pointer prüfen
			if(inst->pRunServer != 0)
			{
				inst->pRunServer->State.eState = eBRB_RSSTATE_INITIALIZING;
				inst->pRunServer->State.nErroId = 0x00000000;
				strcpy(inst->pRunServer->State.sErrorText, "");
				inst->pRunServer->State.eServerState = UASS_Shutdown;
				memset(&inst->pRunServer->Namespaces, 0, sizeof(inst->pRunServer->Namespaces));
				memset(&inst->pRunServer->Events, 0, sizeof(inst->pRunServer->Events));
				inst->pRunServer->Events.nEventCount = 0;
				inst->pRunServer->Events.nFieldsCountTotal = 0;
				inst->eStep = eSTEP_GET_DAT_INFO;
			}
			else
			{
				inst->nStatus = eBRB_ERR_NULL_POINTER;
				inst->eStep = eSTEP_INIT;
			}
			break;

		case eSTEP_GET_DAT_INFO:
			// Datenobjekt-Ident ermitteln
			inst->nStatus  = eBRB_ERR_BUSY;
			inst->fbDatObjInfo.enable = 1;
			inst->fbDatObjInfo.pName = (UDINT)&inst->pRunServer->Cfg.sCfgDataObjName;
			DatObjInfo(&inst->fbDatObjInfo);
			if(inst->fbDatObjInfo.status == 0)
			{
				inst->eStep = eSTEP_COUNT_GENERAL;
			}
			else if(inst->fbDatObjInfo.status != eBRB_ERR_BUSY)
			{
				// Fehler
				inst->nStatus = inst->fbDatObjInfo.status;
				inst->pRunServer->State.nErroId = inst->nStatus;
				strcpy(inst->pRunServer->State.sErrorText, "Init error on getting data object info");
				inst->pRunServer->State.eState = eBRB_RSSTATE_INIT_ERROR;
				inst->eStep = eSTEP_INIT;
			}
			break;

		case eSTEP_COUNT_GENERAL:
			// Elemente in Datenobjekt zählen
			inst->nStatus  = eBRB_ERR_BUSY;
			inst->pRunServer->Namespaces.nNamespaceCount = (UINT)BrbStringCountText((STRING*)inst->fbDatObjInfo.pDatObjMem, nBRBUA_KEYWORD_NAMESPACE, inst->fbDatObjInfo.len);
			inst->nNamespaceIndex = -1;
			inst->pRunServer->Events.nEventCount = (UINT)BrbStringCountText((STRING*)inst->fbDatObjInfo.pDatObjMem, nBRBUA_KEYWORD_EVENT, inst->fbDatObjInfo.len);
			inst->pRunServer->Events.nFieldsCountTotal = BrbStringCountText((STRING*)inst->fbDatObjInfo.pDatObjMem, nBRBUA_KEYWORD_EVENT_FIELD, inst->fbDatObjInfo.len);
			inst->nEventIndex = -1;
			inst->nEventFieldIndex = 0;
			inst->eStep = eSTEP_ALLOC_NAMESPACES;
			break;

		case eSTEP_ALLOC_NAMESPACES:
			// Speicher für Namespaces allokieren
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunServer->Namespaces.nNamespaceCount > 0)
			{
				inst->pRunServer->Namespaces.nMemLen = inst->pRunServer->Namespaces.nNamespaceCount * sizeof(BrbUaRsNamespace_TYP);
				inst->nAllocStatus = TMP_alloc(inst->pRunServer->Namespaces.nMemLen, (void*)&inst->pRunServer->Namespaces.pNamespaces);
				if(inst->nAllocStatus == 0 && inst->pRunServer->Namespaces.pNamespaces != 0)
				{
					memset((USINT*)inst->pRunServer->Namespaces.pNamespaces, 0, inst->pRunServer->Namespaces.nMemLen);
					inst->eStep = eSTEP_ALLOC_EVENTS;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nAllocStatus;
					inst->pRunServer->State.nErroId = inst->nStatus;
					strcpy(inst->pRunServer->State.sErrorText, "Init error on allocating memory for namespaces");
					inst->pRunServer->State.eState = eBRB_RSSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
				}
			}
			else
			{
				// Keine Namespaces angegeben
				inst->eStep = eSTEP_ALLOC_EVENTS;
			}
			break;

		case eSTEP_ALLOC_EVENTS:
			// Speicher für Events allokieren
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunServer->Events.nEventCount > 0)
			{
				inst->pRunServer->Events.nMemLen = inst->pRunServer->Events.nEventCount * sizeof(BrbUaRsEventIntern_TYP);
				inst->nAllocStatus = TMP_alloc(inst->pRunServer->Events.nMemLen, (void*)&inst->pRunServer->Events.pEvents);
				if(inst->nAllocStatus == 0 && inst->pRunServer->Events.pEvents != 0)
				{
					memset((USINT*)inst->pRunServer->Events.pEvents, 0, inst->pRunServer->Events.nMemLen);
					inst->eStep = eSTEP_PARSE_GENERAL;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nAllocStatus;
					inst->pRunServer->State.nErroId = inst->nStatus;
					strcpy(inst->pRunServer->State.sErrorText, "Init error on allocating memory for events");
					inst->pRunServer->State.eState = eBRB_RSSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
					break;
				}
			}
			else
			{
				// Keine Subscriptions angegeben
				inst->eStep = eSTEP_PARSE_GENERAL;
			}
			break;

		case eSTEP_PARSE_GENERAL:
			// Datenobjekt parsen
			inst->nStatus  = eBRB_ERR_BUSY;
			for(inst->nLoopIndex=0; inst->nLoopIndex<nBRBUA_SRV_READ_LINES; inst->nLoopIndex++) // In einem Zyklus 100 Zeilen lesen
			{
				inst->fbDatObjRead.enable = 1;
				inst->fbDatObjRead.ident = inst->fbDatObjInfo.ident;
				inst->fbDatObjRead.pDestination = (UDINT)&inst->sLine; 
				inst->fbDatObjRead.len = sizeof(inst->sLine)-1;
				if(inst->fbDatObjInfo.len < inst->fbDatObjRead.Offset + inst->fbDatObjRead.len)
				{
					// Es können nur mehr eine bestimmte Anzahl von Bytes gelesen werden
					inst->fbDatObjRead.len = inst->fbDatObjInfo.len - inst->fbDatObjRead.Offset;
				}
				DatObjRead(&inst->fbDatObjRead);
				if(inst->fbDatObjRead.status == 0)
				{
					inst->nLineLen = strlen(inst->sLine);
					if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_NAMESPACE) == 1)
					{
						inst->nNamespaceIndex++;
						if(inst->nNamespaceIndex < inst->pRunServer->Namespaces.nNamespaceCount && inst->pRunServer->Namespaces.pNamespaces != 0)
						{
							// Werte des Namespaces auslesen
							BrbUaRsNamespace_TYP* pNamespace = ((BrbUaRsNamespace_TYP*)inst->pRunServer->Namespaces.pNamespaces) + inst->nNamespaceIndex;
							STRING* pStart = (STRING*)&inst->sLine;
							memset(&inst->sValue, 0, sizeof(inst->sValue));
							if(ParseServerValue(&pStart, "Uri=", inst->sValue) == 1)
							{
								BrbStringCopy(pNamespace->sNamespaceUri, inst->sValue, sizeof(pNamespace->sNamespaceUri));
							}
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_EVENT) == 1)
					{
						inst->nEventIndex++;
						if(inst->nEventIndex < inst->pRunServer->Events.nEventCount && inst->pRunServer->Events.pEvents != 0)
						{
							BrbUaRsEventIntern_TYP* pEvent = ((BrbUaRsEventIntern_TYP*)inst->pRunServer->Events.pEvents) + inst->nEventIndex;
							// Zuerst Default-Werte setzen
							pEvent->nDatObjNamespaceIndex = 0;
							BrbUaSetNodeId(&pEvent->TypeNodeId, "2041", 0);// Server-NamespaceIndex muss erst noch ermittelt werden
							// Werte des Events auslesen
							STRING* pStart = (STRING*)&inst->sLine;
							memset(&inst->sValue, 0, sizeof(inst->sValue));
							if(ParseServerValue(&pStart, "TypeNs=", inst->sValue) == 1)
							{
								inst->nValue = brsatoi((UDINT)&inst->sValue);
								pEvent->nDatObjNamespaceIndex = (UINT)inst->nValue;
							}
							if(ParseServerValue(&pStart, "TypeId=", inst->sValue) == 1)
							{
								BrbUaSetNodeId(&pEvent->TypeNodeId, inst->sValue, 0);// Server-NamespaceIndex muss erst noch ermittelt werden
							}
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_EVENT_FIELD) == 1)
					{
						// Fields zählen
						if(inst->nEventIndex < inst->pRunServer->Events.nEventCount && inst->pRunServer->Events.pEvents != 0)
						{
							BrbUaRsEventIntern_TYP* pEvent = ((BrbUaRsEventIntern_TYP*)inst->pRunServer->Events.pEvents) + inst->nEventIndex;
							pEvent->nFieldCount++;
						}
					}
					// Nächste Zeile lesen
					inst->fbDatObjRead.Offset += inst->nLineLen+1;
				}
				else if(inst->fbDatObjRead.status == doERR_ILLEGALLENGTH)
				{
					// Am Ende des Datenobjekts angelangt
					inst->fbDatObjRead.Offset = 0;
					inst->nEventIndex = 0;
					inst->eStep = eSTEP_ALLOC_EVENT_FIELDS;
					break;
				}
				else if(inst->fbDatObjRead.status != 65535)
				{
					// Fehler
					inst->nStatus = inst->fbDatObjRead.status;
					inst->pRunServer->State.nErroId = inst->nStatus;
					strcpy(inst->pRunServer->State.sErrorText, "Init error on parsing data object for general data");
					inst->pRunServer->State.eState = eBRB_RSSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
					break;
				}
			}
			break;

		case eSTEP_ALLOC_EVENT_FIELDS:
			// Speicher für Fields pro Event allokieren
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunServer->Events.nEventCount > 0 && inst->pRunServer->Events.pEvents != 0)
			{
				if(inst->nEventIndex < inst->pRunServer->Events.nEventCount)
				{
					BrbUaRsEventIntern_TYP* pEvent = (((BrbUaRsEventIntern_TYP*)inst->pRunServer->Events.pEvents)  + inst->nEventIndex);
					if(pEvent->nFieldCount > 0)
					{
						pEvent->nMemLen = pEvent->nFieldCount * sizeof(UaSrv_FireEventFieldType);
						inst->nAllocStatus = TMP_alloc(pEvent->nMemLen, (void*)&pEvent->pFields);
						if(inst->nAllocStatus == 0 && pEvent->pFields != 0)
						{
							memset((USINT*)pEvent->pFields, 0, pEvent->nMemLen);
							inst->nEventIndex++;
						}
						else
						{
							// Fehler
							inst->nStatus = inst->nAllocStatus;
							inst->pRunServer->State.nErroId = inst->nStatus;
							BrbStringCopy(inst->pRunServer->State.sErrorText, "Init error on allocating memory for Fields of Event", sizeof(inst->pRunServer->State.sErrorText));
							STRING sHelp[16];
							brsitoa(inst->nEventIndex, (UDINT)&sHelp);
							BrbStringCat(inst->pRunServer->State.sErrorText, sHelp, sizeof(inst->pRunServer->State.sErrorText));
							inst->pRunServer->State.eState = eBRB_RSSTATE_INIT_ERROR;
							inst->eStep = eSTEP_INIT;
							break;
						}
					}
					else
					{
						inst->nEventIndex++;
					}
				}
				else
				{
					inst->nEventIndex = -1;
					inst->nEventFieldIndex = 0;
					inst->eStep = eSTEP_PARSE_EVENT_FIELDS;
				}
			}
			else
			{
				// Keine Events angegeben
				inst->eStep = eSTEP_FINISHED;
			}
			break;

		case eSTEP_PARSE_EVENT_FIELDS:
			// Parameter der Fields parsen
			inst->nStatus  = eBRB_ERR_BUSY;
			for(inst->nLoopIndex=0; inst->nLoopIndex<nBRBUA_SRV_READ_LINES; inst->nLoopIndex++) // In einem Zyklus 100 Zeilen lesen
			{
				inst->fbDatObjRead.enable = 1;
				inst->fbDatObjRead.ident = inst->fbDatObjInfo.ident;
				inst->fbDatObjRead.pDestination = (UDINT)&inst->sLine; 
				inst->fbDatObjRead.len = sizeof(inst->sLine)-1;
				if(inst->fbDatObjInfo.len < inst->fbDatObjRead.Offset + inst->fbDatObjRead.len)
				{
					// Es können nur mehr eine bestimmte Anzahl von Bytes gelesen werden
					inst->fbDatObjRead.len = inst->fbDatObjInfo.len - inst->fbDatObjRead.Offset;
				}
				DatObjRead(&inst->fbDatObjRead);
				if(inst->fbDatObjRead.status == 0)
				{
					inst->nLineLen = strlen(inst->sLine);
					if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_EVENT) == 1)
					{
						inst->nEventIndex++;
						inst->nEventFieldIndex = 0;
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_EVENT_FIELD) == 1)
					{
						// Werte des Fields auslesen
						if(inst->nEventIndex < inst->pRunServer->Events.nEventCount && inst->pRunServer->Events.pEvents != 0)
						{
							BrbUaRsEventIntern_TYP* pEvent = ((BrbUaRsEventIntern_TYP*)inst->pRunServer->Events.pEvents) + inst->nEventIndex;
							if(inst->nEventFieldIndex < pEvent->nFieldCount)
							{
								UaSrv_FireEventFieldType* pEventField = ((UaSrv_FireEventFieldType*)pEvent->pFields) + inst->nEventFieldIndex;
								// Zuerst Default-Werte setzen
								pEventField->ErrorID = 0;
								// Dann exisitierende Parameter auslesen
								STRING* pStart = (STRING*)&inst->sLine;
								memset(&inst->sValue, 0, sizeof(inst->sValue));
								if(ParseServerValue(&pStart, "Name=", inst->sValue) == 1)
								{
									BrbStringCopy(pEventField->BrowsePath, inst->sValue, sizeof(pEventField->BrowsePath));
								}
								if(ParseServerValue(&pStart, "Var=", inst->sValue) == 1)
								{
									BrbStringCopy(pEventField->Variable, inst->sValue, sizeof(pEventField->Variable));
								}
							}
							inst->nEventFieldIndex++;
						}
					}
					// Nächste Zeile lesen
					inst->fbDatObjRead.Offset += inst->nLineLen+1;
				}
				else if(inst->fbDatObjRead.status == doERR_ILLEGALLENGTH)
				{
					// Am Ende des Datenobjekts angelangt
					inst->fbDatObjRead.Offset = 0;
					inst->nEventIndex = -1;
					inst->nEventFieldIndex = -1;
					inst->eStep = eSTEP_FINISHED;
					break;
				}
				else if(inst->fbDatObjRead.status != 65535)
				{
					// Fehler
					inst->nStatus = inst->fbDatObjRead.status;
					inst->pRunServer->State.nErroId = inst->nStatus;
					strcpy(inst->pRunServer->State.sErrorText, "Init error on parsing Fields");
					inst->pRunServer->State.eState = eBRB_RSSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
					break;
				}
			}
			break;

		case eSTEP_FINISHED:
			inst->nStatus = 0;
			inst->pRunServer->State.eState = eBRB_RSSTATE_INIT_DONE;
			inst->eStep = eSTEP_INIT;
			break;

	}
}

// Wert aus dem Datenobjekt lesen
BOOL ParseServerValue(STRING** ppStart, STRING* pPar, STRING* pValue)
{
	BOOL bResult = 0;
	UDINT nLineLen = brsstrlen((UDINT)*ppStart);
	DINT nStartPar = BrbStringGetIndexOf(*ppStart, pPar, nLineLen);
	if(nStartPar > -1)
	{
		DINT nStartVal = nStartPar + (DINT)strlen(pPar);
		if(nStartVal >= 0)
		{
			DINT nEndVal = BrbStringGetIndexOf(*ppStart, ",", nLineLen);
			if(nEndVal > nStartVal)
			{
				// Bis zum nächsten Komma lesen
				UDINT nLen = (UDINT)(nEndVal- nStartVal);
				BrbStringGetSubText(*ppStart, (UDINT)nStartVal, nLen, pValue);
				BrbStringTrimLeft(pValue, " ");
				BrbStringTrimRight(pValue, " ");
				*ppStart += nEndVal+1;
				bResult = 1;
			}
			else if(nEndVal == -1)
			{
				// Kein Komma am Schluss -> Bis Ende lesen
				UDINT nLen = nLineLen - (UDINT)nStartVal;
				BrbStringGetSubText(*ppStart, (UDINT)nStartVal, nLen, pValue);
				BrbStringTrimLeft(pValue, " ");
				BrbStringTrimRight(pValue, " ");
				*ppStart += nEndVal+1;
				bResult = 1;
			}
		}
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

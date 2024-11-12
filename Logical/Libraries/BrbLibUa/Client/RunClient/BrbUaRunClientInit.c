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
BOOL ParseClientValue(STRING** ppStart, STRING* pPar, STRING* pValue);

// Eigene Enums und Typen
enum Steps_ENUM
{
	eSTEP_INIT,
	eSTEP_GET_DAT_INFO,
	eSTEP_SET_CONN_DEFAULT,
	eSTEP_COUNT_GENERAL,
	eSTEP_ALLOC_NAMESPACES,
	eSTEP_ALLOC_NODEHANDLES,
	eSTEP_ALLOC_READBLOCKS,
	eSTEP_ALLOC_WRITEBLOCKS,
	eSTEP_ALLOC_METHODS,
	eSTEP_ALLOC_SUBSCRIPTIONS,
	eSTEP_PARSE_GENERAL,
	eSTEP_ALLOC_READ_ITEMS,
	eSTEP_PARSE_READ_ITEMS,
	eSTEP_ALLOC_WRITE_ITEMS,
	eSTEP_PARSE_WRITE_ITEMS,
	eSTEP_ALLOC_METHOD_ARGUMENTS,
	eSTEP_PARSE_METHOD_ARGUMENTS,
	eSTEP_ALLOC_MONITORED_ITEMS,
	eSTEP_ALLOC_EVENT_ITEMS,
	eSTEP_PARSE_SUBSCRIPTION_ITEMS,
	eSTEP_COUNT_EVENT_FIELDS,
	eSTEP_ALLOC_EVENT_FIELDS,
	eSTEP_PARSE_EVENT_FIELDS,
	eSTEP_FINISHED,
};

/* Initialisiert eine Client-Instanz */
void BrbUaRunClientInit(struct BrbUaRunClientInit* inst) // NOLINT(hicpp-function-size, readability-function-size)
{
	switch(inst->eStep)
	{
		case eSTEP_INIT:
			// Fub initialisieren
			inst->nStatus =  eBRB_ERR_BUSY;
			memset(&inst->fbDatObjInfo, 0, sizeof(inst->fbDatObjInfo));
			memset(&inst->fbDatObjRead, 0, sizeof(inst->fbDatObjRead));
			// Client-Pointer prüfen
			if(inst->pRunClient != 0)
			{
				inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INITIALIZING;
				inst->pRunClient->State.nClientErroId = 0x00000000;
				strcpy(inst->pRunClient->State.sClientErrorText, "");
				memset(&inst->pRunClient->Connection, 0, sizeof(inst->pRunClient->Connection));
				memset(&inst->pRunClient->Namespaces, 0, sizeof(inst->pRunClient->Namespaces));
				memset(&inst->pRunClient->NodeHandles, 0, sizeof(inst->pRunClient->NodeHandles));
				memset(&inst->pRunClient->ReadBlocks, 0, sizeof(inst->pRunClient->ReadBlocks));
				memset(&inst->pRunClient->WriteBlocks, 0, sizeof(inst->pRunClient->WriteBlocks));
				memset(&inst->pRunClient->Methods, 0, sizeof(inst->pRunClient->Methods));
				memset(&inst->pRunClient->Subscriptions, 0, sizeof(inst->pRunClient->Subscriptions));
				inst->pRunClient->Connection.nConnectTries = 0;
				inst->pRunClient->Connection.nInterruptedCount = 0;
				inst->pRunClient->Subscriptions.nMonitoredItemsCountTotal = 0;
				inst->pRunClient->Subscriptions.nEventItemsCountTotal = 0;
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
			inst->fbDatObjInfo.pName = (UDINT)&inst->pRunClient->Cfg.sCfgDataObjName;
			DatObjInfo(&inst->fbDatObjInfo);
			if(inst->fbDatObjInfo.status == 0)
			{
				inst->fbDatObjInfo.enable = 0;
				inst->eStep = eSTEP_SET_CONN_DEFAULT;
			}
			else if(inst->fbDatObjInfo.status != eBRB_ERR_BUSY)
			{
				// Fehler
				inst->fbDatObjInfo.enable = 0;
				inst->nStatus = inst->fbDatObjInfo.status;
				inst->pRunClient->State.nClientErroId = inst->nStatus;
				strcpy(inst->pRunClient->State.sClientErrorText, "Init error on getting data object info");
				inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
				inst->eStep = eSTEP_INIT;
			}
			break;

		case eSTEP_SET_CONN_DEFAULT:
			// Default-Werte der Connection setzen
			inst->nStatus =  eBRB_ERR_BUSY;
			strcpy(inst->pRunClient->Cfg.sServerEndpointUrl, "");
			strcpy(inst->pRunClient->Cfg.SessionConnectInfo.SessionName, "");
			strcpy(inst->pRunClient->Cfg.SessionConnectInfo.ApplicationName, "");
			inst->pRunClient->Cfg.SessionConnectInfo.SecurityPolicy = UASecurityPolicy_BestAvailable;
			inst->pRunClient->Cfg.SessionConnectInfo.SecurityMsgMode = UASecurityMsgMode_BestAvailable; 
			strcpy(inst->pRunClient->Cfg.SessionConnectInfo.CertificateStore, "");
			strcpy(inst->pRunClient->Cfg.SessionConnectInfo.ServerUri, "");
			inst->pRunClient->Cfg.SessionConnectInfo.CheckServerCertificate = 0;
			inst->pRunClient->Cfg.SessionConnectInfo.TransportProfile = UATP_UATcp; 
			inst->pRunClient->Cfg.SessionConnectInfo.UserIdentityToken.UserIdentityTokenType = UAUITT_Anonymous;
			strcpy(inst->pRunClient->Cfg.SessionConnectInfo.UserIdentityToken.TokenParam1, "");
			strcpy(inst->pRunClient->Cfg.SessionConnectInfo.UserIdentityToken.TokenParam2, "");
			strcpy(inst->pRunClient->Cfg.SessionConnectInfo.VendorSpecificParameter, "");
			inst->pRunClient->Cfg.SessionConnectInfo.SessionTimeout = 10000;
			inst->pRunClient->Cfg.SessionConnectInfo.MonitorConnection = 2000;
			strcpy(inst->pRunClient->Cfg.SessionConnectInfo.LocaleIDs[0], "en");
			inst->pRunClient->Cfg.tConnectTimeout = 3000;
			inst->pRunClient->Cfg.tAccessTimeout = 5000;
			inst->eStep = eSTEP_COUNT_GENERAL;
			break;

		case eSTEP_COUNT_GENERAL:
			// Elemente in Datenobjekt zählen
			inst->nStatus  = eBRB_ERR_BUSY;
			inst->pRunClient->Namespaces.nNamespaceCount = (UINT)BrbStringCountText((STRING*)inst->fbDatObjInfo.pDatObjMem, nBRBUA_KEYWORD_NAMESPACE, inst->fbDatObjInfo.len);
			inst->nNamespaceIndex = -1;
			inst->pRunClient->NodeHandles.nNodeHandleCount = (UINT)BrbStringCountText((STRING*)inst->fbDatObjInfo.pDatObjMem, nBRBUA_KEYWORD_NODEHANDLE, inst->fbDatObjInfo.len);
			inst->nNodeHandleIndex = -1;
			inst->pRunClient->ReadBlocks.nBlockCount = (UINT)BrbStringCountText((STRING*)inst->fbDatObjInfo.pDatObjMem, nBRBUA_KEYWORD_READBLOCK, inst->fbDatObjInfo.len);
			inst->nReadBlockIndex = -1;
			inst->pRunClient->WriteBlocks.nBlockCount = (UINT)BrbStringCountText((STRING*)inst->fbDatObjInfo.pDatObjMem, nBRBUA_KEYWORD_WRITEBLOCK, inst->fbDatObjInfo.len);
			inst->nWriteBlockIndex = -1;
			inst->pRunClient->Methods.nMethodCount = (UINT)BrbStringCountText((STRING*)inst->fbDatObjInfo.pDatObjMem, nBRBUA_KEYWORD_METHOD, inst->fbDatObjInfo.len);
			inst->nMethodIndex = -1;
			inst->nArgumentInputIndex = 0;
			inst->nArgumentOutputIndex = 0;
			inst->pRunClient->Subscriptions.nSubscriptionCount = (UINT)BrbStringCountText((STRING*)inst->fbDatObjInfo.pDatObjMem, nBRBUA_KEYWORD_SUBSCRIPTION, inst->fbDatObjInfo.len);
			inst->pRunClient->Subscriptions.nMonitoredItemsCountTotal = BrbStringCountText((STRING*)inst->fbDatObjInfo.pDatObjMem, nBRBUA_KEYWORD_MONITORED_ITEM, inst->fbDatObjInfo.len);
			inst->pRunClient->Subscriptions.nEventItemsCountTotal = BrbStringCountText((STRING*)inst->fbDatObjInfo.pDatObjMem, nBRBUA_KEYWORD_EVENT_ITEM, inst->fbDatObjInfo.len);
			inst->nSubscriptionIndex = -1;
			inst->nMonItemIndex = 0;
			inst->nEventItemIndex = 0;
			inst->eStep = eSTEP_ALLOC_NAMESPACES;
			break;

		case eSTEP_ALLOC_NAMESPACES:
			// Speicher für Namespaces allokieren
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->Namespaces.nNamespaceCount > 0)
			{
				inst->pRunClient->Namespaces.nMemLen = inst->pRunClient->Namespaces.nNamespaceCount * sizeof(BrbUaRcNamespace_TYP);
				inst->nAllocStatus = TMP_alloc(inst->pRunClient->Namespaces.nMemLen, (void*)&inst->pRunClient->Namespaces.pNamespaces);
				if(inst->nAllocStatus == 0 && inst->pRunClient->Namespaces.pNamespaces != 0)
				{
					memset((USINT*)inst->pRunClient->Namespaces.pNamespaces, 0, inst->pRunClient->Namespaces.nMemLen);
					inst->eStep = eSTEP_ALLOC_NODEHANDLES;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nAllocStatus;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Init error on allocating memory for namespaces");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
				}
			}
			else
			{
				// Keine Namespaces angegeben
				inst->eStep = eSTEP_ALLOC_NODEHANDLES;
			}
			break;

		case eSTEP_ALLOC_NODEHANDLES:
			// Speicher für NodeHandles allokieren
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->NodeHandles.nNodeHandleCount > 0)
			{
				UDINT nMemLenDatObjNsIndices				= inst->pRunClient->NodeHandles.nNodeHandleCount * sizeof(UINT);
				UDINT nMemLenNodeIds								= inst->pRunClient->NodeHandles.nNodeHandleCount * sizeof(UANodeID);
				UDINT nMemLenNodeHandleErrorIds			= inst->pRunClient->NodeHandles.nNodeHandleCount * sizeof(DWORD);
				UDINT nMemLenNodeHandles						= inst->pRunClient->NodeHandles.nNodeHandleCount * sizeof(DWORD);
				inst->pRunClient->NodeHandles.nMemLen = nMemLenDatObjNsIndices + nMemLenNodeIds + nMemLenNodeHandleErrorIds + nMemLenNodeHandles;
				inst->nAllocStatus = TMP_alloc(inst->pRunClient->NodeHandles.nMemLen, (void*)&inst->pRunClient->NodeHandles.pStart);
				if(inst->nAllocStatus == 0 && inst->pRunClient->NodeHandles.pStart != 0)
				{
					memset((USINT*)inst->pRunClient->NodeHandles.pStart, 0, inst->pRunClient->NodeHandles.nMemLen);
					// Pointer auf die einzelnen Arrays speichern
					inst->pRunClient->NodeHandles.pDatObjNamespaceIndices	= inst->pRunClient->NodeHandles.pStart;
					inst->pRunClient->NodeHandles.pNodeIds								= inst->pRunClient->NodeHandles.pDatObjNamespaceIndices	+ nMemLenDatObjNsIndices;
					inst->pRunClient->NodeHandles.pNodeHandleErrorIds			= inst->pRunClient->NodeHandles.pNodeIds								+ nMemLenNodeIds;
					inst->pRunClient->NodeHandles.pNodeHandles						= inst->pRunClient->NodeHandles.pNodeHandleErrorIds			+ nMemLenNodeHandleErrorIds;
					inst->eStep = eSTEP_ALLOC_READBLOCKS;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nAllocStatus;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Init error on allocating memory for nodehandles");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
					break;
				}
			}
			else
			{
				// Keine NodeHandles angegeben
				inst->eStep = eSTEP_ALLOC_READBLOCKS;
			}
			break;

		case eSTEP_ALLOC_READBLOCKS:
			// Speicher für ReadBlocks allokieren
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->ReadBlocks.nBlockCount > 0)
			{
				inst->pRunClient->ReadBlocks.nMemLen = inst->pRunClient->ReadBlocks.nBlockCount * sizeof(BrbUaRcReadBlockIntern_TYP);
				inst->nAllocStatus = TMP_alloc(inst->pRunClient->ReadBlocks.nMemLen, (void*)&inst->pRunClient->ReadBlocks.pBlocks);
				if(inst->nAllocStatus == 0 && inst->pRunClient->ReadBlocks.pBlocks != 0)
				{
					memset((USINT*)inst->pRunClient->ReadBlocks.pBlocks, 0, inst->pRunClient->ReadBlocks.nMemLen);
					inst->eStep = eSTEP_ALLOC_WRITEBLOCKS;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nAllocStatus;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Init error on allocating memory for read blocks");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
					break;
				}
			}
			else
			{
				// Keine ReadBlocks angegeben
				inst->eStep = eSTEP_ALLOC_WRITEBLOCKS;
			}
			break;

		case eSTEP_ALLOC_WRITEBLOCKS:
			// Speicher für WriteBlocks allokieren
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->WriteBlocks.nBlockCount > 0)
			{
				inst->pRunClient->WriteBlocks.nMemLen = inst->pRunClient->WriteBlocks.nBlockCount * sizeof(BrbUaRcWriteBlockIntern_TYP);
				inst->nAllocStatus = TMP_alloc(inst->pRunClient->WriteBlocks.nMemLen, (void*)&inst->pRunClient->WriteBlocks.pBlocks);
				if(inst->nAllocStatus == 0 && inst->pRunClient->WriteBlocks.pBlocks != 0)
				{
					memset((USINT*)inst->pRunClient->WriteBlocks.pBlocks, 0, inst->pRunClient->WriteBlocks.nMemLen);
					inst->eStep = eSTEP_ALLOC_METHODS;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nAllocStatus;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Init error on allocating memory for write blocks");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
					break;
				}
			}
			else
			{
				// Keine WriteBlocks angegeben
				inst->eStep = eSTEP_ALLOC_METHODS;
			}
			break;

		case eSTEP_ALLOC_METHODS:
			// Speicher für Methods allokieren
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->Methods.nMethodCount > 0)
			{
				inst->pRunClient->Methods.nMemLen = inst->pRunClient->Methods.nMethodCount * sizeof(BrbUaRcMethodIntern_TYP);
				inst->nAllocStatus = TMP_alloc(inst->pRunClient->Methods.nMemLen, (void*)&inst->pRunClient->Methods.pMethods);
				if(inst->nAllocStatus == 0 && inst->pRunClient->Methods.pMethods != 0)
				{
					memset((USINT*)inst->pRunClient->Methods.pMethods, 0, inst->pRunClient->Methods.nMemLen);
					inst->nMethodIndex = -1;
					inst->eStep = eSTEP_ALLOC_SUBSCRIPTIONS;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nAllocStatus;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Init error on allocating memory for methods");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
					break;
				}
			}
			else
			{
				// Keine Methods angegeben
				inst->eStep = eSTEP_ALLOC_SUBSCRIPTIONS;
			}
			break;

		case eSTEP_ALLOC_SUBSCRIPTIONS:
			// Speicher für Subscriptions allokieren
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->Subscriptions.nSubscriptionCount > 0)
			{
				inst->pRunClient->Subscriptions.nMemLen = inst->pRunClient->Subscriptions.nSubscriptionCount * sizeof(BrbUaRcSubscriptionIntern_TYP);
				inst->nAllocStatus = TMP_alloc(inst->pRunClient->Subscriptions.nMemLen, (void*)&inst->pRunClient->Subscriptions.pSubscriptions);
				if(inst->nAllocStatus == 0 && inst->pRunClient->Subscriptions.pSubscriptions != 0)
				{
					memset((USINT*)inst->pRunClient->Subscriptions.pSubscriptions, 0, inst->pRunClient->Subscriptions.nMemLen);
					inst->eStep = eSTEP_PARSE_GENERAL;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nAllocStatus;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Init error on allocating memory for subscriptions");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
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
			for(inst->nLoopIndex=0; inst->nLoopIndex<nBRBUA_CLT_READ_LINES; inst->nLoopIndex++) // In einem Zyklus 100 Zeilen lesen
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
					if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_CONNECTION) == 1)
					{
						// Werte der Connection auslesen
						STRING* pStart = (STRING*)&inst->sLine;
						memset(&inst->sValue, 0, sizeof(inst->sValue));
						if(ParseClientValue(&pStart, "Endpoint=", inst->sValue) == 1)
						{
							BrbStringCopy(inst->pRunClient->Cfg.sServerEndpointUrl, inst->sValue, sizeof(inst->pRunClient->Cfg.sServerEndpointUrl));
						}
						if(ParseClientValue(&pStart, "SessionName=", inst->sValue) == 1)
						{
							BrbStringCopy(inst->pRunClient->Cfg.SessionConnectInfo.SessionName, inst->sValue, sizeof(inst->pRunClient->Cfg.SessionConnectInfo.SessionName));
						}
						if(ParseClientValue(&pStart, "AppName=", inst->sValue) == 1)
						{
							BrbStringCopy(inst->pRunClient->Cfg.SessionConnectInfo.ApplicationName, inst->sValue, sizeof(inst->pRunClient->Cfg.SessionConnectInfo.ApplicationName));
						}
						if(ParseClientValue(&pStart, "SecPolicy=", inst->sValue) == 1)
						{
							inst->nValue = brsatoi((UDINT)&inst->sValue);
							inst->pRunClient->Cfg.SessionConnectInfo.SecurityPolicy = (UASecurityPolicy)inst->nValue;
						}
						if(ParseClientValue(&pStart, "SecMode=", inst->sValue) == 1)
						{
							inst->nValue = brsatoi((UDINT)&inst->sValue);
							inst->pRunClient->Cfg.SessionConnectInfo.SecurityMsgMode = (UASecurityMsgMode)inst->nValue;
						}
						if(ParseClientValue(&pStart, "CertStore=", inst->sValue) == 1)
						{
							BrbStringCopy(inst->pRunClient->Cfg.SessionConnectInfo.CertificateStore, inst->sValue, sizeof(inst->pRunClient->Cfg.SessionConnectInfo.CertificateStore));
						}
						if(ParseClientValue(&pStart, "ServerUri=", inst->sValue) == 1)
						{
							BrbStringCopy(inst->pRunClient->Cfg.SessionConnectInfo.ServerUri, inst->sValue, sizeof(inst->pRunClient->Cfg.SessionConnectInfo.ServerUri));
						}
						if(ParseClientValue(&pStart, "CheckSrvCert=", inst->sValue) == 1)
						{
							inst->nValue = brsatoi((UDINT)&inst->sValue);
							inst->pRunClient->Cfg.SessionConnectInfo.CheckServerCertificate = (inst->nValue > 0);
						}
						if(ParseClientValue(&pStart, "UserToken=", inst->sValue) == 1)
						{
							inst->nValue = brsatoi((UDINT)&inst->sValue);
							inst->pRunClient->Cfg.SessionConnectInfo.UserIdentityToken.UserIdentityTokenType = (UAUserIdentityTokenTtype)inst->nValue;
						}
						if(ParseClientValue(&pStart, "TokenPar1=", inst->sValue) == 1)
						{
							BrbStringCopy(inst->pRunClient->Cfg.SessionConnectInfo.UserIdentityToken.TokenParam1, inst->sValue, sizeof(inst->pRunClient->Cfg.SessionConnectInfo.UserIdentityToken.TokenParam1));
						}
						if(ParseClientValue(&pStart, "TokenPar2=", inst->sValue) == 1)
						{
							BrbStringCopy(inst->pRunClient->Cfg.SessionConnectInfo.UserIdentityToken.TokenParam2, inst->sValue, sizeof(inst->pRunClient->Cfg.SessionConnectInfo.UserIdentityToken.TokenParam2));
						}
						if(ParseClientValue(&pStart, "VendorPar=", inst->sValue) == 1)
						{
							BrbStringCopy(inst->pRunClient->Cfg.SessionConnectInfo.VendorSpecificParameter, inst->sValue, sizeof(inst->pRunClient->Cfg.SessionConnectInfo.VendorSpecificParameter));
						}
						if(ParseClientValue(&pStart, "SessionTimeout=", inst->sValue) == 1)
						{
							inst->nValue = brsatoi((UDINT)&inst->sValue);
							inst->pRunClient->Cfg.SessionConnectInfo.SessionTimeout = (TIME)inst->nValue;
						}
						if(ParseClientValue(&pStart, "Monitor=", inst->sValue) == 1)
						{
							inst->nValue = brsatoi((UDINT)&inst->sValue);
							inst->pRunClient->Cfg.SessionConnectInfo.MonitorConnection = (TIME)inst->nValue;
						}
						if(ParseClientValue(&pStart, "Locales=", inst->sValue) == 1)
						{
							BrbStringSplit(inst->sValue, ";", (UDINT)&inst->pRunClient->Cfg.SessionConnectInfo.LocaleIDs, 4, sizeof(inst->pRunClient->Cfg.SessionConnectInfo.LocaleIDs[0]));
						}
						if(ParseClientValue(&pStart, "ConnectTimeout=", inst->sValue) == 1)
						{
							inst->nValue = brsatoi((UDINT)&inst->sValue);
							inst->pRunClient->Cfg.tConnectTimeout = (TIME)inst->nValue;
						}
						if(ParseClientValue(&pStart, "AccessTimeout=", inst->sValue) == 1)
						{
							inst->nValue = brsatoi((UDINT)&inst->sValue);
							inst->pRunClient->Cfg.tAccessTimeout = (TIME)inst->nValue;
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_NAMESPACE) == 1)
					{
						inst->nNamespaceIndex++;
						if(inst->nNamespaceIndex < inst->pRunClient->Namespaces.nNamespaceCount && inst->pRunClient->Namespaces.pNamespaces != 0)
						{
							// Werte des Namespaces auslesen
							BrbUaRcNamespace_TYP* pNamespace = ((BrbUaRcNamespace_TYP*)inst->pRunClient->Namespaces.pNamespaces) + inst->nNamespaceIndex;
							STRING* pStart = (STRING*)&inst->sLine;
							memset(&inst->sValue, 0, sizeof(inst->sValue));
							if(ParseClientValue(&pStart, "Uri=", inst->sValue) == 1)
							{
								BrbStringCopy(pNamespace->sNamespaceUri, inst->sValue, sizeof(pNamespace->sNamespaceUri));
							}
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_NODEHANDLE) == 1)
					{
						inst->nNodeHandleIndex++;
						if(inst->nNodeHandleIndex < inst->pRunClient->NodeHandles.nNodeHandleCount && inst->pRunClient->NodeHandles.pDatObjNamespaceIndices != 0 && inst->pRunClient->NodeHandles.pNodeIds != 0 && inst->pRunClient->NodeHandles.pNodeHandleErrorIds != 0 && inst->pRunClient->NodeHandles.pNodeHandles != 0)
						{
							// Werte des NodeHandles auslesen
							STRING* pStart = (STRING*)&inst->sLine;
							memset(&inst->sValue, 0, sizeof(inst->sValue));
							if(ParseClientValue(&pStart, "Ns=", inst->sValue) == 1)
							{
								inst->nValue = brsatoi((UDINT)&inst->sValue);
								*(((UINT*)(inst->pRunClient->NodeHandles.pDatObjNamespaceIndices)) + inst->nNodeHandleIndex) = (UINT)inst->nValue;
							}
							if(ParseClientValue(&pStart, "Id=", inst->sValue) == 1)
							{
								UANodeID* pNodeId = ((UANodeID*)inst->pRunClient->NodeHandles.pNodeIds) + inst->nNodeHandleIndex;
								BrbUaSetNodeId(pNodeId, inst->sValue, 0); // Server-NamespaceIndex muss erst noch ermittelt werden
							}
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_READBLOCK) == 1)
					{
						inst->nReadBlockIndex++;
						if(inst->nReadBlockIndex < inst->pRunClient->ReadBlocks.nBlockCount && inst->pRunClient->ReadBlocks.pBlocks != 0)
						{
							// Werte des ReadBlocks auslesen
							// Keine Werte
							/*
							BrbUaRcReadBlockIntern_TYP* pReadBlock = ((BrbUaRcReadBlockIntern_TYP*)inst->pRunClient->ReadBlocks.pBlocks) + inst->nReadBlockIndex;
							STRING* pStart = (STRING*)&inst->sLine;
							memset(&inst->sValue, 0, sizeof(inst->sValue));
							*/
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_READITEM) == 1)
					{
						// ReadItems zählen
						if(inst->nReadBlockIndex < inst->pRunClient->ReadBlocks.nBlockCount && inst->pRunClient->ReadBlocks.pBlocks != 0)
						{
							BrbUaRcReadBlockIntern_TYP* pReadBlock = ((BrbUaRcReadBlockIntern_TYP*)inst->pRunClient->ReadBlocks.pBlocks) + inst->nReadBlockIndex;
							pReadBlock->nReadItemCount++;
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_WRITEBLOCK) == 1)
					{
						inst->nWriteBlockIndex++;
						if(inst->nWriteBlockIndex < inst->pRunClient->WriteBlocks.nBlockCount && inst->pRunClient->WriteBlocks.pBlocks != 0)
						{
							// Werte des WriteBlocks auslesen
							// Keine Werte
							/*
							BrbUaRcWriteBlockIntern_TYP* pWriteBlock = ((BrbUaRcWriteBlockIntern_TYP*)inst->pRunClient->WriteBlocks.pBlocks) + inst->nWriteBlockIndex;
							STRING* pStart = (STRING*)&inst->sLine;
							memset(&inst->sValue, 0, sizeof(inst->sValue));
							*/
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_WRITEITEM) == 1)
					{
						// WriteItems zählen
						if(inst->nWriteBlockIndex < inst->pRunClient->WriteBlocks.nBlockCount && inst->pRunClient->WriteBlocks.pBlocks != 0)
						{
							BrbUaRcWriteBlockIntern_TYP* pWriteBlock = ((BrbUaRcWriteBlockIntern_TYP*)inst->pRunClient->WriteBlocks.pBlocks) + inst->nWriteBlockIndex;
							pWriteBlock->nWriteItemCount++;
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_METHOD) == 1)
					{
						inst->nMethodIndex++;
						if(inst->nMethodIndex < inst->pRunClient->Methods.nMethodCount && inst->pRunClient->Methods.pMethods != 0)
						{
							BrbUaRcMethodIntern_TYP* pMethod = (((BrbUaRcMethodIntern_TYP*)inst->pRunClient->Methods.pMethods) + inst->nMethodIndex);
							// Zuerst Default-Werte setzen
							pMethod->tTimeout = 5000;
							// Dann Werte der Method auslesen
							STRING* pStart = (STRING*)&inst->sLine;
							memset(&inst->sValue, 0, sizeof(inst->sValue));
							if(ParseClientValue(&pStart, "Ns=", inst->sValue) == 1)
							{
								inst->nValue = brsatoi((UDINT)&inst->sValue);
								pMethod->nDatObjNamespaceIndex = (UINT)inst->nValue;
							}
							if(ParseClientValue(&pStart, "ObjectId=", inst->sValue) == 1)
							{
								BrbUaSetNodeId(&pMethod->ObjectNodeId, inst->sValue, 0); // Server-NamespaceIndex muss erst noch ermittelt werden
							}
							if(ParseClientValue(&pStart, "MethodId=", inst->sValue) == 1)
							{
								BrbUaSetNodeId(&pMethod->MethodNodeId, inst->sValue, 0); // Server-NamespaceIndex muss erst noch ermittelt werden
							}
							if(ParseClientValue(&pStart, "Timeout=", inst->sValue) == 1)
							{
								inst->nValue = brsatoi((UDINT)&inst->sValue);
								pMethod->tTimeout = (UINT)inst->nValue;
							}
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_METHOD_ARG_IN) == 1)
					{
						// Eingangs-Argumente zählen
						if(inst->nMethodIndex < inst->pRunClient->Methods.nMethodCount && inst->pRunClient->Methods.pMethods != 0)
						{
							BrbUaRcMethodIntern_TYP* pMethod = (((BrbUaRcMethodIntern_TYP*)inst->pRunClient->Methods.pMethods) + inst->nMethodIndex);
							pMethod->nInputArgsCount++;
							if(pMethod->nInputArgsCount > MAX_ELEMENTS_ARGUMENTS)
							{
								pMethod->nInputArgsCount = MAX_ELEMENTS_ARGUMENTS;
							}
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_METHOD_ARG_OUT) == 1)
					{
						// Ausgangs-Argumente zählen
						if(inst->nMethodIndex < inst->pRunClient->Methods.nMethodCount && inst->pRunClient->Methods.pMethods != 0)
						{
							BrbUaRcMethodIntern_TYP* pMethod = (((BrbUaRcMethodIntern_TYP*)inst->pRunClient->Methods.pMethods) + inst->nMethodIndex);
							pMethod->nOutputArgsCount++;
							if(pMethod->nOutputArgsCount > MAX_ELEMENTS_ARGUMENTS)
							{
								pMethod->nOutputArgsCount = MAX_ELEMENTS_ARGUMENTS;
							}
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_SUBSCRIPTION) == 1)
					{
						inst->nSubscriptionIndex++;
						if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount && inst->pRunClient->Subscriptions.pSubscriptions != 0)
						{
							BrbUaRcSubscriptionIntern_TYP* pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex;
							// Zuerst Default-Werte setzen
							pSubscription->bPublishingEnable = 1;
							pSubscription->nPriority = 128;
							pSubscription->tPublishingInterval = 500;
							// Werte der Subscription auslesen
							STRING* pStart = (STRING*)&inst->sLine;
							memset(&inst->sValue, 0, sizeof(inst->sValue));
							if(ParseClientValue(&pStart, "Ena=", inst->sValue) == 1)
							{
								inst->nValue = brsatoi((UDINT)&inst->sValue);
								pSubscription->bPublishingEnable = (inst->nValue > 0);
							}
							if(ParseClientValue(&pStart, "Prio=", inst->sValue) == 1)
							{
								inst->nValue = brsatoi((UDINT)&inst->sValue);
								if(inst->nValue < 0)
								{
									inst->nValue = 0;
								}
								if(inst->nValue > 255)
								{
									inst->nValue = 255;
								}
								pSubscription->nPriority = (USINT)inst->nValue;
							}
							if(ParseClientValue(&pStart, "PubInt=", inst->sValue) == 1)
							{
								inst->nValue = brsatoi((UDINT)&inst->sValue);
								if(inst->nValue < 1)
								{
									inst->nValue = 1;
								}
								pSubscription->tPublishingInterval = (TIME)inst->nValue;
							}
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_MONITORED_ITEM) == 1)
					{
						// MonitoredItems zählen
						if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount && inst->pRunClient->Subscriptions.pSubscriptions != 0)
						{
							BrbUaRcSubscriptionIntern_TYP* pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex;
							pSubscription->nMonitoredItemCount++;
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_EVENT_ITEM) == 1)
					{
						// EventItems zählen
						if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount && inst->pRunClient->Subscriptions.pSubscriptions != 0)
						{
							BrbUaRcSubscriptionIntern_TYP* pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex;
							pSubscription->nEventItemCount++;
						}
					}
					// Nächste Zeile lesen
					inst->fbDatObjRead.Offset += inst->nLineLen+1;
				}
				else if(inst->fbDatObjRead.status == doERR_ILLEGALLENGTH)
				{
					// Am Ende des Datenobjekts angelangt
					inst->fbDatObjRead.Offset = 0;
					inst->nReadBlockIndex = 0;
					inst->nWriteBlockIndex = 0;
					inst->nMethodIndex = 0;
					inst->nSubscriptionIndex = 0;
					inst->eStep = eSTEP_ALLOC_READ_ITEMS;
					break;
				}
				else if(inst->fbDatObjRead.status != 65535)
				{
					// Fehler
					inst->nStatus = inst->fbDatObjRead.status;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Init error on parsing data object for general data");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
					break;
				}
			}
			break;

		case eSTEP_ALLOC_READ_ITEMS:
			// Speicher für ReadItems pro ReadBlock allokieren
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->ReadBlocks.nBlockCount > 0 && inst->pRunClient->ReadBlocks.pBlocks != 0)
			{
				if(inst->nReadBlockIndex < inst->pRunClient->ReadBlocks.nBlockCount)
				{
					BrbUaRcReadBlockIntern_TYP* pReadBlock = (((BrbUaRcReadBlockIntern_TYP*)inst->pRunClient->ReadBlocks.pBlocks)  + inst->nReadBlockIndex);
					if(pReadBlock->nReadItemCount > 0)
					{
						UDINT nMemLenDatObjNsIndices				= pReadBlock->nReadItemCount	* sizeof(UINT);
						UDINT nMemLenNodeIds								= pReadBlock->nReadItemCount	* sizeof(UANodeID);
						UDINT nMemLenNodeAddInfos						= pReadBlock->nReadItemCount	* sizeof(UANodeAdditionalInfo);
						UDINT nMemLenVariables							= pReadBlock->nReadItemCount	* sizeof(inst->sVarName);
						UDINT nMemLenNodeErrorIds						= pReadBlock->nReadItemCount	* sizeof(DWORD);
						UDINT nMemLenTimestamps							= pReadBlock->nReadItemCount	* sizeof(DATE_AND_TIME);
						pReadBlock->nMemLen = nMemLenDatObjNsIndices + nMemLenNodeIds + nMemLenNodeAddInfos + nMemLenVariables + nMemLenNodeErrorIds + nMemLenTimestamps;
						inst->nAllocStatus = TMP_alloc(pReadBlock->nMemLen, (void*)&pReadBlock->pRiStart);
						if(inst->nAllocStatus == 0 && pReadBlock->pRiStart != 0)
						{
							memset((USINT*)pReadBlock->pRiStart, 0, pReadBlock->nMemLen);
							// Pointer auf die einzelnen Arrays ermitteln
							pReadBlock->pRiDatObjNamespaceIndices	= pReadBlock->pRiStart;
							pReadBlock->pRiNodeIds								= pReadBlock->pRiDatObjNamespaceIndices	+ nMemLenDatObjNsIndices;
							pReadBlock->pRiNodeAddInfos						= pReadBlock->pRiNodeIds								+ nMemLenNodeIds;
							pReadBlock->pRiVariables							= pReadBlock->pRiNodeAddInfos						+ nMemLenNodeAddInfos;
							pReadBlock->pRiNodeErrorIds		 				= pReadBlock->pRiVariables							+ nMemLenVariables;
							pReadBlock->pRiTimestamps			 				= pReadBlock->pRiNodeErrorIds						+ nMemLenNodeErrorIds;
							inst->nReadBlockIndex++;
						}
						else
						{
							// Fehler
							inst->nStatus = inst->nAllocStatus;
							inst->pRunClient->State.nClientErroId = inst->nStatus;
							strcpy(inst->pRunClient->State.sClientErrorText, "Init error on allocating memory for Items of ReadBlock#");
							STRING sHelp[16];
							brsitoa(inst->nReadBlockIndex, (UDINT)&sHelp);
							BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
							inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
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
					inst->nReadBlockIndex = -1;
					inst->nReadItemIndex = 0;
					inst->eStep = eSTEP_PARSE_READ_ITEMS;
				}
			}
			else
			{
				// Keine ReadBlocks angegeben
				inst->eStep = eSTEP_ALLOC_WRITE_ITEMS;
			}
			break;

		case eSTEP_PARSE_READ_ITEMS:
			// Parameter der ReadItems parsen
			inst->nStatus  = eBRB_ERR_BUSY;
			for(inst->nLoopIndex=0; inst->nLoopIndex<nBRBUA_CLT_READ_LINES; inst->nLoopIndex++) // In einem Zyklus 100 Zeilen lesen
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
					if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_READBLOCK) == 1)
					{
						inst->nReadBlockIndex++;
						inst->nReadItemIndex = 0;
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_READITEM) == 1)
					{
						// Werte des ReadItems auslesen
						if(inst->nReadBlockIndex < inst->pRunClient->ReadBlocks.nBlockCount && inst->pRunClient->ReadBlocks.pBlocks != 0)
						{
							BrbUaRcReadBlockIntern_TYP* pReadBlock = ((BrbUaRcReadBlockIntern_TYP*)inst->pRunClient->ReadBlocks.pBlocks) + inst->nReadBlockIndex;
							if(inst->nReadItemIndex < pReadBlock->nReadItemCount)
							{
								// Zuerst Default-Werte setzen
								UANodeAdditionalInfo* pNodeAddInfo = ((UANodeAdditionalInfo*)pReadBlock->pRiNodeAddInfos) + inst->nReadItemIndex;
								pNodeAddInfo->AttributeId = UAAI_Value;
								// Dann exisitierende Parameter auslesen
								STRING* pStart = (STRING*)&inst->sLine;
								memset(&inst->sValue, 0, sizeof(inst->sValue));
								if(ParseClientValue(&pStart, "Ns=", inst->sValue) == 1)
								{
									inst->nValue = brsatoi((UDINT)&inst->sValue);
									*(((UINT*)pReadBlock->pRiDatObjNamespaceIndices) + inst->nReadItemIndex) = (UINT)inst->nValue;
								}
								if(ParseClientValue(&pStart, "Id=", inst->sValue) == 1)
								{
									UANodeID* pNodeId = ((UANodeID*)pReadBlock->pRiNodeIds) + inst->nReadItemIndex;
									BrbUaSetNodeId(pNodeId, inst->sValue, 0); // Server-NamespaceIndex muss erst noch ermittelt werden
								}
								if(ParseClientValue(&pStart, "Var=", inst->sValue) == 1)
								{
									STRING* pVar = (STRING*)((USINT*)pReadBlock->pRiVariables) + ((UDINT)inst->nReadItemIndex * sizeof(inst->sVarName));
									BrbStringCopy(pVar, inst->sValue, sizeof(inst->sVarName)); // Speicher hat dieselbe Grösse wie inst->sVarName
								}
								if(ParseClientValue(&pStart, "AttId=", inst->sValue) == 1)
								{
									inst->nValue = brsatoi((UDINT)&inst->sValue);
									pNodeAddInfo->AttributeId = (UAAttributeId)inst->nValue;
								}
							}
							inst->nReadItemIndex++;
						}
					}
					// Nächste Zeile lesen
					inst->fbDatObjRead.Offset += inst->nLineLen+1;
				}
				else if(inst->fbDatObjRead.status == doERR_ILLEGALLENGTH)
				{
					// Am Ende des Datenobjekts angelangt
					inst->fbDatObjRead.Offset = 0;
					inst->nReadBlockIndex = 0;
					inst->nReadItemIndex = 0;
					inst->eStep = eSTEP_ALLOC_WRITE_ITEMS;
					break;
				}
				else if(inst->fbDatObjRead.status != 65535)
				{
					// Fehler
					inst->nStatus = inst->fbDatObjRead.status;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Init error on parsing ReadItems");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
					break;
				}
			}
			break;

		case eSTEP_ALLOC_WRITE_ITEMS:
			// Speicher für WriteItems pro WriteBlock allokieren
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->WriteBlocks.nBlockCount > 0 && inst->pRunClient->WriteBlocks.pBlocks != 0)
			{
				if(inst->nWriteBlockIndex < inst->pRunClient->WriteBlocks.nBlockCount)
				{
					BrbUaRcWriteBlockIntern_TYP* pWriteBlock = (((BrbUaRcWriteBlockIntern_TYP*)inst->pRunClient->WriteBlocks.pBlocks)  + inst->nWriteBlockIndex);
					if(pWriteBlock->nWriteItemCount > 0)
					{
						UDINT nMemLenDatObjNsIndices				= pWriteBlock->nWriteItemCount	* sizeof(UINT);
						UDINT nMemLenNodeIds								= pWriteBlock->nWriteItemCount	* sizeof(UANodeID);
						UDINT nMemLenNodeAddInfos						= pWriteBlock->nWriteItemCount	* sizeof(UANodeAdditionalInfo);
						UDINT nMemLenVariables							= pWriteBlock->nWriteItemCount	* sizeof(inst->sVarName);
						UDINT nMemLenNodeErrorIds						= pWriteBlock->nWriteItemCount	* sizeof(DWORD);
						pWriteBlock->nMemLen = nMemLenDatObjNsIndices + nMemLenNodeIds + nMemLenNodeAddInfos + nMemLenVariables + nMemLenNodeErrorIds;
						inst->nAllocStatus = TMP_alloc(pWriteBlock->nMemLen, (void*)&pWriteBlock->pWiStart);
						if(inst->nAllocStatus == 0 && pWriteBlock->pWiStart != 0)
						{
							memset((USINT*)pWriteBlock->pWiStart, 0, pWriteBlock->nMemLen);
							// Pointer auf die einzelnen Arrays ermitteln
							pWriteBlock->pWiDatObjNamespaceIndices	= pWriteBlock->pWiStart;
							pWriteBlock->pWiNodeIds									= pWriteBlock->pWiDatObjNamespaceIndices	+ nMemLenDatObjNsIndices;
							pWriteBlock->pWiNodeAddInfos						= pWriteBlock->pWiNodeIds									+ nMemLenNodeIds;
							pWriteBlock->pWiVariables								= pWriteBlock->pWiNodeAddInfos						+ nMemLenNodeAddInfos;
							pWriteBlock->pWiNodeErrorIds		 				= pWriteBlock->pWiVariables								+ nMemLenVariables;
							inst->nWriteBlockIndex++;
						}
						else
						{
							// Fehler
							inst->nStatus = inst->nAllocStatus;
							inst->pRunClient->State.nClientErroId = inst->nStatus;
							strcpy(inst->pRunClient->State.sClientErrorText, "Init error on allocating memory for Items of WriteBlock#");
							STRING sHelp[16];
							brsitoa(inst->nWriteBlockIndex, (UDINT)&sHelp);
							BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
							inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
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
					inst->nWriteBlockIndex = -1;
					inst->nWriteItemIndex = 0;
					inst->eStep = eSTEP_PARSE_WRITE_ITEMS;
				}
			}
			else
			{
				// Keine WriteBlocks angegeben
				inst->eStep = eSTEP_ALLOC_METHOD_ARGUMENTS;
			}
			break;

		case eSTEP_PARSE_WRITE_ITEMS:
			// Parameter der WriteItems parsen
			inst->nStatus  = eBRB_ERR_BUSY;
			for(inst->nLoopIndex=0; inst->nLoopIndex<nBRBUA_CLT_READ_LINES; inst->nLoopIndex++) // In einem Zyklus 100 Zeilen lesen
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
					if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_WRITEBLOCK) == 1)
					{
						inst->nWriteBlockIndex++;
						inst->nWriteItemIndex = 0;
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_WRITEITEM) == 1)
					{
						// Werte des WriteItems auslesen
						if(inst->nWriteBlockIndex < inst->pRunClient->WriteBlocks.nBlockCount && inst->pRunClient->WriteBlocks.pBlocks != 0)
						{
							BrbUaRcWriteBlockIntern_TYP* pWriteBlock = ((BrbUaRcWriteBlockIntern_TYP*)inst->pRunClient->WriteBlocks.pBlocks) + inst->nWriteBlockIndex;
							if(inst->nWriteItemIndex < pWriteBlock->nWriteItemCount)
							{
								// Zuerst Default-Werte setzen
								UANodeAdditionalInfo* pNodeAddInfo = ((UANodeAdditionalInfo*)pWriteBlock->pWiNodeAddInfos) + inst->nWriteItemIndex;
								pNodeAddInfo->AttributeId = UAAI_Value;
								// Dann exisitierende Parameter auslesen
								STRING* pStart = (STRING*)&inst->sLine;
								memset(&inst->sValue, 0, sizeof(inst->sValue));
								if(ParseClientValue(&pStart, "Ns=", inst->sValue) == 1)
								{
									inst->nValue = brsatoi((UDINT)&inst->sValue);
									*(((UINT*)pWriteBlock->pWiDatObjNamespaceIndices) + inst->nWriteItemIndex) = (UINT)inst->nValue;
								}
								if(ParseClientValue(&pStart, "Id=", inst->sValue) == 1)
								{
									UANodeID* pNodeId = ((UANodeID*)pWriteBlock->pWiNodeIds) + inst->nWriteItemIndex;
									BrbUaSetNodeId(pNodeId, inst->sValue, 0); // Server-NamespaceIndex muss erst noch ermittelt werden
								}
								if(ParseClientValue(&pStart, "Var=", inst->sValue) == 1)
								{
									STRING* pVar = (STRING*)((USINT*)pWriteBlock->pWiVariables) + ((UDINT)inst->nWriteItemIndex * sizeof(inst->sVarName));
									BrbStringCopy(pVar, inst->sValue, sizeof(inst->sVarName)); // Speicher hat dieselbe Grösse wie inst->sVarName
								}
								if(ParseClientValue(&pStart, "AttId=", inst->sValue) == 1)
								{
									inst->nValue = brsatoi((UDINT)&inst->sValue);
									pNodeAddInfo->AttributeId = (UAAttributeId)inst->nValue;
								}
							}
							inst->nWriteItemIndex++;
						}
					}
					// Nächste Zeile lesen
					inst->fbDatObjRead.Offset += inst->nLineLen+1;
				}
				else if(inst->fbDatObjRead.status == doERR_ILLEGALLENGTH)
				{
					// Am Ende des Datenobjekts angelangt
					inst->fbDatObjRead.Offset = 0;
					inst->nWriteBlockIndex = 0;
					inst->nWriteItemIndex = 0;
					inst->eStep = eSTEP_ALLOC_METHOD_ARGUMENTS;
					break;
				}
				else if(inst->fbDatObjRead.status != 65535)
				{
					// Fehler
					inst->nStatus = inst->fbDatObjRead.status;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Init error on parsing WriteItems");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
					break;
				}
			}
			break;

		case eSTEP_ALLOC_METHOD_ARGUMENTS:
			// Speicher für Arguments pro Method allokieren
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->Methods.nMethodCount > 0 && inst->pRunClient->Methods.pMethods != 0)
			{
				if(inst->nMethodIndex < inst->pRunClient->Methods.nMethodCount)
				{
					BrbUaRcMethodIntern_TYP* pMethod = (((BrbUaRcMethodIntern_TYP*)inst->pRunClient->Methods.pMethods)  + inst->nMethodIndex);
					if(pMethod->nInputArgsCount > 0 || pMethod->nOutputArgsCount > 0)
					{
						UDINT nMemLenInputArguments		= pMethod->nInputArgsCount	* sizeof(UAMethodArgument);
						UDINT nMemLenOutputArguments	= pMethod->nOutputArgsCount	* sizeof(UAMethodArgument);
						pMethod->nMemLen = nMemLenInputArguments + nMemLenOutputArguments;
						inst->nAllocStatus = TMP_alloc(pMethod->nMemLen, (void*)&pMethod->pStart);
						if(inst->nAllocStatus == 0 && pMethod->pStart != 0)
						{
							memset((USINT*)pMethod->pStart, 0, pMethod->nMemLen);
							// Pointer auf die einzelnen Argumente ermitteln
							pMethod->pInputArguments	= pMethod->pStart;
							pMethod->pOutputArguments	= pMethod->pInputArguments	+ nMemLenInputArguments;
							inst->nMethodIndex++;
						}
						else
						{
							// Fehler
							inst->nStatus = inst->nAllocStatus;
							inst->pRunClient->State.nClientErroId = inst->nStatus;
							strcpy(inst->pRunClient->State.sClientErrorText, "Init error on allocating memory for Arguments of Method#");
							STRING sHelp[16];
							brsitoa(inst->nMethodIndex, (UDINT)&sHelp);
							BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
							inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
							inst->eStep = eSTEP_INIT;
							break;
						}
					}
					else
					{
						inst->nMethodIndex++;
					}
				}
				else
				{
					inst->nMethodIndex = -1;
					inst->nArgumentInputIndex = 0;
					inst->nArgumentOutputIndex = 0;
					inst->eStep = eSTEP_PARSE_METHOD_ARGUMENTS;
				}
			}
			else
			{
				// Keine ReadBlocks angegeben
				inst->eStep = eSTEP_ALLOC_MONITORED_ITEMS;
			}
			break;

		case eSTEP_PARSE_METHOD_ARGUMENTS:
			// Argumente der Methods parsen
			inst->nStatus  = eBRB_ERR_BUSY;
			for(inst->nLoopIndex=0; inst->nLoopIndex<nBRBUA_CLT_READ_LINES; inst->nLoopIndex++) // In einem Zyklus 100 Zeilen lesen
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
					if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_METHOD) == 1)
					{
						inst->nMethodIndex++;
						inst->nArgumentInputIndex = 0;
						inst->nArgumentOutputIndex = 0;
					}
					if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_METHOD_ARG_IN) == 1)
					{
						if(inst->nMethodIndex < inst->pRunClient->Methods.nMethodCount && inst->pRunClient->Methods.pMethods != 0)
						{
							BrbUaRcMethodIntern_TYP* pMethod = (((BrbUaRcMethodIntern_TYP*)inst->pRunClient->Methods.pMethods)  + inst->nMethodIndex);
							if(pMethod->nInputArgsCount > 0 && pMethod->pInputArguments != 0)
							{
								if(inst->nArgumentInputIndex < pMethod->nInputArgsCount)
								{
									UAMethodArgument* pArgument = ((UAMethodArgument*)pMethod->pInputArguments) + inst->nArgumentInputIndex;
									STRING* pStart = (STRING*)&inst->sLine;
									memset(&inst->sValue, 0, sizeof(inst->sValue));
									if(ParseClientValue(&pStart, "Name=", inst->sValue) == 1)
									{
										inst->nValue = brsatoi((UDINT)&inst->sValue);
										BrbStringCopy(pArgument->Name, inst->sValue, sizeof(pArgument->Name));
									}
									if(ParseClientValue(&pStart, "Var=", inst->sValue) == 1)
									{
										inst->nValue = brsatoi((UDINT)&inst->sValue);
										BrbStringCopy(pArgument->Value, inst->sValue, sizeof(pArgument->Name));
									}
									inst->nArgumentInputIndex++;
								}
							}
						}
					}
					if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_METHOD_ARG_OUT) == 1)
					{
						if(inst->nMethodIndex < inst->pRunClient->Methods.nMethodCount && inst->pRunClient->Methods.pMethods != 0)
						{
							BrbUaRcMethodIntern_TYP* pMethod = (((BrbUaRcMethodIntern_TYP*)inst->pRunClient->Methods.pMethods)  + inst->nMethodIndex);
							if(pMethod->nOutputArgsCount > 0 && pMethod->pOutputArguments != 0)
							{
								if(inst->nArgumentOutputIndex < pMethod->nOutputArgsCount)
								{
									UAMethodArgument* pArgument = ((UAMethodArgument*)pMethod->pOutputArguments) + inst->nArgumentOutputIndex;
									STRING* pStart = (STRING*)&inst->sLine;
									memset(&inst->sValue, 0, sizeof(inst->sValue));
									if(ParseClientValue(&pStart, "Name=", inst->sValue) == 1)
									{
										inst->nValue = brsatoi((UDINT)&inst->sValue);
										BrbStringCopy(pArgument->Name, inst->sValue, sizeof(pArgument->Name));
									}
									if(ParseClientValue(&pStart, "Var=", inst->sValue) == 1)
									{
										inst->nValue = brsatoi((UDINT)&inst->sValue);
										BrbStringCopy(pArgument->Value, inst->sValue, sizeof(pArgument->Value));
									}
									inst->nArgumentOutputIndex++;
								}
							}
						}
					}
					// Nächste Zeile lesen
					inst->fbDatObjRead.Offset += inst->nLineLen+1;
				}
				else if(inst->fbDatObjRead.status == doERR_ILLEGALLENGTH)
				{
					// Am Ende des Datenobjekts angelangt
					inst->fbDatObjRead.Offset = 0;
					inst->nReadBlockIndex = 0;
					inst->nReadItemIndex = 0;
					inst->eStep = eSTEP_ALLOC_MONITORED_ITEMS;
					break;
				}
				else if(inst->fbDatObjRead.status != 65535)
				{
					// Fehler
					inst->nStatus = inst->fbDatObjRead.status;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Init error on parsing Arguments from Method#");
					STRING sHelp[16];
					brsitoa(inst->nMethodIndex, (UDINT)&sHelp);
					BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
					break;
				}
			}
			break;

		case eSTEP_ALLOC_MONITORED_ITEMS:
			// Speicher für MonitoredItems pro Subscription allokieren
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->Subscriptions.nSubscriptionCount > 0 && inst->pRunClient->Subscriptions.pSubscriptions != 0)
			{
				if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount)
				{
					BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions)  + inst->nSubscriptionIndex);
					if(pSubscription->nMonitoredItemCount > 0)
					{
						/*
							Beim späteren Aufruf von UA_MonitoredItemAddList werden teilweise Pointer auf Arrays übergeben.
							Dieses Arrays müssen genau 64 Elemente groß sein, weil es sonst seltsamerweise zu Speicherverletzungen kommt. Anscheinend wird in dem FB von genau 64 Elementen
							großen Arrays ausgegangen.
							Diese Arrays befinden sich im allokierten Speicherbereich der MonitoredItems, dessen Größe hier berechnet wird.
							Es reicht also nicht, genauso viele Elemente anzugeben, wie man MonitoredItems hat. Vielmehr müssen die Elemente immer ein Vielfaches von 64 sein.
							Deshalb wird hier die benötigte Elementgröße berechnet. Sie wird aber nur für jene Arrays verwendet, welche später als Pointer übergeben werden.
						*/
						UINT nMonitorItemCountBlock64 = (((pSubscription->nMonitoredItemCount-1) / 64) + 1) * 64;
						UDINT nMemLenDatObjNsIndices				= pSubscription->nMonitoredItemCount	* sizeof(UINT);
						UDINT nMemLenNodeIds								= pSubscription->nMonitoredItemCount	* sizeof(UANodeID);
						UDINT nMemLenNodeHandleErrorIds			= pSubscription->nMonitoredItemCount	* sizeof(DWORD);
						UDINT nMemLenNodeHandles						= pSubscription->nMonitoredItemCount	* sizeof(DWORD);
						UDINT nMemLenNodeAddInfos						= pSubscription->nMonitoredItemCount	* sizeof(UANodeAdditionalInfo);
						UDINT nMemLenVariables							= nMonitorItemCountBlock64						* sizeof(inst->sVarName);
						UDINT nMemLenQueueSizeOri						= pSubscription->nMonitoredItemCount	* sizeof(UINT);
						UDINT nMemLenMonitorSettings				= nMonitorItemCountBlock64						* sizeof(UAMonitoringParameters);
						UDINT nMemLenValuesChanged					= nMonitorItemCountBlock64						* sizeof(BOOL);
						UDINT nMemLenRemainingValueCounts		= nMonitorItemCountBlock64						* sizeof(UINT);
						UDINT nMemLenTimestamps							= nMonitorItemCountBlock64						* sizeof(DT);
						UDINT nMemLenNodeQualityIds					= nMonitorItemCountBlock64						* sizeof(DWORD);
						UDINT nMemLenMonitoredItemErrorIds	= pSubscription->nMonitoredItemCount	* sizeof(DWORD);
						UDINT nMemLenMonitoredItemHandles		= pSubscription->nMonitoredItemCount	* sizeof(DWORD);
						pSubscription->nMiMemLen = 
							nMemLenDatObjNsIndices + nMemLenNodeIds + nMemLenNodeHandleErrorIds + nMemLenNodeHandles + nMemLenNodeAddInfos + nMemLenVariables + nMemLenQueueSizeOri + 
							nMemLenMonitorSettings + nMemLenValuesChanged + nMemLenRemainingValueCounts + nMemLenTimestamps + nMemLenNodeQualityIds + nMemLenMonitoredItemErrorIds + 
							nMemLenMonitoredItemHandles;
						inst->nAllocStatus = TMP_alloc(pSubscription->nMiMemLen, (void*)&pSubscription->pMiStart);
						if(inst->nAllocStatus == 0 && pSubscription->pMiStart != 0)
						{
							memset((USINT*)pSubscription->pMiStart, 0, pSubscription->nMiMemLen);
							// Pointer auf die einzelnen Arrays ermitteln
							pSubscription->pMiDatObjNamespaceIndices	= pSubscription->pMiStart;
							pSubscription->pMiNodeIds									= pSubscription->pMiDatObjNamespaceIndices	+ nMemLenDatObjNsIndices;
							pSubscription->pMiNodeHandleErrorIds			= pSubscription->pMiNodeIds									+ nMemLenNodeIds;
							pSubscription->pMiNodeHandles							= pSubscription->pMiNodeHandleErrorIds			+ nMemLenNodeHandleErrorIds;
							pSubscription->pMiNodeAddInfos						= pSubscription->pMiNodeHandles							+ nMemLenNodeHandles;
							pSubscription->pMiVariables								= pSubscription->pMiNodeAddInfos						+ nMemLenNodeAddInfos;
							pSubscription->pMiQueueSizeOri		 				= pSubscription->pMiVariables								+ nMemLenVariables;
							pSubscription->pMiMonitorSettings 				= pSubscription->pMiQueueSizeOri						+ nMemLenQueueSizeOri;
							pSubscription->pMiValuesChanged		 				= pSubscription->pMiMonitorSettings					+ nMemLenMonitorSettings;
							pSubscription->pMiRemainingValueCounts		= pSubscription->pMiValuesChanged						+ nMemLenValuesChanged;
							pSubscription->pMiTimestamps							= pSubscription->pMiRemainingValueCounts		+ nMemLenRemainingValueCounts;
							pSubscription->pMiNodeQualityIds					= pSubscription->pMiTimestamps							+ nMemLenTimestamps;
							pSubscription->pMiMonitoredItemErrorIds		= pSubscription->pMiNodeQualityIds					+ nMemLenNodeQualityIds;
							pSubscription->pMiMonitoredItemHandles		= pSubscription->pMiMonitoredItemErrorIds		+ nMemLenMonitoredItemErrorIds;
							inst->nSubscriptionIndex++;
						}
						else
						{
							// Fehler
							inst->nStatus = inst->nAllocStatus;
							inst->pRunClient->State.nClientErroId = inst->nStatus;
							strcpy(inst->pRunClient->State.sClientErrorText, "Init error on allocating memory for MonitoredItems of Subscription#");
							STRING sHelp[16];
							brsitoa(inst->nSubscriptionIndex, (UDINT)&sHelp);
							BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
							inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
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
					inst->nMonItemIndex = 0;
					inst->nEventItemIndex = 0;
					inst->eStep = eSTEP_ALLOC_EVENT_ITEMS;
				}
			}
			else
			{
				// Keine Subscriptions angegeben
				inst->eStep = eSTEP_FINISHED;
			}
			break;

		case eSTEP_ALLOC_EVENT_ITEMS:
			// Speicher für EventItems pro Subscription allokieren
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunClient->Subscriptions.nSubscriptionCount > 0 && inst->pRunClient->Subscriptions.pSubscriptions != 0)
			{
				if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount)
				{
					BrbUaRcSubscriptionIntern_TYP* pSubscription = (((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions)  + inst->nSubscriptionIndex);
					if(pSubscription->nEventItemCount > 0)
					{
						pSubscription->nEiMemLen = pSubscription->nEventItemCount * sizeof(BrbUaRcEventItemIntern_TYP);
						inst->nAllocStatus = TMP_alloc(pSubscription->nEiMemLen, (void*)&pSubscription->pEventItems);
						if(inst->nAllocStatus == 0 && pSubscription->pEventItems != 0)
						{
							memset((USINT*)pSubscription->pEventItems, 0, pSubscription->nEiMemLen);
							inst->nSubscriptionIndex++;
						}
						else
						{
							// Fehler
							inst->nStatus = inst->nAllocStatus;
							inst->pRunClient->State.nClientErroId = inst->nStatus;
							strcpy(inst->pRunClient->State.sClientErrorText, "Init error on allocating memory for EventItems of Subscription#");
							STRING sHelp[16];
							brsitoa(inst->nSubscriptionIndex, (UDINT)&sHelp);
							BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
							inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
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
					inst->nSubscriptionIndex = -1;
					inst->nMonItemIndex = 0;
					inst->nEventItemIndex = 0;
					inst->eStep = eSTEP_PARSE_SUBSCRIPTION_ITEMS;
				}
			}
			else
			{
				// Keine Subscriptions angegeben
				inst->eStep = eSTEP_FINISHED;
			}
			break;

		case eSTEP_PARSE_SUBSCRIPTION_ITEMS:
			// Parameter der MonitoredItems und EventItems parsen
			inst->nStatus  = eBRB_ERR_BUSY;
			for(inst->nLoopIndex=0; inst->nLoopIndex<nBRBUA_CLT_READ_LINES; inst->nLoopIndex++) // In einem Zyklus 100 Zeilen lesen
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
					if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_SUBSCRIPTION) == 1)
					{
						inst->nSubscriptionIndex++;
						inst->nMonItemIndex = 0;
						inst->nEventItemIndex = 0;
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_MONITORED_ITEM) == 1)
					{
						// Werte des MonitoredItems auslesen
						if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount && inst->pRunClient->Subscriptions.pSubscriptions != 0)
						{
							BrbUaRcSubscriptionIntern_TYP* pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex;
							if(inst->nMonItemIndex < pSubscription->nMonitoredItemCount)
							{
								// Zuerst Default-Werte setzen
								UANodeAdditionalInfo* pNodeAddInfo = ((UANodeAdditionalInfo*)pSubscription->pMiNodeAddInfos) + inst->nMonItemIndex;
								pNodeAddInfo->AttributeId = UAAI_Value;
								UAMonitoringParameters* pMonitoringSetting = ((UAMonitoringParameters*)pSubscription->pMiMonitorSettings) + inst->nMonItemIndex;
								pMonitoringSetting->SamplingInterval = pSubscription->tPublishingInterval;
								pMonitoringSetting->QueueSize = 0;
								pMonitoringSetting->DiscardOldest = 1;
								pMonitoringSetting->DeadbandType = UADeadbandType_None;
								pMonitoringSetting->Deadband = 0.0f;
								// Dann exisitierende Parameter auslesen
								STRING* pStart = (STRING*)&inst->sLine;
								memset(&inst->sValue, 0, sizeof(inst->sValue));
								if(ParseClientValue(&pStart, "Ns=", inst->sValue) == 1)
								{
									inst->nValue = brsatoi((UDINT)&inst->sValue);
									*(((UINT*)pSubscription->pMiDatObjNamespaceIndices) + inst->nMonItemIndex) = (UINT)inst->nValue;
								}
								if(ParseClientValue(&pStart, "Id=", inst->sValue) == 1)
								{
									UANodeID* pNodeId = ((UANodeID*)pSubscription->pMiNodeIds) + inst->nMonItemIndex;
									BrbUaSetNodeId(pNodeId, inst->sValue, 0); // Server-NamespaceIndex muss erst noch ermittelt werden
								}
								if(ParseClientValue(&pStart, "Var=", inst->sValue) == 1)
								{
									STRING* pVar = (STRING*)((USINT*)pSubscription->pMiVariables) + ((UDINT)inst->nMonItemIndex * sizeof(inst->sVarName));
									BrbStringCopy(pVar, inst->sValue, sizeof(inst->sVarName)); // Speicher hat dieselbe Grösse wie inst->sVarName
								}
								if(ParseClientValue(&pStart, "AttId=", inst->sValue) == 1)
								{
									inst->nValue = brsatoi((UDINT)&inst->sValue);
									pNodeAddInfo->AttributeId = (UAAttributeId)inst->nValue;
								}
								if(ParseClientValue(&pStart, "Sampling=", inst->sValue) == 1)
								{
									inst->nValue = brsatoi((UDINT)&inst->sValue);
									pMonitoringSetting->SamplingInterval = (TIME)inst->nValue;
								}
								if(ParseClientValue(&pStart, "Queue=", inst->sValue) == 1)
								{
									inst->nValue = brsatoi((UDINT)&inst->sValue);
									*(((UINT*)pSubscription->pMiQueueSizeOri) + inst->nMonItemIndex) = (UINT)inst->nValue;
									pMonitoringSetting->QueueSize = (UINT)inst->nValue;
								}
								if(ParseClientValue(&pStart, "Discard=", inst->sValue) == 1)
								{
									inst->nValue = brsatoi((UDINT)&inst->sValue);
									pMonitoringSetting->DiscardOldest = (inst->nValue > 0);
								}
								if(ParseClientValue(&pStart, "DeadType=", inst->sValue) == 1)
								{
									inst->nValue = brsatoi((UDINT)&inst->sValue);
									if(inst->nValue < 0  || inst->nValue > UADeadbandType_Percent)
									{
										inst->nValue = 0;
									}
									pMonitoringSetting->DeadbandType = (UADeadbandType)inst->nValue;
								}
								if(ParseClientValue(&pStart, "Deadband=", inst->sValue) == 1)
								{
									inst->rValue = brsatof((UDINT)&inst->sValue);
									pMonitoringSetting->Deadband = inst->rValue;
								}
							}
							inst->nMonItemIndex++;
						}
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_EVENT_ITEM) == 1)
					{
						// Werte des EventItems auslesen
						if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount && inst->pRunClient->Subscriptions.pSubscriptions != 0)
						{
							BrbUaRcSubscriptionIntern_TYP* pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex;
							if(inst->nEventItemIndex < pSubscription->nEventItemCount)
							{
								BrbUaRcEventItemIntern_TYP* pEventItem = ((BrbUaRcEventItemIntern_TYP*)pSubscription->pEventItems) + inst->nEventItemIndex;
								// Zuerst Default-Werte setzen
								BrbUaSetNodeId(&pEventItem->EventNodeId, "2253", 0);
								BrbUaSetNodeId(&pEventItem->TypeNodeId, "2041", 0);
								pEventItem->nEventFieldCount = 0;
								pEventItem->tTimeout = 5000;
								pEventItem->bCallOperate = 1;
								// Dann exisitierende Parameter auslesen
								STRING* pStart = (STRING*)&inst->sLine;
								memset(&inst->sValue, 0, sizeof(inst->sValue));
								if(ParseClientValue(&pStart, "EvtNs=", inst->sValue) == 1)
								{
									inst->nValue = brsatoi((UDINT)&inst->sValue);
									pEventItem->nEventDatObjNamespaceIndex = (UINT)inst->nValue;
								}
								if(ParseClientValue(&pStart, "EvtId=", inst->sValue) == 1)
								{
									BrbUaSetNodeId(&pEventItem->EventNodeId, inst->sValue, 0); // Server-NamespaceIndex muss erst noch ermittelt werden
								}
								if(ParseClientValue(&pStart, "TypeNs=", inst->sValue) == 1)
								{
									inst->nValue = brsatoi((UDINT)&inst->sValue);
									pEventItem->nTypeDatObjNamespaceIndex = (UINT)inst->nValue;
								}
								if(ParseClientValue(&pStart, "TypeId=", inst->sValue) == 1)
								{
									BrbUaSetNodeId(&pEventItem->TypeNodeId, inst->sValue, 0); // Server-NamespaceIndex muss erst noch ermittelt werden
								}
								if(ParseClientValue(&pStart, "Timeout=", inst->sValue) == 1)
								{
									inst->nValue = brsatoi((UDINT)&inst->sValue);
									pEventItem->tTimeout = (TIME)inst->nValue;
								}
								if(ParseClientValue(&pStart, "CallOperate=", inst->sValue) == 1)
								{
									inst->nValue = brsatoi((UDINT)&inst->sValue);
									pEventItem->bCallOperate = (inst->nValue > 0);
								}
							}
							inst->nEventItemIndex++;
						}
					}
					// Nächste Zeile lesen
					inst->fbDatObjRead.Offset += inst->nLineLen+1;
				}
				else if(inst->fbDatObjRead.status == doERR_ILLEGALLENGTH)
				{
					// Am Ende des Datenobjekts angelangt
					inst->fbDatObjRead.Offset = 0;
					inst->nSubscriptionIndex = -1;
					inst->nEventItemIndex = -1;
					inst->eStep = eSTEP_COUNT_EVENT_FIELDS;
					break;
				}
				else if(inst->fbDatObjRead.status != 65535)
				{
					// Fehler
					inst->nStatus = inst->fbDatObjRead.status;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Init error on parsing Monitored/EventItems");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
					break;
				}
			}
			break;

		case eSTEP_COUNT_EVENT_FIELDS:
			// Fields der EventItems zählen
			inst->nStatus  = eBRB_ERR_BUSY;
			for(inst->nLoopIndex=0; inst->nLoopIndex<nBRBUA_CLT_READ_LINES; inst->nLoopIndex++) // In einem Zyklus 100 Zeilen lesen
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
					if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_SUBSCRIPTION) == 1)
					{
						inst->nSubscriptionIndex++;
						inst->nEventItemIndex = -1;
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_EVENT_ITEM) == 1)
					{
						inst->nEventItemIndex++;
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_EVENT_FIELD) == 1)
					{
						// Fields des EventItems zählen
						if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount && inst->pRunClient->Subscriptions.pSubscriptions != 0)
						{
							BrbUaRcSubscriptionIntern_TYP* pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex;
							if(inst->nEventItemIndex > -1 && inst->nEventItemIndex < pSubscription->nEventItemCount)
							{
								BrbUaRcEventItemIntern_TYP* pEventItem = ((BrbUaRcEventItemIntern_TYP*)pSubscription->pEventItems) + inst->nEventItemIndex;
								pEventItem->nEventFieldCount++;
								if(pEventItem->nEventFieldCount > MAX_ELEMENTS_EVENTFIELDSELECTION)
								{
									pEventItem->nEventFieldCount = MAX_ELEMENTS_EVENTFIELDSELECTION;
								}
							}
						}
					}
					// Nächste Zeile lesen
					inst->fbDatObjRead.Offset += inst->nLineLen+1;
				}
				else if(inst->fbDatObjRead.status == doERR_ILLEGALLENGTH)
				{
					// Am Ende des Datenobjekts angelangt
					inst->fbDatObjRead.Offset = 0;
					inst->nSubscriptionIndex = 0;
					inst->nEventItemIndex = 0;
					inst->eStep = eSTEP_ALLOC_EVENT_FIELDS;
					break;
				}
				else if(inst->fbDatObjRead.status != 65535)
				{
					// Fehler
					inst->nStatus = inst->fbDatObjRead.status;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Init error on counting EventItems");
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
					break;
				}
			}
			break;

		case eSTEP_ALLOC_EVENT_FIELDS:
			// Speicher für Fields pro EventItem pro Subscription allokieren
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
							if(pEventItem->nEventFieldCount > 0)
							{
								/*
									Beim späteren Aufruf von UA_EventItemAdd wird ein Pointer auf ein Array übergeben.
									Dieses Array muss genau 64 Elemente groß sein, weil es sonst seltsamerweise zu Speicherverletzungen kommt. Anscheinend wird in dem FB von einem genau 64 Elementen
									großen Arrays ausgegangen.
									Dieses Array befinden sich im allokierten Speicherbereich der EventFields, dessen Größe hier berechnet wird.
									Es reicht also nicht, genauso viele Elemente anzugeben, wie man EventFields hat. Vielmehr müssen die Elemente immer ein Vielfaches von 64 sein.
									Deshalb wird hier die benötigte Elementgröße berechnet. Sie wird aber nur für jene Arrays verwendet, welche später als Pointer übergeben werden.
								*/
								UINT nEventFieldCountBlock64 = (((pEventItem->nEventFieldCount-1) / 64) + 1) * 64;
								UDINT nMemLenDatObjNsIndices				= pEventItem->nEventFieldCount	* sizeof(UINT);
								UDINT nMemLenFieldSelections				= pEventItem->nEventFieldCount	* sizeof(UARelativePath);
								UDINT nMemLenFieldVars							= nEventFieldCountBlock64				* sizeof(inst->sVarName);
								pEventItem->nEfMemLen = nMemLenDatObjNsIndices + nMemLenFieldSelections + nMemLenFieldVars;
								inst->nAllocStatus = TMP_alloc(pEventItem->nEfMemLen, (void*)&pEventItem->pEfStart);
								if(inst->nAllocStatus == 0 && pEventItem->pEfStart != 0)
								{
									memset((USINT*)pEventItem->pEfStart, 0, pEventItem->nEfMemLen);
									// Pointer auf die einzelnen Arrays ermitteln
									pEventItem->pEfDatObjNamespaceIndices	= pEventItem->pEfStart;
									pEventItem->pEfFieldSelections				= pEventItem->pEfDatObjNamespaceIndices	+ nMemLenDatObjNsIndices;
									pEventItem->pEfFieldVars							= pEventItem->pEfFieldSelections				+ nMemLenFieldSelections;
									inst->nEventItemIndex++;
								}
								else
								{
									// Fehler
									inst->nStatus = inst->nAllocStatus;
									inst->pRunClient->State.nClientErroId = inst->nStatus;
									strcpy(inst->pRunClient->State.sClientErrorText, "Init error on allocating memory for EventFields of Subscription#");
									STRING sHelp[16];
									brsitoa(inst->nSubscriptionIndex, (UDINT)&sHelp);
									BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
									BrbStringCat(inst->pRunClient->State.sClientErrorText, " of EventItem#", sizeof(inst->pRunClient->State.sClientErrorText));
									brsitoa(inst->nEventItemIndex, (UDINT)&sHelp);
									BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
									inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
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
					inst->nSubscriptionIndex = -1;
					inst->nEventItemIndex = -1;
					inst->nEventFieldIndex = 0;
					inst->eStep = eSTEP_PARSE_EVENT_FIELDS;
				}
			}
			else
			{
				// Keine Subscriptions angegeben
				inst->eStep = eSTEP_FINISHED;
			}
			break;

		case eSTEP_PARSE_EVENT_FIELDS:
			// Parameter der EventFields parsen
			inst->nStatus  = eBRB_ERR_BUSY;
			for(inst->nLoopIndex=0; inst->nLoopIndex<nBRBUA_CLT_READ_LINES; inst->nLoopIndex++) // In einem Zyklus 100 Zeilen lesen
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
					if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_SUBSCRIPTION) == 1)
					{
						inst->nSubscriptionIndex++;
						inst->nEventItemIndex = -1;
						inst->nEventFieldIndex = 0;
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_EVENT_ITEM) == 1)
					{
						inst->nEventItemIndex++;
						inst->nEventFieldIndex = 0;
					}
					else if(BrbStringStartsWith(inst->sLine, nBRBUA_KEYWORD_EVENT_FIELD) == 1)
					{
						// Werte des EventFields auslesen
						if(inst->nSubscriptionIndex < inst->pRunClient->Subscriptions.nSubscriptionCount && inst->pRunClient->Subscriptions.pSubscriptions != 0)
						{
							BrbUaRcSubscriptionIntern_TYP* pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)inst->pRunClient->Subscriptions.pSubscriptions) + inst->nSubscriptionIndex;
							if(inst->nEventItemIndex < pSubscription->nEventItemCount && pSubscription->pEventItems != 0)
							{
								BrbUaRcEventItemIntern_TYP* pEventItem = ((BrbUaRcEventItemIntern_TYP*)pSubscription->pEventItems) + inst->nEventItemIndex;
								if(inst->nEventFieldIndex < pEventItem->nEventFieldCount && pEventItem->pEfFieldSelections != 0 && pEventItem->pEfFieldVars != 0)
								{
									UARelativePath* pSelection = ((UARelativePath*)pEventItem->pEfFieldSelections) + inst->nEventFieldIndex;
									// Exisitierende Parameter auslesen
									STRING* pStart = (STRING*)&inst->sLine;
									memset(&inst->sValue, 0, sizeof(inst->sValue));
									if(ParseClientValue(&pStart, "FieldNs=", inst->sValue) == 1)
									{
										inst->nValue = brsatoi((UDINT)&inst->sValue);
										*(((UINT*)pEventItem->pEfDatObjNamespaceIndices) + inst->nEventFieldIndex) = (UINT)inst->nValue;
									}
									UINT nPathElementCount = (UINT)BrbStringCountText(inst->sLine, "FieldPath=", inst->nLineLen);
									if(nPathElementCount > MAX_ELEMENTS_RELATIVEPATH)
									{
										nPathElementCount = MAX_ELEMENTS_RELATIVEPATH;
									}
									pSelection->NoOfElements = nPathElementCount;
									UINT nPathElementIndex = 0;
									for(nPathElementIndex=0; nPathElementIndex<nPathElementCount; nPathElementIndex++)
									{
										if(ParseClientValue(&pStart, "FieldPath=", inst->sValue) == 1)
										{
											BrbStringCopy(pSelection->Elements[nPathElementIndex].TargetName.Name, inst->sValue, sizeof(pSelection->Elements[nPathElementIndex].TargetName.Name));
										}
									}
									if(ParseClientValue(&pStart, "Var=", inst->sValue) == 1)
									{
										STRING* pVar = (STRING*)((USINT*)pEventItem->pEfFieldVars) + ((UDINT)inst->nEventFieldIndex * sizeof(inst->sVarName));
										BrbStringCopy(pVar, inst->sValue, sizeof(inst->sVarName)); // Speicher hat dieselbe Grösse wie inst->sVarName
									}
								}
							}
						}
						inst->nEventFieldIndex++;
					}
					// Nächste Zeile lesen
					inst->fbDatObjRead.Offset += inst->nLineLen+1;
				}
				else if(inst->fbDatObjRead.status == doERR_ILLEGALLENGTH)
				{
					// Am Ende des Datenobjekts angelangt
					inst->fbDatObjRead.Offset = 0;
					inst->nSubscriptionIndex = 0;
					inst->nEventItemIndex = 0;
					inst->eStep = eSTEP_FINISHED;
					break;
				}
				else if(inst->fbDatObjRead.status != 65535)
				{
					// Fehler
					inst->nStatus = inst->fbDatObjRead.status;
					inst->pRunClient->State.nClientErroId = inst->nStatus;
					strcpy(inst->pRunClient->State.sClientErrorText, "Init error on parsing EventFields of Subscription#");
					STRING sHelp[16];
					brsitoa(inst->nSubscriptionIndex, (UDINT)&sHelp);
					BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
					BrbStringCat(inst->pRunClient->State.sClientErrorText, " of EventItem#", sizeof(inst->pRunClient->State.sClientErrorText));
					brsitoa(inst->nEventItemIndex, (UDINT)&sHelp);
					BrbStringCat(inst->pRunClient->State.sClientErrorText, sHelp, sizeof(inst->pRunClient->State.sClientErrorText));
					inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_ERROR;
					inst->eStep = eSTEP_INIT;
					break;
				}
			}
			break;

		case eSTEP_FINISHED:
			inst->nStatus = 0;
			inst->pRunClient->State.eClientState = eBRB_RCCLTSTATE_INIT_DONE;
			inst->eStep = eSTEP_INIT;
			break;

	}
}

// Wert aus dem Datenobjekt lesen
BOOL ParseClientValue(STRING** ppStart, STRING* pPar, STRING* pValue)
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
				UDINT nLen = (UDINT)(nEndVal - nStartVal);
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

(*General*)

TYPE
	BrbErrorUa_ENUM : 
		( (*OpcUa-Error-Stati*)
		eBRB_ERR_UA_ERROR := 51000,
		eBRB_ERR_UA_NO_ELEMENTS := 51001,
		eBRB_ERR_UA_INVALID_INDEX := 51002,
		eBRB_ERR_UA_NOT_CONNECTED := 51003,
		eBRB_ERR_UA_NOT_RUNNING := 51004
		);
END_TYPE

(*General - Attributes*)

TYPE
	BrbUaNodeInfoAttribute_TYP : 	STRUCT  (*Attribut-Info*)
		sName : STRING[nBRBUA_ATTRIBUTE_NAME_CHAR_MAX]; (*Name des Attributs*)
		sValue : STRING[nBRBUA_VALUE_TEXT_CHAR_MAX]; (*Wert des Attributs als Text*)
	END_STRUCT;
	BrbUaNodeInfoAttributes_TYP : 	STRUCT  (*Attribute-Liste der Infos*)
		Attribute : ARRAY[0..nBRBUA_ATTRIBUTES_INDEX_MAX]OF BrbUaNodeInfoAttribute_TYP; (*Attribute-Liste der Infos*)
	END_STRUCT;
END_TYPE

(*General - ByteStrings*)
(*General - ServerInfo*)

TYPE
	BrbUaServerNamespacesArray_TYP : 	STRUCT  (*Array für Namespaces*)
		Length : UAArrayLength;
		Data : ARRAY[0..nBRBUA_SRVDIAG_NAMESPACE_IDX_MAX]OF STRING[nBRBUA_NAMESPACE_URI_CHAR_MAX];
	END_STRUCT;
	BrbUaServerBuildInfo_TYP : 	STRUCT  (*Build-Daten des Servers*)
		sProductUri : STRING[255];
		sManufacturerName : STRING[255];
		sProductName : STRING[255];
		sSoftwareVersion : STRING[255];
		sBuildNumber : STRING[255];
		dtBuildDate : DATE_AND_TIME;
	END_STRUCT;
	BrbUaServerState_ENUM : 
		( (*Server-Status*)
		eBRBUA_SRVSTATE_RUNNING,
		eBRBUA_SRVSTATE_FAILED,
		eBRBUA_SRVSTATE_NOCONFIG,
		eBRBUA_SRVSTATE_SUSPENDED,
		eBRBUA_SRVSTATE_SHUTDOWN,
		eBRBUA_SRVSTATE_TEST,
		eBRBUA_SRVSTATE_COMMFAULT,
		eBRBUA_SRVSTATE_UNKNOWN
		);
	BrbUaServerStatus_TYP : 	STRUCT  (*Status-Daten des Servers*)
		dtStartTime : DATE_AND_TIME;
		dtCurrentTime : DATE_AND_TIME;
		eServerState : BrbUaServerState_ENUM;
		BuildInfo : BrbUaServerBuildInfo_TYP;
		nSecondsTillShutdown : UDINT;
		ShutdownReason : UALocalizedText;
	END_STRUCT;
END_TYPE

(*General - ServerDiag*)

TYPE
	BrbUaServerDiagData_TYP : 	STRUCT  (*Diagnose-Daten einer Session*)
		nServerViewCount : UDINT;
		nCurrentSessionCount : UDINT;
		nCumulatedSessionCount : UDINT;
		nSecurityRejectedSessionCount : UDINT;
		nRejectedSessionCount : UDINT;
		nSessionTimeoutCount : UDINT;
		nSessionAbortCount : UDINT;
		nCurrentSubscriptionCount : UDINT;
		nCumulatedSubscriptionCount : UDINT;
		nPublishingIntervalCount : UDINT;
		nSecurityRejectedRequestsCount : UDINT;
		nRejectedRequestsCount : UDINT;
	END_STRUCT;
	BrbUaApplicationType_ENUM : 
		( (*Applikations-Typen*)
		eBRBUA_APPTYPE_SERVER, (*Nur Server*)
		eBRBUA_APPTYPE_CLIENT, (*Nur Client*)
		eBRBUA_APPTYPE_CLIENT_AND_SERVER, (*Client und Server*)
		eBRBUA_APPTYPE_DISCOVERY_SERVER (*Nur Discovery-Server*)
		);
	BrbUaApplicationDescription_TYP : 	STRUCT  (*Applikations-Beschreibung*)
		sApplicationUri : STRING[255];
		sProductUri : STRING[255];
		ApplicationName : UALocalizedText;
		eApplicationType : BrbUaApplicationType_ENUM;
		sGatewayServerUri : STRING[255];
		sDiscoveryProfileUri : STRING[255];
		DiscoveryUrlsLength : UANoOfElements;
		sDiscoveryUrls : ARRAY[0..9]OF STRING[255];
	END_STRUCT;
	BrbUaServiceCounterData_TYP : 	STRUCT  (*Zähler für Service-Daten*)
		nTotalCount : UDINT;
		nErrorCount : UDINT;
	END_STRUCT;
	BrbUaSessDiagData_TYP : 	STRUCT  (*Diagnose-Daten einer Session*)
		SessionId : UANodeID;
		sSessionName : STRING[255];
		ClientDescription : BrbUaApplicationDescription_TYP;
		sServerUri : STRING[255];
		sEndpointUrl : STRING[255];
		LocaleIdsCount : UANoOfElements;
		sLocaleIds : ARRAY[0..nBRBUA_SRVDIAG_LOCALES_INDEX_MAX]OF STRING[7];
		rActualSessionTimeout : LREAL;
		nMaxResponseMessageSize : UDINT;
		dtClientConnectionTime : DATE_AND_TIME;
		dtClientLastContactTime : DATE_AND_TIME;
		nCurrentSubscriptionsCount : UDINT;
		nCurrentMonitoredItemsCount : UDINT;
		nCurrentPublishRequestsInQueue : UDINT;
		TotalRequestCount : BrbUaServiceCounterData_TYP;
		nUnauthorizedRequestCount : UDINT;
		ReadCount : BrbUaServiceCounterData_TYP;
		HistoryReadCount : BrbUaServiceCounterData_TYP;
		WriteCount : BrbUaServiceCounterData_TYP;
		HistoryUpdateCount : BrbUaServiceCounterData_TYP;
		CallCount : BrbUaServiceCounterData_TYP;
		CreateMonitoredItemsCount : BrbUaServiceCounterData_TYP;
		ModifyMonitoredItemsCount : BrbUaServiceCounterData_TYP;
		SetMonitoringModeCount : BrbUaServiceCounterData_TYP;
		SetTriggeringCount : BrbUaServiceCounterData_TYP;
		DeleteMonitoredItemsCount : BrbUaServiceCounterData_TYP;
		CreateSubscriptionCount : BrbUaServiceCounterData_TYP;
		ModifySubscriptionCount : BrbUaServiceCounterData_TYP;
		SetPublishingModeCount : BrbUaServiceCounterData_TYP;
		PublishCount : BrbUaServiceCounterData_TYP;
		RepublishCount : BrbUaServiceCounterData_TYP;
		TransferSubscriptionsCount : BrbUaServiceCounterData_TYP;
		DeleteSubscriptionsCount : BrbUaServiceCounterData_TYP;
		AddNodesCount : BrbUaServiceCounterData_TYP;
		AddReferencesCount : BrbUaServiceCounterData_TYP;
		DeleteNodesCount : BrbUaServiceCounterData_TYP;
		DeleteReferencesCount : BrbUaServiceCounterData_TYP;
		BrowseCount : BrbUaServiceCounterData_TYP;
		BrowseNextCount : BrbUaServiceCounterData_TYP;
		TranslateBrowsePathToNodeIdCount : BrbUaServiceCounterData_TYP;
		QueryFirstCount : BrbUaServiceCounterData_TYP;
		QueryNextCount : BrbUaServiceCounterData_TYP;
		RegisterNodesCount : BrbUaServiceCounterData_TYP;
		UnregisterNodesCount : BrbUaServiceCounterData_TYP;
	END_STRUCT;
	BrbUaSessDiagArray_TYP : 	STRUCT  (*Array für Session-Diagnose*)
		Length : UAArrayLength;
		Data : ARRAY[0..nBRBUA_SRVDIAG_SESSION_INDEX_MAX]OF BrbUaSessDiagData_TYP;
	END_STRUCT;
	BrbUaMessageSecurityMode_ENUM : 
		( (*Message-Secutity-Modes*)
		eBRBUA_SECMODE_INVALID, (*Ungültig*)
		eBRBUA_SECMODE_NONE, (*Keine Security*)
		eBRBUA_SECMODE_SIGN, (*Nur Signierung*)
		eBRBUA_SECMODE_SIGN_AND_ENCRYPT (*Signierung und Verschlüsselung*)
		);
	BrbUaSessSecDiagData_TYP : 	STRUCT  (*Security-Diagnose-Daten einer Session*)
		SessionId : UANodeID;
		sClientUserIdOfSession : STRING[64];
		ClientUserIdHistoryCount : UANoOfElements;
		sClientUserIdHistory : ARRAY[0..nBRBUA_SRVDIAG_USERHIST_IDX_MAX]OF STRING[32];
		sAuthenticationMechanism : STRING[64];
		sEncoding : STRING[64];
		sTransportProtocol : STRING[64];
		eSecurityMode : BrbUaMessageSecurityMode_ENUM;
		sSecurityPolicyUri : STRING[64];
		ClientCertificate : ARRAY[0..nBRBUA_CERT_ARRAY_INDEX_MAX]OF USINT;
	END_STRUCT;
	BrbUaSessSecDiagArray_TYP : 	STRUCT  (*Array für Security-Session-Diagnose*)
		Length : UAArrayLength;
		Data : ARRAY[0..nBRBUA_SRVDIAG_SESSION_INDEX_MAX]OF BrbUaSessSecDiagData_TYP;
	END_STRUCT;
	BrbUaSubscriptDiagData_TYP : 	STRUCT  (*Diagnose-Daten einer Subscription*)
		SessionId : UANodeID;
		nSubscriptionId : UDINT;
		nPriority : USINT;
		rPublishingInterval : LREAL;
		nMaxKeepAliveCount : UDINT;
		nMaxLifetimeCount : UDINT;
		nMaxNotificationsPerPublish : UDINT;
		bPublishingEnabled : BOOL;
		nModifyCount : UDINT;
		nEnableCount : UDINT;
		nDisableCount : UDINT;
		nRepublishRequestCount : UDINT;
		nRepublishMessageRequestCount : UDINT;
		nRepublishMessageCount : UDINT;
		nTransferRequestCount : UDINT;
		nTransferredToAltClientCount : UDINT;
		nTransferredToSameClientCount : UDINT;
		nPublishRequestCount : UDINT;
		nDataChangeNotificationsCount : UDINT;
		nEventNotificationsCount : UDINT;
		nNotificationsCount : UDINT;
		nLatePublishRequestCount : UDINT;
		nCurrentKeepAliveCount : UDINT;
		nCurrentLifetimeCount : UDINT;
		nUnacknowledgedMessageCount : UDINT;
		nDiscardedMessageCount : UDINT;
		nMonitoredItemCount : UDINT;
		nDisabledMonitoredItemCount : UDINT;
		nMonitoringQueueOverflowCount : UDINT;
		nNextSequenceNumber : UDINT;
		nEventQueueOverflowCount : UDINT;
	END_STRUCT;
	BrbUaSubscriptDiagArray_TYP : 	STRUCT  (*Array für Subscription-Diagnose*)
		Length : UAArrayLength;
		Data : ARRAY[0..nBRBUA_SRVDIAG_SUBSCR_INDEX_MAX]OF BrbUaSubscriptDiagData_TYP;
	END_STRUCT;
END_TYPE

(*Client - RunClient*)

TYPE
	UAByteStringBrbEventId_TYP : 	STRUCT  (*EventId als ByteString mit Länge 16*)
		Length : DINT; (*Länge der Daten (sollte mit 16 besetzt werden)*)
		Data : ARRAY[0..nBRBUA_EVENTID_INDEX_MAX]OF USINT; (*Bytes der EventId*)
	END_STRUCT;
	BrbUaRcCfg_TYP : 	STRUCT  (*Verbindungs-Parameter*)
		sCfgDataObjName : STRING[nBRBUA_DATOBJECT_NAME_CHAR_MAX]; (*Name des Datenobjekts*)
		sServerEndpointUrl : STRING[sBRBUA_ENDPOINT_URL_CHAR_MAX]; (*Endpoint-Url*)
		SessionConnectInfo : UASessionConnectInfo; (*Angaben zur Verbindung*)
		tConnectTimeout : TIME; (*Timeout für den Connect in [ms]*)
		tAccessTimeout : TIME; (*Timeout für Zugriff auf den Server in [ms]*)
	END_STRUCT;
	BrbUaRcCommandos_ENUM : 
		( (*Client-Kommandos*)
		eBRB_RCCLTCMD_NONE, (*Aktuell kein Kommando*)
		eBRB_RCCLTCMD_CONNECT, (*Verbindung aufbauen*)
		eBRB_RCCLTCMD_DISCONNECT (*Verbindung trennen*)
		);
	BrbUaRcConnection_TYP : 	STRUCT  (*Daten der Verbindung*)
		nConnectionHandle : UDINT; (*Handle der Verbindung*)
		nErrorId : DWORD; (*OpcUa-Fehler beim Verbinden*)
		nConnectTries : UDINT; (*Connect-Versuche*)
		nInterruptedCount : UDINT; (*Anzahl der Verbindungs-Unterbrechungen*)
	END_STRUCT;
	BrbUaRcNamespaces_TYP : 	STRUCT  (*Daten der Namespaces*)
		nNamespaceCount : UINT; (*Anzahl der Namespaces*)
		pNamespaces : {REDUND_UNREPLICABLE} UDINT; (*Interner Zeiger*)
		nMemLen : UDINT; (*Interne Speichergröße*)
	END_STRUCT;
	BrbUaRcNamespace_TYP : 	STRUCT  (*Daten eines Namespaces*)
		sNamespaceUri : STRING[nBRBUA_NAMESPACE_URI_CHAR_MAX]; (*Namespace-Uri aus dem Datenobjekt*)
		nNamespaceIndex : UINT; (*Server-Namespace-Index*)
		nErrorId : DWORD; (*OpcUa-Fehler-Status*)
	END_STRUCT;
	BrbUaRcNodeHandles_TYP : 	STRUCT  (*Daten der NodeHandles*)
		nNodeHandleCount : UINT; (*Anzahl der NodeHandles*)
		pStart : UDINT; (*Interner Zeiger*)
		pDatObjNamespaceIndices : {REDUND_UNREPLICABLE} UDINT; (*Interner Zeiger*)
		pNodeIds : {REDUND_UNREPLICABLE} UDINT; (*Interner Zeiger*)
		pNodeHandleErrorIds : {REDUND_UNREPLICABLE} UDINT; (*Interner Zeiger*)
		pNodeHandles : {REDUND_UNREPLICABLE} UDINT; (*Interner Zeiger*)
		nMemLen : UDINT; (*Interne Speichergröße*)
	END_STRUCT;
	BrbUaRcNodeHandle_TYP : 	STRUCT  (*Daten eines NodeHandles*)
		nDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		NodeId : UANodeID; (*NodeId laut Datenobjekt*)
		nErrorId : DWORD; (*OpcUa-Fehler-Status beim Ermitteln des NodeHandles*)
		nNodeHandle : DWORD; (*Ermittelter NodeHandle*)
	END_STRUCT;
	BrbUaRcReadBlocks_TYP : 	STRUCT  (*Daten der ReadBlocks*)
		nBlockCount : UINT; (*Anzahl der ReadBlocks*)
		pBlocks : {REDUND_UNREPLICABLE} UDINT; (*Interner Zeiger*)
		nMemLen : UDINT; (*Interne Speichergröße*)
	END_STRUCT;
	BrbUaRcReadBlockIntern_TYP : 	STRUCT  (*Interne Daten eines ReadBlocks*)
		nReadItemCount : UINT; (*Anzahl der ReadItems*)
		pRiStart : UDINT; (*Interner Zeiger*)
		pRiDatObjNamespaceIndices : UDINT; (*Interner Zeiger*)
		pRiNodeIds : UDINT; (*Interner Zeiger*)
		pRiNodeAddInfos : UDINT; (*Interner Zeiger*)
		pRiVariables : UDINT; (*Interner Zeiger*)
		pRiNodeErrorIds : UDINT; (*Interner Zeiger*)
		pRiTimestamps : UDINT; (*Interner Zeiger*)
		nMemLen : UDINT; (*Interne Speichergröße*)
	END_STRUCT;
	BrbUaRcReadBlock_TYP : 	STRUCT  (*Daten eines ReadBlocks*)
		nReadItemCount : UINT; (*Anzahl der ReadItems*)
	END_STRUCT;
	BrbUaRcReadItem_TYP : 	STRUCT  (*Daten eines ReadItems*)
		nDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		NodeId : UANodeID; (*NodeId laut Datenobjekt*)
		AddInfo : UANodeAdditionalInfo; (*Zusatzangaben für den Zugriff*)
		sVar : STRING[nBRBUA_VARNAME_TEXT_CHAR_MAX]; (*Name der gemappten Variable*)
		dtTimestamp : DATE_AND_TIME; (*Zeitstempel der letzten Aktion*)
		nErrorId : DWORD; (*OpcUa-Fehler-Status*)
	END_STRUCT;
	BrbUaRcWriteBlocks_TYP : 	STRUCT  (*Daten der WriteBlocks*)
		nBlockCount : UINT; (*Anzahl der WriteBlocks*)
		pBlocks : {REDUND_UNREPLICABLE} UDINT; (*Interner Zeiger*)
		nMemLen : UDINT; (*Interne Speichergröße*)
	END_STRUCT;
	BrbUaRcWriteBlockIntern_TYP : 	STRUCT  (*Interne Daten eines WriteBlocks*)
		nWriteItemCount : UINT; (*Anzahl der WriteBlocks*)
		pWiStart : UDINT; (*Interner Zeiger*)
		pWiDatObjNamespaceIndices : UDINT; (*Interner Zeiger*)
		pWiNodeIds : UDINT; (*Interner Zeiger*)
		pWiNodeAddInfos : UDINT; (*Interner Zeiger*)
		pWiVariables : UDINT; (*Interner Zeiger*)
		pWiNodeErrorIds : UDINT; (*Interner Zeiger*)
		nMemLen : UDINT; (*Interne Speichergröße*)
	END_STRUCT;
	BrbUaRcWriteBlock_TYP : 	STRUCT  (*Daten eines WriteBlocks*)
		nWriteItemCount : UINT; (*Anzahl der WriteItems*)
	END_STRUCT;
	BrbUaRcWriteItem_TYP : 	STRUCT  (*Daten eines WriteItems*)
		nDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		NodeId : UANodeID; (*NodeId laut Datenobjekt*)
		AddInfo : UANodeAdditionalInfo; (*Zusatzangaben für den Zugriff*)
		sVar : STRING[nBRBUA_VARNAME_TEXT_CHAR_MAX]; (*Name der gemappten Variable*)
		nErrorId : DWORD; (*OpcUa-Fehler-Status*)
	END_STRUCT;
	BrbUaRcMethods_TYP : 	STRUCT  (*Daten der Methods*)
		nMethodCount : UINT; (*Anzahl der Methods*)
		pMethods : {REDUND_UNREPLICABLE} UDINT; (*Interner Zeiger*)
		nMemLen : UDINT; (*Interne Speichergröße*)
	END_STRUCT;
	BrbUaRcMethodIntern_TYP : 	STRUCT  (*Interne Daten einer Method*)
		nDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		ObjectNodeId : UANodeID; (*NodeId laut Datenobjekt*)
		MethodNodeId : UANodeID; (*NodeId laut Datenobjekt*)
		tTimeout : TIME; (*Timeout für den Call*)
		pStart : UDINT; (*Interner Zeiger*)
		nInputArgsCount : USINT; (*Anzahl der Eingangs-Argumente*)
		pInputArguments : UDINT; (*Interner Zeiger*)
		nOutputArgsCount : USINT; (*Anzahl der Ausgangs-Argumente*)
		pOutputArguments : UDINT; (*Interner Zeiger*)
		nMemLen : UDINT; (*Interne Speichergröße*)
		nErrorId : DWORD; (*OpcUa-Fehler-Status beim Ermitteln des MethodHandles*)
		nMethodHandle : DWORD; (*Ermittelter MethodHandle*)
	END_STRUCT;
	BrbUaRcMethod_TYP : 	STRUCT  (*Daten einer Method*)
		nDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		ObjectNodeId : UANodeID; (*NodeId laut Datenobjekt*)
		MethodNodeId : UANodeID; (*NodeId laut Datenobjekt*)
		tTimeout : TIME; (*Timeout für den Call*)
		nInputArgsCount : USINT; (*Anzahl der Eingangs-Argumente*)
		nOutputArgsCount : USINT; (*Anzahl der Ausgangs-Argumente*)
		nErrorId : DWORD; (*OpcUa-Fehler-Status beim Ermitteln des MethodHandles*)
		nMethodHandle : DWORD; (*Ermittelter MethodHandle*)
	END_STRUCT;
	BrbUaRcSubscriptions_TYP : 	STRUCT  (*Daten der Subscriptions*)
		nSubscriptionCount : UINT; (*Anzahl der Subscriptions*)
		pSubscriptions : {REDUND_UNREPLICABLE} UDINT; (*Interner Zeiger*)
		nMemLen : UDINT; (*Interne Speichergröße*)
		nMonitoredItemsCountTotal : UDINT; (*Anzahl aller MonitorredItems*)
		nEventItemsCountTotal : UDINT; (*Anzahl aller EventItems*)
	END_STRUCT;
	BrbUaRcSubscriptionIntern_TYP : 	STRUCT  (*Interne Daten einer Subscription*)
		bPublishingEnable : BOOL; (*Aktivierung der Subscription*)
		nPriority : USINT; (*Priorität (0..255, je größer desto höher)*)
		tPublishingInterval : TIME; (*Sende-Intervall in [ms]*)
		nMonitoredItemCount : UINT; (*Anzahl der MonitoredItems*)
		nEventItemCount : UINT; (*Anzahl der EventItems*)
		nErrorId : DWORD; (*OpcUa-Fehler-Status*)
		nSubscriptionHandle : DWORD; (*Ermitteltes SubscriptionHandle*)
		pMiStart : UDINT; (*Interner Zeiger*)
		pMiDatObjNamespaceIndices : UDINT; (*Interner Zeiger*)
		pMiNodeIds : UDINT; (*Interner Zeiger*)
		pMiNodeHandleErrorIds : UDINT; (*Interner Zeiger*)
		pMiNodeHandles : UDINT; (*Interner Zeiger*)
		pMiNodeAddInfos : UDINT; (*Interner Zeiger*)
		pMiVariables : UDINT; (*Interner Zeiger*)
		pMiQueueSizeOri : UDINT; (*Interner Zeiger*)
		pMiMonitorSettings : UDINT; (*Interner Zeiger*)
		pMiValuesChanged : UDINT; (*Interner Zeiger*)
		pMiRemainingValueCounts : UDINT; (*Interner Zeiger*)
		pMiTimestamps : UDINT; (*Interner Zeiger*)
		pMiNodeQualityIds : UDINT; (*Interner Zeiger*)
		pMiMonitoredItemErrorIds : UDINT; (*Interner Zeiger*)
		pMiMonitoredItemHandles : UDINT; (*Interner Zeiger*)
		nMiMemLen : UDINT; (*Interne Speichergröße*)
		pEventItems : UDINT; (*Interner Zeiger*)
		nEiMemLen : UDINT; (*Interne Speichergröße*)
	END_STRUCT;
	BrbUaRcSubscription_TYP : 	STRUCT  (*Daten einer Subscription*)
		bPublishingEnable : BOOL; (*Aktivierung der Subscription*)
		nPriority : USINT; (*Priorität (0..255, je größer desto höher)*)
		tPublishingInterval : TIME; (*Sende-Intervall in [ms]*)
		nMonitoredItemCount : UINT; (*Anzahl der MonitoredItems*)
		nEventItemCount : UINT; (*Anzahl der EventItems*)
		nErrorId : DWORD; (*OpcUa-Fehler-Status*)
		nSubscriptionHandle : DWORD; (*Ermitteltes SubscriptionHandle*)
	END_STRUCT;
	BrbUaRcMonitoredItem_TYP : 	STRUCT  (*Daten eines MonitoredItems*)
		nDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		NodeId : UANodeID; (*NodeId laut Datenobjekt*)
		nNodeHandleErrorId : DWORD; (*OpcUa-Fehler-Status*)
		nNodeHandle : DWORD; (*Ermitteltes NodeHandle*)
		AddInfo : UANodeAdditionalInfo; (*Zusatzangaben für den Zugriff*)
		sVar : STRING[nBRBUA_VARNAME_TEXT_CHAR_MAX]; (*Name der gemappten Variable*)
		nQueueSizeOri : UINT; (*Puffergröße laut Datenobjekt*)
		MonitorSettings : UAMonitoringParameters; (*Überwachungs-Einstellungen*)
		bValueChanged : BOOL; (*1=Wert hat sich geändert*)
		nRemainingValueCount : UINT; (*Anzahl der verbleibenden Wert-Änderungen*)
		dtTimestamp : DATE_AND_TIME; (*Zeitstempel der letzten Wert-Änderung*)
		nNodeQualityId : DWORD; (*OpcUa-Fehler-Status der letzten Wert-Änderung*)
		nMonitoredItemErrorId : DWORD; (*OpcUa-Fehler-Status*)
		nMonitoredItemHandle : DWORD; (*Ermitteltes MonitoredItemHandle*)
	END_STRUCT;
	BrbUaRcEventItemIntern_TYP : 	STRUCT  (*Interne Daten eines EventItems*)
		nEventDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		EventNodeId : UANodeID; (*NodeId laut Datenobjekt*)
		nEventNodeHandleErrorId : DWORD; (*OpcUa-Fehler-Status*)
		nEventNodeHandle : DWORD; (*Ermitteltes NodeHandle*)
		nTypeDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		TypeNodeId : UANodeID; (*NodeId laut Datenobjekt*)
		nEventItemErrorId : DWORD; (*OpcUa-Fehler-Status*)
		nEventItemHandle : DWORD; (*Ermitteltes NodeHandle*)
		tTimeout : TIME; (*Timeout für Operate in [ms]*)
		bCallOperate : BOOL; (*1=Zyklischer Aufruf von Operate*)
		nEventFieldCount : UINT; (*Anzahl der Fields*)
		pEfStart : UDINT; (*Interner Zeiger*)
		pEfDatObjNamespaceIndices : UDINT; (*Interner Zeiger*)
		pEfFieldSelections : UDINT; (*Interner Zeiger*)
		pEfFieldVars : UDINT; (*Interner Zeiger*)
		nEfMemLen : UDINT; (*Interne Speichergröße*)
		nReceiveCount : UDINT; (*Empfangs-Zähler*)
		bEventReceived : BOOL; (*Empfangs-Flag*)
	END_STRUCT;
	BrbUaRcEventItem_TYP : 	STRUCT  (*Daten eines EventItems*)
		nEventDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		EventNodeId : UANodeID; (*NodeId laut Datenobjekt*)
		nEventNodeHandleErrorId : DWORD; (*OpcUa-Fehler-Status*)
		nEventNodeHandle : DWORD; (*Ermitteltes NodeHandle*)
		nTypeDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		TypeNodeId : UANodeID; (*NodeId laut Datenobjekt*)
		nEventItemErrorId : DWORD; (*OpcUa-Fehler-Status*)
		nEventItemHandle : DWORD; (*Ermitteltes NodeHandle*)
		tTimeout : TIME; (*Timeout für Operate in [ms]*)
		bCallOperate : BOOL; (*1=Zyklischer Aufruf von Operate*)
		nEventFieldCount : UINT; (*Anzahl der Fields*)
		nReceiveCount : UDINT; (*Empfangs-Zähler*)
		bEventReceived : BOOL; (*1=Event wurde empfangen (nur für einen Zyklus)*)
	END_STRUCT;
	BrbUaRcEventField_TYP : 	STRUCT  (*Daten eines EventFields*)
		nDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		FieldSelection : UARelativePath; (*Angaben zum Field*)
		sVar : STRING[nBRBUA_VARNAME_TEXT_CHAR_MAX]; (*Name der gemappten Variable*)
	END_STRUCT;
	BrbUaRcClientStates_ENUM : 
		( (*Stati des RunClients*)
		eBRB_RCCLTSTATE_NO_INIT,
		eBRB_RCCLTSTATE_INITIALIZING,
		eBRB_RCCLTSTATE_INIT_ERROR,
		eBRB_RCCLTSTATE_INIT_DONE,
		eBRB_RCCLTSTATE_WAIT_FOR_CONNECT,
		eBRB_RCCLTSTATE_CONNECTING,
		eBRB_RCCLTSTATE_CONNECT_ERROR,
		eBRB_RCCLTSTATE_CON_INTERRUPTED,
		eBRB_RCCLTSTATE_CONNECTED,
		eBRB_RCCLTSTATE_DISCONNECTING,
		eBRB_RCCLTSTATE_DISCONNECT_ERROR,
		eBRB_RCCLTSTATE_DISCONNECTED,
		eBRB_RCCLTSTATE_EXITING,
		eBRB_RCCLTSTATE_EXIT_ERROR,
		eBRB_RCCLTSTATE_EXIT_DONE
		);
	BrbUaRcStateConStatus_TYP : 	STRUCT  (*Status des Servers*)
		eConnectionStatus : {REDUND_UNREPLICABLE} UAConnectionStatus; (*Status der Verbindung*)
		eServerState : UAServerState; (*Status des Servers*)
		nServiceLevel : USINT; (*Level des Servers*)
	END_STRUCT;
	BrbUaRcState_TYP : 	STRUCT  (*Status des Clients und der Verbindung und des Servers*)
		eClientState : {REDUND_UNREPLICABLE} BrbUaRcClientStates_ENUM; (*Status des Clients*)
		nClientErroId : UDINT; (*OpcUa-Fehler-Status bei internen Aufrufen*)
		sClientErrorText : STRING[nBRBUA_VALUE_TEXT_CHAR_MAX]; (*Details zum Fehler*)
		ConnectionStatus : BrbUaRcStateConStatus_TYP; (*Status des Servers*)
	END_STRUCT;
	BrbUaRunClient_TYP : 	STRUCT  (*RunClient-Struktur zum Betreiben eines Clients*)
		Cfg : BrbUaRcCfg_TYP; (*Verbindungs-Parameter*)
		eCmd : BrbUaRcCommandos_ENUM; (*Client-Kommandos (z.B. Verbindung trennen)*)
		Connection : BrbUaRcConnection_TYP; (*Daten der Verbindung*)
		Namespaces : BrbUaRcNamespaces_TYP; (*Daten der Namespaces*)
		NodeHandles : BrbUaRcNodeHandles_TYP; (*Daten der NodeHandles*)
		ReadBlocks : BrbUaRcReadBlocks_TYP; (*Daten der ReadBlocks*)
		WriteBlocks : BrbUaRcWriteBlocks_TYP; (*Daten der WriteBlocks*)
		Methods : BrbUaRcMethods_TYP; (*Daten der Methods*)
		Subscriptions : BrbUaRcSubscriptions_TYP; (*Daten der Subscriptions*)
		State : BrbUaRcState_TYP; (*Status des Clients, der Verbindung und des Servers*)
	END_STRUCT;
	BrbUaRcMonitorNamespace_TYP : 	STRUCT  (*Interne Daten zu einem Namespace*)
		nDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		Namespace : BrbUaRcNamespace_TYP; (*Daten des Namespaces*)
	END_STRUCT;
	BrbUaRcMonitorNodeHandle_TYP : 	STRUCT  (*Interne Daten zu einem NodeHandle*)
		nNodeHandleIndex : UINT; (*0-basierter Index des NodeHandles*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		NodeHandle : BrbUaRcNodeHandle_TYP; (*Daten des NodeHandles*)
	END_STRUCT;
	BrbUaRcMonitorReadBlock_TYP : 	STRUCT  (*Interne Daten zu einem ReadBlock*)
		nReadBlockIndex : UINT; (*0-basierter Index des ReadBlocks*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		ReadBlock : BrbUaRcReadBlock_TYP; (*Daten des ReadBlocks*)
		ReadBlockIntern : BrbUaRcReadBlockIntern_TYP; (*Interne Daten des ReadBlocks*)
	END_STRUCT;
	BrbUaRcMonitorReadItem_TYP : 	STRUCT  (*Interne Daten zu einem ReadItem*)
		nReadBlockIndex : UINT; (*0-basierter Index des ReadBlocks*)
		nReadItemIndex : UINT; (*0-basierter Index des ReadItems*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		ReadItem : BrbUaRcReadItem_TYP; (*Daten des ReadItems*)
	END_STRUCT;
	BrbUaRcMonitorWriteBlock_TYP : 	STRUCT  (*Interne Daten zu einem WriteBlock*)
		nWriteBlockIndex : UINT; (*0-basierter Index des WriteBlocks*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		WriteBlock : BrbUaRcWriteBlock_TYP; (*Daten des WriteBlocks*)
		WriteBlockIntern : BrbUaRcWriteBlockIntern_TYP; (*Interne Daten des WriteBlocks*)
	END_STRUCT;
	BrbUaRcMonitorWriteItem_TYP : 	STRUCT  (*Interne Daten zu einem WriteItem*)
		nWriteBlockIndex : UINT; (*0-basierter Index des WriteBlocks*)
		nWriteItemIndex : UINT; (*0-basierter Index des WriteItems*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		WriteItem : BrbUaRcWriteItem_TYP; (*Daten des WriteItems*)
	END_STRUCT;
	BrbUaRcMonitorMethod_TYP : 	STRUCT  (*Interne Daten zu einer Method*)
		nMethodIndex : UINT; (*0-basierter Index der Method*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		Method : BrbUaRcMethod_TYP; (*Daten der Method*)
		MethodIntern : BrbUaRcMethodIntern_TYP; (*Interne Daten der Method*)
	END_STRUCT;
	BrbUaRcMonitorArgument_TYP : 	STRUCT  (*Interne Daten zu einem Argument*)
		nMethodIndex : UINT; (*0-basierter Index der Method*)
		bOutput : BOOL; (*0=Eingangs-Argument, 1=Ausgangs-Argument*)
		nArgumentIndex : UINT; (*0-basierter Index des Arguments*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		Argument : UAMethodArgument; (*Daten des Arguments*)
	END_STRUCT;
	BrbUaRcMonitorSubscription_TYP : 	STRUCT  (*Interne Daten zu einer Subscription*)
		nSubscriptionIndex : UINT; (*0-basierter Index der Subscription*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		Subscription : BrbUaRcSubscription_TYP; (*Daten einer Subscription*)
		SubscriptionIntern : BrbUaRcSubscriptionIntern_TYP; (*Interne Daten der Subscription*)
	END_STRUCT;
	BrbUaRcMonitorMonitoredItem_TYP : 	STRUCT  (*Interne Daten zu einem MonitoredItem*)
		nSubscriptionIndex : UINT; (*0-basierter Index der Subscription*)
		nMonitoredItemIndex : UINT; (*0-basierter Index des MonitoredItems*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		MonitoredItem : BrbUaRcMonitoredItem_TYP; (*Daten des MonitoredItems*)
	END_STRUCT;
	BrbUaRcMonitorEventItem_TYP : 	STRUCT  (*Interne Daten zu einem EventItem*)
		nSubscriptionIndex : UINT; (*0-basierter Index der Subscription*)
		nEventItemIndex : UINT; (*0-basierter Index des EventItems*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		EventItem : BrbUaRcEventItem_TYP; (*Daten des EventItems*)
		EventItemIntern : BrbUaRcEventItemIntern_TYP; (*Interne Daten des EventItems*)
	END_STRUCT;
	BrbUaRcMonitorEventField_TYP : 	STRUCT  (*Interne Daten zu einem EventField*)
		nSubscriptionIndex : UINT; (*0-basierter Index der Subscription*)
		nEventItemIndex : UINT; (*0-basierter Index des EventItems*)
		nEventFieldIndex : UINT; (*0-basierter Index des EventFields*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		EventField : BrbUaRcEventField_TYP; (*Daten eines EventFields*)
	END_STRUCT;
	BrbUaRcMonitor_TYP : 	STRUCT  (*Monitor für interne Daten*)
		bEnable : BOOL; (*1=Aktiv*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		Namespace : BrbUaRcMonitorNamespace_TYP; (*Interne Daten zu einem Namespace*)
		NodeHandle : BrbUaRcMonitorNodeHandle_TYP; (*Interne Daten zu einem NodeHandle*)
		ReadBlock : BrbUaRcMonitorReadBlock_TYP; (*Interne Daten zu einem ReadBlock*)
		ReadItem : BrbUaRcMonitorReadItem_TYP; (*Interne Daten zu einem ReadItem*)
		WriteBlock : BrbUaRcMonitorWriteBlock_TYP; (*Interne Daten zu einem WriteBlock*)
		WriteItem : BrbUaRcMonitorWriteItem_TYP; (*Interne Daten zu einem WriteItem*)
		Method : BrbUaRcMonitorMethod_TYP; (*Interne Daten zu einer Method*)
		Argument : BrbUaRcMonitorArgument_TYP; (*Interne Daten zu einem Argument*)
		Subscription : BrbUaRcMonitorSubscription_TYP; (*Interne Daten zu einer Subscription*)
		MonitoredItem : BrbUaRcMonitorMonitoredItem_TYP; (*Interne Daten zu einem MonitoredItem*)
		EventItem : BrbUaRcMonitorEventItem_TYP; (*Interne Daten zu einem EventItem*)
		EventField : BrbUaRcMonitorEventField_TYP; (*Interne Daten zu einem EventField*)
	END_STRUCT;
END_TYPE

(*Server - Methods*)

TYPE
	BrbUaSrvMethodPar_TYP : 	STRUCT  (*Parameter einer Methode*)
		sMethodName : STRING[nBRBUA_METHOD_CHAR_MAX]; (*Name der Methode*)
		bEnable : BOOL; (*0=Ausführung beenden, 1=Ausführen*)
		bUserCodeIsFinished : BOOL; (*Rückmeldung, dass Benutzer-Code ausgeführt wurde*)
	END_STRUCT;
	BrbUaSrvMethodState_TYP : 	STRUCT  (*Status einer Methode*)
		bExecuteUserCode : BOOL; (*Meldung, dass Benutzer-Code ausgeführt werden muss*)
		bExecuteUserCodeInit : BOOL; (*Wird nur im ersten Zyklus gesetzt*)
		nCallCount : UINT; (*Aufruf-Zähler*)
		nErrorCount : UDINT; (*Fehler-Zähler*)
		nLastErrorId : UDINT; (*Letzter aufgetretener Fehler*)
		sLastErrorId : STRING[nBRBUA_VALUE_TEXT_CHAR_MAX]; (*Letzter aufgetretener Fehler als Hex*)
		eLastErrorAction : UaMethodOperateAction; (*Aktion beim letzten aufgetretenen Fehler*)
	END_STRUCT;
	BrbUaSrvMethodIntern_TYP : 	STRUCT  (*Intern verwendet*)
		bEnabled : BOOL; (*Interne Variable*)
		nStep : UINT; (*Step-Nummer für die interne Schrittkette*)
		fbUaSrv_MethodOperate : UaSrv_MethodOperate; (*Interner FB*)
		nErrorId : UDINT; (*Interne Variable*)
	END_STRUCT;
	BrbUaSrvMethod_TYP : 	STRUCT  (*Methode*)
		Par : BrbUaSrvMethodPar_TYP; (*Parameter*)
		State : BrbUaSrvMethodState_TYP; (*Status*)
		Intern : BrbUaSrvMethodIntern_TYP; (*Interne Variablen*)
	END_STRUCT;
END_TYPE

(*Server -RunServer*)

TYPE
	BrbUaRsCfg_TYP : 	STRUCT  (*Parameter*)
		sCfgDataObjName : STRING[nBRBUA_DATOBJECT_NAME_CHAR_MAX]; (*Name des Datenobjekts*)
	END_STRUCT;
	BrbUaRsNamespaces_TYP : 	STRUCT  (*Daten der Namespaces*)
		nNamespaceCount : UINT; (*Anzahl der Namespaces*)
		pNamespaces : {REDUND_UNREPLICABLE} UDINT; (*Interner Zeiger*)
		nMemLen : UDINT; (*Interne Speichergröße*)
	END_STRUCT;
	BrbUaRsNamespace_TYP : 	STRUCT  (*Daten eines Namespaces*)
		sNamespaceUri : STRING[nBRBUA_NAMESPACE_URI_CHAR_MAX]; (*Namespace-Uri aus dem Datenobjekt*)
		nNamespaceIndex : UINT; (*Server-Namespace-Index*)
		nErrorId : DWORD; (*OpcUa-Fehler-Status*)
	END_STRUCT;
	BrbUaRsEvents_TYP : 	STRUCT  (*Daten der Events*)
		nEventCount : UINT; (*Anzahl der Subscriptions*)
		pEvents : {REDUND_UNREPLICABLE} UDINT; (*Interner Zeiger*)
		nMemLen : UDINT; (*Interne Speichergröße*)
		nFieldsCountTotal : UDINT; (*Anzahl aller Fields aller Events*)
	END_STRUCT;
	BrbUaRsEvent_TYP : 	STRUCT  (*Daten eines Events*)
		nDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		TypeNodeId : UANodeID; (*TypeNodeId laut Datenobjekt*)
		nFieldCount : UINT; (*Anzahl der Fields*)
	END_STRUCT;
	BrbUaRsEventIntern_TYP : 	STRUCT  (*Interne Daten eines Events*)
		nDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		TypeNodeId : UANodeID; (*TypeNodeId laut Datenobjekt*)
		nFieldCount : UINT; (*Anzahl der Fields*)
		pFields : UDINT; (*Interner Zeiger*)
		nMemLen : UDINT; (*Interne Speichergröße*)
	END_STRUCT;
	BrbUaRsStates_ENUM : 
		( (*Stati des RunServers*)
		eBRB_RSSTATE_NO_INIT,
		eBRB_RSSTATE_INITIALIZING,
		eBRB_RSSTATE_INIT_ERROR,
		eBRB_RSSTATE_INIT_DONE,
		eBRB_RSSTATE_DETECTING,
		eBRB_RSSTATE_RUNNING,
		eBRB_RSSTATE_EXITING,
		eBRB_RSSTATE_EXIT_ERROR,
		eBRB_RSSTATE_EXIT_DONE
		);
	BrbUaRsState_TYP : 	STRUCT  (*Status des Clients und der Verbindung und des Servers*)
		eState : {REDUND_UNREPLICABLE} BrbUaRsStates_ENUM; (*Status des RunServers*)
		nErroId : UDINT; (*OpcUa-Fehler-Status bei internen Aufrufen*)
		sErrorText : STRING[nBRBUA_VALUE_TEXT_CHAR_MAX]; (*Details zum Fehler*)
		eServerState : {REDUND_UNREPLICABLE} UAServerState; (*Status des Servers*)
	END_STRUCT;
	BrbUaRunServer_TYP : 	STRUCT  (*RunServer-Struktur zum Betreiben des RunServers*)
		Cfg : BrbUaRsCfg_TYP; (*Parameter*)
		Namespaces : BrbUaRsNamespaces_TYP; (*Daten der Namespaces*)
		Events : BrbUaRsEvents_TYP; (*Daten der Events*)
		State : BrbUaRsState_TYP; (*Status des RunServers*)
	END_STRUCT;
	BrbUaRsMonitorNamespace_TYP : 	STRUCT  (*Interne Daten zu einem Namespace*)
		nDatObjNamespaceIndex : UINT; (*Namespace-Index laut Datenobjekt*)
		Namespace : BrbUaRsNamespace_TYP; (*Daten des Namespaces*)
	END_STRUCT;
	BrbUaRsMonitorEvent_TYP : 	STRUCT  (*Interne Daten zu einer Subscription*)
		nEventIndex : UINT; (*0-basierter Index des Events*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		Event : BrbUaRsEvent_TYP; (*Daten eines Events*)
		EventIntern : BrbUaRsEventIntern_TYP; (*Interne Daten eines Events*)
	END_STRUCT;
	BrbUaRsMonitorEventField_TYP : 	STRUCT  (*Interne Daten zu einem EventField*)
		nEventIndex : UINT; (*0-basierter Index des Events*)
		nEventFieldIndex : UINT; (*0-basierter Index des Fields*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		Field : UaSrv_FireEventFieldType; (*Daten des Fields*)
	END_STRUCT;
	BrbUaRsMonitor_TYP : 	STRUCT  (*Monitor für interne Daten*)
		bEnable : BOOL; (*1=Aktiv*)
		nMonitorStatus : UINT; (*Status des Monitors*)
		Namespace : BrbUaRsMonitorNamespace_TYP; (*Interne Daten zu einem Namespace*)
		Event : BrbUaRsMonitorEvent_TYP; (*Interne Daten zu einem Event*)
		EventField : BrbUaRsMonitorEventField_TYP; (*Interne Daten zu einem Field*)
	END_STRUCT;
END_TYPE

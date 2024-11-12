#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

void _INIT Init(void)
{
	// Initialisierung des Tasks
	brsmemset((UDINT)&ClientVarsSubscription, 0, sizeof(ClientVarsSubscription)); // Auf diese Variablen werden die vom Server geschickten Werte geschrieben
	fbTrigger.PT = 1000; // = 1000ms
	brsmemset((UDINT)&ClientVarsRead, 0, sizeof(ClientVarsRead)); // Auf diese Variablen werden die vom Server gelesenen Werte geschrieben
	brsmemset((UDINT)&ReceivedEvent, 0, sizeof(ReceivedEvent)); // Auf diese Variablen werden die vom Server empfangenen Event-Felder geschrieben

	// Initialisierung der Schrittkette
	Step.eStepNr = eSTEP_INIT;
	bStartClient = 1; // Der Client startet erst, wenn auf 1. Kann zum Debugging auf 0 gesetzt werden.

	// Vorbesetzen der Konfiguration
	brsstrcpy((UDINT)&ClientCfg.Connection.sServerEndpointUrl, (UDINT)&"opc.tcp://localhost:4840");
	ClientCfg.Connection.UserIdentityToken.UserIdentityTokenType = UAUITT_Username;
	brsstrcpy((UDINT)&ClientCfg.Connection.UserIdentityToken.TokenParam1, (UDINT)&"Admin");
	brsstrcpy((UDINT)&ClientCfg.Connection.UserIdentityToken.TokenParam2, (UDINT)&"admin");
	ClientCfg.Connection.tSessionTimeout = 30000; // [ms] = 30s
	ClientCfg.Connection.tMonitorConnection = 1000; // [ms] = 1s

	brsstrcpy((UDINT)&ClientCfg.Subscriptions.sNamespaceUriOrg, (UDINT)&"http://opcfoundation.org/UA/"); // NamespaceUri für den Namespace der Foundation
	//brsstrcpy((UDINT)&ClientCfg.Subscriptions.sNamespaceUriBrPv, (UDINT)&"urn:B&R/pv/"); // NamespaceUri für B&R V1.0
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.sNamespaceUriBrPv, (UDINT)&"http://br-automation.com/OpcUa/PLC/PV/"); // NamespaceUri für B&R V2.0

	nSubscriptionIndex = 0;
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].tPublishingInterval = 500; // = 500ms
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].nPriority = 200; // 0..255: Je größer, desto höher die Priorität
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[0].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.bBool");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[0].sVarName, (UDINT)&"::ClientC:ClientVarsSubscription.bBool");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[1].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.nUsint");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[1].sVarName, (UDINT)&"::ClientC:ClientVarsSubscription.nUsint");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[2].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.nUint");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[2].sVarName, (UDINT)&"::ClientC:ClientVarsSubscription.nUint");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[3].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.nUdint");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[3].sVarName, (UDINT)&"::ClientC:ClientVarsSubscription.nUdint");
		
	nSubscriptionIndex = 1;
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].tPublishingInterval = 1000; // = 1000ms = 1s
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].nPriority = 100; // 0..255: Je größer, desto höher die Priorität
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[0].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.nSint");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[0].sVarName, (UDINT)&"::ClientC:ClientVarsSubscription.nSint");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[1].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.nInt");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[1].sVarName, (UDINT)&"::ClientC:ClientVarsSubscription.nInt");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[2].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.nDint");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[2].sVarName, (UDINT)&"::ClientC:ClientVarsSubscription.nDint");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[3].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.rReal");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[3].sVarName, (UDINT)&"::ClientC:ClientVarsSubscription.rReal");

	nSubscriptionIndex = 2;
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].tPublishingInterval = 2000; // = 2000ms = 2s
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].nPriority = 50; // 0..255: Je größer, desto höher die Priorität
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[0].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.rLongReal");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[0].sVarName, (UDINT)&"::ClientC:ClientVarsSubscription.rLongReal");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[1].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.sString");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[1].sVarName, (UDINT)&"::ClientC:ClientVarsSubscription.sString");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[2].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.tTime");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[2].sVarName, (UDINT)&"::ClientC:ClientVarsSubscription.tTime");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[3].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.dtDateTime");
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[3].sVarName, (UDINT)&"::ClientC:ClientVarsSubscription.dtDateTime");

	MonitoredItemParameter.SamplingInterval = 0; // Wird von Subscription.PublishingInterval abgeleitet
	MonitoredItemParameter.QueueSize = 0; // Wenn > 0, dann müsste zyklisch der FB 'UA_MonitoredItemOperateList' für jede Subscription ausgeführt werden
	MonitoredItemParameter.DiscardOldest = 1;
	MonitoredItemParameter.DeadbandType = UADeadbandType_None;
	MonitoredItemParameter.Deadband = 0.0f;
	for(nSubscriptionIndex=0; nSubscriptionIndex<=(INT)nCLIENT_SUBSCRIPTION_INDEX_MAX; nSubscriptionIndex++)
	{
		for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_MONITORED_ITEM_INDEX_MAX; nItemIndex++)
		{
			ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[nItemIndex].NodeId.NamespaceIndex = 0; // Der NamespaceIndex wird später einmalig ermiitelt und dann zugewiesen
			ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[nItemIndex].NodeId.IdentifierType = UAIdentifierType_String;
		}
	}

	ClientCfg.Subscriptions.SubEvt.tPublishingInterval = 100; // = 100ms
	ClientCfg.Subscriptions.SubEvt.nPriority = 250; // 0..255: Je größer, desto höher die Priorität
	ClientCfg.Subscriptions.SubEvt.NotifierNodeId.IdentifierType = UAIdentifierType_Numeric;
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubEvt.NotifierNodeId.Identifier, (UDINT)&"2253"); // Root/Objects/Server
	ClientCfg.Subscriptions.SubEvt.EventTypeNodeId.IdentifierType = UAIdentifierType_Numeric;
	brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubEvt.EventTypeNodeId.Identifier, (UDINT)&"11436"); // Root/Types/EventTypes/BaseEventType/ProgressEventType
	
	brsmemset((UDINT)&asReadVars, 0, sizeof(asReadVars));
	brsstrcpy((UDINT)&ClientCfg.Read.Item[0].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.nUdint");
	brsstrcpy((UDINT)&ClientCfg.Read.Item[0].sVarName, (UDINT)&"::ClientC:ClientVarsRead.nUdint");
	brsstrcpy((UDINT)&ClientCfg.Read.Item[1].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.nDint");
	brsstrcpy((UDINT)&ClientCfg.Read.Item[1].sVarName, (UDINT)&"::ClientC:ClientVarsRead.nDint");
	brsstrcpy((UDINT)&ClientCfg.Read.Item[2].NodeId.Identifier, (UDINT)&"::ServerData:VarsLocal.ReadOnly.anInt");
	brsstrcpy((UDINT)&ClientCfg.Read.Item[2].sVarName, (UDINT)&"::ClientC:ClientVarsRead.anInt");
	for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_READ_ITEM_INDEX_MAX; nItemIndex++)
	{
		ClientCfg.Read.Item[nItemIndex].NodeId.NamespaceIndex = 0; // Der NamespaceIndex wird später einmalig ermiitelt und dann zugewiesen
		ClientCfg.Read.Item[nItemIndex].NodeId.IdentifierType = UAIdentifierType_String;
	}

	brsmemset((UDINT)&asWriteVars, 0, sizeof(asWriteVars));
	brsstrcpy((UDINT)&ClientCfg.Write.Item[0].NodeId.Identifier, (UDINT)&"::ServerData:WriteC.nUdint");
	brsstrcpy((UDINT)&ClientCfg.Write.Item[0].sVarName, (UDINT)&"::ClientC:ClientVarsRead.nUdint");
	brsstrcpy((UDINT)&ClientCfg.Write.Item[1].NodeId.Identifier, (UDINT)&"::ServerData:WriteC.nDint");
	brsstrcpy((UDINT)&ClientCfg.Write.Item[1].sVarName, (UDINT)&"::ClientC:ClientVarsRead.nDint");
	brsstrcpy((UDINT)&ClientCfg.Write.Item[2].NodeId.Identifier, (UDINT)&"::ServerData:WriteC.anInt");
	brsstrcpy((UDINT)&ClientCfg.Write.Item[2].sVarName, (UDINT)&"::ClientC:ClientVarsRead.anInt");
	for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_WRITE_ITEM_INDEX_MAX; nItemIndex++)
	{
		ClientCfg.Write.Item[nItemIndex].NodeId.NamespaceIndex = 0; // Der NamespaceIndex wird später einmalig ermiitelt und dann zugewiesen
		ClientCfg.Write.Item[nItemIndex].NodeId.IdentifierType = UAIdentifierType_String;
	}
	
	brsmemset((UDINT)&MethCalculateArgs, 0, sizeof(MethCalculateArgs));
	brsstrcpy((UDINT)&ClientCfg.Methods.Method[0].ObjectNodeId.Identifier, (UDINT)&"::SrvMethC"); // Task-Node
	brsstrcpy((UDINT)&ClientCfg.Methods.Method[0].MethodNodeId.Identifier, (UDINT)&"::SrvMethC:Calculate"); // Method-Node
	brsstrcpy((UDINT)&ClientCfg.Methods.Method[0].ArgumentsIn[0].Name, (UDINT)&"nValue0"); // Name des Eingans wie in der Methode deklariert
	brsstrcpy((UDINT)&ClientCfg.Methods.Method[0].ArgumentsIn[0].Value, (UDINT)&"::ClientC:MethCalculateArgs.In.nVal0"); // Name der Variable, auf die der Wert des Eingang geschrieben wird
	brsstrcpy((UDINT)&ClientCfg.Methods.Method[0].ArgumentsIn[1].Name, (UDINT)&"nValue1");
	brsstrcpy((UDINT)&ClientCfg.Methods.Method[0].ArgumentsIn[1].Value, (UDINT)&"::ClientC:MethCalculateArgs.In.nVal1");
	brsstrcpy((UDINT)&ClientCfg.Methods.Method[0].ArgumentsIn[2].Name, (UDINT)&"anArrayIn");
	brsstrcpy((UDINT)&ClientCfg.Methods.Method[0].ArgumentsIn[2].Value, (UDINT)&"::ClientC:MethCalculateArgs.In.anArray");
	brsstrcpy((UDINT)&ClientCfg.Methods.Method[0].ArgumentsOut[0].Name, (UDINT)&"nAddition"); // Name des Ausgangs wie in der Methode deklariert
	brsstrcpy((UDINT)&ClientCfg.Methods.Method[0].ArgumentsOut[0].Value, (UDINT)&"::ClientC:MethCalculateArgs.Out.nAddition"); // Name der Variable, von der der Wert des Ausgangs genommen wird
	brsstrcpy((UDINT)&ClientCfg.Methods.Method[0].ArgumentsOut[1].Name, (UDINT)&"nMultiplication");
	brsstrcpy((UDINT)&ClientCfg.Methods.Method[0].ArgumentsOut[1].Value, (UDINT)&"::ClientC:MethCalculateArgs.Out.nMultiplication");
	brsstrcpy((UDINT)&ClientCfg.Methods.Method[0].ArgumentsOut[2].Name, (UDINT)&"anArrayOut");
	brsstrcpy((UDINT)&ClientCfg.Methods.Method[0].ArgumentsOut[2].Value, (UDINT)&"::ClientC:MethCalculateArgs.Out.anArray");
	for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_METHODS_INDEX_MAX; nItemIndex++)
	{
		ClientCfg.Methods.Method[0].ObjectNodeId.NamespaceIndex = 0; // Der NamespaceIndex wird später einmalig ermiitelt und dann zugewiesen
		ClientCfg.Methods.Method[0].ObjectNodeId.IdentifierType = UAIdentifierType_String;
		ClientCfg.Methods.Method[0].MethodNodeId.NamespaceIndex = 0; // Der NamespaceIndex wird später einmalig ermiitelt und dann zugewiesen
		ClientCfg.Methods.Method[0].MethodNodeId.IdentifierType = UAIdentifierType_String;
	}

	// Ablöschen der Funktionsblöcke und Strukturen 
	brsmemset((UDINT)&fbUA_ConnectionGetStatus, 0, sizeof(fbUA_ConnectionGetStatus));
	brsmemset((UDINT)&fbUA_Connect, 0, sizeof(fbUA_Connect));
	brsmemset((UDINT)&fbUA_Disconnect, 0, sizeof(fbUA_Disconnect));
	brsmemset((UDINT)&fbUA_GetNamespaceIndex, 0, sizeof(fbUA_GetNamespaceIndex));
	brsmemset((UDINT)&fbUA_SubscriptionCreate, 0, sizeof(fbUA_SubscriptionCreate));
	brsmemset((UDINT)&fbUA_NodeGetHandleList, 0, sizeof(fbUA_NodeGetHandleList));
	brsmemset((UDINT)&fbUA_MonitoredItemAddList, 0, sizeof(fbUA_MonitoredItemAddList));
	brsmemset((UDINT)&fbUA_NodeGetHandle, 0, sizeof(fbUA_NodeGetHandle));
	brsmemset((UDINT)&fbUA_EventItemAdd, 0, sizeof(fbUA_EventItemAdd));
	brsmemset((UDINT)&fbUA_MethodGetHandle, 0, sizeof(fbUA_MethodGetHandle));
	brsmemset((UDINT)&fbUA_ReadList, 0, sizeof(fbUA_ReadList));
	brsmemset((UDINT)&fbUA_WriteList, 0, sizeof(fbUA_WriteList));
	brsmemset((UDINT)&fbUA_MethodCall, 0, sizeof(fbUA_MethodCall));
	brsmemset((UDINT)&fbUA_EventItemOperate, 0, sizeof(fbUA_EventItemOperate));
}

void _CYCLIC Cyclic(void)
{
	// Schrittkette
	switch(Step.eStepNr)
	{
		case eSTEP_NONE:
			break;

		case eSTEP_INIT:
			if(bStartClient == 1)
			{
				Step.eStepNr = eSTEP_CONNECT;
			}
			break;

		// -----------------------------------------------------------------------------------------------------------------------------------------------
		case eSTEP_CONNECT:
			// Hier wird die Verbindung zum Server aufgebaut.
			brsmemset((UDINT)&fbUA_Connect, 0, sizeof(fbUA_Connect));
			fbUA_Connect.Execute = 1;
			brsstrcpy((UDINT)&fbUA_Connect.ServerEndpointUrl, (UDINT)&ClientCfg.Connection.sServerEndpointUrl);
			brsstrcpy((UDINT)&fbUA_Connect.SessionConnectInfo.SessionName, (UDINT)&"SampleClientC_Session");
			brsstrcpy((UDINT)&fbUA_Connect.SessionConnectInfo.ApplicationName, (UDINT)&"SampleClientC_Application");
			fbUA_Connect.SessionConnectInfo.SecurityMsgMode = UASecurityMsgMode_None; // Ohne Security
			fbUA_Connect.SessionConnectInfo.SecurityPolicy = UASecurityPolicy_None; // Ohne Security
			brsstrcpy((UDINT)&fbUA_Connect.SessionConnectInfo.CertificateStore, (UDINT)&"SslCfgOpcUaClient"); // Angabe der SSL-Configuration unter 'ConfigurationView/AccessAndSecurity/TransortLayerSecurity/OpcUaCfg.sslcfg'
			brsstrcpy((UDINT)&fbUA_Connect.SessionConnectInfo.ClientCertificateName, (UDINT)&""); // Muss leer bleiben
			brsstrcpy((UDINT)&fbUA_Connect.SessionConnectInfo.ServerUri, (UDINT)&""); // Kann leer bleiben
			fbUA_Connect.SessionConnectInfo.CheckServerCertificate = 0;
			fbUA_Connect.SessionConnectInfo.TransportProfile = UATP_UATcp;
			brsmemcpy((UDINT)&fbUA_Connect.SessionConnectInfo.UserIdentityToken, (UDINT)&ClientCfg.Connection.UserIdentityToken, sizeof(UAUserIdentityToken));
			brsstrcpy((UDINT)&fbUA_Connect.SessionConnectInfo.VendorSpecificParameter, (UDINT)&""); // Kann leer bleiben
			fbUA_Connect.SessionConnectInfo.SessionTimeout = ClientCfg.Connection.tSessionTimeout;
			fbUA_Connect.SessionConnectInfo.MonitorConnection = ClientCfg.Connection.tMonitorConnection;
			brsstrcpy((UDINT)&fbUA_Connect.SessionConnectInfo.LocaleIDs[0], (UDINT)&"de");
			fbUA_Connect.Timeout = tFB_TIMEOUT;
			nConnectionHandle = 0;
			Step.eStepNr = eSTEP_CONNECT_WAIT;
			break;

		case eSTEP_CONNECT_WAIT:
			// Aufruf abwarten
			if(fbUA_Connect.Busy == 0)
			{
				fbUA_Connect.Execute = 0;
				if(fbUA_Connect.Done == 1)
				{
					nConnectionHandle = fbUA_Connect.ConnectionHdl;
					Step.eStepNr = eSTEP_GET_NAMESPACEIDX_ORG;
				}
				else if(fbUA_Connect.Error == 1)
				{
					// Ständig versuchen, die Verbindung aufzubauen
					nConnectionHandle = 0;
					Step.eStepNr = eSTEP_CONNECT;
				}
			}
			break;
		
		// -----------------------------------------------------------------------------------------------------------------------------------------------
		case eSTEP_GET_NAMESPACEIDX_ORG:
			// Hier wird der Namespace-Uri vom Server in einen Index übersetzt (für den Namespace der Foundation)
			brsmemset((UDINT)&fbUA_GetNamespaceIndex, 0, sizeof(fbUA_GetNamespaceIndex));
			fbUA_GetNamespaceIndex.Execute = 1;
			fbUA_GetNamespaceIndex.ConnectionHdl = nConnectionHandle;
			brsstrcpy((UDINT)&fbUA_GetNamespaceIndex.NamespaceUri, (UDINT)&ClientCfg.Subscriptions.sNamespaceUriOrg);
			fbUA_GetNamespaceIndex.Timeout = tFB_TIMEOUT;
			Step.eStepNr = eSTEP_GET_NAMESPACEIDX_ORG_WAIT;
			break;
		
		case eSTEP_GET_NAMESPACEIDX_ORG_WAIT:
			// Aufruf abwarten
			if(fbUA_GetNamespaceIndex.Busy == 0)
			{
				fbUA_GetNamespaceIndex.Execute = 0;
				if(fbUA_GetNamespaceIndex.Done == 1)
				{
					ClientCfg.Subscriptions.nNamespaceUriOrg = fbUA_GetNamespaceIndex.NamespaceIndex;
					ClientCfg.Subscriptions.SubEvt.NotifierNodeId.NamespaceIndex = ClientCfg.Subscriptions.nNamespaceUriOrg;
					ClientCfg.Subscriptions.SubEvt.EventTypeNodeId.NamespaceIndex = ClientCfg.Subscriptions.nNamespaceUriOrg;
					Step.eStepNr = eSTEP_GET_NAMESPACEIDX_BRPV;
				}
				else if(fbUA_GetNamespaceIndex.Error == 1)
				{
					Step.eErrorStep = Step.eStepNr;
					Step.nSubscriptionIndex = -1;
					Step.nItemIndex = -1;
					Step.nErrorId = fbUA_GetNamespaceIndex.ErrorID;
					Step.eStepNr = eSTEP_PAR_ERROR;
				}
			}
			break;
		
		case eSTEP_GET_NAMESPACEIDX_BRPV:
			// Hier wird der Namespace-Uri vom Server in einen Index übersetzt.	Bei B&R-PV ist nur ein Namespace benötigt.
			brsmemset((UDINT)&fbUA_GetNamespaceIndex, 0, sizeof(fbUA_GetNamespaceIndex));
			fbUA_GetNamespaceIndex.Execute = 1;
			fbUA_GetNamespaceIndex.ConnectionHdl = nConnectionHandle;
			brsstrcpy((UDINT)&fbUA_GetNamespaceIndex.NamespaceUri, (UDINT)&ClientCfg.Subscriptions.sNamespaceUriBrPv);
			fbUA_GetNamespaceIndex.Timeout = tFB_TIMEOUT;
			Step.eStepNr = eSTEP_GET_NAMESPACEIDX_BRPV_WAIT;
			break;
		
		case eSTEP_GET_NAMESPACEIDX_BRPV_WAIT:
			// Aufruf abwarten
			if(fbUA_GetNamespaceIndex.Busy == 0)
			{
				fbUA_GetNamespaceIndex.Execute = 0;
				if(fbUA_GetNamespaceIndex.Done == 1)
				{
					ClientCfg.Subscriptions.nNamespaceUriBrPv = fbUA_GetNamespaceIndex.NamespaceIndex;
					// NamespaceIndex auf alle MonitoredItems übernehmen
					for(nSubscriptionIndex=0; nSubscriptionIndex<=(INT)nCLIENT_SUBSCRIPTION_INDEX_MAX; nSubscriptionIndex++)
					{
						for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_MONITORED_ITEM_INDEX_MAX; nItemIndex++)
						{
							ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[nItemIndex].NodeId.NamespaceIndex = fbUA_GetNamespaceIndex.NamespaceIndex;
						}
					}
					// NamespaceIndex auf alle ReadItems übernehmen
					for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_READ_ITEM_INDEX_MAX; nItemIndex++)
					{
						ClientCfg.Read.Item[nItemIndex].NodeId.NamespaceIndex = fbUA_GetNamespaceIndex.NamespaceIndex;
					}
					// NamespaceIndex auf alle WriteItems übernehmen
					for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_WRITE_ITEM_INDEX_MAX; nItemIndex++)
					{
						ClientCfg.Write.Item[nItemIndex].NodeId.NamespaceIndex = fbUA_GetNamespaceIndex.NamespaceIndex;
					}
					// NamespaceIndex auf alle Methods übernehmen
					for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_METHODS_INDEX_MAX; nItemIndex++)
					{
						ClientCfg.Methods.Method[nItemIndex].MethodNodeId.NamespaceIndex = fbUA_GetNamespaceIndex.NamespaceIndex;
						ClientCfg.Methods.Method[nItemIndex].ObjectNodeId.NamespaceIndex = fbUA_GetNamespaceIndex.NamespaceIndex;
					}
					Step.eStepNr = eSTEP_CREATE_SUBSCRIPTIONS_VAR;
				}
				else if(fbUA_GetNamespaceIndex.Error == 1)
				{
					Step.eErrorStep = Step.eStepNr;
					Step.nSubscriptionIndex = -1;
					Step.nItemIndex = -1;
					Step.nErrorId = fbUA_GetNamespaceIndex.ErrorID;
					Step.eStepNr = eSTEP_PAR_ERROR;
				}
			}
			break;
		
		// -----------------------------------------------------------------------------------------------------------------------------------------------
		case eSTEP_CREATE_SUBSCRIPTIONS_VAR:
			nSubscriptionIndex = -1; // Mit der ersten Subscription beginnen
			Step.eStepNr = eSTEP_CREATE_SUBSCRIPTION_VAR;
			break;
		
		case eSTEP_CREATE_SUBSCRIPTION_VAR:
			// Nächstes Subscription hinzufügen
			nSubscriptionIndex += 1;
			if(nSubscriptionIndex <= (INT)nCLIENT_SUBSCRIPTION_INDEX_MAX)
			{
				// Nächste Subscription anlegen
				brsmemset((UDINT)&fbUA_SubscriptionCreate, 0, sizeof(fbUA_SubscriptionCreate));
				fbUA_SubscriptionCreate.Execute = 1;
				fbUA_SubscriptionCreate.ConnectionHdl = nConnectionHandle;
				fbUA_SubscriptionCreate.PublishingEnable = 1;
				fbUA_SubscriptionCreate.Priority = ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].nPriority;
				fbUA_SubscriptionCreate.Timeout = tFB_TIMEOUT;
				fbUA_SubscriptionCreate.PublishingInterval = &ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].tPublishingInterval;
				Step.eStepNr = eSTEP_CREATE_SUBSCRIPT_VAR_WAIT;
			}
			else
			{
				// Alle Subscriptions angelegt
				if(Step.nErrorId != 0)
				{
					Step.eStepNr = eSTEP_PAR_ERROR;
				}
				else
				{
					Step.eStepNr = eSTEP_CREATE_SUBSCRIPTION_EVT;
				}
			}
			break;
		
		case eSTEP_CREATE_SUBSCRIPT_VAR_WAIT:
			// Aufruf abwarten
			if(fbUA_SubscriptionCreate.Busy == 0)
			{
				fbUA_SubscriptionCreate.Execute = 0;
				if(fbUA_SubscriptionCreate.Done == 1)
				{
					Step.eStepNr = eSTEP_SUB_GET_NODE_HDL_LIST;
				}
				else if(fbUA_SubscriptionCreate.Error == 1)
				{
					// Fehler eintragen, aber trotzdem mit der nächsten Subcription weiter machen
					Step.eErrorStep = Step.eStepNr;
					Step.nSubscriptionIndex = nSubscriptionIndex;
					Step.nItemIndex = -1;
					Step.nErrorId = fbUA_SubscriptionCreate.ErrorID;
					Step.eStepNr = eSTEP_CREATE_SUBSCRIPTION_VAR;
				}
			}
			break;
				
		case eSTEP_SUB_GET_NODE_HDL_LIST:
			// Die Handles für die MonitoredItems ermitteln
			brsmemset((UDINT)&fbUA_NodeGetHandleList, 0, sizeof(fbUA_NodeGetHandleList));
			fbUA_NodeGetHandleList.Execute = 1;
			fbUA_NodeGetHandleList.ConnectionHdl = nConnectionHandle;
			for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_MONITORED_ITEM_INDEX_MAX; nItemIndex++)
			{
				if(brsstrlen((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[nItemIndex].NodeId.Identifier) > 0)
				{
					brsmemcpy((UDINT)&fbUA_NodeGetHandleList.NodeIDs[nItemIndex], (UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[nItemIndex].NodeId, sizeof(UANodeID));
				}
				else
				{
					break;
				}
			}
			fbUA_NodeGetHandleList.NodeIDCount = (UINT)nItemIndex;
			fbUA_NodeGetHandleList.Timeout = tFB_TIMEOUT;
			Step.eStepNr = eSTEP_SUB_GET_NODE_HDL_LIST_WAIT;
			break;
		
		case eSTEP_SUB_GET_NODE_HDL_LIST_WAIT:
			// Aufruf abwarten
			if(fbUA_NodeGetHandleList.Busy == 0)
			{
				fbUA_NodeGetHandleList.Execute = 0;
				if(fbUA_NodeGetHandleList.Done == 1)
				{
					Step.eStepNr = eSTEP_ADD_MONITORED_ITEMS;
				}
				else if(fbUA_NodeGetHandleList.Error == 1)
				{
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep = Step.eStepNr;
					Step.nSubscriptionIndex = nSubscriptionIndex;
					if(fbUA_NodeGetHandleList.ErrorID != 0)
					{
						Step.nErrorId = fbUA_NodeGetHandleList.ErrorID;
					}
					else
					{
						for(nItemIndex=0; nItemIndex<=(INT)MAX_INDEX_NODELIST; nItemIndex++)
						{
							if(fbUA_NodeGetHandleList.NodeErrorIDs[nItemIndex] != 0)
							{
								Step.nItemIndex = nItemIndex;
								Step.nErrorId = fbUA_NodeGetHandleList.NodeErrorIDs[nItemIndex];
								break;
							}
						}
					}
					Step.eStepNr = eSTEP_CREATE_SUBSCRIPTION_VAR;
				}
			}
			break;
			
		case eSTEP_ADD_MONITORED_ITEMS:
			// MonitoredItems hinzufügen
			brsmemset((UDINT)&fbUA_MonitoredItemAddList, 0, sizeof(fbUA_MonitoredItemAddList));
			fbUA_MonitoredItemAddList.Execute = 1;
			fbUA_MonitoredItemAddList.SubscriptionHdl = fbUA_SubscriptionCreate.SubscriptionHdl;
			for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_MONITORED_ITEM_INDEX_MAX; nItemIndex++)
			{
				if(brsstrlen((UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[nItemIndex].NodeId.Identifier) > 0)
				{
					fbUA_MonitoredItemAddList.NodeHdls[nItemIndex] = fbUA_NodeGetHandleList.NodeHdls[nItemIndex];
					fbUA_MonitoredItemAddList.NodeAddInfos[nItemIndex].AttributeId = UAAI_Value; // Es ist möglich, alle Attribute eines Nodes zu adressieren, aber normalerweise wird natürlich das Attribut 'Value' benötigt
					fbUA_MonitoredItemAddList.NodeAddInfos[nItemIndex].IndexRangeCount = 0; // Nur Einzel-Variablen, keine Arrays
					brsmemset((UDINT)&fbUA_MonitoredItemAddList.NodeAddInfos[nItemIndex].IndexRange, 0, sizeof(fbUA_MonitoredItemAddList.NodeAddInfos[nItemIndex].IndexRange));
					brsstrcpy((UDINT)&asMonitoredItemVarNames[nItemIndex], (UDINT)&ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[nItemIndex].sVarName);
					brsmemcpy((UDINT)&aMonitoredItemParameter[nItemIndex], (UDINT)&MonitoredItemParameter, sizeof(MonitoredItemParameter));
					aMonitoredItemParameter[nItemIndex].SamplingInterval = ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].tPublishingInterval; // Nur das SamplingInterval wird von der Subscription abgeleitet
				}
				else
				{
					break;
				}
			}
			fbUA_MonitoredItemAddList.NodeHdlCount = (UINT)nItemIndex;
			fbUA_MonitoredItemAddList.Timeout = tFB_TIMEOUT;
			fbUA_MonitoredItemAddList.Variables = &asMonitoredItemVarNames;
			fbUA_MonitoredItemAddList.MonitoringSettings = &aMonitoredItemParameter;
			fbUA_MonitoredItemAddList.ValuesChanged = &abMonItemValuesChanged;
			fbUA_MonitoredItemAddList.RemainingValueCount = &anMonItemRemainingValueCount;
			fbUA_MonitoredItemAddList.TimeStamps = &adtMonItemTimeStamps;
			fbUA_MonitoredItemAddList.NodeQualityIDs = &anMonItemNodeQualityId;
			Step.eStepNr = eSTEP_ADD_MONITORED_ITEMS_WAIT;
			break;
		
		case eSTEP_ADD_MONITORED_ITEMS_WAIT:
		// Aufruf abwarten
		if(fbUA_MonitoredItemAddList.Busy == 0)
		{
			fbUA_MonitoredItemAddList.Execute = 0;
			if(fbUA_MonitoredItemAddList.Done == 1)
			{
				Step.eStepNr = eSTEP_CREATE_SUBSCRIPTION_VAR;
			}
			else if(fbUA_MonitoredItemAddList.Error == 1)
			{
				// Fehler eintragen, aber trotzdem weiter machen
				Step.eErrorStep = Step.eStepNr;
				Step.nSubscriptionIndex = nSubscriptionIndex;
				if(fbUA_MonitoredItemAddList.ErrorID != 0)
				{
					Step.nItemIndex = -1;
					Step.nErrorId = fbUA_MonitoredItemAddList.ErrorID;
				}
				else
				{
					for(nItemIndex=0; nItemIndex<=(INT)MAX_INDEX_NODELIST; nItemIndex++)
					{
						if(fbUA_MonitoredItemAddList.NodeErrorIDs[nItemIndex] != 0)
						{
							Step.nItemIndex = nItemIndex;
							Step.nErrorId = fbUA_MonitoredItemAddList.NodeErrorIDs[nItemIndex];
							break;
						}
					}
				}
				Step.eStepNr = eSTEP_CREATE_SUBSCRIPTION_VAR;
			}
		}
		break;

		// -----------------------------------------------------------------------------------------------------------------------------------------------
		case eSTEP_CREATE_SUBSCRIPTION_EVT:
			// Subscription für Event hinzufügen
			brsmemset((UDINT)&fbUA_SubscriptionCreate, 0, sizeof(fbUA_SubscriptionCreate));
			fbUA_SubscriptionCreate.Execute = 1;
			fbUA_SubscriptionCreate.ConnectionHdl = nConnectionHandle;
			fbUA_SubscriptionCreate.PublishingEnable = 1;
			fbUA_SubscriptionCreate.Priority = ClientCfg.Subscriptions.SubEvt.nPriority;
			fbUA_SubscriptionCreate.Timeout = tFB_TIMEOUT;
			fbUA_SubscriptionCreate.PublishingInterval = &ClientCfg.Subscriptions.SubEvt.tPublishingInterval;
			Step.eStepNr = eSTEP_CREATE_SUBSCRIPT_EVT_WAIT;
			break;
		
		case eSTEP_CREATE_SUBSCRIPT_EVT_WAIT:
			// Aufruf abwarten
			if(fbUA_SubscriptionCreate.Busy == 0)
			{
				fbUA_SubscriptionCreate.Execute = 0;
				if(fbUA_SubscriptionCreate.Done == 1)
				{
					Step.eStepNr = eSTEP_EVT_GET_NODE_HDL;
				}
				else if(fbUA_SubscriptionCreate.Error == 1)
				{
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep = Step.eStepNr;
					Step.nSubscriptionIndex = -1;
					Step.nItemIndex = -1;
					Step.nErrorId = fbUA_SubscriptionCreate.ErrorID;
					Step.eStepNr = eSTEP_RD_GET_NODE_HDL_LIST;
				}
			}
			break;
		
		case eSTEP_EVT_GET_NODE_HDL:
			brsmemset((UDINT)&fbUA_NodeGetHandle, 0, sizeof(fbUA_NodeGetHandle));
			fbUA_NodeGetHandle.Execute = 1;
			fbUA_NodeGetHandle.ConnectionHdl = nConnectionHandle;
			brsmemcpy((UDINT)&fbUA_NodeGetHandle.NodeID, (UDINT)&ClientCfg.Subscriptions.SubEvt.NotifierNodeId, sizeof(UANodeID)); // Root/Objects/Server
			fbUA_NodeGetHandle.Timeout = tFB_TIMEOUT;
			Step.eStepNr = eSTEP_EVT_GET_NODE_HDL_WAIT;
			break;
		
		case eSTEP_EVT_GET_NODE_HDL_WAIT:
			// Aufruf abwarten
			if(fbUA_NodeGetHandle.Busy == 0)
			{
				fbUA_NodeGetHandle.Execute = 0;
				if(fbUA_NodeGetHandle.Done == 1)
				{
					Step.eStepNr = eSTEP_ADD_EVENT_ITEM;
				}
				else if(fbUA_NodeGetHandle.Error == 1)
				{
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep = Step.eStepNr;
					Step.nSubscriptionIndex = -1;
					Step.nErrorId = fbUA_NodeGetHandle.ErrorID;
					Step.eStepNr = eSTEP_RD_GET_NODE_HDL_LIST;
				}
			}
			break;
		
		case eSTEP_ADD_EVENT_ITEM:
			fbUA_EventItemAdd.Execute = 1;
			fbUA_EventItemAdd.SubscriptionHdl = fbUA_SubscriptionCreate.SubscriptionHdl;
			fbUA_EventItemAdd.NodeHdl = fbUA_NodeGetHandle.NodeHdl; // Root/Objects/Server
			// Event-Typ festlegen
			brsmemcpy((UDINT)&fbUA_EventItemAdd.EventType, (UDINT)&ClientCfg.Subscriptions.SubEvt.EventTypeNodeId, sizeof(UANodeID));
			// Zu sendende Felder festlegen
			// EventId
			nItemIndex = 0;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements = 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex = ClientCfg.Subscriptions.nNamespaceUriOrg;
			brsstrcpy((UDINT)&fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name, (UDINT)&"EventId");
			brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex], (UDINT)&"::ClientC:ReceivedEvent.EventId");
			// EventType
			nItemIndex += 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements = 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex = ClientCfg.Subscriptions.nNamespaceUriOrg;
			brsstrcpy((UDINT)&fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name, (UDINT)&"EventType");
			brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex], (UDINT)&"::ClientC:ReceivedEvent.EventType");
			// LocalTime
			nItemIndex += 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements = 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex = ClientCfg.Subscriptions.nNamespaceUriOrg;
			brsstrcpy((UDINT)&fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name, (UDINT)&"LocalTime");
			brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex], (UDINT)&"::ClientC:ReceivedEvent.LocalTime");
			// Message
			nItemIndex += 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements = 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex = ClientCfg.Subscriptions.nNamespaceUriOrg;
			brsstrcpy((UDINT)&fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name, (UDINT)&"Message");
			brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex], (UDINT)&"::ClientC:ReceivedEvent.Message");
			// ReceiveTime
			nItemIndex += 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements = 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex = ClientCfg.Subscriptions.nNamespaceUriOrg;
			brsstrcpy((UDINT)&fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name, (UDINT)&"ReceiveTime");
			brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex], (UDINT)&"::ClientC:ReceivedEvent.ReceiveTime");
			// Severity
			nItemIndex += 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements = 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex = ClientCfg.Subscriptions.nNamespaceUriOrg;
			brsstrcpy((UDINT)&fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name, (UDINT)&"Severity");
			brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex], (UDINT)&"::ClientC:ReceivedEvent.Severity");
			// SourceName
			nItemIndex += 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements = 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex = ClientCfg.Subscriptions.nNamespaceUriOrg;
			brsstrcpy((UDINT)&fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name, (UDINT)&"SourceName");
			brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex], (UDINT)&"::ClientC:ReceivedEvent.SourceName");
			// SourceNode
			nItemIndex += 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements = 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex = ClientCfg.Subscriptions.nNamespaceUriOrg;
			brsstrcpy((UDINT)&fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name, (UDINT)&"SourceNode");
			brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex], (UDINT)&"::ClientC:ReceivedEvent.SourceNode");
			// Time
			nItemIndex += 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements = 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex = ClientCfg.Subscriptions.nNamespaceUriOrg;
			brsstrcpy((UDINT)&fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name, (UDINT)&"Time");
			brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex], (UDINT)&"::ClientC:ReceivedEvent.Time");
			// Context
			nItemIndex += 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements = 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex = ClientCfg.Subscriptions.nNamespaceUriOrg;
			brsstrcpy((UDINT)&fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name, (UDINT)&"Context");
			brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex], (UDINT)&"::ClientC:ReceivedEvent.Context");
			// Progress
			nItemIndex += 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements = 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex = ClientCfg.Subscriptions.nNamespaceUriOrg;
			brsstrcpy((UDINT)&fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name, (UDINT)&"Progress");
			brsstrcpy((UDINT)&ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex], (UDINT)&"::ClientC:ReceivedEvent.Progress");
			fbUA_EventItemAdd.EventFieldSelectionCount = (UINT)(nItemIndex + 1);
			fbUA_EventItemAdd.Timeout = tFB_TIMEOUT;
			fbUA_EventItemAdd.EventFields = &ClientCfg.Subscriptions.SubEvt.EventFieldVarNames;
			Step.eStepNr = eSTEP_ADD_EVENT_ITEM_WAIT;
			break;
		
		case eSTEP_ADD_EVENT_ITEM_WAIT:
			// Aufruf abwarten
			if(fbUA_EventItemAdd.Busy == 0)
			{
				fbUA_EventItemAdd.Execute = 0;
				if(fbUA_EventItemAdd.Done == 1)
				{
					Step.eStepNr = eSTEP_RD_GET_NODE_HDL_LIST;
				}
				else if(fbUA_EventItemAdd.Error == 1)
				{
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep = Step.eStepNr;
					Step.nSubscriptionIndex = -1;
					Step.nErrorId = fbUA_EventItemAdd.ErrorID;
					Step.eStepNr = eSTEP_RD_GET_NODE_HDL_LIST;
				}
			}
			break;
			
		// -----------------------------------------------------------------------------------------------------------------------------------------------
		case eSTEP_RD_GET_NODE_HDL_LIST:
			// Die Handles für die ReadItems ermitteln
			brsmemset((UDINT)&fbUA_NodeGetHandleList, 0, sizeof(fbUA_NodeGetHandleList));
			fbUA_NodeGetHandleList.Execute = 1;
			fbUA_NodeGetHandleList.ConnectionHdl = nConnectionHandle;
			for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_READ_ITEM_INDEX_MAX; nItemIndex++)
			{
				if(brsstrlen((UDINT)&ClientCfg.Read.Item[nItemIndex].NodeId.Identifier) > 0)
				{
					brsmemcpy((UDINT)&fbUA_NodeGetHandleList.NodeIDs[nItemIndex], (UDINT)&ClientCfg.Read.Item[nItemIndex].NodeId, sizeof(UANodeID));
				}
				else
				{
					break;
				}
			}
			fbUA_NodeGetHandleList.NodeIDCount = (UINT)nItemIndex;
			fbUA_NodeGetHandleList.Timeout = tFB_TIMEOUT;
			Step.eStepNr = eSTEP_RD_GET_NODE_HDL_LIST_WAIT;
			break;
		
		case eSTEP_RD_GET_NODE_HDL_LIST_WAIT:
			// Aufruf abwarten
			if(fbUA_NodeGetHandleList.Busy == 0)
			{
				fbUA_NodeGetHandleList.Execute = 0;
				if(fbUA_NodeGetHandleList.Done == 1)
				{
					// Daten speichern
					for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_READ_ITEM_INDEX_MAX; nItemIndex++)
					{
						if(brsstrlen((UDINT)&ClientCfg.Read.Item[nItemIndex].NodeId.Identifier) > 0)
						{
							fbUA_ReadList.NodeHdls[nItemIndex] = fbUA_NodeGetHandleList.NodeHdls[nItemIndex];
							fbUA_ReadList.NodeAddInfo[nItemIndex].AttributeId = UAAI_Value;
							brsstrcpy((UDINT)&asReadVars[nItemIndex],  (UDINT)&ClientCfg.Read.Item[nItemIndex].sVarName);
						}
						else
						{
							break;
						}
					}
					fbUA_ReadList.NodeHdlCount = (UINT)nItemIndex;
					Step.eStepNr = eSTEP_WR_GET_NODE_HDL_LIST;
				}
				else if(fbUA_NodeGetHandleList.Error == 1)
				{
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep = Step.eStepNr;
					Step.nSubscriptionIndex = -1;
					if(fbUA_NodeGetHandleList.ErrorID != 0)
					{
						Step.nItemIndex = -1;
						Step.nErrorId = fbUA_NodeGetHandleList.ErrorID;
					}
					else
					{
						for(nItemIndex=0; nItemIndex<=(INT)MAX_INDEX_NODELIST; nItemIndex++)
						{
							if(fbUA_NodeGetHandleList.NodeErrorIDs[nItemIndex] != 0)
							{
								Step.nItemIndex = nItemIndex;
								Step.nErrorId = fbUA_NodeGetHandleList.NodeErrorIDs[nItemIndex];
								break;
							}
						}
					}
					nItemIndex = -1;
					Step.eStepNr = eSTEP_WR_GET_NODE_HDL_LIST;
				}
			}
			break;
			
		case eSTEP_WR_GET_NODE_HDL_LIST:
			// Die Handles für die WriteItems ermitteln
			brsmemset((UDINT)&fbUA_NodeGetHandleList, 0, sizeof(fbUA_NodeGetHandleList));
			fbUA_NodeGetHandleList.Execute = 1;
			fbUA_NodeGetHandleList.ConnectionHdl = nConnectionHandle;
			for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_WRITE_ITEM_INDEX_MAX; nItemIndex++)
			{
				if(brsstrlen((UDINT)&ClientCfg.Write.Item[nItemIndex].NodeId.Identifier) > 0)
				{
					brsmemcpy((UDINT)&fbUA_NodeGetHandleList.NodeIDs[nItemIndex], (UDINT)&ClientCfg.Write.Item[nItemIndex].NodeId, sizeof(UANodeID));
				}
				else
				{
					break;
				}
			}
			fbUA_NodeGetHandleList.NodeIDCount = (UINT)nItemIndex;
			fbUA_NodeGetHandleList.Timeout = tFB_TIMEOUT;
			Step.eStepNr = eSTEP_WR_GET_NODE_HDL_LIST_WAIT;
			break;
		
		case eSTEP_WR_GET_NODE_HDL_LIST_WAIT:
			// Aufruf abwarten
			if(fbUA_NodeGetHandleList.Busy == 0)
			{
				fbUA_NodeGetHandleList.Execute = 0;
				if(fbUA_NodeGetHandleList.Done == 1)
				{
					// Daten speichern
					for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_WRITE_ITEM_INDEX_MAX; nItemIndex++)
					{
						if(brsstrlen((UDINT)&ClientCfg.Write.Item[nItemIndex].NodeId.Identifier) > 0)
						{
							fbUA_WriteList.NodeHdls[nItemIndex] = fbUA_NodeGetHandleList.NodeHdls[nItemIndex];
							fbUA_WriteList.NodeAddInfo[nItemIndex].AttributeId = UAAI_Value;
							brsstrcpy((UDINT)&asWriteVars[nItemIndex],  (UDINT)&ClientCfg.Write.Item[nItemIndex].sVarName);
						}
						else
						{
							break;
						}
					}
					fbUA_WriteList.NodeHdlCount = (UINT)nItemIndex;
					Step.eStepNr = eSTEP_METH_GET_HANDLES;
				}
				else if(fbUA_NodeGetHandleList.Error == 1)
				{
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep = Step.eStepNr;
					Step.nSubscriptionIndex = -1;
					if(fbUA_NodeGetHandleList.ErrorID != 0)
					{
						Step.nItemIndex = -1;
						Step.nErrorId = fbUA_NodeGetHandleList.ErrorID;
					}
					else
					{
						for(nItemIndex=0; nItemIndex<=(INT)MAX_INDEX_NODELIST; nItemIndex++)
						{
							if(fbUA_NodeGetHandleList.NodeErrorIDs[nItemIndex] != 0)
							{
								Step.nItemIndex = nItemIndex;
								Step.nErrorId = fbUA_NodeGetHandleList.NodeErrorIDs[nItemIndex];
								break;
							}
						}
					}
					nItemIndex = -1;
					Step.eStepNr = eSTEP_METH_GET_HANDLES;
				}
			}
			break;

		// -----------------------------------------------------------------------------------------------------------------------------------------------
		case eSTEP_METH_GET_HANDLES:
			nMethodIndex = -1; // Mit der ersten Method beginnen
			Step.eStepNr = eSTEP_METH_GET_HANDLE;
			break;
		
		case eSTEP_METH_GET_HANDLE:
			// Nächstes Method-Handle ermitteln
			nMethodIndex += 1;
			if(nMethodIndex <= (INT)nCLIENT_METHODS_INDEX_MAX)
			{
				brsmemset((UDINT)&fbUA_MethodGetHandle, 0, sizeof(fbUA_MethodGetHandle));
				fbUA_MethodGetHandle.Execute = 1;
				fbUA_MethodGetHandle.ConnectionHdl = nConnectionHandle;
				brsmemcpy((UDINT)&fbUA_MethodGetHandle.ObjectNodeID, (UDINT)&ClientCfg.Methods.Method[nMethodIndex].ObjectNodeId, sizeof(UANodeID));
				brsmemcpy((UDINT)&fbUA_MethodGetHandle.MethodNodeID, (UDINT)&ClientCfg.Methods.Method[nMethodIndex].MethodNodeId, sizeof(UANodeID));
				fbUA_MethodGetHandle.Timeout = tFB_TIMEOUT;
				Step.eStepNr = eSTEP_METH_GET_HANDLE_WAIT;
			}
			else
			{
				// Alle Method-Handles ermittelt
				if(Step.nErrorId != 0)
				{
					Step.eStepNr = eSTEP_PAR_ERROR;
				}
				else
				{
					Step.eStepNr = eSTEP_RUNNING;
				}
			}
			break;
		
		case eSTEP_METH_GET_HANDLE_WAIT:
			// Aufruf abwarten
			if(fbUA_MethodGetHandle.Busy == 0)
			{
				fbUA_MethodGetHandle.Execute = 0;
				if(fbUA_MethodGetHandle.Done == 1)
				{
					anMethodHandles[nMethodIndex] = fbUA_MethodGetHandle.MethodHdl;
					Step.eStepNr = eSTEP_METH_GET_HANDLE;
				}
				else if(fbUA_MethodGetHandle.Error == 1)
				{
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep = Step.eStepNr;
					Step.nSubscriptionIndex = -1;
					Step.nItemIndex = nMethodIndex;
					Step.nErrorId = fbUA_MethodGetHandle.ErrorID;
					Step.eStepNr = eSTEP_METH_GET_HANDLE;
				}
			}
			break;
				
		// -----------------------------------------------------------------------------------------------------------------------------------------------
		case eSTEP_RUNNING:
			if(fbUA_ConnectionGetStatus.Execute == 1)
			{
				if(ConnectionStatus.eConnectionStatus != UACS_Connected)
				{
					// Der Server ist nicht mehr verbunden. In diesem Fall kann die Verbindung später vom Client automatisch wieder komplett reastauriert, wenn der Server wieder erreichbar ist.
					Step.eStepNr = eSTEP_CONNECTION_ERROR;
				}
				else
				{
					// Trigger für zyklisches Lesen + Schreiben
					fbTrigger.IN = 1;
					if(fbTrigger.Q == 1)
					{
						fbTrigger.IN = 0;
						Step.eStepNr = eSTEP_READ_LIST;
					}
				}
			}
			break;

		case eSTEP_PAR_ERROR:
			/*
				Es liegt eine Parameter-Fehler vor, bei dem die Schrittkette nicht weiter abgearbeitet werden kann.
				Der falsche Parameter muss behoben werden.
				Dieser ist unter der Struktur 'Step' einsehbar und kann in der AS-Hilfe nachgeschlagen werden.
				Tipp: Die ErrorId sollte in Hexadezimal-Format angezeigt werden, da die OpcUa-Fehler immer als Hex dokumentiert werden.
			*/
			break;

		case eSTEP_CONNECTION_ERROR:
			if(fbUA_ConnectionGetStatus.Execute == 1)
			{
				if(ConnectionStatus.eConnectionStatus == UACS_Connected)
				{
					// Die Verbindung konnte vom Client automatisch wieder komplett reastauriert werden (mit allen Subscriptions und MonitoredItems)
					Step.eStepNr = eSTEP_RUNNING;		
				}
			}
			break;

		// -----------------------------------------------------------------------------------------------------------------------------------------------
		case eSTEP_READ_LIST:
			// Achtung: Zyklisches Lesen (Polling) sollte niemals in einer Applikation implementiert werden! Stattdessen sollte unbedingt Subscription verwendet werden.
			// Dieses Beispiel soll lediglich die Besetzung des FB's veranschaulichen.
			if(ConnectionStatus.eConnectionStatus != UACS_Connected)
			{
				Step.eStepNr = eSTEP_RUNNING;
			}
			else
			{
				fbUA_ReadList.Execute = 1;
				fbUA_ReadList.ConnectionHdl = nConnectionHandle;
				fbUA_ReadList.Timeout = tFB_TIMEOUT;
				fbUA_ReadList.Variables = &asReadVars;
				Step.eStepNr = eSTEP_READ_LIST_WAIT;
			}
			break;

		case eSTEP_READ_LIST_WAIT:
			// Aufruf abwarten
			if(ConnectionStatus.eConnectionStatus != UACS_Connected)
			{
				fbUA_ReadList.Execute = 0;
				Step.eStepNr = eSTEP_RUNNING;
			}
			else
			{
				if(fbUA_ReadList.Busy == 0)
				{
					fbUA_ReadList.Execute = 0;
					if(fbUA_ReadList.Error == 1)
					{
						// Fehler eintragen, aber trotzdem weiter machen
						Step.eErrorStep = Step.eStepNr;
						Step.nSubscriptionIndex = -1;
						if(fbUA_ReadList.ErrorID != 0)
						{
							Step.nItemIndex = -1;
							Step.nErrorId = fbUA_ReadList.ErrorID;
						}
						else
						{
							for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_READ_ITEM_INDEX_MAX; nItemIndex++)
							{
								if(fbUA_ReadList.NodeErrorIDs[nItemIndex] != 0)
								{
									Step.nItemIndex = nItemIndex;
									Step.nErrorId = fbUA_ReadList.NodeErrorIDs[nItemIndex];
									break;
								}
							}
						}
					}
					Step.eStepNr = eSTEP_WRITE_LIST;
				}
			}
			break;
	
		case eSTEP_WRITE_LIST:
			if(ConnectionStatus.eConnectionStatus != UACS_Connected)
			{
				Step.eStepNr = eSTEP_RUNNING;
			}
			else
			{
				fbUA_WriteList.Execute = 1;
				fbUA_WriteList.ConnectionHdl = nConnectionHandle;
				fbUA_WriteList.Timeout = tFB_TIMEOUT;
				fbUA_WriteList.Variables = &asReadVars;
				Step.eStepNr = eSTEP_WRITE_LIST_WAIT;
			}
			break;

		case eSTEP_WRITE_LIST_WAIT:
			// Aufruf abwarten
			if(ConnectionStatus.eConnectionStatus != UACS_Connected)
			{
				fbUA_WriteList.Execute = 0;
				Step.eStepNr = eSTEP_RUNNING;
			}
			else
			{
				if(fbUA_WriteList.Busy == 0)
				{
					fbUA_WriteList.Execute = 0;
					if(fbUA_WriteList.Error == 1)
					{
						// Fehler eintragen, aber trotzdem weiter machen
						Step.eErrorStep = Step.eStepNr;
						Step.nSubscriptionIndex = -1;
						if(fbUA_WriteList.ErrorID != 0)
						{
							Step.nItemIndex = -1;
							Step.nErrorId = fbUA_WriteList.ErrorID;
						}
						else
						{
							for(nItemIndex=0; nItemIndex<=(INT)nCLIENT_WRITE_ITEM_INDEX_MAX; nItemIndex++)
							{
								if(fbUA_WriteList.NodeErrorIDs[nItemIndex] != 0)
								{
									Step.nItemIndex = nItemIndex;
									Step.nErrorId = fbUA_WriteList.NodeErrorIDs[nItemIndex];
									break;
								}
							}
						}
					}
					Step.eStepNr = eSTEP_CALL_METH_CALC;
				}
			}
			break;
	
		case eSTEP_CALL_METH_CALC:
			// Aufruf der Methode 'Calculate'
			if(ConnectionStatus.eConnectionStatus != UACS_Connected)
			{
				Step.eStepNr = eSTEP_RUNNING;
			}
			else
			{
				fbUA_MethodCall.Execute = 1;
				fbUA_MethodCall.ConnectionHdl = nConnectionHandle;
				fbUA_MethodCall.MethodHdl = anMethodHandles[0];
				fbUA_MethodCall.Timeout = tFB_TIMEOUT;
				fbUA_MethodCall.InputArguments = &ClientCfg.Methods.Method[0].ArgumentsIn;
				fbUA_MethodCall.OutputArguments = &ClientCfg.Methods.Method[0].ArgumentsOut;
				// Eingänge mit Zufallszahlen besetzen
				MethCalculateArgs.In.nVal0 = BrbGetRandomDint(1, 10);
				MethCalculateArgs.In.nVal1 = BrbGetRandomDint(1, 10);
				for(nItemIndex=0; nItemIndex<=(INT)nMETHOD_CALC_ARRAY_INDEX_MAX; nItemIndex++)
				{
					MethCalculateArgs.In.anArray[nItemIndex] = (INT)BrbGetRandomDint(1, 10);
				}
				Step.eStepNr = eSTEP_CALL_METH_CALC_WAIT;
			}
			break;

		case eSTEP_CALL_METH_CALC_WAIT:
			// Aufruf abwarten
			if(ConnectionStatus.eConnectionStatus != UACS_Connected)
			{
				fbUA_MethodCall.Execute = 0;
				Step.eStepNr = eSTEP_RUNNING;
			}
			else
			{
				if(fbUA_MethodCall.Busy == 0)
				{
					fbUA_MethodCall.Execute = 0;
					if(fbUA_MethodCall.Done == 1)
					{
						// Hier könnten die Ausgangs-Argumente ausgewertet werden
					}
					else if(fbUA_MethodCall.Error == 1)
					{
						// Fehler eintragen, aber trotzdem weiter machen
						Step.eErrorStep = Step.eStepNr;
						Step.nSubscriptionIndex = -1;
						Step.nItemIndex = 0;
						Step.nErrorId = fbUA_MethodCall.ErrorID;
					}
					Step.eStepNr = eSTEP_RUNNING;
				}
			}
			break;
	
	}
	
	// Der Verbindungs-Status sollte zyklisch geprüft werden
	fbUA_ConnectionGetStatus.Execute = (nConnectionHandle != 0);
	fbUA_ConnectionGetStatus.ConnectionHdl = nConnectionHandle;
	fbUA_ConnectionGetStatus.Timeout = tFB_TIMEOUT;
	UA_ConnectionGetStatus(&fbUA_ConnectionGetStatus);
	if(fbUA_ConnectionGetStatus.Done == 1)
	{
		ConnectionStatus.eConnectionStatus = fbUA_ConnectionGetStatus.ConnectionStatus;
		ConnectionStatus.eServerState = fbUA_ConnectionGetStatus.ServerState;
		ConnectionStatus.eServerLevel = fbUA_ConnectionGetStatus.ServiceLevel;
		fbUA_ConnectionGetStatus.Execute = 0;
		UA_ConnectionGetStatus(&fbUA_ConnectionGetStatus);
	}
	else if(fbUA_ConnectionGetStatus.Error == 1)
	{
		fbUA_ConnectionGetStatus.Execute = 0;
		UA_ConnectionGetStatus(&fbUA_ConnectionGetStatus);
	}
	if(nConnectionHandle == 0)
	{
		ConnectionStatus.eConnectionStatus = UACS_Shutdown;
		ConnectionStatus.eServerState = UASS_Unknown;
		ConnectionStatus.eServerLevel = 0;
	}

	// Bearbeitung des EventItems (muss gemacht werden, um Events zu empfangen)
	fbUA_EventItemOperate.Execute = (fbUA_EventItemAdd.SubscriptionHdl != 0 && fbUA_EventItemAdd.EventItemHdl != 0);
	fbUA_EventItemOperate.SubscriptionHdl = fbUA_EventItemAdd.SubscriptionHdl;
	fbUA_EventItemOperate.EventItemHdl = fbUA_EventItemAdd.EventItemHdl;
	fbUA_EventItemOperate.Timeout = tFB_TIMEOUT;
	UA_EventItemOperate(&fbUA_EventItemOperate);
	if(fbUA_EventItemOperate.Busy == 0)
	{
		if(fbUA_EventItemOperate.Done == 1)
		{
			if(fbUA_EventItemOperate.EventProcessed == 1)
			{
				// Es wurde ein Event empfangen
				ReceivedEvent.nReceivedCount += 1;
				// Das Feld EventId wird in einen Hex-String gewandelt
				BrbUsintArrayToHex((USINT*)&ReceivedEvent.EventId.Data, ReceivedEvent.EventId.Length, (STRING*)&ReceivedEvent.sEventIdHex, sizeof(ReceivedEvent.sEventIdHex), 0);
			}
		}
		else if(fbUA_EventItemOperate.Error == 1)
		{
			// In diesem Beispiel gibt es keine Fehlerbehandlung
		}
		// Baustein für einen erneuten Aufruf zurücksetzen
		fbUA_EventItemOperate.Execute = 0;
		UA_EventItemOperate(&fbUA_EventItemOperate);
	}
		
	// Aufruf aller sonstigen PlcOpen-Funktionsblöcke
	UA_Connect(&fbUA_Connect);
	UA_GetNamespaceIndex(&fbUA_GetNamespaceIndex);
	UA_SubscriptionCreate(&fbUA_SubscriptionCreate);
	UA_NodeGetHandleList(&fbUA_NodeGetHandleList);
	UA_MonitoredItemAddList(&fbUA_MonitoredItemAddList);
	UA_NodeGetHandle(&fbUA_NodeGetHandle);
	UA_EventItemAdd(&fbUA_EventItemAdd);
	UA_MethodGetHandle(&fbUA_MethodGetHandle);
	TON(&fbTrigger);
	UA_ReadList(&fbUA_ReadList);
	UA_WriteList(&fbUA_WriteList);
	UA_MethodCall(&fbUA_MethodCall);
}

void _EXIT Exit(void)
{
	/*
		Beim Überladen des Tasks wird zuerst der Exit des alten Tasks ausgeführt und dieser dann gelöscht. Erst dann
		wird der neue Task ausgeführt.
		Solange die SPS nicht neu gestartet wird, wäre die Verbindung des alten Tasks immer noch vorhanden. Deshalb
		sollte sie hier beeendet werden. Dabei werden alle angelegte Ressourcen (Verbindung, Subscriptions, MonitoredItems) sowohl beim Client als
		auch beim Server aus dem Speicher gelöscht.
		Auftretende Fehler müssen nicht ausgewertet werden. Deshalb wird nur auf Busy=0 gewartet.
	*/
	if(nConnectionHandle != 0)
	{
		fbUA_Disconnect.Execute = 1;
		fbUA_Disconnect.ConnectionHdl = nConnectionHandle;
		fbUA_Disconnect.Timeout = tFB_TIMEOUT;
		do
		{
			UA_Disconnect(&fbUA_Disconnect);
		} while(fbUA_Disconnect.Busy == 1);
	}
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

PROGRAM _INIT
	// Initialisierung des Tasks
	brsmemset(ADR(ClientVarsSubscription), 0, SIZEOF(ClientVarsSubscription)); // Auf diese Variablen werden die vom Server geschickten Werte geschrieben
	fbTrigger.PT := T#1s;
	brsmemset(ADR(ClientVarsRead), 0, SIZEOF(ClientVarsRead)); // Auf diese Variablen werden die vom Server gelesenen Werte geschrieben
	brsmemset(ADR(ReceivedEvent), 0, SIZEOF(ReceivedEvent)); // Auf diese Variablen werden die vom Server empfangenen Event-Felder geschrieben

	// Initialisierung der Schrittkette
	Step.eStepNr := eSTEP_INIT;
	bStartClient := 1; // Der Client startet erst, wenn auf 1. Kann zum Debugging auf 0 gesetzt werden.

	// Vorbesetzen der Konfiguration
	ClientCfg.Connection.sServerEndpointUrl := 'opc.tcp://localhost:4840';
	//ClientCfg.Connection.sServerEndpointUrl := 'opc.tcp://192.168.178.37:4840'; // Nur zum Test
	ClientCfg.Connection.UserIdentityToken.UserIdentityTokenType := UAUITT_Username;
	ClientCfg.Connection.UserIdentityToken.TokenParam1 := 'Admin';
	ClientCfg.Connection.UserIdentityToken.TokenParam2 := 'admin';
	ClientCfg.Connection.tSessionTimeout := T#30s;
	ClientCfg.Connection.tMonitorConnection := T#1s;

	ClientCfg.Subscriptions.sNamespaceUriOrg := 'http://opcfoundation.org/UA/'; // NamespaceUri für den Namespace der Foundation
	//ClientCfg.Subscriptions.sNamespaceUriBrPv := 'urn:B&R/pv/'; // NamespaceUri für B&R V1.0
	ClientCfg.Subscriptions.sNamespaceUriBrPv := 'http://br-automation.com/OpcUa/PLC/PV/'; // NamespaceUri für B&R V2.0

	nSubscriptionIndex := 0;
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].tPublishingInterval := T#500ms;
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].nPriority := 200; // 0..255: Je größer, desto höher die Priorität
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[0].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.bBool';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[0].sVarName := '::ClientST:ClientVarsSubscription.bBool';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[1].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.nUsint';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[1].sVarName := '::ClientST:ClientVarsSubscription.nUsint';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[2].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.nUint';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[2].sVarName := '::ClientST:ClientVarsSubscription.nUint';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[3].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.nUdint';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[3].sVarName := '::ClientST:ClientVarsSubscription.nUdint';
		
	nSubscriptionIndex := 1;
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].tPublishingInterval := T#1s;
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].nPriority := 100; // 0..255: Je größer, desto höher die Priorität
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[0].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.nSint';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[0].sVarName := '::ClientST:ClientVarsSubscription.nSint';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[1].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.nInt';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[1].sVarName := '::ClientST:ClientVarsSubscription.nInt';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[2].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.nDint';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[2].sVarName := '::ClientST:ClientVarsSubscription.nDint';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[3].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.rReal';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[3].sVarName := '::ClientST:ClientVarsSubscription.rReal';

	nSubscriptionIndex := 2;
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].tPublishingInterval := T#2s;
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].nPriority := 50; // 0..255: Je größer, desto höher die Priorität
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[0].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.rLongReal';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[0].sVarName := '::ClientST:ClientVarsSubscription.rLongReal';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[1].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.sString';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[1].sVarName := '::ClientST:ClientVarsSubscription.sString';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[2].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.tTime';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[2].sVarName := '::ClientST:ClientVarsSubscription.tTime';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[3].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.dtDateTime';
	ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[3].sVarName := '::ClientST:ClientVarsSubscription.dtDateTime';

	MonitoredItemParameter.SamplingInterval := 0; // Wird von Subscription.PublishingInterval abgeleitet
	MonitoredItemParameter.QueueSize := 0; // Wenn > 0, dann müsste zyklisch der FB 'UA_MonitoredItemOperateList' für jede Subscription ausgeführt werden
	MonitoredItemParameter.DiscardOldest := 1;
	MonitoredItemParameter.DeadbandType := UADeadbandType_None;
	MonitoredItemParameter.Deadband := 0.0;
	FOR nSubscriptionIndex := 0 TO nCLIENT_SUBSCRIPTION_INDEX_MAX DO
		FOR nItemIndex := 0 TO nCLIENT_MONITORED_ITEM_INDEX_MAX DO
			ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[nItemIndex].NodeId.NamespaceIndex := 0; // Der NamespaceIndex wird später einmalig ermiitelt und dann zugewiesen
			ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[nItemIndex].NodeId.IdentifierType := UAIdentifierType_String;
		END_FOR
	END_FOR

	ClientCfg.Subscriptions.SubEvt.tPublishingInterval := t#100ms; 
	ClientCfg.Subscriptions.SubEvt.nPriority := 250; // 0..255: Je größer, desto höher die Priorität
	ClientCfg.Subscriptions.SubEvt.NotifierNodeId.IdentifierType := UAIdentifierType_Numeric;
	ClientCfg.Subscriptions.SubEvt.NotifierNodeId.Identifier := '2253'; // Root/Objects/Server
	ClientCfg.Subscriptions.SubEvt.EventTypeNodeId.IdentifierType := UAIdentifierType_Numeric;
	ClientCfg.Subscriptions.SubEvt.EventTypeNodeId.Identifier := '11436'; // Root/Types/EventTypes/BaseEventType/ProgressEventType
	
	brsmemset(ADR(asReadVars), 0, SIZEOF(asReadVars));
	ClientCfg.Read.Item[0].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.nUdint';
	ClientCfg.Read.Item[0].sVarName := '::ClientST:ClientVarsRead.nUdint';
	ClientCfg.Read.Item[1].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.nDint';
	ClientCfg.Read.Item[1].sVarName := '::ClientST:ClientVarsRead.nDint';
	ClientCfg.Read.Item[2].NodeId.Identifier := '::ServerData:VarsLocal.ReadOnly.anInt';
	ClientCfg.Read.Item[2].sVarName := '::ClientST:ClientVarsRead.anInt';
	FOR nItemIndex := 0 TO nCLIENT_READ_ITEM_INDEX_MAX DO
		ClientCfg.Read.Item[nItemIndex].NodeId.NamespaceIndex := 0; // Der NamespaceIndex wird später einmalig ermiitelt und dann zugewiesen
		ClientCfg.Read.Item[nItemIndex].NodeId.IdentifierType := UAIdentifierType_String;
	END_FOR

	brsmemset(ADR(asWriteVars), 0, SIZEOF(asWriteVars));
	ClientCfg.Write.Item[0].NodeId.Identifier := '::ServerData:WriteST.nUdint';
	ClientCfg.Write.Item[0].sVarName := '::ClientST:ClientVarsRead.nUdint';
	ClientCfg.Write.Item[1].NodeId.Identifier := '::ServerData:WriteST.nDint';
	ClientCfg.Write.Item[1].sVarName := '::ClientST:ClientVarsRead.nDint';
	ClientCfg.Write.Item[2].NodeId.Identifier := '::ServerData:WriteST.anInt';
	ClientCfg.Write.Item[2].sVarName := '::ClientST:ClientVarsRead.anInt';
	FOR nItemIndex := 0 TO nCLIENT_WRITE_ITEM_INDEX_MAX DO
		ClientCfg.Write.Item[nItemIndex].NodeId.NamespaceIndex := 0; // Der NamespaceIndex wird später einmalig ermiitelt und dann zugewiesen
		ClientCfg.Write.Item[nItemIndex].NodeId.IdentifierType := UAIdentifierType_String;
	END_FOR

	brsmemset(ADR(MethCalculateArgs), 0, SIZEOF(MethCalculateArgs));
	ClientCfg.Methods.Method[0].ObjectNodeId.Identifier := '::SrvMethST'; // Task-Node
	ClientCfg.Methods.Method[0].MethodNodeId.Identifier := '::SrvMethST:Calculate'; // Method-Node
	ClientCfg.Methods.Method[0].ArgumentsIn[0].Name := 'nValue0'; // Name des Eingans wie in der Methode deklariert
	ClientCfg.Methods.Method[0].ArgumentsIn[0].Value := '::ClientST:MethCalculateArgs.In.nVal0'; // Name der Variable, auf die der Wert des Eingang geschrieben wird
	ClientCfg.Methods.Method[0].ArgumentsIn[1].Name := 'nValue1';
	ClientCfg.Methods.Method[0].ArgumentsIn[1].Value := '::ClientST:MethCalculateArgs.In.nVal1';
	ClientCfg.Methods.Method[0].ArgumentsIn[2].Name := 'anArrayIn';
	ClientCfg.Methods.Method[0].ArgumentsIn[2].Value := '::ClientST:MethCalculateArgs.In.anArray';
	ClientCfg.Methods.Method[0].ArgumentsOut[0].Name := 'nAddition'; // Name des Ausgangs wie in der Methode deklariert
	ClientCfg.Methods.Method[0].ArgumentsOut[0].Value := '::ClientST:MethCalculateArgs.Out.nAddition'; // Name der Variable, von der der Wert des Ausgangs genommen wird
	ClientCfg.Methods.Method[0].ArgumentsOut[1].Name := 'nMultiplication';
	ClientCfg.Methods.Method[0].ArgumentsOut[1].Value := '::ClientST:MethCalculateArgs.Out.nMultiplication';
	ClientCfg.Methods.Method[0].ArgumentsOut[2].Name := 'anArrayOut';
	ClientCfg.Methods.Method[0].ArgumentsOut[2].Value := '::ClientST:MethCalculateArgs.Out.anArray';
	FOR nItemIndex := 0 TO nCLIENT_METHODS_INDEX_MAX DO
		ClientCfg.Methods.Method[0].ObjectNodeId.NamespaceIndex := 0; // Der NamespaceIndex wird später einmalig ermiitelt und dann zugewiesen
		ClientCfg.Methods.Method[0].ObjectNodeId.IdentifierType := UAIdentifierType_String;
		ClientCfg.Methods.Method[0].MethodNodeId.NamespaceIndex := 0; // Der NamespaceIndex wird später einmalig ermiitelt und dann zugewiesen
		ClientCfg.Methods.Method[0].MethodNodeId.IdentifierType := UAIdentifierType_String;
	END_FOR
		
	// Ablöschen der Funktionsblöcke und Strukturen 
	brsmemset(ADR(fbUA_ConnectionGetStatus), 0, SIZEOF(fbUA_ConnectionGetStatus));
	brsmemset(ADR(fbUA_Connect), 0, SIZEOF(fbUA_Connect));
	brsmemset(ADR(fbUA_Disconnect), 0, SIZEOF(fbUA_Disconnect));
	brsmemset(ADR(fbUA_GetNamespaceIndex), 0, SIZEOF(fbUA_GetNamespaceIndex));
	brsmemset(ADR(fbUA_SubscriptionCreate), 0, SIZEOF(fbUA_SubscriptionCreate));
	brsmemset(ADR(fbUA_NodeGetHandleList), 0, SIZEOF(fbUA_NodeGetHandleList));
	brsmemset(ADR(fbUA_MonitoredItemAddList), 0, SIZEOF(fbUA_MonitoredItemAddList));
	brsmemset(ADR(fbUA_MethodGetHandle), 0, SIZEOF(fbUA_MethodGetHandle));
	brsmemset(ADR(fbUA_ReadList), 0, SIZEOF(fbUA_ReadList));
	brsmemset(ADR(fbUA_WriteList), 0, SIZEOF(fbUA_WriteList));
	brsmemset(ADR(fbUA_MethodCall), 0, SIZEOF(fbUA_MethodCall));
END_PROGRAM

PROGRAM _CYCLIC
	// Schrittkette
	CASE Step.eStepNr OF
		eSTEP_NONE:
	
		eSTEP_INIT:
			IF bStartClient = 1 THEN
				Step.eStepNr := eSTEP_CONNECT;
			END_IF

		// -----------------------------------------------------------------------------------------------------------------------------------------------
		eSTEP_CONNECT:
			// Hier wird die Verbindung zum Server aufgebaut.
			brsmemset(ADR(fbUA_Connect), 0, SIZEOF(fbUA_Connect));
			fbUA_Connect.Execute := 1;
			fbUA_Connect.ServerEndpointUrl := ClientCfg.Connection.sServerEndpointUrl;
			fbUA_Connect.SessionConnectInfo.SessionName := 'SampleClientST_Session';
			fbUA_Connect.SessionConnectInfo.ApplicationName := 'SampleClientST_Application';
			fbUA_Connect.SessionConnectInfo.SecurityMsgMode := UASecurityMsgMode_None; // Ohne Security
			fbUA_Connect.SessionConnectInfo.SecurityPolicy := UASecurityPolicy_None; // Ohne Security
			fbUA_Connect.SessionConnectInfo.CertificateStore := 'SslCfgOpcUaClient'; // // Angabe der SSL-Configuration unter 'ConfigurationView/AccessAndSecurity/TransortLayerSecurity/OpcUaCfg.sslcfg'
			fbUA_Connect.SessionConnectInfo.ClientCertificateName := ''; // Muss leer bleiben
			fbUA_Connect.SessionConnectInfo.ServerUri := ''; // Kann leer bleiben
			fbUA_Connect.SessionConnectInfo.CheckServerCertificate := 0;
			fbUA_Connect.SessionConnectInfo.TransportProfile := UATP_UATcp;
			brsmemcpy(ADR(fbUA_Connect.SessionConnectInfo.UserIdentityToken), ADR(ClientCfg.Connection.UserIdentityToken), SIZEOF(UAUserIdentityToken));
			fbUA_Connect.SessionConnectInfo.VendorSpecificParameter := ''; // Kann leer bleiben
			fbUA_Connect.SessionConnectInfo.SessionTimeout := ClientCfg.Connection.tSessionTimeout;
			fbUA_Connect.SessionConnectInfo.MonitorConnection := ClientCfg.Connection.tMonitorConnection;
			fbUA_Connect.SessionConnectInfo.LocaleIDs[0] := 'de';
			fbUA_Connect.Timeout := tFB_TIMEOUT;
			nConnectionHandle := 0;
			Step.eStepNr := eSTEP_CONNECT_WAIT;

		eSTEP_CONNECT_WAIT:
			// Aufruf abwarten
			IF fbUA_Connect.Busy = 0 THEN
				fbUA_Connect.Execute := 0;
				IF fbUA_Connect.Done = 1 THEN
					nConnectionHandle := fbUA_Connect.ConnectionHdl;
					Step.eStepNr := eSTEP_GET_NAMESPACEIDX_ORG;
				ELSIF fbUA_Connect.Error = 1 THEN
						// Ständig versuchen, die Verbindung aufzubauen
						nConnectionHandle := 0;
						Step.eStepNr := eSTEP_CONNECT;
				END_IF
			END_IF

		// -----------------------------------------------------------------------------------------------------------------------------------------------
		eSTEP_GET_NAMESPACEIDX_ORG:
			// Hier wird der Namespace-Uri vom Server in einen Index übersetzt (für den Namespace der Foundation)
			brsmemset(ADR(fbUA_GetNamespaceIndex), 0, SIZEOF(fbUA_GetNamespaceIndex));
			fbUA_GetNamespaceIndex.Execute := 1;
			fbUA_GetNamespaceIndex.ConnectionHdl := nConnectionHandle;
			fbUA_GetNamespaceIndex.NamespaceUri := ClientCfg.Subscriptions.sNamespaceUriOrg;
			fbUA_GetNamespaceIndex.Timeout := tFB_TIMEOUT;
			Step.eStepNr := eSTEP_GET_NAMESPACEIDX_ORG_WAIT;
	
		eSTEP_GET_NAMESPACEIDX_ORG_WAIT:
			// Aufruf abwarten
			IF fbUA_GetNamespaceIndex.Busy = 0 THEN
				fbUA_GetNamespaceIndex.Execute := 0;
				IF fbUA_GetNamespaceIndex.Done = 1 THEN
					ClientCfg.Subscriptions.nNamespaceUriOrg := fbUA_GetNamespaceIndex.NamespaceIndex;
					ClientCfg.Subscriptions.SubEvt.NotifierNodeId.NamespaceIndex := ClientCfg.Subscriptions.nNamespaceUriOrg;
					ClientCfg.Subscriptions.SubEvt.EventTypeNodeId.NamespaceIndex := ClientCfg.Subscriptions.nNamespaceUriOrg;
					Step.eStepNr := eSTEP_GET_NAMESPACEIDX_BRPV;
				ELSIF fbUA_GetNamespaceIndex.Error = 1 THEN
					Step.eErrorStep := Step.eStepNr;
					Step.nSubscriptionIndex := -1;
					Step.nItemIndex := -1;
					Step.nErrorId := fbUA_GetNamespaceIndex.ErrorID;
					Step.eStepNr := eSTEP_PAR_ERROR;
				END_IF
			END_IF
		
		eSTEP_GET_NAMESPACEIDX_BRPV:
			// Hier wird der Namespace-Uri vom Server in einen Index übersetzt.	Bei B&R-PV ist nur ein Namespace benötigt.
			brsmemset(ADR(fbUA_GetNamespaceIndex), 0, SIZEOF(fbUA_GetNamespaceIndex));
			fbUA_GetNamespaceIndex.Execute := 1;
			fbUA_GetNamespaceIndex.ConnectionHdl := nConnectionHandle;
			fbUA_GetNamespaceIndex.NamespaceUri := ClientCfg.Subscriptions.sNamespaceUriBrPv;
			fbUA_GetNamespaceIndex.Timeout := tFB_TIMEOUT;
			Step.eStepNr := eSTEP_GET_NAMESPACEIDX_BRPV_WAIT;
	
		eSTEP_GET_NAMESPACEIDX_BRPV_WAIT:
			// Aufruf abwarten
			IF fbUA_GetNamespaceIndex.Busy = 0 THEN
				fbUA_GetNamespaceIndex.Execute := 0;
				IF fbUA_GetNamespaceIndex.Done = 1 THEN
					ClientCfg.Subscriptions.nNamespaceUriBrPv := fbUA_GetNamespaceIndex.NamespaceIndex;
					// NamespaceIndex auf alle MonitoredItems übernehmen
					FOR nSubscriptionIndex := 0 TO nCLIENT_SUBSCRIPTION_INDEX_MAX DO
						FOR nItemIndex := 0 TO nCLIENT_MONITORED_ITEM_INDEX_MAX DO
							ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[nItemIndex].NodeId.NamespaceIndex := fbUA_GetNamespaceIndex.NamespaceIndex;
						END_FOR
					END_FOR
					// NamespaceIndex auf alle ReadItems übernehmen
					FOR nItemIndex := 0 TO nCLIENT_READ_ITEM_INDEX_MAX DO
						ClientCfg.Read.Item[nItemIndex].NodeId.NamespaceIndex := fbUA_GetNamespaceIndex.NamespaceIndex;
					END_FOR
					// NamespaceIndex auf alle WriteItems übernehmen
					FOR nItemIndex := 0 TO nCLIENT_WRITE_ITEM_INDEX_MAX DO
						ClientCfg.Write.Item[nItemIndex].NodeId.NamespaceIndex := fbUA_GetNamespaceIndex.NamespaceIndex;
					END_FOR
					// NamespaceIndex auf alle Methods übernehmen
					FOR nItemIndex := 0 TO nCLIENT_METHODS_INDEX_MAX DO
						ClientCfg.Methods.Method[nItemIndex].MethodNodeId.NamespaceIndex := fbUA_GetNamespaceIndex.NamespaceIndex;
						ClientCfg.Methods.Method[nItemIndex].ObjectNodeId.NamespaceIndex := fbUA_GetNamespaceIndex.NamespaceIndex;
					END_FOR
					Step.eStepNr := eSTEP_CREATE_SUBSCRIPTIONS_VAR;
				ELSIF fbUA_GetNamespaceIndex.Error = 1 THEN
					Step.eErrorStep := Step.eStepNr;
					Step.nSubscriptionIndex := -1;
					Step.nItemIndex := -1;
					Step.nErrorId := fbUA_GetNamespaceIndex.ErrorID;
					Step.eStepNr := eSTEP_PAR_ERROR;
				END_IF
			END_IF
		
			// -----------------------------------------------------------------------------------------------------------------------------------------------
		eSTEP_CREATE_SUBSCRIPTIONS_VAR:
			nSubscriptionIndex := -1; // Mit der ersten Subscription beginnen
			Step.eStepNr := eSTEP_CREATE_SUBSCRIPTION_VAR;
		
		eSTEP_CREATE_SUBSCRIPTION_VAR:
			// Nächste Subscription hinzufügen
			nSubscriptionIndex := nSubscriptionIndex + 1;
			IF nSubscriptionIndex <= nCLIENT_SUBSCRIPTION_INDEX_MAX THEN
				// Nächste Subscription anlegen
				brsmemset(ADR(fbUA_SubscriptionCreate), 0, SIZEOF(fbUA_SubscriptionCreate));
				fbUA_SubscriptionCreate.Execute := 1;
				fbUA_SubscriptionCreate.ConnectionHdl := nConnectionHandle;
				fbUA_SubscriptionCreate.PublishingEnable := 1;
				fbUA_SubscriptionCreate.Priority := ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].nPriority;
				fbUA_SubscriptionCreate.Timeout := tFB_TIMEOUT;
				// Unter ST können IN/OUT-Elemente nicht direkt angegeben werden, sondern nur beim FB-Aufruf (siehe unten)
				tSubscriptionPublishingInterval := ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].tPublishingInterval; 
				Step.eStepNr := eSTEP_CREATE_SUBSCRIPT_VAR_WAIT;
			ELSE
				// Alle Subscriptions angelegt
				IF Step.nErrorId <> 0 THEN
					Step.eStepNr := eSTEP_PAR_ERROR;
				ELSE
					Step.eStepNr := eSTEP_CREATE_SUBSCRIPTION_EVT;
				END_IF
			END_IF
		
		eSTEP_CREATE_SUBSCRIPT_VAR_WAIT:
			// Aufruf abwarten
			IF fbUA_SubscriptionCreate.Busy = 0 THEN
				fbUA_SubscriptionCreate.Execute := 0;
				IF fbUA_SubscriptionCreate.Done = 1 THEN
					Step.eStepNr := eSTEP_SUB_GET_NODE_HDL_LIST;
				ELSIF fbUA_SubscriptionCreate.Error = 1 THEN
					// Fehler eintragen, aber trotzdem mit der nächsten Subcription weiter machen
					Step.eErrorStep := Step.eStepNr;
					Step.nSubscriptionIndex := nSubscriptionIndex;
					Step.nItemIndex := -1;
					Step.nErrorId := fbUA_SubscriptionCreate.ErrorID;
					Step.eStepNr := eSTEP_CREATE_SUBSCRIPTION_VAR;
				END_IF
			END_IF
				
		eSTEP_SUB_GET_NODE_HDL_LIST:
			// Die Handles für die MonitoredItems ermitteln
			brsmemset(ADR(fbUA_NodeGetHandleList), 0, SIZEOF(fbUA_NodeGetHandleList));
			fbUA_NodeGetHandleList.Execute := 1;
			fbUA_NodeGetHandleList.ConnectionHdl := nConnectionHandle;
			FOR nItemIndex := 0 TO nCLIENT_MONITORED_ITEM_INDEX_MAX DO
				IF brsstrlen(ADR(ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[nItemIndex].NodeId.Identifier)) > 0 THEN
					brsmemcpy(ADR(fbUA_NodeGetHandleList.NodeIDs[nItemIndex]), ADR(ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[nItemIndex].NodeId), SIZEOF(UANodeID));
				ELSE
					EXIT;
				END_IF
			END_FOR
			fbUA_NodeGetHandleList.NodeIDCount := nItemIndex;
			fbUA_NodeGetHandleList.Timeout := tFB_TIMEOUT;
			Step.eStepNr := eSTEP_SUB_GET_NODE_HDL_LIST_WAIT;

		eSTEP_SUB_GET_NODE_HDL_LIST_WAIT:
			// Aufruf abwarten
			IF fbUA_NodeGetHandleList.Busy = 0 THEN
				fbUA_NodeGetHandleList.Execute := 0;
				IF fbUA_NodeGetHandleList.Done = 1 THEN
					nItemIndex := -1;
					Step.eStepNr := eSTEP_ADD_MONITORED_ITEMS;
				ELSIF fbUA_NodeGetHandleList.Error = 1 THEN
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep := Step.eStepNr;
					Step.nSubscriptionIndex := nSubscriptionIndex;
					IF fbUA_NodeGetHandleList.ErrorID <> 0 THEN
						Step.nItemIndex := -1;
						Step.nErrorId := fbUA_NodeGetHandleList.ErrorID;
					ELSE
						FOR nItemIndex := 0 TO MAX_INDEX_NODELIST DO
							IF fbUA_NodeGetHandleList.NodeErrorIDs[nItemIndex] <> 0 THEN
								Step.nItemIndex := nItemIndex;
								Step.nErrorId := fbUA_NodeGetHandleList.NodeErrorIDs[nItemIndex];
								EXIT;
							END_IF
						END_FOR
					END_IF
					nItemIndex := -1;
					Step.eStepNr := eSTEP_CREATE_SUBSCRIPTION_VAR;
				END_IF
			END_IF

		eSTEP_ADD_MONITORED_ITEMS:
			// MonitoredItems hinzufügen
			brsmemset(ADR(fbUA_MonitoredItemAddList), 0, SIZEOF(fbUA_MonitoredItemAddList));
			fbUA_MonitoredItemAddList.Execute := 1;
			fbUA_MonitoredItemAddList.SubscriptionHdl := fbUA_SubscriptionCreate.SubscriptionHdl;
			FOR nItemIndex := 0 TO nCLIENT_MONITORED_ITEM_INDEX_MAX DO
				IF brsstrlen(ADR(ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[nItemIndex].NodeId.Identifier)) > 0 THEN
					fbUA_MonitoredItemAddList.NodeHdls[nItemIndex] := fbUA_NodeGetHandleList.NodeHdls[nItemIndex];
					fbUA_MonitoredItemAddList.NodeAddInfos[nItemIndex].AttributeId := UAAI_Value; // Es ist möglich, alle Attribute eines Nodes zu adressieren, aber normalerweise wird natürlich das Attribut 'Value' benötigt
					fbUA_MonitoredItemAddList.NodeAddInfos[nItemIndex].IndexRangeCount := 0; // Nur Einzel-Variablen, keine Arrays
					brsmemset(ADR(fbUA_MonitoredItemAddList.NodeAddInfos[nItemIndex].IndexRange), 0, SIZEOF(fbUA_MonitoredItemAddList.NodeAddInfos[nItemIndex].IndexRange));
					asMonitoredItemVarNames[nItemIndex] := ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].MonitoredItem[nItemIndex].sVarName;
					brsmemcpy(ADR(aMonitoredItemParameter[nItemIndex]), ADR(MonitoredItemParameter), SIZEOF(MonitoredItemParameter));
					aMonitoredItemParameter[nItemIndex].SamplingInterval := ClientCfg.Subscriptions.SubVar[nSubscriptionIndex].tPublishingInterval; // Nur das SamplingInterval wird von der Subscription abgeleitet
				ELSE
					EXIT;
				END_IF
			END_FOR
			fbUA_MonitoredItemAddList.NodeHdlCount := nItemIndex;
			fbUA_MonitoredItemAddList.Timeout := tFB_TIMEOUT;
			// Unter ST können IN/OUT-Elemente nicht direkt angegeben werden, sondern nur beim FB-Aufruf (siehe unten)
			Step.eStepNr := eSTEP_ADD_MONITORED_ITEMS_WAIT;
		
		eSTEP_ADD_MONITORED_ITEMS_WAIT:
			// Aufruf abwarten
			IF fbUA_MonitoredItemAddList.Busy = 0 THEN
				fbUA_MonitoredItemAddList.Execute := 0;
				IF fbUA_MonitoredItemAddList.Done = 1 THEN
					Step.eStepNr := eSTEP_CREATE_SUBSCRIPTION_VAR;
				ELSIF fbUA_MonitoredItemAddList.Error = 1 THEN
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep := Step.eStepNr;
					Step.nSubscriptionIndex := nSubscriptionIndex;
					IF fbUA_MonitoredItemAddList.ErrorID <> 0 THEN
						Step.nItemIndex := -1;
						Step.nErrorId := fbUA_MonitoredItemAddList.ErrorID;
					ELSE
						FOR nItemIndex := 0 TO MAX_INDEX_NODELIST DO
							IF fbUA_MonitoredItemAddList.NodeErrorIDs[nItemIndex] <> 0 THEN
								Step.nItemIndex := nItemIndex;
								Step.nErrorId := fbUA_MonitoredItemAddList.NodeErrorIDs[nItemIndex];
								EXIT;
							END_IF
						END_FOR
					END_IF
					Step.eStepNr := eSTEP_CREATE_SUBSCRIPTION_VAR;
				END_IF
			END_IF

		// -----------------------------------------------------------------------------------------------------------------------------------------------
		eSTEP_CREATE_SUBSCRIPTION_EVT:
			// Subscription für Event hinzufügen
			brsmemset(ADR(fbUA_SubscriptionCreate), 0, SIZEOF(fbUA_SubscriptionCreate));
			fbUA_SubscriptionCreate.Execute := 1;
			fbUA_SubscriptionCreate.ConnectionHdl := nConnectionHandle;
			fbUA_SubscriptionCreate.PublishingEnable := 1;
			fbUA_SubscriptionCreate.Priority := ClientCfg.Subscriptions.SubEvt.nPriority;
			fbUA_SubscriptionCreate.Timeout := tFB_TIMEOUT;
			tSubscriptionPublishingInterval := ClientCfg.Subscriptions.SubEvt.tPublishingInterval; 
			Step.eStepNr := eSTEP_CREATE_SUBSCRIPT_EVT_WAIT;
		
		eSTEP_CREATE_SUBSCRIPT_EVT_WAIT:
			// Aufruf abwarten
			IF fbUA_SubscriptionCreate.Busy = 0 THEN
				fbUA_SubscriptionCreate.Execute := 0;
				IF fbUA_SubscriptionCreate.Done = 1 THEN
					Step.eStepNr := eSTEP_EVT_GET_NODE_HDL;
				ELSIF fbUA_SubscriptionCreate.Error = 1 THEN
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep := Step.eStepNr;
					Step.nSubscriptionIndex := -1;
					Step.nItemIndex := -1;
					Step.nErrorId := fbUA_SubscriptionCreate.ErrorID;
					Step.eStepNr := eSTEP_RD_GET_NODE_HDL_LIST;
				END_IF
			END_IF
		
		eSTEP_EVT_GET_NODE_HDL:
			brsmemset(ADR(fbUA_NodeGetHandle), 0, SIZEOF(fbUA_NodeGetHandle));
			fbUA_NodeGetHandle.Execute := 1;
			fbUA_NodeGetHandle.ConnectionHdl := nConnectionHandle;
			brsmemcpy(ADR(fbUA_NodeGetHandle.NodeID), ADR(ClientCfg.Subscriptions.SubEvt.NotifierNodeId), SIZEOF(UANodeID)); // Root/Objects/Server
			fbUA_NodeGetHandle.Timeout := tFB_TIMEOUT;
			Step.eStepNr := eSTEP_EVT_GET_NODE_HDL_WAIT;
		
		eSTEP_EVT_GET_NODE_HDL_WAIT:
			// Aufruf abwarten
			IF fbUA_NodeGetHandle.Busy = 0 THEN
				fbUA_NodeGetHandle.Execute := 0;
				IF fbUA_NodeGetHandle.Done = 1 THEN
					Step.eStepNr := eSTEP_ADD_EVENT_ITEM;
				ELSIF fbUA_NodeGetHandle.Error = 1 THEN
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep := Step.eStepNr;
					Step.nSubscriptionIndex := -1;
					Step.nErrorId := fbUA_NodeGetHandle.ErrorID;
					Step.eStepNr := eSTEP_RD_GET_NODE_HDL_LIST;
				END_IF
			END_IF
		
		eSTEP_ADD_EVENT_ITEM:
			fbUA_EventItemAdd.Execute := 1;
			fbUA_EventItemAdd.SubscriptionHdl := fbUA_SubscriptionCreate.SubscriptionHdl;
			fbUA_EventItemAdd.NodeHdl := fbUA_NodeGetHandle.NodeHdl; // Root/Objects/Server
			// Event-Typ festlegen
			brsmemcpy(ADR(fbUA_EventItemAdd.EventType), ADR(ClientCfg.Subscriptions.SubEvt.EventTypeNodeId), SIZEOF(UANodeID));
			// Zu sendende Felder festlegen
			// EventId
			nItemIndex := 0;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements := 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex := ClientCfg.Subscriptions.nNamespaceUriOrg;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name := 'EventId';
			ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex] := '::ClientST:ReceivedEvent.EventId';
			// EventType
			nItemIndex := nItemIndex + 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements := 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex := ClientCfg.Subscriptions.nNamespaceUriOrg;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name := 'EventType';
			ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex] := '::ClientST:ReceivedEvent.EventType';
			// LocalTime
			nItemIndex := nItemIndex + 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements := 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex := ClientCfg.Subscriptions.nNamespaceUriOrg;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name := 'LocalTime';
			ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex] := '::ClientST:ReceivedEvent.LocalTime';
			// Message
			nItemIndex := nItemIndex + 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements := 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex := ClientCfg.Subscriptions.nNamespaceUriOrg;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name := 'Message';
			ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex] := '::ClientST:ReceivedEvent.Message';
			// ReceiveTime
			nItemIndex := nItemIndex + 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements := 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex := ClientCfg.Subscriptions.nNamespaceUriOrg;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name := 'ReceiveTime';
			ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex] := '::ClientST:ReceivedEvent.ReceiveTime';
			// Severity
			nItemIndex := nItemIndex + 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements := 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex := ClientCfg.Subscriptions.nNamespaceUriOrg;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name := 'Severity';
			ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex] := '::ClientST:ReceivedEvent.Severity';
			// SourceName
			nItemIndex := nItemIndex + 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements := 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex := ClientCfg.Subscriptions.nNamespaceUriOrg;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name := 'SourceName';
			ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex] := '::ClientST:ReceivedEvent.SourceName';
			// SourceNode
			nItemIndex := nItemIndex + 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements := 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex := ClientCfg.Subscriptions.nNamespaceUriOrg;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name := 'SourceNode';
			ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex] := '::ClientST:ReceivedEvent.SourceNode';
			// Time
			nItemIndex := nItemIndex + 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements := 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex := ClientCfg.Subscriptions.nNamespaceUriOrg;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name := 'Time';
			ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex] := '::ClientST:ReceivedEvent.Time';
			// Context
			nItemIndex := nItemIndex + 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements := 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex := ClientCfg.Subscriptions.nNamespaceUriOrg;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name := 'Context';
			ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex] := '::ClientST:ReceivedEvent.Context';
			// Progress
			nItemIndex := nItemIndex + 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].NoOfElements := 1;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.NamespaceIndex := ClientCfg.Subscriptions.nNamespaceUriOrg;
			fbUA_EventItemAdd.EventFieldSelections[nItemIndex].Elements[0].TargetName.Name := 'Progress';
			ClientCfg.Subscriptions.SubEvt.EventFieldVarNames[nItemIndex] := '::ClientST:ReceivedEvent.Progress';
			fbUA_EventItemAdd.EventFieldSelectionCount := nItemIndex + 1;
			fbUA_EventItemAdd.Timeout := tFB_TIMEOUT;
			Step.eStepNr := eSTEP_ADD_EVENT_ITEM_WAIT;
		
		eSTEP_ADD_EVENT_ITEM_WAIT:
			// Aufruf abwarten
			IF fbUA_EventItemAdd.Busy = 0 THEN
				fbUA_EventItemAdd.Execute := 0;
				IF fbUA_EventItemAdd.Done = 1 THEN
					Step.eStepNr := eSTEP_RD_GET_NODE_HDL_LIST;
				ELSIF fbUA_EventItemAdd.Error = 1 THEN
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep := Step.eStepNr;
					Step.nSubscriptionIndex := -1;
					Step.nErrorId := fbUA_EventItemAdd.ErrorID;
					Step.eStepNr := eSTEP_RD_GET_NODE_HDL_LIST;
				END_IF
			END_IF	

		eSTEP_RD_GET_NODE_HDL_LIST:
			// Die Handles für die ReadItems ermitteln
			brsmemset(ADR(fbUA_NodeGetHandleList), 0, SIZEOF(fbUA_NodeGetHandleList));
			fbUA_NodeGetHandleList.Execute := 1;
			fbUA_NodeGetHandleList.ConnectionHdl := nConnectionHandle;
			FOR nItemIndex:=0 TO nCLIENT_READ_ITEM_INDEX_MAX DO
				IF brsstrlen(ADR(ClientCfg.Read.Item[nItemIndex].NodeId.Identifier)) > 0 THEN
					brsmemcpy(ADR(fbUA_NodeGetHandleList.NodeIDs[nItemIndex]), ADR(ClientCfg.Read.Item[nItemIndex].NodeId), SIZEOF(UANodeID));
				ELSE
					EXIT;
				END_IF
			END_FOR
			fbUA_NodeGetHandleList.NodeIDCount := nItemIndex;
			fbUA_NodeGetHandleList.Timeout := tFB_TIMEOUT;
			Step.eStepNr := eSTEP_RD_GET_NODE_HDL_LIST_WAIT;
		
		eSTEP_RD_GET_NODE_HDL_LIST_WAIT:
			// Aufruf abwarten
			IF fbUA_NodeGetHandleList.Busy = 0 THEN
				fbUA_NodeGetHandleList.Execute := 0;
				IF fbUA_NodeGetHandleList.Done = 1 THEN
					// Daten speichern
					FOR nItemIndex := 0 TO nCLIENT_READ_ITEM_INDEX_MAX DO
						IF brsstrlen(ADR(ClientCfg.Read.Item[nItemIndex].NodeId.Identifier)) > 0 THEN
							fbUA_ReadList.NodeHdls[nItemIndex] := fbUA_NodeGetHandleList.NodeHdls[nItemIndex];
							fbUA_ReadList.NodeAddInfo[nItemIndex].AttributeId := UAAI_Value;
							brsstrcpy(ADR(asReadVars[nItemIndex]),  ADR(ClientCfg.Read.Item[nItemIndex].sVarName));
						ELSE
							EXIT;
						END_IF
					END_FOR
					fbUA_ReadList.NodeHdlCount := nItemIndex;
					Step.eStepNr := eSTEP_WR_GET_NODE_HDL_LIST;
				ELSIF fbUA_NodeGetHandleList.Error = 1 THEN
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep := Step.eStepNr;
					Step.nSubscriptionIndex := -1;
					IF fbUA_NodeGetHandleList.ErrorID <> 0 THEN
						Step.nItemIndex := -1;
						Step.nErrorId := fbUA_NodeGetHandleList.ErrorID;
					ELSE
						FOR nItemIndex :=0 TO MAX_INDEX_NODELIST DO
							IF fbUA_NodeGetHandleList.NodeErrorIDs[nItemIndex] <> 0 THEN
								Step.nItemIndex := nItemIndex;
								Step.nErrorId := fbUA_NodeGetHandleList.NodeErrorIDs[nItemIndex];
								EXIT;
							END_IF
						END_FOR
					END_IF
					nItemIndex := -1;
					Step.eStepNr := eSTEP_WR_GET_NODE_HDL_LIST;
				END_IF
			END_IF
		
		eSTEP_WR_GET_NODE_HDL_LIST:
			// Die Handles für die WriteItems ermitteln
			brsmemset(ADR(fbUA_NodeGetHandleList), 0, SIZEOF(fbUA_NodeGetHandleList));
			fbUA_NodeGetHandleList.Execute := 1;
			fbUA_NodeGetHandleList.ConnectionHdl := nConnectionHandle;
			FOR nItemIndex:=0 TO nCLIENT_WRITE_ITEM_INDEX_MAX DO
				IF brsstrlen(ADR(ClientCfg.Write.Item[nItemIndex].NodeId.Identifier)) > 0 THEN
					brsmemcpy(ADR(fbUA_NodeGetHandleList.NodeIDs[nItemIndex]), ADR(ClientCfg.Write.Item[nItemIndex].NodeId), SIZEOF(UANodeID));
				ELSE
					EXIT;
				END_IF
			END_FOR
			fbUA_NodeGetHandleList.NodeIDCount := nItemIndex;
			fbUA_NodeGetHandleList.Timeout := tFB_TIMEOUT;
			Step.eStepNr := eSTEP_WR_GET_NODE_HDL_LIST_WAIT;
		
		eSTEP_WR_GET_NODE_HDL_LIST_WAIT:
			// Aufruf abwarten
			IF fbUA_NodeGetHandleList.Busy = 0 THEN
				fbUA_NodeGetHandleList.Execute := 0;
				IF fbUA_NodeGetHandleList.Done = 1 THEN
					// Daten speichern
					FOR nItemIndex := 0 TO nCLIENT_WRITE_ITEM_INDEX_MAX DO
						IF brsstrlen(ADR(ClientCfg.Write.Item[nItemIndex].NodeId.Identifier)) > 0 THEN
							fbUA_WriteList.NodeHdls[nItemIndex] := fbUA_NodeGetHandleList.NodeHdls[nItemIndex];
							fbUA_WriteList.NodeAddInfo[nItemIndex].AttributeId := UAAI_Value;
							brsstrcpy(ADR(asWriteVars[nItemIndex]),  ADR(ClientCfg.Write.Item[nItemIndex].sVarName));
						ELSE
							EXIT;
						END_IF
					END_FOR
					fbUA_WriteList.NodeHdlCount := nItemIndex;
					Step.eStepNr := eSTEP_METH_GET_HANDLES;
				ELSIF fbUA_NodeGetHandleList.Error = 1 THEN
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep := Step.eStepNr;
					Step.nSubscriptionIndex := -1;
					IF fbUA_NodeGetHandleList.ErrorID <> 0 THEN
						Step.nItemIndex := -1;
						Step.nErrorId := fbUA_NodeGetHandleList.ErrorID;
					ELSE
						FOR nItemIndex :=0 TO MAX_INDEX_NODELIST DO
							IF fbUA_NodeGetHandleList.NodeErrorIDs[nItemIndex] <> 0 THEN
								Step.nItemIndex := nItemIndex;
								Step.nErrorId := fbUA_NodeGetHandleList.NodeErrorIDs[nItemIndex];
								EXIT;
							END_IF
						END_FOR
					END_IF
					nItemIndex := -1;
					Step.eStepNr := eSTEP_METH_GET_HANDLES;
				END_IF
			END_IF

		eSTEP_METH_GET_HANDLES:
			nMethodIndex := -1; // Mit der ersten Method beginnen
			Step.eStepNr := eSTEP_METH_GET_HANDLE;
		
		eSTEP_METH_GET_HANDLE:
			// Nächstes Method-Handle ermitteln
			nMethodIndex := nMethodIndex + 1;
			IF nMethodIndex <= nCLIENT_METHODS_INDEX_MAX THEN
				brsmemset(ADR(fbUA_MethodGetHandle), 0, SIZEOF(fbUA_MethodGetHandle));
				fbUA_MethodGetHandle.Execute := 1;
				fbUA_MethodGetHandle.ConnectionHdl := nConnectionHandle;
				brsmemcpy(ADR(fbUA_MethodGetHandle.ObjectNodeID), ADR(ClientCfg.Methods.Method[nMethodIndex].ObjectNodeId), SIZEOF(UANodeID));
				brsmemcpy(ADR(fbUA_MethodGetHandle.MethodNodeID), ADR(ClientCfg.Methods.Method[nMethodIndex].MethodNodeId), SIZEOF(UANodeID));
				fbUA_MethodGetHandle.Timeout := tFB_TIMEOUT;
				Step.eStepNr := eSTEP_METH_GET_HANDLE_WAIT;
			ELSE
				// Alle Method-Handles ermittelt
				IF Step.nErrorId <> 0 THEN
					Step.eStepNr := eSTEP_PAR_ERROR;
				ELSE
					Step.eStepNr := eSTEP_RUNNING;
				END_IF
			END_IF
			
		eSTEP_METH_GET_HANDLE_WAIT:
			// Aufruf abwarten
			IF fbUA_MethodGetHandle.Busy = 0 THEN
				fbUA_MethodGetHandle.Execute := 0;
				IF fbUA_MethodGetHandle.Done = 1 THEN
					anMethodHandles[nMethodIndex] := fbUA_MethodGetHandle.MethodHdl;
					Step.eStepNr := eSTEP_METH_GET_HANDLE;
				ELSIF fbUA_MethodGetHandle.Error = 1 THEN
					// Fehler eintragen, aber trotzdem weiter machen
					Step.eErrorStep := Step.eStepNr;
					Step.nSubscriptionIndex := -1;
					Step.nItemIndex := nMethodIndex;
					Step.nErrorId := fbUA_MethodGetHandle.ErrorID;
					Step.eStepNr := eSTEP_METH_GET_HANDLE;
				END_IF
			END_IF

		// -----------------------------------------------------------------------------------------------------------------------------------------------
		eSTEP_RUNNING:
			IF fbUA_ConnectionGetStatus.Execute = 1 THEN
				IF ConnectionStatus.eConnectionStatus <> UACS_Connected THEN
					// Der Server ist nicht mehr verbunden. In diesem Fall kann die Verbindung später vom Client automatisch wieder komplett reastauriert, wenn der Server wieder erreichbar ist.
					Step.eStepNr := eSTEP_CONNECTION_ERROR;
				ELSE
					// Trigger für zyklisches Lesen + Schreiben
					fbTrigger.IN := 1;
					IF fbTrigger.Q = 1 THEN
						fbTrigger.IN := 0;
						Step.eStepNr := eSTEP_READ_LIST;
					END_IF
				END_IF
			END_IF

		eSTEP_PAR_ERROR:
		// Es liegt eine Parameter-Fehler vor, bei dem die Schrittkette nicht weiter abgearbeitet werden kann.
		// Der falsche Parameter muss behoben werden.
		// Dieser ist unter der Struktur 'Step' einsehbar und kann in der AS-Hilfe nachgeschlagen werden.
		// Tipp: Die ErrorId sollte in Hexadezimal-Format angezeigt werden, da die OpcUa-Fehler immer als Hex dokumentiert werden.

		eSTEP_CONNECTION_ERROR:
			IF fbUA_ConnectionGetStatus.Execute = 1 THEN
				IF ConnectionStatus.eConnectionStatus = UACS_Connected THEN
					// Die Verbindung konnte vom Client automatisch wieder komplett reastauriert werden (mit allen Subscriptions und MonitoredItems)
					Step.eStepNr := eSTEP_RUNNING;		
				END_IF
			END_IF

		// -----------------------------------------------------------------------------------------------------------------------------------------------
		eSTEP_READ_LIST:
			// Achtung: Zyklisches Lesen (Polling) sollte niemals in einer Applikation implementiert werden! Stattdessen sollte unbedingt Subscription verwendet werden.
			// Dieses Beispiel soll lediglich die Besetzung des FB's veranschaulichen.
			IF ConnectionStatus.eConnectionStatus <> UACS_Connected THEN
				Step.eStepNr := eSTEP_RUNNING;
			ELSE
				fbUA_ReadList.Execute := 1;
				fbUA_ReadList.ConnectionHdl := nConnectionHandle;
				fbUA_ReadList.Timeout := tFB_TIMEOUT;
				// Unter ST können IN/OUT-Elemente nicht direkt angegeben werden, sondern nur beim FB-Aufruf (siehe unten)
				// Der Eingang 'Variables' wird deshalb beim Aufruf übergeben
				Step.eStepNr := eSTEP_READ_LIST_WAIT;
			END_IF

		eSTEP_READ_LIST_WAIT:
			// Aufruf abwarten
			IF ConnectionStatus.eConnectionStatus <> UACS_Connected THEN
				fbUA_ReadList.Execute := 0;
				Step.eStepNr := eSTEP_RUNNING;
			ELSE
				IF fbUA_ReadList.Busy = 0 THEN
					fbUA_ReadList.Execute := 0;
					IF fbUA_ReadList.Error = 1 THEN
						// Fehler eintragen, aber trotzdem weiter machen
						Step.eErrorStep := Step.eStepNr;
						Step.nSubscriptionIndex := -1;
						IF fbUA_ReadList.ErrorID <> 0 THEN
							Step.nItemIndex := -1;
							Step.nErrorId := fbUA_ReadList.ErrorID;
						ELSE
							FOR nItemIndex := 0 TO nCLIENT_READ_ITEM_INDEX_MAX DO
								IF fbUA_ReadList.NodeErrorIDs[nItemIndex] <> 0 THEN
									Step.nItemIndex := nItemIndex;
									Step.nErrorId := fbUA_ReadList.NodeErrorIDs[nItemIndex];
									EXIT;
								END_IF
							END_FOR
						END_IF
					END_IF
					Step.eStepNr := eSTEP_WRITE_LIST;
				END_IF
			END_IF
		
		eSTEP_WRITE_LIST:
			IF ConnectionStatus.eConnectionStatus <> UACS_Connected THEN
				Step.eStepNr := eSTEP_RUNNING;
			ELSE
				fbUA_WriteList.Execute := 1;
				fbUA_WriteList.ConnectionHdl := nConnectionHandle;
				fbUA_WriteList.Timeout := tFB_TIMEOUT;
				// Unter ST können IN/OUT-Elemente nicht direkt angegeben werden, sondern nur beim FB-Aufruf (siehe unten)
				// Der Eingang 'Variables' wird deshalb beim Aufruf übergeben
				Step.eStepNr := eSTEP_WRITE_LIST_WAIT;
			END_IF
		
		eSTEP_WRITE_LIST_WAIT:
			// Aufruf abwarten
			IF ConnectionStatus.eConnectionStatus <> UACS_Connected THEN
				fbUA_WriteList.Execute := 0;
				Step.eStepNr := eSTEP_RUNNING;
			ELSE
				IF fbUA_WriteList.Busy = 0 THEN
					fbUA_WriteList.Execute := 0;
					IF fbUA_WriteList.Error = 1 THEN
						// Fehler eintragen, aber trotzdem weiter machen
						Step.eErrorStep := Step.eStepNr;
						Step.nSubscriptionIndex := -1;
						IF fbUA_WriteList.ErrorID <> 0 THEN
							Step.nItemIndex := -1;
							Step.nErrorId := fbUA_WriteList.ErrorID;
						ELSE
							FOR nItemIndex := 0 TO nCLIENT_WRITE_ITEM_INDEX_MAX DO
								IF fbUA_WriteList.NodeErrorIDs[nItemIndex] <> 0 THEN
									Step.nItemIndex := nItemIndex;
									Step.nErrorId := fbUA_WriteList.NodeErrorIDs[nItemIndex];
									EXIT;
								END_IF
							END_FOR
						END_IF
					END_IF
					Step.eStepNr := eSTEP_CALL_METH_CALC;
				END_IF
			END_IF

		eSTEP_CALL_METH_CALC:
			// Aufruf der Methode 'Calculate'
			IF ConnectionStatus.eConnectionStatus <> UACS_Connected THEN
				Step.eStepNr := eSTEP_RUNNING;
			ELSE
				fbUA_MethodCall.Execute := 1;
				fbUA_MethodCall.ConnectionHdl := nConnectionHandle;
				fbUA_MethodCall.MethodHdl := anMethodHandles[0];
				fbUA_MethodCall.Timeout := tFB_TIMEOUT;
				// Unter ST können IN/OUT-Elemente nicht direkt angegeben werden, sondern nur beim FB-Aufruf (siehe unten)
				// Eingänge mit Zufallszahlen besetzen
				MethCalculateArgs.In.nVal0 := BrbGetRandomDint(1, 10);
				MethCalculateArgs.In.nVal1 := BrbGetRandomDint(1, 10);
				FOR nItemIndex :=0 TO nMETHOD_CALC_ARRAY_INDEX_MAX DO
					MethCalculateArgs.In.anArray[nItemIndex] := DINT_TO_INT(BrbGetRandomDint(1, 10));
				END_FOR
				Step.eStepNr := eSTEP_CALL_METH_CALC_WAIT;
			END_IF

		eSTEP_CALL_METH_CALC_WAIT:
			// Aufruf abwarten
			IF ConnectionStatus.eConnectionStatus <> UACS_Connected THEN
				fbUA_MethodCall.Execute := 0;
				Step.eStepNr := eSTEP_RUNNING;
			ELSE
				IF fbUA_MethodCall.Busy = 0 THEN
					fbUA_MethodCall.Execute := 0;
					IF fbUA_MethodCall.Done = 1 THEN
						// Hier könnten die Ausgangs-Argumente ausgewertet werden						
					ELSIF fbUA_MethodCall.Error = 1 THEN
						// Fehler eintragen, aber trotzdem weiter machen
						Step.eErrorStep := Step.eStepNr;
						Step.nSubscriptionIndex := -1;
						Step.nItemIndex := 0;
						Step.nErrorId := fbUA_MethodCall.ErrorID;
					END_IF
					Step.eStepNr := eSTEP_RUNNING;
				END_IF
			END_IF
		
	END_CASE

	// Der Verbindungs-Status sollte zyklisch geprüft werden
	fbUA_ConnectionGetStatus.Execute := (nConnectionHandle <> 0);
	fbUA_ConnectionGetStatus.ConnectionHdl := nConnectionHandle;
	fbUA_ConnectionGetStatus.Timeout := tFB_TIMEOUT;
	fbUA_ConnectionGetStatus();
	IF fbUA_ConnectionGetStatus.Done = 1 THEN
		ConnectionStatus.eConnectionStatus := fbUA_ConnectionGetStatus.ConnectionStatus;
		ConnectionStatus.eServerState := fbUA_ConnectionGetStatus.ServerState;
		ConnectionStatus.eServerLevel := fbUA_ConnectionGetStatus.ServiceLevel;
		fbUA_ConnectionGetStatus.Execute := 0;
		fbUA_ConnectionGetStatus();
	ELSIF fbUA_ConnectionGetStatus.Error = 1 THEN
		fbUA_ConnectionGetStatus.Execute := 0;
		fbUA_ConnectionGetStatus();
	END_IF
	IF nConnectionHandle = 0 THEN
		ConnectionStatus.eConnectionStatus := UACS_Shutdown;
		ConnectionStatus.eServerState := UASS_Unknown;
		ConnectionStatus.eServerLevel := 0;
	END_IF
	
	// Bearbeitung des EventItems (muss gemacht werden, um Events zu empfangen)
	fbUA_EventItemOperate.Execute := (fbUA_EventItemAdd.SubscriptionHdl <> 0 AND fbUA_EventItemAdd.EventItemHdl <> 0);
	fbUA_EventItemOperate.SubscriptionHdl := fbUA_EventItemAdd.SubscriptionHdl;
	fbUA_EventItemOperate.EventItemHdl := fbUA_EventItemAdd.EventItemHdl;
	fbUA_EventItemOperate.Timeout := tFB_TIMEOUT;
	fbUA_EventItemOperate();
	IF fbUA_EventItemOperate.Busy = 0 THEN
		IF fbUA_EventItemOperate.Done = 1 THEN
			IF fbUA_EventItemOperate.EventProcessed = 1 THEN
				// Es wurde ein Event empfangen
				ReceivedEvent.nReceivedCount := ReceivedEvent.nReceivedCount + 1;
				// Das Feld EventId wird in einen Hex-String gewandelt
				BrbUsintArrayToHex(ADR(ReceivedEvent.EventId.Data), ReceivedEvent.EventId.Length, ReceivedEvent.sEventIdHex, SIZEOF(ReceivedEvent.sEventIdHex), 0);
			END_IF
		ELSIF fbUA_EventItemOperate.Error = 1 THEN
			// In diesem Beispiel gibt es keine Fehlerbehandlung
		END_IF
		// Baustein für einen erneuten Aufruf zurücksetzen
		fbUA_EventItemOperate.Execute := 0;
		fbUA_EventItemOperate();
	END_IF
		
	// Aufruf aller sonstigen PlcOpen-Funktionsblöcke
	fbUA_Connect();
	fbUA_GetNamespaceIndex();
	fbUA_SubscriptionCreate(PublishingInterval := tSubscriptionPublishingInterval);
	fbUA_NodeGetHandleList();
	fbUA_MonitoredItemAddList(Variables := asMonitoredItemVarNames, MonitoringSettings := aMonitoredItemParameter, ValuesChanged := abMonItemValuesChanged, RemainingValueCount := anMonItemRemainingValueCount, TimeStamps := adtMonItemTimeStamps, NodeQualityIDs := anMonItemNodeQualityId);
	fbUA_NodeGetHandle();
	fbUA_EventItemAdd(EventFields := ClientCfg.Subscriptions.SubEvt.EventFieldVarNames);
	fbUA_MethodGetHandle();
	fbTrigger();
	fbUA_ReadList(Variables := asReadVars);
	fbUA_WriteList(Variables := asReadVars);
	fbUA_MethodCall(InputArguments := ClientCfg.Methods.Method[0].ArgumentsIn, OutputArguments := ClientCfg.Methods.Method[0].ArgumentsOut);

END_PROGRAM

PROGRAM _EXIT
	// Beim Überladen des Tasks wird zuerst der EXIT des alten Tasks ausgeführt und dieser dann gelöscht. Erst dann
	// wird der neue Task ausgeführt.
	// Solange die SPS nicht neu gestartet wird, wäre die Verbindung des alten Tasks immer noch vorhanden. Deshalb
	// sollte sie hier beeendet werden. Dabei werden alle angelegte Ressourcen (Verbindung, Subscriptions, MonitoredItems) sowohl beim Client als
	// auch beim Server aus dem Speicher gelöscht.
	// Auftretende Fehler müssen nicht ausgewertet werden. Deshalb wird nur auf Busy=0 gewartet.
	IF nConnectionHandle <> 0 THEN
		fbUA_Disconnect.Execute := 1;
		fbUA_Disconnect.ConnectionHdl := nConnectionHandle;
		fbUA_Disconnect.Timeout := tFB_TIMEOUT;
		REPEAT
			fbUA_Disconnect();
		UNTIL
			fbUA_Disconnect.Busy = 0
		END_REPEAT;
	END_IF
END_PROGRAM

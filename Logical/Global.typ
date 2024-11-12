
TYPE
	OpcUaTestDatatypes_TYP : 	STRUCT 
		bBool : BOOL;
		nUsint : USINT;
		nUint : UINT;
		nUdint : UDINT;
		nSint : SINT;
		nInt : INT;
		nDint : DINT;
		rReal : REAL;
		rLongReal : LREAL;
		sString : STRING[nOPCUA_STRING_CHAR_MAX];
		tTime : TIME;
		dtDateTime : DATE_AND_TIME;
		anInt : ARRAY[0..nOPCUA_ARRAY_INDEX_MAX]OF INT;
	END_STRUCT;
	OpcUaServerVars_TYP : 	STRUCT 
		WriteOnly : OpcUaTestDatatypes_TYP;
		ReadOnly : OpcUaTestDatatypes_TYP;
		ReadWrite : OpcUaTestDatatypes_TYP;
	END_STRUCT;
	ClientCfgConnectionTYP : 	STRUCT 
		UserIdentityToken : UAUserIdentityToken;
		tSessionTimeout : TIME;
		tMonitorConnection : TIME;
		sServerEndpointUrl : STRING[nENDPOINT_URL_CHAR_MAX];
	END_STRUCT;
	ClientCfgSubscriptionsTYP : 	STRUCT 
		sNamespaceUriOrg : STRING[nNAMESPACE_URI_CHAR_MAX];
		nNamespaceUriOrg : UINT;
		sNamespaceUriBrPv : STRING[nNAMESPACE_URI_CHAR_MAX];
		nNamespaceUriBrPv : UINT;
		SubVar : ARRAY[0..nCLIENT_SUBSCRIPTION_INDEX_MAX]OF ClientCfgSubscriptionVarTYP;
		SubEvt : ClientCfgSubscriptionEvtTYP;
	END_STRUCT;
	ClientCfgSubscriptionVarTYP : 	STRUCT 
		tPublishingInterval : TIME;
		nPriority : BYTE;
		MonitoredItem : ARRAY[0..nCLIENT_MONITORED_ITEM_INDEX_MAX]OF ClientCfgMonItemTYP;
	END_STRUCT;
	ClientCfgMonItemTYP : 	STRUCT 
		NodeId : UANodeID;
		sVarName : STRING[nVAR_NAME_CHAR_MAX];
	END_STRUCT;
	ClientCfgSubscriptionEvtTYP : 	STRUCT 
		tPublishingInterval : TIME;
		nPriority : BYTE;
		NotifierNodeId : UANodeID;
		EventTypeNodeId : UANodeID;
		EventFieldVarNames : ARRAY[0..MAX_INDEX_EVENTFIELDSELECTION]OF STRING[MAX_LENGTH_VARIABLE];
	END_STRUCT;
	ClientCfgReadTYP : 	STRUCT 
		Item : ARRAY[0..nCLIENT_READ_ITEM_INDEX_MAX]OF ClientCfgMonItemTYP;
	END_STRUCT;
	ClientCfgWriteTYP : 	STRUCT 
		Item : ARRAY[0..nCLIENT_WRITE_ITEM_INDEX_MAX]OF ClientCfgMonItemTYP;
	END_STRUCT;
	ClientCfgMethodsTYP : 	STRUCT 
		Method : ARRAY[0..nCLIENT_METHODS_INDEX_MAX]OF ClientCfgMethodTYP;
	END_STRUCT;
	ClientCfgMethodTYP : 	STRUCT 
		ObjectNodeId : UANodeID;
		MethodNodeId : UANodeID;
		ArgumentsIn : ARRAY[0..MAX_INDEX_ARGUMENTS]OF UAMethodArgument;
		ArgumentsOut : ARRAY[0..MAX_INDEX_ARGUMENTS]OF UAMethodArgument;
	END_STRUCT;
	ClientCfgTYP : 	STRUCT 
		Connection : ClientCfgConnectionTYP;
		Subscriptions : ClientCfgSubscriptionsTYP;
		Read : ClientCfgReadTYP;
		Write : ClientCfgWriteTYP;
		Methods : ClientCfgMethodsTYP;
	END_STRUCT;
	ClientConnectionStatus_TYP : 	STRUCT 
		eConnectionStatus : UAConnectionStatus;
		eServerState : UAServerState;
		eServerLevel : BYTE;
	END_STRUCT;
	MethCalculateArgsIn_TYP : 	STRUCT 
		nVal0 : DINT;
		nVal1 : DINT;
		anArray : ARRAY[0..nMETHOD_CALC_ARRAY_INDEX_MAX]OF INT;
	END_STRUCT;
	MethCalculateArgsOut_TYP : 	STRUCT 
		nAddition : DINT;
		nMultiplication : DINT;
		anArray : ARRAY[0..nMETHOD_CALC_ARRAY_INDEX_MAX]OF INT;
	END_STRUCT;
	MethCalculateArgs_TYP : 	STRUCT 
		In : MethCalculateArgsIn_TYP;
		Out : MethCalculateArgsOut_TYP;
	END_STRUCT;
	EventFieldContext_TYP : 	STRUCT 
		nUsint : USINT;
		rReal : REAL;
		sString : STRING[255];
	END_STRUCT;
	ClientReceivedMonItem_TYP : 	STRUCT 
		bValueChanged : BOOL;
		nReceivedCount : UDINT;
	END_STRUCT;
	ProgressEvent_TYP : 	STRUCT 
		nReceivedCount : UDINT;
		EventId : UAByteStringBrbEventId_TYP;
		sEventIdHex : STRING[255];
		EventType : UANodeID;
		LocalTime : UATimeZoneData;
		Message : UALocalizedText;
		ReceiveTime : UaSrv_DateTimeType;
		Severity : UINT;
		SourceName : STRING[nBRBUA_VALUE_TEXT_CHAR_MAX];
		SourceNode : UANodeID;
		Time : UaSrv_DateTimeType;
		Context : EventFieldContext_TYP;
		Progress : UINT;
	END_STRUCT;
	TransitionEvent_TYP : 	STRUCT 
		nReceivedCount : UDINT;
		EventId : UAByteStringBrbEventId_TYP;
		sEventIdHex : STRING[255];
		EventType : UANodeID;
		LocalTime : UATimeZoneData;
		Message : UALocalizedText;
		ReceiveTime : UaSrv_DateTimeType;
		sReceiveTime : STRING[64];
		nSeverity : UINT;
		sSourceName : STRING[nBRBUA_VALUE_TEXT_CHAR_MAX];
		SourceNode : UANodeID;
		FromState : UALocalizedText;
		nFromStateId : UINT;
		ToState : UALocalizedText;
		nToStateId : UINT;
		Transition : UALocalizedText;
		nTransitionId : DINT;
	END_STRUCT;
	PubSubDiagDataMsg_TYP : 	STRUCT 
		nTotal : UDINT;
		nError : UDINT;
	END_STRUCT;
	PubSubDiagData_TYP : 	STRUCT 
		UdpMessage : PubSubDiagDataMsg_TYP;
		DataSet : PubSubDiagDataMsg_TYP;
	END_STRUCT;
END_TYPE

(*General - Status*)

FUNCTION BrbUaGetStatusCodeText : DWORD (*Gibt den symbolischen Text für einen Ua-Status-Code zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		nStatusCode : UDINT; (*Status-Code*)
		pStatusText : STRING[0]; (*Zeiger auf Text*)
		nStatusTextSize : UDINT; (*Größe des Textes*)
	END_VAR
END_FUNCTION
(*General - Nodes*)

FUNCTION BrbUaSetNodeId : DWORD (*Besetzt eine NodeId*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pNodeId : UANodeID; (*Zeiger auf die NodeId*)
		sIdentifier : STRING[0]; (*Knoten-Name*)
		nNamespaceIndex : UINT; (*Namensraum-Index*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaSetNodeIdNum : DWORD (*Besetzt eine numerische NodeId*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pNodeId : UANodeID; (*Zeiger auf die NodeId*)
		nIdentifier : UDINT; (*Knoten-Nummer*)
		nNamespaceIndex : UINT; (*Namensraum-Index*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaGetRandomNodeId : DWORD (*Erzeugt eine zufällige NodeId*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pNodeId : UANodeID; (*Zeiger auf die NodeId*)
		eIdentifierType : UAIdentifierType; (*UAIdentifierType_String, Numeric, GUID oder Opaque*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaAreNodeIdsEqual : BOOL (*Gibt zurück, ob zwei NodeIds gleich sind*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pNodeId1 : UANodeID; (*Zeiger auf die erste NodeId*)
		pNodeId2 : UANodeID; (*Zeiger auf die zweite NodeId*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaAddNodeIdText : DWORD (*Hängt den Text einer NodeId an*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pNodeId : UANodeID; (*Zeiger auf Quelle*)
		pText : STRING[0]; (*Zeiger auf Text*)
		nTextSize : UDINT; (*Größe des Textes*)
	END_VAR
END_FUNCTION
(*General - Attributes*)

FUNCTION BrbUaGetAttributeIdDatatype : UAVariantType (*Gibt den OpcUa-Datentyp für ein Attribut zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		eAttributeId : UAAttributeId; (*Attribut*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaGetAttributeList : DWORD (*Gibt eine Liste mit Attribut-Texten zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pNodeInfo : UANodeInfo; (*Zeiger auf die NodeInfo*)
		pAttributes : BrbUaNodeInfoAttributes_TYP; (*Zeiger auf die Liste der Attrbute*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaAddBooleanText : DWORD (*Hängt den Text eines boolschen Werts an*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		bBoolean : BOOL; (*Quelle*)
		pText : STRING[0]; (*Zeiger auf Text*)
		nTextSize : UDINT; (*Größe des Textes*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaAddNodeClassText : DWORD (*Hängt den Text einer NodeClass an*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		eNodeClass : UANodeClass; (*Quelle*)
		pText : STRING[0]; (*Zeiger auf Text*)
		nTextSize : UDINT; (*Größe des Textes*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaAddDatatypeIdText : DWORD (*Hängt den Text zu einem Datentyp-Identifier an*)
	VAR_INPUT
		nDatatypeId : UDINT; (*Quelle*)
		pText : STRING[0]; (*Zeiger auf Text*)
		nTextSize : UDINT; (*Größe des Textes*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaAddArrayDimensionText : DWORD (*Hängt den Text für eine ArrayDimension an*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pArrayDimension : REFERENCE TO UDINT; (*Zeiger auf Quelle*)
		nValueRank : DINT; (*Anzahl der Dimensionen*)
		pText : STRING[0]; (*Zeiger auf Text*)
		nTextSize : UDINT; (*Größe des Textes*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaAddAccessLevelText : DWORD (*Hängt den Text eines AccessLevels an*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		nAccessLevel : BYTE; (*Quelle*)
		pText : STRING[0]; (*Zeiger auf Text*)
		nTextSize : UDINT; (*Größe des Textes*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaAddEventNotifierText : DWORD (*Hängt den Text eines EventNotifiers an*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		nEventNotifier : BYTE; (*Quelle*)
		pText : STRING[0]; (*Zeiger auf Text*)
		nTextSize : UDINT; (*Größe des Textes*)
	END_VAR
END_FUNCTION
(*General - VariantValues*)

FUNCTION BrbUaClearVariantValue : DWORD (*Löscht den Inhalt eines OpcUa-Values, aber nicht die Datentyp-Angabe*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pUaVariantData : UAVariantData; (*Zeiger auf Variant*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaConvVariantValueFromString : DWORD (*Wandelt einen OpcUa-Value in einen Text*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pUaVariantData : UAVariantData; (*Zeiger auf Variant*)
		pValueText : STRING[0]; (*Zeiger auf Text*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaConvVariantValueToString : DWORD (*Wandelt einen Text in einen OpcUa-Value*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pUaVariantData : UAVariantData; (*Zeiger auf Variant#*)
		pValueText : STRING[0]; (*Zeiger auf Text*)
		nValueTextSize : UDINT; (*Größe des Textes*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaAddVariantValueSubName : DWORD (*Hängt den Element-Namen eines OpcUa-Values anhand des Datentypen an einen Text an*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		eVariantType : UAVariantType; (*Datentyp*)
		pText : STRING[0]; (*Zeiger auf Text*)
		nTextSize : UDINT; (*Größe des Textes*)
	END_VAR
END_FUNCTION
(*General - ByteStrings*)

FUNCTION BrbUaIncByteString : DWORD (*Inkrementiert einen ByteString*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pData : REFERENCE TO USINT; (*Zeiger auf das Daten-Array des ByteStrings*)
		nLength : DINT; (*Länge des Daten-Arrays*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaGetRandomByteString : DWORD (*Erzeugt einen zufälligen ByteString*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pData : REFERENCE TO USINT; (*Zeiger auf das Daten-Array des ByteStrings*)
		nLength : DINT; (*Länge des Daten-Arrays*)
	END_VAR
END_FUNCTION
(*General - Images*)

{REDUND_UNREPLICABLE} FUNCTION_BLOCK BrbUaLoadImage (*Lädt ein Image*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pDevice : REFERENCE TO STRING[0]; (*Zeiger auf den Laufwerks-Namen*)
		pFile : REFERENCE TO STRING[0]; (*Zeiger auf den Datei-Namen*)
		pImageData : REFERENCE TO USINT; (*Zeiger auf die Image-Daten*)
		nImageDataSize : {REDUND_UNREPLICABLE} UDINT; (*Größe der Image-Daten*)
		pImageLength : REFERENCE TO DINT; (*Zeiger auf die Image-Länge*)
	END_VAR
	VAR_OUTPUT
		nStatus : {REDUND_UNREPLICABLE} UINT; (*Fub-Status*)
	END_VAR
	VAR
		eStep : {REDUND_UNREPLICABLE} DINT; (*Step-Nummer für die interne Schrittkette*)
		fbBrbLoadFileBin : {REDUND_UNREPLICABLE} BrbLoadFileBin; (*Interner Fub*)
	END_VAR
END_FUNCTION_BLOCK
(*General - LocalizedTexts*)

FUNCTION BrbUaSetLocalizedText : DWORD (*Besetzt einen LocalizedText*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pLocalizedText : REFERENCE TO BrUaLocalizedText; (*Zeiger auf den LocalizedText*)
		pLocale : STRING[0]; (*Locale-Angabe*)
		pText : STRING[0]; (*Text-Angabe*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaGetRandomLocalizedText : DWORD (*Erzeugt einen zufälligen LocalizedText*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pLocalizedText : REFERENCE TO BrUaLocalizedText; (*Zeiger auf den LocalizedText*)
		nLength : UINT; (*Zu erzeugende Länge des Textes*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaAddLocalizedTextText : DWORD (*Hängt den Text eines LocalizedText an*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pLocalizedText : REFERENCE TO BrUaLocalizedText; (*Zeiger auf den LocalizedText*)
		pText : STRING[0]; (*Zeiger auf Text*)
		nTextSize : UDINT; (*Größe des Textes*)
	END_VAR
END_FUNCTION
(*General - QualifiedNames*)

FUNCTION BrbUaSetQualifedName : DWORD (*Besetzt einen QualifiedName*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pQualifiedName : REFERENCE TO BrUaQualifiedName; (*Zeiger auf den QualifiedName*)
		nNamespaceIndex : UINT; (*Namensraum-Index*)
		pName : STRING[0]; (*Zeiger auf den Namen*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaGetRandomQualifiedName : DWORD (*Erzeugt einen zufälligen QualifiedName*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pQualifiedName : REFERENCE TO BrUaQualifiedName; (*Zeiger auf den QualifiedName*)
		nLength : UINT; (*Zu erzeugende Länge des Namens*)
	END_VAR
END_FUNCTION
(*General - TimeAndDate*)

FUNCTION BrbUaDtStructToUaSrvDateTime : UINT (*Wandelt eine DtStruct-Zeit in eine UaSrvDateTime-Zeit*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pUaSrvDateTime : UaSrv_DateTimeType; (*Zeiger auf eine Struktur "UaSrv_DateTimeType"*)
		pDtStruct : DTStructure; (*Zeiger auf eine Struktur "DTStructure"*)
		nNanoSeconds : UINT; (*Anzahl der Nano-Sekunden (0..999)*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaSrvDateTimeToDtStruct : UINT (*Wandelt eine UaSrvDateTime-Zeit in eine DtStruct-Zeit*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pDtStruct : DTStructure; (*Zeiger auf eine Struktur "DTStructure"*)
		pUaSrvDateTime : UaSrv_DateTimeType; (*Zeiger auf eine Struktur "UaSrv_DateTimeType"*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaGetSrvTimeText : UINT (*Gibt den Text eines Server-Zeitstempels zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pSrvTime : UaSrv_DateTimeType; (*Zeiger auf eine Zeit-Struktur*)
		pText : STRING[0]; (*Zeiger auf den String*)
		nTextSize : UDINT; (*Größe der String-Variablen*)
		nTimeOffset : INT; (*Lokaler Zeit-Offset in [min]*)
		pFormat : STRING[0]; (*Zeiger auf den Formatierungstext*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaGetRandomTimeZone : DWORD (*Erzeugt eine zufällige TimeZone*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pTimeZone : REFERENCE TO BrUaTimeZoneDataType; (*Zeiger auf die TimeZone*)
	END_VAR
END_FUNCTION
(*General - Additional*)

FUNCTION BrbUaGetRandomGuidString : DWORD (*Erzeugt einen zufälligen GuidString im Format '01234567-0123-0123-0123-0123456789AB'*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pGuidString : REFERENCE TO BrUaGuidString; (*Zeiger auf den GuidString*)
		nGuidStringSize : UDINT; (*Größe des Textes*)
		bWithSeparator : BOOL; (*1=Mit Trennzeichen -*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaGetRandomXmlElement : DWORD (*Erzeugt ein zufälliges XmlElement im Format '<Tag Attribute="X">Value</Tag>'*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pXmlElement : BrUaXmlElement; (*Zeiger auf das XmlElement*)
	END_VAR
END_FUNCTION
(*Client - Connection*)

FUNCTION BrbUaGetConnectionStatusText : DWORD (*Gibt einen Verbindungs-Status als Text zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		eConnectionStatus : UAConnectionStatus; (*Verbindungs-Status*)
		pStatusText : STRING[0]; (*Zeiger auf Text*)
		nStatusTextSize : UDINT; (*Größe des Textes*)
	END_VAR
END_FUNCTION
(*Client - RunClient*)

{REDUND_UNREPLICABLE} FUNCTION_BLOCK BrbUaRunClientInit (*Initialisiert eine Client-Instanz*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : REFERENCE TO BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
	END_VAR
	VAR_OUTPUT
		nStatus : {REDUND_UNREPLICABLE} UINT; (*Fub-Status*)
	END_VAR
	VAR
		eStep : {REDUND_UNREPLICABLE} DINT; (*Step-Nummer für die interne Schrittkette*)
		fbDatObjInfo : {REDUND_UNREPLICABLE} DatObjInfo; (*Interner FB*)
		fbDatObjRead : {REDUND_UNREPLICABLE} DatObjRead; (*Interner FB*)
		nAllocStatus : {REDUND_UNREPLICABLE} UINT; (*Interne Variable*)
		nNamespaceIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nNodeHandleIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nReadBlockIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nReadItemIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nWriteBlockIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nWriteItemIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nMethodIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nArgumentInputIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nArgumentOutputIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nSubscriptionIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nMonItemIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nEventItemIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nEventFieldIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nLoopIndex : {REDUND_UNREPLICABLE} UINT; (*Interne Variable*)
		sLine : {REDUND_UNREPLICABLE} STRING[1024]; (*Interne Variable*)
		nLineLen : {REDUND_UNREPLICABLE} UDINT; (*Interne Variable*)
		sValue : {REDUND_UNREPLICABLE} STRING[1024]; (*Interne Variable*)
		nValue : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		rValue : {REDUND_UNREPLICABLE} REAL; (*Interne Variable*)
		sVarName : {REDUND_UNREPLICABLE} STRING[nBRBUA_VARNAME_TEXT_CHAR_MAX]; (*Interne Variable*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_UNREPLICABLE} FUNCTION_BLOCK BrbUaRunClientCyclic (*Behandelt eine Client-Instanz*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : REFERENCE TO BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
	END_VAR
	VAR_OUTPUT
		nStatus : {REDUND_UNREPLICABLE} UINT; (*Fub-Status*)
	END_VAR
	VAR
		eStep : {REDUND_UNREPLICABLE} DINT; (*Step-Nummer für die interne Schrittkette*)
		fbUA_Connect : {REDUND_UNREPLICABLE} UA_Connect; (*Interner FB*)
		eCmdOld : {REDUND_UNREPLICABLE} BrbUaRcCommandos_ENUM; (*Interne Variable*)
		fbUA_GetNamespaceIndex : {REDUND_UNREPLICABLE} UA_GetNamespaceIndex; (*Interner FB*)
		nNamespaceIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		fbUA_NodeGetHandleList : {REDUND_UNREPLICABLE} UA_NodeGetHandleList; (*Interner FB*)
		nNodeHandleIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nReadBlockIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nWriteBlockIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		fbUA_MethodGetHandle : {REDUND_UNREPLICABLE} UA_MethodGetHandle; (*Interner FB*)
		nMethodIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		fbUA_SubscriptionCreate : {REDUND_UNREPLICABLE} UA_SubscriptionCreate; (*Interner FB*)
		nSubscriptionIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		fbUA_MonitoredItemAddList : {REDUND_UNREPLICABLE} UA_MonitoredItemAddList; (*Interner FB*)
		nMonItemIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nEventItemIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nEventFieldIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nLoopIndex : {REDUND_UNREPLICABLE} UINT; (*Interne Variable*)
		sVarName : {REDUND_UNREPLICABLE} STRING[nBRBUA_VARNAME_TEXT_CHAR_MAX]; (*Interne Variable*)
		fbUA_NodeGetHandle : {REDUND_UNREPLICABLE} UA_NodeGetHandle; (*Interner FB*)
		fbUA_EventItemAdd : {REDUND_UNREPLICABLE} UA_EventItemAdd; (*Interner FB*)
		fbUA_ConnectionGetStatus : {REDUND_UNREPLICABLE} UA_ConnectionGetStatus; (*Interner FB*)
		eClientStateOld : {REDUND_UNREPLICABLE} BrbUaRcClientStates_ENUM;
		bEventItemFound : {REDUND_UNREPLICABLE} BOOL; (*Interne Variable*)
		pEventItemReceived : REFERENCE TO BOOL; (*Interne Variable*)
		fbUA_EventItemOperate : {REDUND_UNREPLICABLE} UA_EventItemOperate; (*Interner FB*)
		fbUA_Disconnect : {REDUND_UNREPLICABLE} UA_Disconnect; (*Interner FB*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_UNREPLICABLE} FUNCTION_BLOCK BrbUaRunClientExit (*Exilisiert eine Client-Instanz*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : REFERENCE TO BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
	END_VAR
	VAR_OUTPUT
		nStatus : {REDUND_UNREPLICABLE} UINT; (*Fub-Status*)
	END_VAR
	VAR
		eStep : {REDUND_UNREPLICABLE} DINT; (*Step-Nummer für die interne Schrittkette*)
		fbUA_Disconnect : {REDUND_UNREPLICABLE} UA_Disconnect; (*Interner FB*)
		nReadBlockIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nWriteBlockIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nSubscriptionIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nEventItemIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nFreeStatus : {REDUND_UNREPLICABLE} UINT; (*Interne Variable*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK BrbUaRcReadBlock (*Liest eine ReadBlock vom Server*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : REFERENCE TO BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nReadBlockIndex : {REDUND_UNREPLICABLE} UINT; (*0-basierter Index des ReadBlocks*)
	END_VAR
	VAR_OUTPUT
		nStatus : {REDUND_UNREPLICABLE} UINT; (*Fub-Status*)
		nErrorId : {REDUND_UNREPLICABLE} DWORD; (*OpcUa-Fehler-Status*)
		sErrorId : {REDUND_UNREPLICABLE} STRING[nBRBUA_STATUS_TEXT_CHAR_MAX]; (*OpcUa-Fehler-Text*)
		nReadCount : UDINT; (*Anzahl der Reads*)
	END_VAR
	VAR
		eStep : {REDUND_UNREPLICABLE} DINT; (*Step-Nummer für die interne Schrittkette*)
		fbUaClt_ReadBulk : {REDUND_UNREPLICABLE} UaClt_ReadBulk; (*Interner FB*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_UNREPLICABLE} FUNCTION_BLOCK BrbUaRcWriteBlock (*Liest eine ReadBlock vom Server*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : REFERENCE TO BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nWriteBlockIndex : {REDUND_UNREPLICABLE} UINT; (*0-basierter Index des WriteBlocks*)
	END_VAR
	VAR_OUTPUT
		nStatus : {REDUND_UNREPLICABLE} UINT; (*Fub-Status*)
		nErrorId : {REDUND_UNREPLICABLE} DWORD; (*OpcUa-Fehler-Status*)
		sErrorId : {REDUND_UNREPLICABLE} STRING[nBRBUA_STATUS_TEXT_CHAR_MAX]; (*OpcUa-Fehler-Text*)
		nWriteCount : {REDUND_UNREPLICABLE} UDINT; (*Anzahl der Writes*)
	END_VAR
	VAR
		eStep : {REDUND_UNREPLICABLE} DINT; (*Step-Nummer für die interne Schrittkette*)
		fbUaClt_WriteBulk : {REDUND_UNREPLICABLE} UaClt_WriteBulk; (*Interner FB*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_UNREPLICABLE} FUNCTION_BLOCK BrbUaRcCallMethod (*Liest eine ReadBlock vom Server*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : REFERENCE TO BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nMethodIndex : {REDUND_UNREPLICABLE} UINT; (*0-basierter Index der Method*)
	END_VAR
	VAR_OUTPUT
		bInit : {REDUND_UNREPLICABLE} BOOL; (*Vor dem Call für einen Zyklus auf 1*)
		nStatus : {REDUND_UNREPLICABLE} UINT; (*Fub-Status*)
		nErrorId : {REDUND_UNREPLICABLE} DWORD; (*OpcUa-Fehler-Status*)
		sErrorId : {REDUND_UNREPLICABLE} STRING[nBRBUA_STATUS_TEXT_CHAR_MAX]; (*OpcUa-Fehler-Text*)
		nCallCount : {REDUND_UNREPLICABLE} UDINT; (*Anzahl der Calls*)
	END_VAR
	VAR
		nArgumentIndex : {REDUND_UNREPLICABLE} UINT; (*Interne Variable*)
		aInputArguments : {REDUND_UNREPLICABLE} ARRAY[0..MAX_INDEX_ARGUMENTS] OF UAMethodArgument; (*Interne Variable*)
		aOutputArguments : {REDUND_UNREPLICABLE} ARRAY[0..MAX_INDEX_ARGUMENTS] OF UAMethodArgument; (*Interne Variable*)
		eStep : {REDUND_UNREPLICABLE} DINT; (*Step-Nummer für die interne Schrittkette*)
		fbUA_MethodCall : {REDUND_UNREPLICABLE} UA_MethodCall; (*Interner FB*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION BrbUaRcGetSrvNamespace : UINT (*Gibt den Server-Namespace aufgrund des DatObj-NamespaceIndex zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nDatObjNamespaceIndex : UINT; (*0-basierter Index des Namespaces im Datenobjekt*)
		pServerNamespace : BrbUaRcNamespace_TYP; (*Zeiger auf die zu füllende Struktur*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRcGetNodeHandle : UINT (*Gibt einen ermittelten NodeHandle zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nNodeHandleIndex : UINT; (*0-basierter Index des NodeHandles*)
		pNodeHandle : BrbUaRcNodeHandle_TYP; (*Zeiger auf die zu füllende Struktur*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRcGetReadBlock : UINT (*Gibt einen ermittelten ReadBlock zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nReadBlockIndex : UINT; (*0-basierter Index des ReadBlocks*)
		pReadBlock : BrbUaRcReadBlock_TYP; (*Zeiger auf die zu füllende Struktur*)
		pReadBlockIntern : BrbUaRcReadBlockIntern_TYP; (*Zeiger auf die optional zu füllende, interne Struktur*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRcGetReadItem : UINT (*Gibt ein ermitteltes ReadItem zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nReadBlockIndex : UINT; (*0-basierter Index des ReadBlocks*)
		nReadItemIndex : UINT; (*0-basierter Index des ReadItems*)
		pReadItem : BrbUaRcReadItem_TYP; (*Zeiger auf die zu füllende Struktur*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRcGetWriteBlock : UINT (*Gibt einen ermittelten ReadBlock zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nWriteBlockIndex : UINT; (*0-basierter Index des WriteBlocks*)
		pWriteBlock : BrbUaRcWriteBlock_TYP; (*Zeiger auf die zu füllende Struktur*)
		pWriteBlockIntern : BrbUaRcWriteBlockIntern_TYP; (*Zeiger auf die optional zu füllende, interne Struktur*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRcGetWriteItem : UINT (*Gibt ein ermitteltes ReadItem zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nWriteBlockIndex : UINT; (*0-basierter Index des WriteBlocks*)
		nWriteItemIndex : UINT; (*0-basierter Index des WriteItems*)
		pWriteItem : BrbUaRcWriteItem_TYP; (*Zeiger auf die zu füllende Struktur*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRcGetMethod : UINT (*Gibt eine ermittelte Methode zuück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nMethodIndex : UINT; (*0-basierter Index der Method*)
		pMethod : BrbUaRcMethod_TYP; (*Zeiger auf die zu füllende Struktur*)
		pMethodIntern : BrbUaRcMethodIntern_TYP; (*Zeiger auf die optional zu füllende, interne Struktur*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRcGetArgument : UINT (*Gibt ein ermitteltes ReadItem zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nMethodIndex : UINT; (*0-basierter Index der Method*)
		bOutput : BOOL; (*0=Eingangs-Argument, 1=Ausgangs-Argument*)
		nArgumentIndex : UINT; (*0-basierter Index des Arguments*)
		pArgument : UAMethodArgument; (*Zeiger auf die zu füllende Struktur*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRcGetSubscription : UINT (*Gibt eine ermittelte Subscription zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nSubscriptionIndex : UINT; (*0-basierter Index der Subscription*)
		pSubscription : BrbUaRcSubscription_TYP; (*Zeiger auf die zu füllende Struktur*)
		pSubscriptionIntern : BrbUaRcSubscriptionIntern_TYP; (*Zeiger auf die optional zu füllende, interne Struktur*)
	END_VAR
END_FUNCTION

{REDUND_UNREPLICABLE} FUNCTION_BLOCK BrbUaRcSetSubscription (*Ändert die Parameter einer Subscription*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : REFERENCE TO BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nSubscriptionIndex : {REDUND_UNREPLICABLE} UINT; (*0-basierter Index der Subscription*)
		pSubscription : REFERENCE TO BrbUaRcSubscription_TYP; (*Zeiger auf die zu ändernden Werte*)
	END_VAR
	VAR_OUTPUT
		nStatus : {REDUND_UNREPLICABLE} DINT; (*Fub-Status*)
		bPublished : {REDUND_UNREPLICABLE} BOOL; (*Daten veröffentlicht seit dem letzten Aufruf*)
		nErrorId : {REDUND_UNREPLICABLE} DWORD; (*OpcUa-Fehler-Status*)
		sErrorId : {REDUND_UNREPLICABLE} STRING[80]; (*OpcUa-Fehler-Text*)
	END_VAR
	VAR
		eStep : {REDUND_UNREPLICABLE} DINT; (*Step-Nummer für die interne Schrittkette*)
		fbUA_SubscriptionOperate : {REDUND_UNREPLICABLE} UA_SubscriptionOperate; (*Interner FB*)
		tPublishingInterval : {REDUND_UNREPLICABLE} TIME; (*Interne Variable*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION BrbUaRcGetMonitoredItem : UINT (*Gibt ein ermitteltes MonitoredItem zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nSubscriptionIndex : UINT; (*0-basierter Index der Subscription*)
		nMonitoredItemIndex : UINT; (*0-basierter Index des MonitoredItems*)
		pMonitoredItem : BrbUaRcMonitoredItem_TYP; (*Zeiger auf die zu füllende Struktur*)
	END_VAR
END_FUNCTION

FUNCTION_BLOCK BrbUaRcSetMonitoredItem (*Ändert die Parameter eines MonitoredItems*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : REFERENCE TO BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nSubscriptionIndex : {REDUND_UNREPLICABLE} UINT; (*0-basierter Index der Subscription*)
		nMonitoredItemIndex : {REDUND_UNREPLICABLE} UINT; (*0-basierter Index des MonitoredItems*)
		pMonitoringSettings : REFERENCE TO UAMonitoringSettings; (*Zeiger auf die zu ändernden Werte*)
	END_VAR
	VAR_OUTPUT
		nStatus : {REDUND_UNREPLICABLE} DINT; (*Fub-Status*)
		bValueChanged : {REDUND_UNREPLICABLE} BOOL; (*Der Wert der überwachten Variable hat sich geändert*)
		dtTimestamp : {REDUND_UNREPLICABLE} DATE_AND_TIME; (*Zeitstempel der Änderung*)
		nErrorId : {REDUND_UNREPLICABLE} DWORD; (*OpcUa-Fehler-Status*)
		sErrorId : {REDUND_UNREPLICABLE} STRING[80]; (*OpcUa-Fehler-Text*)
	END_VAR
	VAR
		eStep : {REDUND_UNREPLICABLE} DINT; (*Step-Nummer für die interne Schrittkette*)
		fbUA_MonitoredItemOperate : {REDUND_UNREPLICABLE} UA_MonitoredItemOperate; (*Interner FB*)
		MonitoredItemIntern : BrbUaRcMonitoredItem_TYP; (*Interne Variable*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION BrbUaRcGetMiValueChanged : BOOL (*Gibt das ValueChanged-Flag eines MonitoredItems zurück und löscht es optional*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nSubscriptionIndex : UINT; (*0-basierter Index der Subscription*)
		nMonitoredItemIndex : UINT; (*0-basierter Index des MonitoredItems*)
		bClear : BOOL; (*1=Flag löschen*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRcGetMiRemainingValueCount : UINT (*Gibt den RemainingValue-Zähler eines MonitoredItems zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nSubscriptionIndex : UINT; (*0-basierter Index der Subscription*)
		nMonitoredItemIndex : UINT; (*0-basierter Index des MonitoredItems*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRcGetEventItem : UINT (*Gibt ein ermitteltes EventItem zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nSubscriptionIndex : UINT; (*0-basierter Index der Subscription*)
		nEventItemIndex : UINT; (*0-basierter Index des EventItems*)
		pEventItem : BrbUaRcEventItem_TYP; (*Zeiger auf die zu füllende Struktur*)
		pEventItemIntern : BrbUaRcEventItemIntern_TYP; (*Zeiger auf die optional zu füllende, interne Struktur*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRcGetEventItemReceived : BOOL (*Gibt zurück, ob ein Event empfangen wurde*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nSubscriptionIndex : UINT; (*0-basierter Index der Subscription*)
		nEventItemIndex : UINT; (*0-basierter Index des EventItems*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRcGetEventItemReceiveCount : UDINT (*Gibt zurück, wie oft ein Event empfangen wurde*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nSubscriptionIndex : UINT; (*0-basierter Index der Subscription*)
		nEventItemIndex : UINT; (*0-basierter Index des EventItems*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRcGetEventField : UINT (*Gibt ein ermitteltes EventField zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		nSubscriptionIndex : UINT; (*0-basierter Index der Subscription*)
		nEventItemIndex : UINT; (*0-basierter Index des EventItems*)
		nEventFieldIndex : UINT; (*0-basierter Index des EventFields*)
		pEventField : BrbUaRcEventField_TYP; (*Zeiger auf die zu füllende Struktur*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRcMonitor : UINT (*Zeigt die Inhalte des internen Speichers*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunClient : BrbUaRunClient_TYP; (*Zeiger auf die RunClient-Struktur*)
		pMonitor : BrbUaRcMonitor_TYP; (*Zeiger auf die Monitor-Struktur*)
	END_VAR
END_FUNCTION
(*Server - Methods*)

FUNCTION BrbUaSrvHandleMethod : DWORD (*Behandelt einen Methoden-Aufruf*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pMethod : BrbUaSrvMethod_TYP; (*Zeiger auf die Methode*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaSrvGetMethodOperateText : DWORD (*Gibt den Text einer MethodOperateAction zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		eAction : UaMethodOperateAction; (*Angabe der Aktion*)
		pActionText : STRING[0]; (*Zeiger auf den String*)
		nActionTextSize : UDINT; (*Größe des Strings*)
	END_VAR
END_FUNCTION
(*Server - RunServer*)

{REDUND_UNREPLICABLE} FUNCTION_BLOCK BrbUaRunServerInit (*Initialisiert eine Server-Instanz*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunServer : REFERENCE TO BrbUaRunServer_TYP; (*Zeiger auf die RunServer-Struktur*)
	END_VAR
	VAR_OUTPUT
		nStatus : {REDUND_UNREPLICABLE} UINT; (*Fub-Status*)
	END_VAR
	VAR
		eStep : {REDUND_UNREPLICABLE} DINT; (*Step-Nummer für die interne Schrittkette*)
		fbDatObjInfo : {REDUND_UNREPLICABLE} DatObjInfo; (*Interner FB*)
		fbDatObjRead : {REDUND_UNREPLICABLE} DatObjRead; (*Interner FB*)
		nAllocStatus : {REDUND_UNREPLICABLE} UINT; (*Interne Variable*)
		nNamespaceIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nEventIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nEventFieldIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nLoopIndex : {REDUND_UNREPLICABLE} UINT; (*Interne Variable*)
		sLine : {REDUND_UNREPLICABLE} STRING[1024]; (*Interne Variable*)
		nLineLen : {REDUND_UNREPLICABLE} UDINT; (*Interne Variable*)
		sValue : {REDUND_UNREPLICABLE} STRING[1024]; (*Interne Variable*)
		nValue : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		rValue : {REDUND_UNREPLICABLE} REAL; (*Interne Variable*)
		sVarName : {REDUND_UNREPLICABLE} STRING[nBRBUA_VARNAME_TEXT_CHAR_MAX]; (*Interne Variable*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_UNREPLICABLE} FUNCTION_BLOCK BrbUaRunServerCyclic (*Behandelt eine Server-Instanz*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunServer : REFERENCE TO BrbUaRunServer_TYP; (*Zeiger auf die RunServer-Struktur*)
	END_VAR
	VAR_OUTPUT
		nStatus : {REDUND_UNREPLICABLE} UINT; (*Fub-Status*)
	END_VAR
	VAR
		eStep : {REDUND_UNREPLICABLE} DINT; (*Step-Nummer für die interne Schrittkette*)
		fbUaSrv_GetNamespaceIndex : {REDUND_UNREPLICABLE} UaSrv_GetNamespaceIndex; (*Interner FB*)
		nNamespaceIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nLoopIndex : {REDUND_UNREPLICABLE} UINT; (*Interne Variable*)
		nEventIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nEventFieldIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_UNREPLICABLE} FUNCTION_BLOCK BrbUaRunServerExit (*Exilisiert eine Server-Instanz*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunServer : REFERENCE TO BrbUaRunServer_TYP; (*Zeiger auf die RunServer-Struktur*)
	END_VAR
	VAR_OUTPUT
		nStatus : {REDUND_UNREPLICABLE} UINT; (*Fub-Status*)
	END_VAR
	VAR
		eStep : {REDUND_UNREPLICABLE} DINT; (*Step-Nummer für die interne Schrittkette*)
		nEventIndex : {REDUND_UNREPLICABLE} DINT; (*Interne Variable*)
		nFreeStatus : {REDUND_UNREPLICABLE} UINT; (*Interne Variable*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK BrbUaRsFireEvent (*Liest eine ReadBlock vom Server*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunServer : REFERENCE TO BrbUaRunServer_TYP; (*Zeiger auf die RunServer-Struktur*)
		nEventIndex : {REDUND_UNREPLICABLE} UINT; (*0-basierter Index des Events*)
	END_VAR
	VAR_OUTPUT
		bInit : {REDUND_UNREPLICABLE} BOOL; (*Vor dem Fire für einen Zyklus auf 1*)
		nStatus : {REDUND_UNREPLICABLE} UINT; (*Fub-Status*)
		nErrorId : {REDUND_UNREPLICABLE} DWORD; (*OpcUa-Fehler-Status*)
		sErrorId : {REDUND_UNREPLICABLE} STRING[nBRBUA_STATUS_TEXT_CHAR_MAX]; (*OpcUa-Fehler-Text*)
		nFireCount : UDINT; (*Anzahl der gefeuerten Events*)
	END_VAR
	VAR
		eStep : {REDUND_UNREPLICABLE} DINT; (*Step-Nummer für die interne Schrittkette*)
		fbUaSrv_FireEvent : {REDUND_UNREPLICABLE} UaSrv_FireEvent; (*Interner FB*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION BrbUaRsGetNamespace : UINT (*Gibt den Server-Namespace aufgrund des DataObjekt-NamespaceIndex zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunServer : BrbUaRunServer_TYP; (*Zeiger auf die RunClient-Struktur*)
		nDatObjNamespaceIndex : UINT; (*0-basierter Index des Namespaces im Datenobjekt*)
		pServerNamespace : BrbUaRsNamespace_TYP; (*Zeiger auf die zu füllende Struktur*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRsGetEvent : UINT (*Gibt ein ermitteltes Event zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunServer : BrbUaRunServer_TYP; (*Zeiger auf die RunClient-Struktur*)
		nEventIndex : UINT; (*0-basierter Index des Events*)
		pEvent : BrbUaRsEvent_TYP; (*Zeiger auf die zu füllende Struktur*)
		pEventIntern : BrbUaRsEventIntern_TYP; (*Zeiger auf die optional zu füllende, interne Struktur*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRsGetEventField : UINT (*Gibt ein ermitteltes Field zurück*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunServer : BrbUaRunServer_TYP; (*Zeiger auf die RunClient-Struktur*)
		nEventIndex : UINT; (*0-basierter Index des Events*)
		nEventFieldIndex : UINT; (*0-basierter Index des Fields*)
		pEventField : UaSrv_FireEventFieldType; (*Zeiger auf die zu füllende Struktur*)
	END_VAR
END_FUNCTION

FUNCTION BrbUaRsMonitor : UINT (*Zeigt die Inhalte des internen Speichers*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		pRunServer : BrbUaRunServer_TYP; (*Zeiger auf die RunServer-Struktur*)
		pMonitor : BrbUaRsMonitor_TYP; (*Zeiger auf die Monitor-Struktur*)
	END_VAR
END_FUNCTION

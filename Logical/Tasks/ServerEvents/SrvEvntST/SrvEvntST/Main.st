
PROGRAM _INIT
	// Ablöschen der Funktionsblöcke und Strukturen 
	brsmemset(ADR(fbUaSrv_GetNamespaceIndex), 0, SIZEOF(fbUaSrv_GetNamespaceIndex));
	brsmemset(ADR(fbUaSrv_FireEvent), 0, SIZEOF(fbUaSrv_FireEvent));
	brsmemset(ADR(Fields), 0, SIZEOF(Fields));
	
	// Setzen des Events 'ProgressEventType'
	fbUaSrv_FireEvent.EventType.NamespaceIndex := 0; // Wird in der Schrittkette ermittelt
	fbUaSrv_FireEvent.EventType.IdentifierType := UAIdentifierType_Numeric;
	fbUaSrv_FireEvent.EventType.Identifier := '11436'; // ProgressEventType
	
	//Parametrieren der anwenderseitigen Felder
	nFieldIndex := 0;
	Fields.FieldCfg[nFieldIndex].BrowsePath := '/Message';
	Fields.FieldCfg[nFieldIndex].Variable := '::SrvEvntST:Fields.Message';
	nFieldIndex := nFieldIndex + 1;
	Fields.FieldCfg[nFieldIndex].BrowsePath := '/Severity';
	Fields.FieldCfg[nFieldIndex].Variable := '::SrvEvntST:Fields.nSeverity';
	nFieldIndex := nFieldIndex + 1;
	Fields.FieldCfg[nFieldIndex].BrowsePath := '/Context';
	Fields.FieldCfg[nFieldIndex].Variable := '::SrvEvntST:Fields.Context'; // Hier könnte auch eine Variable eines anderen Standard-Datentyps angebunden werden
	nFieldIndex := nFieldIndex + 1;
	Fields.FieldCfg[nFieldIndex].BrowsePath := '/Progress';
	Fields.FieldCfg[nFieldIndex].Variable := '::SrvEvntST:Fields.nProgress';
	// Die Felder 'EventId', 'EventType', 'LocalTime', 'ReceiveTime', 'SourceName', 'SourceNode' und 'Time'
	// werden nicht übergeben und daher automatisch vom Betriebssystem besetzt.

	fbUaSrv_FireEvent.EventFieldCount := nFieldIndex + 1;
	
	// Sonstige Initialisierung
	fbDelay.PT := t#5s;
	bSuspendTimer := 0;

	// Initialisierung der Schrittkette
	Step.eStepNr := eSTEP_INIT;
	
END_PROGRAM

PROGRAM _CYCLIC
	// Schrittkette
	CASE Step.eStepNr OF
		eSTEP_INIT:
			// Start
			nNamespaceIndexBrPv := 0;
			bFire := 0;
			Step.eStepNr := eSTEP_GET_NS_ORG;
	
		eSTEP_GET_NS_ORG:
			// Ermitteln des Namespace-Index für Foundation-Adressbereich am B&R-Server
			fbUaSrv_GetNamespaceIndex.Execute := 1;
			fbUaSrv_GetNamespaceIndex.NamespaceUri := 'http://opcfoundation.org/UA/';
			IF fbUaSrv_GetNamespaceIndex.Done = 1 THEN
				fbUaSrv_GetNamespaceIndex.Execute := 0;
				nNamespaceIndexFoundation := fbUaSrv_GetNamespaceIndex.NamespaceIndex;
				fbUaSrv_FireEvent.EventType.NamespaceIndex := nNamespaceIndexFoundation;
				Step.eStepNr := eSTEP_GET_NS_BR_PV;
			ELSIF fbUaSrv_GetNamespaceIndex.Error = 1 THEN
				fbUaSrv_GetNamespaceIndex.Execute := 0;
				Step.eErrorStep := eSTEP_GET_NS_ORG;
				Step.nErrorId := fbUaSrv_GetNamespaceIndex.ErrorID;
				Step.nFieldIndex := -1;
				Step.eStepNr := eSTEP_GET_NS_ORG;
			END_IF
	
		eSTEP_GET_NS_BR_PV:
			// Ermitteln des Namespace-Index für PV-Adressbereich am B&R-Server
			fbUaSrv_GetNamespaceIndex.Execute := 1;
			fbUaSrv_GetNamespaceIndex.NamespaceUri := 'http://br-automation.com/OpcUa/PLC/PV/';
			IF fbUaSrv_GetNamespaceIndex.Done = 1 THEN
				fbUaSrv_GetNamespaceIndex.Execute := 0;
				nNamespaceIndexBrPv := fbUaSrv_GetNamespaceIndex.NamespaceIndex;
				Step.eStepNr := eSTEP_DELAY;
			ELSIF fbUaSrv_GetNamespaceIndex.Error = 1 THEN
				fbUaSrv_GetNamespaceIndex.Execute := 0;
				Step.eErrorStep := eSTEP_GET_NS_BR_PV;
				Step.nErrorId := fbUaSrv_GetNamespaceIndex.ErrorID;
				Step.nFieldIndex := -1;
				Step.eStepNr := eSTEP_GET_NS_BR_PV;
			END_IF
	
		eSTEP_DELAY:
			// Warten, bis Event gefeuert werden soll
			fbDelay.IN := NOT(bSuspendTimer);
			IF fbDelay.Q = 1 THEN
				fbDelay.IN := 0;
				bFire := 1;
			END_IF
			IF bFire = 1 THEN
				bFire := 0;
				Step.eStepNr := eSTEP_SET_FIELD_VALUES;
			END_IF
	
		eSTEP_SET_FIELD_VALUES:
			// Fortschritt erhöhen
			Fields.nProgress := Fields.nProgress + 1;
			IF Fields.nProgress > 100 THEN
				Fields.nProgress := 0;
			END_IF
			// Besetzen der anwenderseitigen Felder. Sie können bei jedem Feuern anders besetzt werden.
			Fields.Message.Locale := 'en';
			brsstrcpy(ADR(Fields.Message.Text), ADR('Progress at Task $'SrvEvntST$' has changed to $''));
			brsitoa(UINT_TO_DINT(Fields.nProgress), ADR(sHelp));
			brsstrcat(ADR(Fields.Message.Text), ADR(sHelp));
			brsstrcat(ADR(Fields.Message.Text), ADR('$'.'));
			Fields.nSeverity := UDINT_TO_UINT(BrbGetRandomUdint(1, 500));
			Fields.Context.nUsint := DINT_TO_USINT(BrbGetRandomDint(0,255));
			Fields.Context.rReal := BrbGetRandomPercent();
			BrbUsintToHex(Fields.Context.nUsint, Fields.Context.sString, SIZEOF(Fields.Context.sString), 0);
			Step.eStepNr := eSTEP_FIRE;
	
		eSTEP_FIRE:
			fbUaSrv_FireEvent.Execute := 1;
			IF fbUaSrv_FireEvent.Done = 1 THEN
				fbUaSrv_FireEvent.Execute := 0;
				Step.eStepNr := eSTEP_DELAY;
			ELSIF fbUaSrv_FireEvent.Error = 1 THEN
				fbUaSrv_FireEvent.Execute := 0;
				IF fbUaSrv_FireEvent.ErrorID > 0 THEN
					Step.eErrorStep := eSTEP_FIRE;
					Step.nErrorId := fbUaSrv_FireEvent.ErrorID;
					Step.nFieldIndex := -1;
				ELSE
					// Fehler in einem der Fields
					FOR nFieldIndex := 0 TO fbUaSrv_FireEvent.EventFieldCount DO
						IF Fields.FieldCfg[nFieldIndex].ErrorID > 0 THEN
							Step.eErrorStep := eSTEP_FIRE;
							Step.nErrorId := Fields.FieldCfg[nFieldIndex].ErrorID;
							Step.nFieldIndex := nFieldIndex;
						END_IF
					END_FOR
				END_IF
				Step.eStepNr := eSTEP_DELAY;
			END_IF
	
	END_CASE

		// Aufruf des FB's
		fbUaSrv_GetNamespaceIndex();
		fbDelay();
		fbUaSrv_FireEvent(EventFields := Fields.FieldCfg[0]);

END_PROGRAM

PROGRAM _EXIT
END_PROGRAM


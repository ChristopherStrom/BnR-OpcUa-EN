
ACTION InitAirCond: 
	// Logik
	pInstance.Act.eOperationMode := eAC_OPERATIONMODE_OFF;
	pInstance.Act.rTemperature := rAIR_COND_TEMP_OUTSIDE;
	pInstance.Act.nFanLevel := 0;
	pInstance.Set.rTemperature := 20.0;	
	pInstance.Set.nFanLevel := 0;
END_ACTION

ACTION OperateAirCond: 
	// Methode 'SetOperationMode'
	CASE pIntern.MethSetOperationMode.nStep OF
		0:
			// Prüfen, ob Methode von einem Client aufgerufen wurde
			pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.Execute := 1;
			pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.Action := UaMoa_CheckIsCalled;
			IF pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.Done = 1 THEN
				pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.Execute := 0;
				IF pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.IsCalled = 1 THEN
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					pIntern.MethSetOperationMode.nStep := 1;
				END_IF
			ELSIF pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.Error = 1 THEN
				// Fehler, aber trotzdem weiter machen
				pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.Execute := 0;
			END_IF

		1:
			// Ausführen der Methode
			IF pIntern.MethSetOperationMode.ArgsIn.eOperationMode >= eAC_OPERATIONMODE_OFF AND pIntern.MethSetOperationMode.ArgsIn.eOperationMode <= eAC_OPERATIONMODE_AUTO THEN
				pInstance.Act.eOperationMode := pIntern.MethSetOperationMode.ArgsIn.eOperationMode;
				pIntern.MethSetOperationMode.ArgsOut.eStatus := eAC_METH_STATUS_OK;
			ELSE
				pIntern.MethSetOperationMode.ArgsOut.eStatus := eAC_METH_STATUS_INVALID_OPMODE;
			END_IF
			pIntern.MethSetOperationMode.nStep := 2;

		2:
			// Rückmelden, dass Methode ausgeführt wurde. Zu diesem Zeitpunkt müssen die Ausgangs-Argumente besetzt sein und dürfen nicht mehr geändert werden
			pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.Execute := 1;
			pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.Action := UaMoa_Finished;
			IF pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.Done = 1 THEN
				pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.Execute := 0;
				pIntern.MethSetOperationMode.nStep := 0;
			ELSIF pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.Error = 1 THEN
				// Fehler, aber trotzdem weiter machen
				pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.Execute := 0;
				pIntern.MethSetOperationMode.nStep := 0;
			END_IF

	END_CASE
	pIntern.MethSetOperationMode.fbUaSrv_MethodOperate();

	// Begrenzung der SetTemp
	IF pInstance.Set.rTemperature < rAIR_COND_TEMP_MIN THEN
		pInstance.Set.rTemperature := rAIR_COND_TEMP_MIN;
	ELSIF pInstance.Set.rTemperature > rAIR_COND_TEMP_OUTSIDE THEN
		pInstance.Set.rTemperature := rAIR_COND_TEMP_OUTSIDE;
	END_IF
	// Berechnung der internen Werte (Abweichung in Prozent)
	pIntern.rDiff := pInstance.Act.rTemperature - pInstance.Set.rTemperature;
	pIntern.rDiffPercent := pIntern.rDiff / pInstance.Act.rTemperature * 100.0;
	// Steuern des Lüfters
	IF pInstance.Act.eOperationMode = eAC_OPERATIONMODE_OFF THEN
		// Lüfter ausschalten
		pInstance.Act.nFanLevel := 0;
	ELSIF pInstance.Act.eOperationMode = eAC_OPERATIONMODE_MANUAL THEN
		// Lüfter-Stufe aus manueller Vorgabe übernehmen
		IF pInstance.Set.nFanLevel > 5 THEN
			pInstance.Act.nFanLevel := 5;
		ELSE
			pInstance.Act.nFanLevel := pInstance.Set.nFanLevel;
		END_IF
	ELSIF pInstance.Act.eOperationMode = eAC_OPERATIONMODE_AUTO THEN
		// Lüfter-Stufe je nach Temperatur-Differenz setzen
		IF pIntern.rDiffPercent <= 0.0 THEN
			pInstance.Act.nFanLevel := 0;
		ELSIF pIntern.rDiffPercent <= 10.0 THEN
			pInstance.Act.nFanLevel := 1;
		ELSIF pIntern.rDiffPercent <= 15.0 THEN
			pInstance.Act.nFanLevel := 2;
		ELSIF pIntern.rDiffPercent <= 20.0 THEN
			pInstance.Act.nFanLevel := 3;
		ELSIF pIntern.rDiffPercent <= 25.0 THEN
			pInstance.Act.nFanLevel := 4;
		ELSE 
			pInstance.Act.nFanLevel := 5;
		END_IF
	END_IF
	SimulateAirCond;
	
	// Event 'AirConditionOperationModeChanged'
	IF pInstance.Act.eOperationMode <> pIntern.EvntOperationModeChanged.eOldOperationMode THEN
		// Besetzen der Felder mit aktuellen Werten
		pIntern.EvntOperationModeChanged.Fields.OldOperationMode := pIntern.EvntOperationModeChanged.eOldOperationMode;
		pIntern.EvntOperationModeChanged.Fields.NewOperationMode := pInstance.Act.eOperationMode;
		sMessageText := 'Operation mode of air condition $'';
		brsstrcat(ADR(sMessageText), ADR(pInstance.sName));
		brsstrcat(ADR(sMessageText), ADR('$' has changed from $''));
		eOperationMode := pIntern.EvntOperationModeChanged.Fields.OldOperationMode;
		GetOperationModeText;
		brsstrcat(ADR(sMessageText), ADR(sOperationModeText));
		brsstrcat(ADR(sMessageText), ADR('$' to $''));
		eOperationMode := pIntern.EvntOperationModeChanged.Fields.NewOperationMode;
		GetOperationModeText;
		brsstrcat(ADR(sMessageText), ADR(sOperationModeText));
		brsstrcat(ADR(sMessageText), ADR('$' (ST).'));
		brsstrcpy(ADR(pIntern.EvntOperationModeChanged.Fields.Message.Text), ADR(sMessageText));
		// Event feuern
		pIntern.EvntOperationModeChanged.bFire := 1;
	END_IF
	pIntern.EvntOperationModeChanged.eOldOperationMode := pInstance.Act.eOperationMode;
	CASE pIntern.EvntOperationModeChanged.nStep OF
		0:
			// Ermitteln des Namespace-Index für Fremdmodell-Adressbereich am am B&R-Server
			pIntern.EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex.Execute := 1;
			pIntern.EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex.NamespaceUri := 'http://br-automation.com/AirCondModel/';
			IF pIntern.EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex.Done = 1 THEN
				pIntern.EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex.Execute := 0;
				pIntern.EvntOperationModeChanged.nNamespaceIndexAirCond := pIntern.EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex.NamespaceIndex;
				brsitoa(pIntern.EvntOperationModeChanged.nNamespaceIndexAirCond, ADR(pIntern.EvntOperationModeChanged.sNamespaceIndexAirCond));
				pIntern.EvntOperationModeChanged.nStep := pIntern.EvntOperationModeChanged.nStep + 1;
			ELSIF pIntern.EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex.Error = 1 THEN
				// Fehler
				pIntern.EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex.Execute := 0;
			END_IF

		1:
			// Initialisierung zum Feuern des Events
			// Event-Typ
			pIntern.EvntOperationModeChanged.fbUaSrv_FireEvent.EventType.NamespaceIndex := pIntern.EvntOperationModeChanged.nNamespaceIndexAirCond;
			pIntern.EvntOperationModeChanged.fbUaSrv_FireEvent.EventType.IdentifierType := UAIdentifierType_Numeric;
			pIntern.EvntOperationModeChanged.fbUaSrv_FireEvent.EventType.Identifier := '1002'; // = AirConditionOperationModeChanged
			// Event-Felder
			nFieldIndex := 0;
			// SourceNode
			pIntern.EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].BrowsePath := '/SourceNode';
			sVarNameTotal := pIntern.EvntOperationModeChanged.sEventFieldsBaseVarName;
			brsstrcat(ADR(sVarNameTotal), ADR('.SourceNode'));
			pIntern.EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].Variable := sVarNameTotal;
			pIntern.EvntOperationModeChanged.Fields.SourceNode.NamespaceIndex := pIntern.EvntOperationModeChanged.nNamespaceIndexAirCond;
			pIntern.EvntOperationModeChanged.Fields.SourceNode.IdentifierType := UAIdentifierType_Numeric;
			pIntern.EvntOperationModeChanged.Fields.SourceNode.Identifier := pIntern.EvntOperationModeChanged.sEventFieldSourceNode;
			// Message
			nFieldIndex := nFieldIndex + 1;
			pIntern.EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].BrowsePath := '/Message';
			sVarNameTotal := pIntern.EvntOperationModeChanged.sEventFieldsBaseVarName;
			brsstrcat(ADR(sVarNameTotal), ADR('.Message'));
			pIntern.EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].Variable := sVarNameTotal;
			pIntern.EvntOperationModeChanged.Fields.Message.Text := 'Operation mode has changed.';
			// OldOperationMode
			nFieldIndex := nFieldIndex + 1;
			sFieldNameTotal := '/';
			brsstrcat(ADR(sFieldNameTotal), ADR(pIntern.EvntOperationModeChanged.sNamespaceIndexAirCond));
			brsstrcat(ADR(sFieldNameTotal), ADR(':OldOperationMode'));
			pIntern.EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].BrowsePath := sFieldNameTotal;
			sVarNameTotal := pIntern.EvntOperationModeChanged.sEventFieldsBaseVarName;
			brsstrcat(ADR(sVarNameTotal), ADR('.OldOperationMode'));
			pIntern.EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].Variable := sVarNameTotal;
			// NewOperationMode
			nFieldIndex := nFieldIndex + 1;
			sFieldNameTotal := '/';
			brsstrcat(ADR(sFieldNameTotal), ADR(pIntern.EvntOperationModeChanged.sNamespaceIndexAirCond));
			brsstrcat(ADR(sFieldNameTotal), ADR(':NewOperationMode'));
			pIntern.EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].BrowsePath := sFieldNameTotal;
			sVarNameTotal := pIntern.EvntOperationModeChanged.sEventFieldsBaseVarName;
			brsstrcat(ADR(sVarNameTotal), ADR('.NewOperationMode'));
			pIntern.EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].Variable := sVarNameTotal;
			// Statische Funktionsblock-Eingänge
			pIntern.EvntOperationModeChanged.fbUaSrv_FireEvent.EventFieldCount := nFieldIndex+1;
			pIntern.EvntOperationModeChanged.nStep := pIntern.EvntOperationModeChanged.nStep + 1;
		
		2:
			// Prüfen, ob Event gefeuert werden muss
			IF pIntern.EvntOperationModeChanged.bFire = 1 THEN
				pIntern.EvntOperationModeChanged.bFire := 0;
				pIntern.EvntOperationModeChanged.nStep := pIntern.EvntOperationModeChanged.nStep + 1;
			END_IF

		3:
			// Event feuern
			pIntern.EvntOperationModeChanged.fbUaSrv_FireEvent.Execute := 1;
			IF pIntern.EvntOperationModeChanged.fbUaSrv_FireEvent.Done = 1 THEN
				pIntern.EvntOperationModeChanged.fbUaSrv_FireEvent.Execute := 0;
				pIntern.EvntOperationModeChanged.nStep := pIntern.EvntOperationModeChanged.nStep - 1;
			ELSIF pIntern.EvntOperationModeChanged.fbUaSrv_FireEvent.Error = 1 THEN
				// Fehler
			END_IF

	END_CASE
	pIntern.EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex();
	pIntern.EvntOperationModeChanged.fbUaSrv_FireEvent(EventFields := pIntern.EvntOperationModeChanged.Fields.FieldCfg[0]);

END_ACTION

ACTION SimulateAirCond: 
	// Stetiges Angleichen an die Aussentemperatur
	pInstance.Act.rTemperature := pInstance.Act.rTemperature + 0.0005;
	IF pInstance.Act.rTemperature > rAIR_COND_TEMP_OUTSIDE THEN
		pInstance.Act.rTemperature := rAIR_COND_TEMP_OUTSIDE;
	END_IF
	// Kühlen
	IF pInstance.Act.eOperationMode <> eAC_OPERATIONMODE_OFF THEN
		// Je nach Lüfter-Stufe kühlt die ActTemp runter
		pIntern.rCoolStepTemp := pInstance.Act.nFanLevel * 0.005;
		pInstance.Act.rTemperature := pInstance.Act.rTemperature - pIntern.rCoolStepTemp;
	END_IF
	// Physikalische Begrenzung der ActTemp
	IF pInstance.Act.rTemperature < rAIR_COND_TEMP_MIN THEN
		pInstance.Act.rTemperature := rAIR_COND_TEMP_MIN;
	END_IF
END_ACTION

ACTION GetOperationModeText:
	IF eOperationMode = eAC_OPERATIONMODE_OFF THEN
		sOperationModeText := 'Off';
	ELSIF eOperationMode = eAC_OPERATIONMODE_MANUAL THEN
		sOperationModeText := 'Manual';
	ELSIF eOperationMode = eAC_OPERATIONMODE_AUTO THEN
		sOperationModeText := 'Automatic';
	ELSE
		sOperationModeText := 'Unknown';
	END_IF
END_ACTION
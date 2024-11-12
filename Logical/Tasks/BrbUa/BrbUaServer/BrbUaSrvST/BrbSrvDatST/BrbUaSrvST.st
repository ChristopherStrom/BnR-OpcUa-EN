
PROGRAM _INIT
	// Initialisieren der Test-Variablen
	brsmemset(ADR(VarsLocal), 0, SIZEOF(VarsLocal));
	VarsLocal.ReadOnly.sString := '000';
	EventId.Length := nBRBUA_EVENTID_INDEX_MAX+1;
	BrbHexToUsintArray('000102030405060708090A0B0C0D0E0F', ADR(EventId.Data[0]), EventId.Length, 0);

	// Initialisieren der Methode 'Calculate'
	brsmemset(ADR(MethodCalculate), 0, SIZEOF(MethodCalculate));
	MethodCalculate.Par.sMethodName:= 'Calculate';
	MethodCalculate.Par.bEnable := 1;

	// Initialisieren des RunServers
	brsmemset(ADR(fbBrbUaRunServerInit), 0, SIZEOF(fbBrbUaRunServerInit));
	brsmemset(ADR(fbBrbUaRunServerCyclic), 0, SIZEOF(fbBrbUaRunServerCyclic));
	brsmemset(ADR(fbBrbUaRunServerExit), 0, SIZEOF(fbBrbUaRunServerExit));
	brsmemset(ADR(RunServer), 0, SIZEOF(RunServer));

	// Aufruf zum Initialisieren des RunServers
	RunServer.Cfg.sCfgDataObjName := 'BrbSrvDatS';	
	REPEAT
		fbBrbUaRunServerInit.pRunServer := ADR(RunServer);
		fbBrbUaRunServerInit();
		UNTIL fbBrbUaRunServerInit.nStatus <> eBRB_ERR_BUSY
	END_REPEAT

	// Initialisieren des Events
	brsmemset(ADR(fbBrbUaRsFireEvent), 0, SIZEOF(fbBrbUaRsFireEvent));
	brsmemset(ADR(SrvTransitionEventData), 0, SIZEOF(SrvTransitionEventData));

	// Initialisierung der RunServer-Monitors
	brsmemset(ADR(RsMonitor), 0, SIZEOF(RsMonitor));

END_PROGRAM

PROGRAM _CYCLIC

	// Änderung der Test-Variablen
	IncrementOpcUaTestDatatypes(VarsLocal.ReadOnly);
	BrbUaGetRandomByteString(ADR(EventId.Data[0]), EventId.Length);

	// Methode "Calculate"
	pMethodCalculate ACCESS ADR(MethodCalculate);
	IF(BrbUaSrvHandleMethod(pMethodCalculate) = 0) THEN
		IF(MethodCalculate.State.bExecuteUserCode = 1) THEN
			IF(MethodCalculate.State.bExecuteUserCodeInit = 1) THEN
				// Optionale Initialisierung pro Aufruf (hier nicht benötigt)
			END_IF
	
			// User-Code
			MethCalculateArgs.Out.nAddition := MethCalculateArgs.In.nVal0 + MethCalculateArgs.In.nVal1;
			MethCalculateArgs.Out.nMultiplication := MethCalculateArgs.In.nVal0 * MethCalculateArgs.In.nVal1;
			brsmemcpy(ADR(MethCalculateArgs.Out.anArray), ADR(MethCalculateArgs.In.anArray), SIZEOF(MethCalculateArgs.Out.anArray)); // In-Array auf Out-Array übernehmen
				
			// Rückmeldung
			MethodCalculate.Par.bUserCodeIsFinished := 1;
		END_IF
	ELSE
		// Hier können eventuell aufgetretene Fehler behandelt werden
	END_IF

	// Zyklischer Aufruf des RunServers
	IF(RunServer.State.eState >= eBRB_RSSTATE_INIT_DONE AND RunServer.State.eState <= eBRB_RSSTATE_EXITING) THEN
		fbBrbUaRunServerCyclic.pRunServer := ADR(RunServer);
		fbBrbUaRunServerCyclic();
	END_IF

	// Feuern von Event 0 (TransitionType)
	fbTimerFireEvent.IN := (RunServer.State.eState = eBRB_RSSTATE_RUNNING);
	fbTimerFireEvent.PT := T#5s;
	fbTimerFireEvent();
	IF fbTimerFireEvent.Q = 1 THEN
		fbBrbUaRsFireEvent.pRunServer := ADR(RunServer);
		fbBrbUaRsFireEvent.nEventIndex := 0;
		fbBrbUaRsFireEvent();
		IF fbBrbUaRsFireEvent.bInit = 1 THEN
			// Optionales Init (Hier: Besetzen der Fields)
			SrvTransitionEventData.nFromStateId := SrvTransitionEventData.nToStateId;
			BrbUaSetLocalizedText(ADR(SrvTransitionEventData.FromState), 'en', 'State=');
			brsitoa(SrvTransitionEventData.nFromStateId, ADR(sHelp));
			brsstrcat(ADR(SrvTransitionEventData.FromState.Text), ADR(sHelp));
	
			SrvTransitionEventData.nToStateId := DINT_TO_UINT(BrbGetRandomDint(1, 100));
			BrbUaSetLocalizedText(ADR(SrvTransitionEventData.ToState), 'en', 'State=');
			brsitoa(SrvTransitionEventData.nToStateId, ADR(sHelp));
			brsstrcat(ADR(SrvTransitionEventData.ToState.Text), ADR(sHelp));
	
			SrvTransitionEventData.nTransitionId := SrvTransitionEventData.nTransitionId + 1;
			BrbUaSetLocalizedText(ADR(SrvTransitionEventData.Transition), 'en', 'Transition=');
			brsitoa(SrvTransitionEventData.nTransitionId, ADR(sHelp));
			brsstrcat(ADR(SrvTransitionEventData.Transition.Text), ADR(sHelp));
	
			BrbUaSetLocalizedText(ADR(SrvTransitionEventData.Message), 'en', 'BrbUaSrvST changed from State ');
			brsitoa(SrvTransitionEventData.nFromStateId, ADR(sHelp));
			brsstrcat(ADR(SrvTransitionEventData.Message.Text), ADR(sHelp));
			brsstrcat(ADR(SrvTransitionEventData.Message.Text), ADR(' to '));
			brsitoa(SrvTransitionEventData.nToStateId, ADR(sHelp));
			brsstrcat(ADR(SrvTransitionEventData.Message.Text), ADR(sHelp));
				
			SrvTransitionEventData.nSeverity := DINT_TO_UINT(BrbGetRandomDint(1, 500));
			SrvTransitionEventData.sSourceName := 'BrbUaSrvST';
		END_IF
		IF(fbBrbUaRsFireEvent.nStatus <> eBRB_ERR_BUSY) THEN
			// Timer neu triggern
			fbTimerFireEvent.IN := 0;
			fbTimerFireEvent();
		END_IF
	END_IF

	// RunServer-Monitor
	BrbUaRsMonitor(RunServer, RsMonitor);
	
END_PROGRAM

PROGRAM _EXIT
	// Aufruf zum Exit des RunServers
	REPEAT
		fbBrbUaRunServerExit.pRunServer := ADR(RunServer);
		fbBrbUaRunServerExit();
		UNTIL fbBrbUaRunServerExit.nStatus <> eBRB_ERR_BUSY
	END_REPEAT
END_PROGRAM


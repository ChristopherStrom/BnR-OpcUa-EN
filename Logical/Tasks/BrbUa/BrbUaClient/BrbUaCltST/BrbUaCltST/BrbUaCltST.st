
PROGRAM _INIT
	// Initialisierung des Clients
	brsmemset(ADR(fbBrbUaRunClientInit), 0, SIZEOF(fbBrbUaRunClientInit));
	brsmemset(ADR(fbBrbUaRunClientCyclic), 0, SIZEOF(fbBrbUaRunClientCyclic));
	brsmemset(ADR(fbBrbUaRunClientExit), 0, SIZEOF(fbBrbUaRunClientExit));
	brsmemset(ADR(RunClient), 0, SIZEOF(RunClient));
	
	// Aufruf zum Initialisieren des Clients
	RunClient.Cfg.sCfgDataObjName := 'BrbCltDatS';
	REPEAT
		fbBrbUaRunClientInit.pRunClient := ADR(RunClient);
		fbBrbUaRunClientInit();
		UNTIL fbBrbUaRunClientInit.nStatus <> eBRB_ERR_BUSY
	END_REPEAT
	
	// Wenn Verbindungs-Parameter im Datenobjekt nicht angeben sind, müssen sie nach dem Aufruf von RunClientInit, aber noch vor dem Connect-Kommando vom Programm gesetzt werden
	RunClient.Cfg.sServerEndpointUrl := 'opc.tcp://127.0.0.1:4840/'; // z.B. Endpoint-Url besetzen
	RunClient.eCmd := eBRB_RCCLTCMD_CONNECT; // Sofort verbinden
	
	// Initialisierung des ReadBlock 0
	brsmemset(ADR(fbTimerReadBlock0), 0, SIZEOF(fbTimerReadBlock0));
	brsmemset(ADR(fbBrbUaRcReadBlock0), 0, SIZEOF(fbBrbUaRcReadBlock0));
	brsmemset(ADR(ClientVarsRead), 0, SIZEOF(ClientVarsRead));
	
	// Initialisierung des WriteBlock 0
	brsmemset(ADR(fbTimerWriteBlock0), 0, SIZEOF(fbTimerWriteBlock0));
	brsmemset(ADR(fbBrbUaRcWriteBlock0), 0, SIZEOF(fbBrbUaRcWriteBlock0));
	// Als Quelle der zu schreibenden Werte wird die Struktur 'ClientVarsRead' verwendet
	
	// Initialisierung der Methode 0 (Calculate)
	brsmemset(ADR(fbTimerCallMethodCalculate), 0, SIZEOF(fbTimerCallMethodCalculate));
	brsmemset(ADR(fbBrbUaRcCallMethodCalculate), 0, SIZEOF(fbBrbUaRcCallMethodCalculate));
	brsmemset(ADR(ClientMethCalculateArgs), 0, SIZEOF(ClientMethCalculateArgs));
	
	// Initialisierung der Variablen, die von den Subscriptions befüllt werden
	brsmemset(ADR(ClientVarsSubscription), 0, SIZEOF(ClientVarsSubscription));
	brsmemset(ADR(ClientReceivedEvent), 0, SIZEOF(ClientReceivedEvent));
	brsmemset(ADR(ServerNamespacesArray), 0, SIZEOF(ServerNamespacesArray));
	brsmemset(ADR(ServerStatus), 0, SIZEOF(ServerStatus));
	brsmemset(ADR(ServerDiagData), 0, SIZEOF(ServerDiagData));
	brsmemset(ADR(SessionDiagnosticsArray), 0, SIZEOF(SessionDiagnosticsArray));
	brsmemset(ADR(SessionSecurityDiagnosticsArray), 0, SIZEOF(SessionSecurityDiagnosticsArray));
	brsmemset(ADR(SubscriptionDiagnosticsArray), 0, SIZEOF(SubscriptionDiagnosticsArray));
	
	// Initialisierung der Monitors
	brsmemset(ADR(RcMonitor), 0, SIZEOF(RcMonitor));

END_PROGRAM

PROGRAM _CYCLIC
	
	// Zyklischer Aufruf des Clients
	IF RunClient.State.eClientState >= eBRB_RCCLTSTATE_INIT_DONE AND RunClient.State.eClientState <= eBRB_RCCLTSTATE_EXITING THEN
		fbBrbUaRunClientCyclic.pRunClient := ADR(RunClient);
		fbBrbUaRunClientCyclic();
	END_IF
	
	// ReadBlock 0 lesen
	fbTimerReadBlock0.IN := (RunClient.State.eClientState = eBRB_RCCLTSTATE_CONNECTED);
	fbTimerReadBlock0.PT := T#1s;
	fbTimerReadBlock0();
	IF fbTimerReadBlock0.Q = 1 THEN
		fbBrbUaRcReadBlock0.pRunClient := ADR(RunClient);
		fbBrbUaRcReadBlock0.nReadBlockIndex := 0;
		fbBrbUaRcReadBlock0();
		IF fbBrbUaRcReadBlock0.nStatus <> eBRB_ERR_BUSY THEN
			// Timer neu triggern
			fbTimerReadBlock0.IN := 0;
			fbTimerReadBlock0();
		END_IF
	END_IF

	// WriteBlock 0 schreiben
	fbTimerWriteBlock0.IN := (RunClient.State.eClientState = eBRB_RCCLTSTATE_CONNECTED);
	fbTimerWriteBlock0.PT := T#1s;
	fbTimerWriteBlock0();
	IF fbTimerWriteBlock0.Q = 1 THEN
		fbBrbUaRcWriteBlock0.pRunClient := ADR(RunClient);
		fbBrbUaRcWriteBlock0.nWriteBlockIndex := 0;
		fbBrbUaRcWriteBlock0();
		IF fbBrbUaRcWriteBlock0.nStatus <> eBRB_ERR_BUSY THEN
			// Timer neu triggern
			fbTimerWriteBlock0.IN := 0;
			fbTimerWriteBlock0();
		END_IF
	END_IF
	
	// Method 0 aufrufen (Calculate)
	fbTimerCallMethodCalculate.IN := (RunClient.State.eClientState = eBRB_RCCLTSTATE_CONNECTED);
	fbTimerCallMethodCalculate.PT := T#1s;
	fbTimerCallMethodCalculate();
	IF fbTimerCallMethodCalculate.Q = 1 THEN
		fbBrbUaRcCallMethodCalculate.pRunClient := ADR(RunClient);
		fbBrbUaRcCallMethodCalculate.nMethodIndex := 0;
		fbBrbUaRcCallMethodCalculate();
		IF fbBrbUaRcCallMethodCalculate.bInit = 1 THEN
			// Pro Aufruf einmalig Eingänge mit Zufallszahlen besetzen
			ClientMethCalculateArgs.In.nVal0 := BrbGetRandomDint(1, 10);
			ClientMethCalculateArgs.In.nVal1 := BrbGetRandomDint(1, 10);
			FOR nItemIndex :=0 TO nMETHOD_CALC_ARRAY_INDEX_MAX DO
				ClientMethCalculateArgs.In.anArray[nItemIndex] := DINT_TO_INT(BrbGetRandomDint(1, 10));
			END_FOR
		END_IF
		IF fbBrbUaRcCallMethodCalculate.nStatus <> eBRB_ERR_BUSY THEN
			// Call zurückgemeldet -> Timer neu triggern
			fbTimerCallMethodCalculate.IN := 0;
			fbTimerCallMethodCalculate();
		END_IF
	END_IF
	
	// Erkennen einer Wert-Änderung von Subscripton0, MonitoredItem1 (=nUsint)
	ClientReceivedMonItem.bValueChanged := BrbUaRcGetMiValueChanged(RunClient, 0, 1, 0);
	IF ClientReceivedMonItem.bValueChanged = 1 THEN
		// Wert-Änderung wurde empfangen
		// Beispielsweise Zähler erhöhen
		ClientReceivedMonItem.nReceivedCount := ClientReceivedMonItem.nReceivedCount + 1;
		// Flag zurücksetzen
		BrbUaRcGetMiValueChanged(RunClient, 0, 1, 1);
	END_IF
		
	// Prüfen, ob Event von Subscripton3, EventItem0 empfangen wurde
	IF BrbUaRcGetEventItemReceived(RunClient, 3, 0) = 1 THEN
		// Event wurde empfangen
		ClientReceivedEvent.nReceivedCount := BrbUaRcGetEventItemReceiveCount(RunClient, 3, 0);
		// Das Feld EventId wird in einen Hex-String gewandelt
		BrbUsintArrayToHex(ADR(ClientReceivedEvent.EventId.Data), ClientReceivedEvent.EventId.Length, ClientReceivedEvent.sEventIdHex, SIZEOF(ClientReceivedEvent.sEventIdHex), 0);
		// Das Feld ReceiveTime wird in einen Text gewandelt. Dabei wird mithilfe des Felds LocalTime von Utc-Zeit in lokale Server-Zeit umgerechnet
		BrbUaGetSrvTimeText(ClientReceivedEvent.ReceiveTime, ClientReceivedEvent.sReceiveTime, SIZEOF(ClientReceivedEvent.sReceiveTime), ClientReceivedEvent.LocalTime.TimeOffset, 'yyyy:mm:dd hh:MM:ss::milms:mic.µs:nanns');
		
	END_IF
	
	// RunClient-Monitor
	BrbUaRcMonitor(RunClient, RcMonitor);

END_PROGRAM

PROGRAM _EXIT
	// Aufruf zum Exit des RunClients
	REPEAT
		fbBrbUaRunClientExit.pRunClient := ADR(RunClient);
		fbBrbUaRunClientExit();
		UNTIL fbBrbUaRunClientExit.nStatus <> eBRB_ERR_BUSY
	END_REPEAT
END_PROGRAM


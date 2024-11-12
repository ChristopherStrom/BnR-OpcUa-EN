PROGRAM _INIT
    // Initialize the test variables
    brsmemset(ADR(VarsLocal), 0, SIZEOF(VarsLocal));
    VarsLocal.ReadOnly.sString := '000';
    EventId.Length := nBRBUA_EVENTID_INDEX_MAX+1;
    BrbHexToUsintArray('000102030405060708090A0B0C0D0E0F', ADR(EventId.Data[0]), EventId.Length, 0);

    // Initialize the 'Calculate' method
    brsmemset(ADR(MethodCalculate), 0, SIZEOF(MethodCalculate));
    MethodCalculate.Par.sMethodName := 'Calculate';
    MethodCalculate.Par.bEnable := 1;

    // Initialize the RunServers
    brsmemset(ADR(fbBrbUaRunServerInit), 0, SIZEOF(fbBrbUaRunServerInit));
    brsmemset(ADR(fbBrbUaRunServerCyclic), 0, SIZEOF(fbBrbUaRunServerCyclic));
    brsmemset(ADR(fbBrbUaRunServerExit), 0, SIZEOF(fbBrbUaRunServerExit));
    brsmemset(ADR(RunServer), 0, SIZEOF(RunServer));

    // Call to initialize the RunServer
    RunServer.Cfg.sCfgDataObjName := 'BrbSrvDatS';    
    REPEAT
        fbBrbUaRunServerInit.pRunServer := ADR(RunServer);
        fbBrbUaRunServerInit();
        UNTIL fbBrbUaRunServerInit.nStatus <> eBRB_ERR_BUSY
    END_REPEAT

    // Initialize the events
    brsmemset(ADR(fbBrbUaRsFireEvent), 0, SIZEOF(fbBrbUaRsFireEvent));
    brsmemset(ADR(SrvTransitionEventData), 0, SIZEOF(SrvTransitionEventData));

    // Initialize the RunServer monitors
    brsmemset(ADR(RsMonitor), 0, SIZEOF(RsMonitor));
END_PROGRAM

PROGRAM _CYCLIC

    // Modify the test variables
    IncrementOpcUaTestDatatypes(VarsLocal.ReadOnly);
    BrbUaGetRandomByteString(ADR(EventId.Data[0]), EventId.Length);

    // Method "Calculate"
    pMethodCalculate ACCESS ADR(MethodCalculate);
    IF (BrbUaSrvHandleMethod(pMethodCalculate) = 0) THEN
        IF (MethodCalculate.State.bExecuteUserCode = 1) THEN
            IF (MethodCalculate.State.bExecuteUserCodeInit = 1) THEN
                // Optional initialization for each call (not needed here)
            END_IF

            // User code
            MethCalculateArgs.Out.nAddition := MethCalculateArgs.In.nVal0 + MethCalculateArgs.In.nVal1;
            MethCalculateArgs.Out.nMultiplication := MethCalculateArgs.In.nVal0 * MethCalculateArgs.In.nVal1;
            brsmemcpy(ADR(MethCalculateArgs.Out.anArray), ADR(MethCalculateArgs.In.anArray), SIZEOF(MethCalculateArgs.Out.anArray)); // Copy In-Array to Out-Array

            // Feedback
            MethodCalculate.Par.bUserCodeIsFinished := 1;
        END_IF
    ELSE
        // Handle potential errors here
    END_IF

    // Cyclic call of the RunServer
    IF (RunServer.State.eState >= eBRB_RSSTATE_INIT_DONE AND RunServer.State.eState <= eBRB_RSSTATE_EXITING) THEN
        fbBrbUaRunServerCyclic.pRunServer := ADR(RunServer);
        fbBrbUaRunServerCyclic();
    END_IF

    // Fire event 0 (TransitionType)
    fbTimerFireEvent.IN := (RunServer.State.eState = eBRB_RSSTATE_RUNNING);
    fbTimerFireEvent.PT := T#5s;
    fbTimerFireEvent();
    IF fbTimerFireEvent.Q = 1 THEN
        fbBrbUaRsFireEvent.pRunServer := ADR(RunServer);
        fbBrbUaRsFireEvent.nEventIndex := 0;
        fbBrbUaRsFireEvent();
        IF fbBrbUaRsFireEvent.bInit = 1 THEN
            // Optional initialization (Here: Populate the fields)
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
        IF (fbBrbUaRsFireEvent.nStatus <> eBRB_ERR_BUSY) THEN
            // Retrigger the timer
            fbTimerFireEvent.IN := 0;
            fbTimerFireEvent();
        END_IF
    END_IF

    // RunServer Monitor
    BrbUaRsMonitor(RunServer, RsMonitor);
    
END_PROGRAM

PROGRAM _EXIT
    // Call to exit the RunServer
    REPEAT
        fbBrbUaRunServerExit.pRunServer := ADR(RunServer);
        fbBrbUaRunServerExit();
        UNTIL fbBrbUaRunServerExit.nStatus <> eBRB_ERR_BUSY
    END_REPEAT
END_PROGRAM

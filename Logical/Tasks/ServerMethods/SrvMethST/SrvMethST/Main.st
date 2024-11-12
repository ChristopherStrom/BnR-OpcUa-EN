
PROGRAM _INIT
	// Ablöschen der Funktionsblöcke und Strukturen 
	brsmemset(ADR(fbUaSrv_MethodOperateCalculate), 0, SIZEOF(fbUaSrv_MethodOperateCalculate));
	brsmemset(ADR(MethCalculateArgs), 0, SIZEOF(MethCalculateArgs));
	
	// Setzen der Methode 'Calculate'
	fbUaSrv_MethodOperateCalculate.MethodName := 'Calculate'; // Name der Methode wie in 'Methods.uam' angegeben
	
	// Initialisierung der Schrittkette
	Step.eStepNr := eSTEP_CHECK;

END_PROGRAM

PROGRAM _CYCLIC

		// Schrittkette
	CASE Step.eStepNr OF
		eSTEP_NONE:
		
		eSTEP_CHECK:
			// Prüfen, ob Methode von einem Client aufgerufen wurde
			fbUaSrv_MethodOperateCalculate.Execute := 1;
			fbUaSrv_MethodOperateCalculate.Action := UaMoa_CheckIsCalled;
			IF fbUaSrv_MethodOperateCalculate.Done = 1 THEN
				fbUaSrv_MethodOperateCalculate.Execute := 0;
				IF fbUaSrv_MethodOperateCalculate.IsCalled = 1 THEN
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					Step.eStepNr := eSTEP_EXECUTE;
				END_IF
			ELSIF fbUaSrv_MethodOperateCalculate.Error = 1 THEN
				fbUaSrv_MethodOperateCalculate.Execute := 0;
				Step.eErrorStep := Step.eStepNr;
				Step.eAction := fbUaSrv_MethodOperateCalculate.Action;
				Step.nErrorId := fbUaSrv_MethodOperateCalculate.ErrorID;
			END_IF
	
		eSTEP_EXECUTE:
			// Ausführen der Methode
			MethCalculateArgs.Out.nAddition := MethCalculateArgs.In.nVal0 + MethCalculateArgs.In.nVal1;
			MethCalculateArgs.Out.nMultiplication := MethCalculateArgs.In.nVal0 * MethCalculateArgs.In.nVal1;
			brsmemcpy(ADR(MethCalculateArgs.Out.anArray), ADR(MethCalculateArgs.In.anArray), SIZEOF(MethCalculateArgs.Out.anArray)); // In-Array auf Out-Array übernehmen
			
			nMethCalculateCallCount := nMethCalculateCallCount + 1; // Nur zur Diagnose
			Step.eStepNr := eSTEP_FINSHED;

		eSTEP_FINSHED:
			// Rückmelden, dass Methode ausgeführt wurde. Zu diesem Zeitpunkt müssen die Ausgangs-Argumente besetzt sein und dürfen nicht mehr geändert werden
			fbUaSrv_MethodOperateCalculate.Execute := 1;
			fbUaSrv_MethodOperateCalculate.Action := UaMoa_Finished;
			IF fbUaSrv_MethodOperateCalculate.Done = 1 THEN
				fbUaSrv_MethodOperateCalculate.Execute := 0;
				Step.eStepNr := eSTEP_CHECK;
			ELSIF fbUaSrv_MethodOperateCalculate.Error = 1 THEN
				// Fehler eintragen, aber trotzdem weiter machen
				fbUaSrv_MethodOperateCalculate.Execute := 0;
				Step.eErrorStep := Step.eStepNr;
				Step.eAction := fbUaSrv_MethodOperateCalculate.Action;
				Step.nErrorId := fbUaSrv_MethodOperateCalculate.ErrorID;
				Step.eStepNr := eSTEP_CHECK;
			END_IF

	END_CASE

	// Aufruf aller PlcOpen-Funktionsblöcke
	fbUaSrv_MethodOperateCalculate();

END_PROGRAM

PROGRAM _EXIT
END_PROGRAM


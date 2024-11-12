#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

// Prototypen der lokalen Funktionen
void IncrementOpcUaTestDatatypes(OpcUaTestDatatypes_TYP* pDatatypes);

void _INIT Init(void)
{
	// Initialisieren der Server-Variablen
	brsmemset((UDINT)&VarsLocal, 0, sizeof(VarsLocal));
	brsstrcpy((UDINT)&VarsLocal.ReadOnly.sString, (UDINT)&"000");
	EventId.Length = nBRBUA_EVENTID_INDEX_MAX+1;
	BrbHexToUsintArray("000102030405060708090A0B0C0D0E0F", &EventId.Data[0], EventId.Length, 0);

	// Initialisieren der Methode 'Calculate'
	brsmemset((UDINT)&MethodCalculate, 0, sizeof(MethodCalculate));
	brsstrcpy((UDINT)&MethodCalculate.Par.sMethodName, (UDINT)&"Calculate");
	MethodCalculate.Par.bEnable = 1;
	
	// Initialisieren des RunServers
	brsmemset((UDINT)&fbBrbUaRunServerInit, 0, sizeof(fbBrbUaRunServerInit));
	brsmemset((UDINT)&fbBrbUaRunServerCyclic, 0, sizeof(fbBrbUaRunServerCyclic));
	brsmemset((UDINT)&fbBrbUaRunServerExit, 0, sizeof(fbBrbUaRunServerExit));
	brsmemset((UDINT)&RunServer, 0, sizeof(RunServer));
	
	// Aufruf zum Initialisieren des RunServers
	brsstrcpy((UDINT)&RunServer.Cfg.sCfgDataObjName, (UDINT)&"BrbSrvDatC");
	do
	{
		fbBrbUaRunServerInit.pRunServer = &RunServer;
		BrbUaRunServerInit(&fbBrbUaRunServerInit);
	} while(fbBrbUaRunServerInit.nStatus == eBRB_ERR_BUSY);
	
	// Initialisieren des Events
	brsmemset((UDINT)&fbBrbUaRsFireEvent, 0, sizeof(fbBrbUaRsFireEvent));
	brsmemset((UDINT)&SrvTransitionEventData, 0, sizeof(SrvTransitionEventData));
	
	// Initialisierung der RunServer-Monitors
	brsmemset((UDINT)&RsMonitor, 0, sizeof(RsMonitor));
	
}

void _CYCLIC Cyclic(void)
{
	// Änderung der Test-Variablen für Client
	IncrementOpcUaTestDatatypes(&VarsLocal.ReadOnly);
	BrbUaGetRandomByteString(&EventId.Data[0], EventId.Length);

	// Methode "Calculate"
	if(BrbUaSrvHandleMethod(&MethodCalculate) == 0)
	{
		if(MethodCalculate.State.bExecuteUserCode == 1)
		{
			if(MethodCalculate.State.bExecuteUserCodeInit == 1)
			{
				// Optionale Initialisierung pro Aufruf (hier nicht benötigt)
			}

			// User-Code
			MethCalculateArgs.Out.nAddition = MethCalculateArgs.In.nVal0 + MethCalculateArgs.In.nVal1;
			MethCalculateArgs.Out.nMultiplication = MethCalculateArgs.In.nVal0 * MethCalculateArgs.In.nVal1;
			brsmemcpy((UDINT)&MethCalculateArgs.Out.anArray, (UDINT)&MethCalculateArgs.In.anArray, sizeof(MethCalculateArgs.Out.anArray)); // In-Array auf Out-Array übernehmen
			
			// Rückmeldung
			MethodCalculate.Par.bUserCodeIsFinished = 1;
		}
	}
	else
	{
		// Hier können eventuell aufgetretene Fehler behandelt werden
	}

	// Zyklischer Aufruf des RunServers
	if(RunServer.State.eState >= eBRB_RSSTATE_INIT_DONE && RunServer.State.eState <= eBRB_RSSTATE_EXITING)
	{
		fbBrbUaRunServerCyclic.pRunServer = &RunServer;
		BrbUaRunServerCyclic(&fbBrbUaRunServerCyclic);
	}

	// Feuern von Event 0 (TransitionType)
	fbTimerFireEvent.IN = (RunServer.State.eState == eBRB_RSSTATE_RUNNING);
	fbTimerFireEvent.PT = 5000;
	TON(&fbTimerFireEvent);
	if(fbTimerFireEvent.Q == 1)
	{
		fbBrbUaRsFireEvent.pRunServer = &RunServer;
		fbBrbUaRsFireEvent.nEventIndex = 0;
		BrbUaRsFireEvent(&fbBrbUaRsFireEvent);
		if(fbBrbUaRsFireEvent.bInit == 1)
		{
			// Optionales Init (Hier: Besetzen der Fields)
			STRING sHelp[16];

			SrvTransitionEventData.nFromStateId = SrvTransitionEventData.nToStateId;
			BrbUaSetLocalizedText(&SrvTransitionEventData.FromState, "en", "State=");
			brsitoa((DINT)SrvTransitionEventData.nFromStateId, (UDINT)&sHelp);
			brsstrcat((UDINT)&SrvTransitionEventData.FromState.Text, (UDINT)&sHelp);

			SrvTransitionEventData.nToStateId = (UINT)BrbGetRandomUdint(1, 100);
			BrbUaSetLocalizedText(&SrvTransitionEventData.ToState, "en", "State=");
			brsitoa((DINT)SrvTransitionEventData.nToStateId, (UDINT)&sHelp);
			brsstrcat((UDINT)&SrvTransitionEventData.ToState.Text, (UDINT)&sHelp);

			SrvTransitionEventData.nTransitionId++;
			BrbUaSetLocalizedText(&SrvTransitionEventData.Transition, "en", "Transition=");
			brsitoa((DINT)SrvTransitionEventData.nTransitionId, (UDINT)&sHelp);
			brsstrcat((UDINT)&SrvTransitionEventData.Transition.Text, (UDINT)&sHelp);

			BrbUaSetLocalizedText(&SrvTransitionEventData.Message, "en", "BrbUaSrvC changed from State ");
			brsitoa((DINT)SrvTransitionEventData.nFromStateId, (UDINT)&sHelp);
			brsstrcat((UDINT)&SrvTransitionEventData.Message.Text, (UDINT)&sHelp);
			brsstrcat((UDINT)&SrvTransitionEventData.Message.Text, (UDINT)&" to ");
			brsitoa((DINT)SrvTransitionEventData.nToStateId, (UDINT)&sHelp);
			brsstrcat((UDINT)&SrvTransitionEventData.Message.Text, (UDINT)&sHelp);
			
			SrvTransitionEventData.nSeverity = (UINT)BrbGetRandomDint(1, 500);
			brsstrcpy((UDINT)&SrvTransitionEventData.sSourceName, (UDINT)&"BrbUaSrvC");

		}
		if(fbBrbUaRsFireEvent.nStatus != eBRB_ERR_BUSY)
		{
			// Timer neu triggern
			fbTimerFireEvent.IN = 0;
			TON(&fbTimerFireEvent);
		}
	}

	// RunServer-Monitor
	BrbUaRsMonitor(&RunServer, &RsMonitor);	
	
}

void _EXIT Exit(void)
{
	// Aufruf zum Exit des RunServers
	do
	{
		fbBrbUaRunServerExit.pRunServer = &RunServer;
		BrbUaRunServerExit(&fbBrbUaRunServerExit);
	} while(fbBrbUaRunServerExit.nStatus == eBRB_ERR_BUSY);
}

// Hilfsfunktion zum Ändern der Server-Variablen
void IncrementOpcUaTestDatatypes(OpcUaTestDatatypes_TYP* pDatatypes)
{
	UINT		nStringLen;
	STRING	sHelpString[nOPCUA_STRING_CHAR_MAX];
	UINT		nHelpStringLen;

	pDatatypes->bBool = !pDatatypes->bBool;
	pDatatypes->nSint++;
	pDatatypes->nInt++;
	pDatatypes->nDint++;
	pDatatypes->nUsint++;
	pDatatypes->nUint++;
	pDatatypes->nUdint++;
	pDatatypes->rReal += 0.1f;
	pDatatypes->rLongReal += 0.2;
	pDatatypes->tTime++;
	pDatatypes->dtDateTime++;
	pDatatypes->anInt[0]++;
	pDatatypes->anInt[1]++;
	pDatatypes->anInt[2]++;
	pDatatypes->anInt[3]++;
	pDatatypes->anInt[4]++;

	nStringLen = (UINT)brsstrlen((UDINT)&pDatatypes->sString);
	brsitoa((DINT)pDatatypes->nUsint, (UDINT)&sHelpString);
	nHelpStringLen = (UINT)brsstrlen((UDINT)&sHelpString);
	if((nStringLen >= 3))
	{
		if(nHelpStringLen >= 3)
		{
			pDatatypes->sString[0] = sHelpString[0];
			pDatatypes->sString[1] = sHelpString[1];
			pDatatypes->sString[2] = sHelpString[2];
		}
		else if(nHelpStringLen == 2)
		{
			pDatatypes->sString[0] = 48;
			pDatatypes->sString[1] = sHelpString[0];
			pDatatypes->sString[2] = sHelpString[1];
		}
		else
		{
			pDatatypes->sString[0] = 48;
			pDatatypes->sString[1] = 48;
			pDatatypes->sString[2] = sHelpString[0];
		}
	}
	else if(nStringLen == 2)
	{
		if(nHelpStringLen >= 3)
		{
			pDatatypes->sString[0] = sHelpString[1];
			pDatatypes->sString[1] = sHelpString[2];
		}
		else if(nHelpStringLen == 2)
		{
			pDatatypes->sString[0] = sHelpString[0];
			pDatatypes->sString[1] = sHelpString[1];
		}
		else
		{
			pDatatypes->sString[0] = 48;
			pDatatypes->sString[1] = sHelpString[0];
		}
	}
	else if(nStringLen == 1)
	{
		if(nHelpStringLen >= 3)
		{
			pDatatypes->sString[0] = sHelpString[2];
		}
		else if(nHelpStringLen == 2)
		{
			pDatatypes->sString[0] = sHelpString[1];
		}
		else
		{
			pDatatypes->sString[0] = sHelpString[0];
		}
	}
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

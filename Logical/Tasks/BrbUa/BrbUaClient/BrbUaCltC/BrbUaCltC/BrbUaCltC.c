#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

void _INIT Init(void)
{
	// Initialisierung des RunClients
	brsmemset((UDINT)&fbBrbUaRunClientInit, 0, sizeof(fbBrbUaRunClientInit));
	brsmemset((UDINT)&fbBrbUaRunClientCyclic, 0, sizeof(fbBrbUaRunClientCyclic));
	brsmemset((UDINT)&fbBrbUaRunClientExit, 0, sizeof(fbBrbUaRunClientExit));
	brsmemset((UDINT)&RunClient, 0, sizeof(RunClient));
	
	// Aufruf zum Initialisieren des RunClients
	brsstrcpy((UDINT)&RunClient.Cfg.sCfgDataObjName, (UDINT)&"BrbCltDatC");
	do
	{
		fbBrbUaRunClientInit.pRunClient = &RunClient;
		BrbUaRunClientInit(&fbBrbUaRunClientInit);
	} while(fbBrbUaRunClientInit.nStatus == eBRB_ERR_BUSY);
	
	// Wenn Verbindungs-Parameter im Datenobjekt nicht angeben sind, müssen sie nach dem Aufruf von RunClientInit, aber noch vor dem Connect-Kommando vom Programm gesetzt werden
	brsstrcpy((UDINT)&RunClient.Cfg.sServerEndpointUrl, (UDINT)&"opc.tcp://127.0.0.1:4840"); // z.B. Endpoint-Url besetzen

	RunClient.eCmd = eBRB_RCCLTCMD_CONNECT; // Sofort verbinden
	
	// Initialisierung des ReadBlock 0
	brsmemset((UDINT)&fbTimerReadBlock0, 0, sizeof(fbTimerReadBlock0));
	brsmemset((UDINT)&fbBrbUaRcReadBlock0, 0, sizeof(fbBrbUaRcReadBlock0));
	brsmemset((UDINT)&ClientVarsRead, 0, sizeof(ClientVarsRead));
	
	// Initialisierung des WriteBlock 0
	brsmemset((UDINT)&fbTimerWriteBlock0, 0, sizeof(fbTimerWriteBlock0));
	brsmemset((UDINT)&fbBrbUaRcWriteBlock0, 0, sizeof(fbBrbUaRcWriteBlock0));
	// Als Quelle der zu schreibenden Werte wird die Struktur 'ClientVarsRead' verwendet
	
	// Initialisierung der Methode 0 (Calculate)
	brsmemset((UDINT)&fbTimerCallMethodCalculate, 0, sizeof(fbTimerCallMethodCalculate));
	brsmemset((UDINT)&fbBrbUaRcCallMethodCalculate, 0, sizeof(fbBrbUaRcCallMethodCalculate));
	brsmemset((UDINT)&ClientMethCalculateArgs, 0, sizeof(ClientMethCalculateArgs));
	
	// Initialisierung der Variablen, die von den Subscriptions befüllt werden
	brsmemset((UDINT)&ClientVarsSubscription, 0, sizeof(ClientVarsSubscription));
	brsmemset((UDINT)&ClientReceivedEvent, 0, sizeof(ClientReceivedEvent));
	brsmemset((UDINT)&ServerNamespacesArray, 0, sizeof(ServerNamespacesArray));
	brsmemset((UDINT)&ServerStatus, 0, sizeof(ServerStatus));
	brsmemset((UDINT)&ServerDiagData, 0, sizeof(ServerDiagData));
	brsmemset((UDINT)&SessionDiagnosticsArray, 0, sizeof(SessionDiagnosticsArray));
	brsmemset((UDINT)&SessionSecurityDiagnosticsArray, 0, sizeof(SessionSecurityDiagnosticsArray));
	brsmemset((UDINT)&SubscriptionDiagnosticsArray, 0, sizeof(SubscriptionDiagnosticsArray));
	
	// Initialisierung der RunClient-Monitors
	brsmemset((UDINT)&RcMonitor, 0, sizeof(RcMonitor));

}

void _CYCLIC Cyclic(void)
{
	// Zyklischer Aufruf des RunClients
	if(RunClient.State.eClientState >= eBRB_RCCLTSTATE_INIT_DONE && RunClient.State.eClientState <= eBRB_RCCLTSTATE_EXITING)
	{
		fbBrbUaRunClientCyclic.pRunClient = &RunClient;
		BrbUaRunClientCyclic(&fbBrbUaRunClientCyclic);
	}
	
	// ReadBlock 0 lesen
	fbTimerReadBlock0.IN = (RunClient.State.eClientState == eBRB_RCCLTSTATE_CONNECTED);
	fbTimerReadBlock0.PT = 1000;
	TON(&fbTimerReadBlock0);
	if(fbTimerReadBlock0.Q == 1)
	{
		fbBrbUaRcReadBlock0.pRunClient = &RunClient;
		fbBrbUaRcReadBlock0.nReadBlockIndex = 0;
		BrbUaRcReadBlock(&fbBrbUaRcReadBlock0);
		if(fbBrbUaRcReadBlock0.nStatus != eBRB_ERR_BUSY)
		{
			// Timer neu triggern
			fbTimerReadBlock0.IN = 0;
			TON(&fbTimerReadBlock0);
		}
	}

	// WriteBlock 0 schreiben
	fbTimerWriteBlock0.IN = (RunClient.State.eClientState == eBRB_RCCLTSTATE_CONNECTED);
	fbTimerWriteBlock0.PT = 1000;
	TON(&fbTimerWriteBlock0);
	if(fbTimerWriteBlock0.Q == 1)
	{
		fbBrbUaRcWriteBlock0.pRunClient = &RunClient;
		fbBrbUaRcWriteBlock0.nWriteBlockIndex = 0;
		BrbUaRcWriteBlock(&fbBrbUaRcWriteBlock0);
		if(fbBrbUaRcWriteBlock0.nStatus != eBRB_ERR_BUSY)
		{
			// Timer neu triggern
			fbTimerWriteBlock0.IN = 0;
			TON(&fbTimerWriteBlock0);
		}
	}
	
	// Method 0 aufrufen (Calculate)
	fbTimerCallMethodCalculate.IN = (RunClient.State.eClientState == eBRB_RCCLTSTATE_CONNECTED);
	fbTimerCallMethodCalculate.PT = 1000;
	TON(&fbTimerCallMethodCalculate);
	if(fbTimerCallMethodCalculate.Q == 1)
	{
		fbBrbUaRcCallMethodCalculate.pRunClient = &RunClient;
		fbBrbUaRcCallMethodCalculate.nMethodIndex = 0;
		BrbUaRcCallMethod(&fbBrbUaRcCallMethodCalculate);
		if(fbBrbUaRcCallMethodCalculate.bInit == 1)
		{
			// Pro Aufruf einmalig Eingänge mit Zufallszahlen besetzen
			ClientMethCalculateArgs.In.nVal0 = BrbGetRandomDint(1, 10);
			ClientMethCalculateArgs.In.nVal1 = BrbGetRandomDint(1, 10);
			UINT nItemIndex = 0;
			for(nItemIndex=0; nItemIndex<=nMETHOD_CALC_ARRAY_INDEX_MAX; nItemIndex++)
			{
				ClientMethCalculateArgs.In.anArray[nItemIndex] = (INT)BrbGetRandomDint(1, 10);
			}
		}
		if(fbBrbUaRcCallMethodCalculate.nStatus != eBRB_ERR_BUSY)
		{
			// Call zurückgemeldet -> Timer neu triggern
			fbTimerCallMethodCalculate.IN = 0;
			TON(&fbTimerCallMethodCalculate);
		}
	}
	
	// Erkennen einer Wert-Änderung von Subscripton0, MonitoredItem1 (=nUsint)
	ClientReceivedMonItem.bValueChanged = BrbUaRcGetMiValueChanged(&RunClient, 0, 1, 0);
	if(ClientReceivedMonItem.bValueChanged == 1)
	{
		// Wert-Änderung wurde empfangen
		// Beispielsweise Zähler erhöhen
		ClientReceivedMonItem.nReceivedCount++;
		// Flag zurücksetzen
		BrbUaRcGetMiValueChanged(&RunClient, 0, 1, 1);
	}
		
	// Prüfen, ob Event von Subscripton3, EventItem0 empfangen wurde
	if(BrbUaRcGetEventItemReceived(&RunClient, 3, 0) == 1)
	{
		// Event wurde empfangen
		ClientReceivedEvent.nReceivedCount = BrbUaRcGetEventItemReceiveCount(&RunClient, 3, 0);
		// Das Feld EventId wird in einen Hex-String gewandelt
		BrbUsintArrayToHex((USINT*)&ClientReceivedEvent.EventId.Data, ClientReceivedEvent.EventId.Length, (STRING*)&ClientReceivedEvent.sEventIdHex, sizeof(ClientReceivedEvent.sEventIdHex), 0);
		// Das Feld ReceiveTime wird in einen Text gewandelt. Dabei wird mithilfe des Felds LocalTime von Utc-Zeit in lokale Server-Zeit umgerechnet
		BrbUaGetSrvTimeText(&ClientReceivedEvent.ReceiveTime, ClientReceivedEvent.sReceiveTime, sizeof(ClientReceivedEvent.sReceiveTime), ClientReceivedEvent.LocalTime.TimeOffset, "yyyy:mm:dd hh:MM:ss::milms:mic.µs:nanns");
	}
	
	// RunClient-Monitor
	BrbUaRcMonitor(&RunClient, &RcMonitor);
	
}

void _EXIT Exit(void)
{
	// Aufruf zum Exit des RunClients
	do
	{
		fbBrbUaRunClientExit.pRunClient = &RunClient;
		BrbUaRunClientExit(&fbBrbUaRunClientExit);
	} while(fbBrbUaRunClientExit.nStatus == eBRB_ERR_BUSY);
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLibUa.h"
#include <AnsiCFunc.h>
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Behandelt einen Methoden-Aufruf */
plcdword BrbUaSrvHandleMethod(struct BrbUaSrvMethod_TYP* pMethod)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pMethod != 0)
	{
		nStatus = 0x00000000; // = Good
		if(pMethod->Par.bEnable == 1)
		{
			pMethod->Intern.bEnabled = 1;
		}
		if(pMethod->Intern.bEnabled == 1)
		{
			switch(pMethod->Intern.nStep)
			{
				case 0: // Init
					BrbStringCopy(pMethod->Intern.fbUaSrv_MethodOperate.MethodName, pMethod->Par.sMethodName, sizeof(pMethod->Intern.fbUaSrv_MethodOperate.MethodName));
					pMethod->Intern.nErrorId = 0;
					pMethod->Intern.fbUaSrv_MethodOperate.Action = UaMoa_CheckIsCalled;	// Abfrage über Baustein
					pMethod->Intern.fbUaSrv_MethodOperate.Execute = 1;
					pMethod->Intern.nStep = 1;
					break;
		
				case 1: // Prüfen, ob Methode aufgerufen ist
					UaSrv_MethodOperate(&pMethod->Intern.fbUaSrv_MethodOperate);
					if(pMethod->Intern.fbUaSrv_MethodOperate.Busy == 0)
					{
						if(pMethod->Intern.fbUaSrv_MethodOperate.Done == 1)
						{	
							if(pMethod->Intern.fbUaSrv_MethodOperate.IsCalled == 1)
							{
								// Methode ist aufgerufen -> Ausführung
								pMethod->State.bExecuteUserCode = 1;
								pMethod->State.bExecuteUserCodeInit = 1;
								pMethod->Par.bUserCodeIsFinished = 0;
								pMethod->State.nCallCount += 1;
								pMethod->Intern.fbUaSrv_MethodOperate.Execute = 0;
								UaSrv_MethodOperate(&pMethod->Intern.fbUaSrv_MethodOperate);
								pMethod->Intern.nStep = 2;
							}
							else if(pMethod->Par.bEnable == 0)
							{
								// Ausführung soll und kann beendet werden
								pMethod->Intern.fbUaSrv_MethodOperate.Execute = 0;
								UaSrv_MethodOperate(&pMethod->Intern.fbUaSrv_MethodOperate);
								pMethod->Intern.bEnabled = 0;
								pMethod->Intern.nStep = 0;
							}
							else
							{
								// Weiter prüfen
								pMethod->Intern.fbUaSrv_MethodOperate.Execute = 0;
								UaSrv_MethodOperate(&pMethod->Intern.fbUaSrv_MethodOperate);
								pMethod->Intern.fbUaSrv_MethodOperate.Execute = 1;
							}
						}
						else if(pMethod->Intern.fbUaSrv_MethodOperate.Error == 1)
						{
							// Fehler
							pMethod->Intern.nErrorId = pMethod->Intern.fbUaSrv_MethodOperate.ErrorID;
							pMethod->State.nLastErrorId = pMethod->Intern.fbUaSrv_MethodOperate.ErrorID;
							pMethod->State.eLastErrorAction = pMethod->Intern.fbUaSrv_MethodOperate.Action;
							pMethod->State.nErrorCount += 1;
							pMethod->Intern.fbUaSrv_MethodOperate.Execute = 0;
							UaSrv_MethodOperate(&pMethod->Intern.fbUaSrv_MethodOperate);
							pMethod->Intern.nStep = 4;
						}
					}
					break;

				case 2:	// Warten auf Ausführung des User-Codes
					pMethod->State.bExecuteUserCodeInit = 0;
					if(pMethod->Par.bUserCodeIsFinished == 1)
					{
						// User-Code ist fertig ausgeführt
						pMethod->State.bExecuteUserCode = 0;
						pMethod->Par.bUserCodeIsFinished = 0;
						BrbStringCopy(pMethod->Intern.fbUaSrv_MethodOperate.MethodName, pMethod->Par.sMethodName, sizeof(pMethod->Intern.fbUaSrv_MethodOperate.MethodName));
						pMethod->Intern.fbUaSrv_MethodOperate.Action = UaMoa_Finished;	// Rückmeldung an Baustein
						pMethod->Intern.fbUaSrv_MethodOperate.Execute = 1;
						pMethod->Intern.nStep = 3;
					}
					break;

				case 3:	// Ausführung rückmelden
					UaSrv_MethodOperate(&pMethod->Intern.fbUaSrv_MethodOperate);
					if(pMethod->Intern.fbUaSrv_MethodOperate.Busy == 0)
					{
						if(pMethod->Intern.fbUaSrv_MethodOperate.Done == 1)
						{
							// Bereit für neuen Aufruf
							if(pMethod->Par.bEnable == 0)
							{
								// Ausführung soll und kann beendet werden
								pMethod->Intern.bEnabled = 0;
							}		
							pMethod->Intern.fbUaSrv_MethodOperate.Execute = 0;
							UaSrv_MethodOperate(&pMethod->Intern.fbUaSrv_MethodOperate);
							pMethod->Intern.nStep = 0;
						}
						else if(pMethod->Intern.fbUaSrv_MethodOperate.Error == 1)
						{
							// Fehler
							pMethod->Intern.nErrorId = pMethod->Intern.fbUaSrv_MethodOperate.ErrorID;
							pMethod->State.nLastErrorId = pMethod->Intern.fbUaSrv_MethodOperate.ErrorID;
							pMethod->State.eLastErrorAction = pMethod->Intern.fbUaSrv_MethodOperate.Action;
							pMethod->State.nErrorCount += 1;
							pMethod->Intern.fbUaSrv_MethodOperate.Execute = 0;
							UaSrv_MethodOperate(&pMethod->Intern.fbUaSrv_MethodOperate);
							pMethod->Intern.nStep = 4;
						}
					}
					break;

				case 4:	// Fehler im Baustein
					nStatus = pMethod->Intern.nErrorId;
					pMethod->State.bExecuteUserCode = 0;
					pMethod->Par.bUserCodeIsFinished = 0;
					pMethod->Intern.fbUaSrv_MethodOperate.Execute = 0;
					UaSrv_MethodOperate(&pMethod->Intern.fbUaSrv_MethodOperate);
					if(pMethod->Par.bEnable == 0)
					{
						// Ausführung soll und kann beendet werden
						pMethod->Intern.bEnabled = 0;
					}
					pMethod->Intern.nStep = 0;
					break;

			}
			BrbUaGetStatusCodeText(pMethod->State.nLastErrorId, pMethod->State.sLastErrorId, sizeof(pMethod->State.sLastErrorId));
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

void _INIT Init(void)
{
	// Abl�schen der Funktionsbl�cke und Strukturen 
	brsmemset((UDINT)&fbUaSrv_MethodOperateCalculate, 0, sizeof(fbUaSrv_MethodOperateCalculate));
	brsmemset((UDINT)&MethCalculateArgs, 0, sizeof(MethCalculateArgs));
	
	// Setzen der Methode 'Calculate'
	brsstrcpy((UDINT)&fbUaSrv_MethodOperateCalculate.MethodName, (UDINT)&"Calculate"); // Name der Methode wie in 'Methods.uam' angegeben
	
	// Initialisierung der Schrittkette
	Step.eStepNr = eSTEP_CHECK;

}

void _CYCLIC Cyclic(void)
{
	
	// Schrittkette
	switch(Step.eStepNr)
	{
		case eSTEP_NONE:

		case eSTEP_CHECK:
			// Pr�fen, ob Methode von einem Client aufgerufen wurde
			fbUaSrv_MethodOperateCalculate.Execute = 1;
			fbUaSrv_MethodOperateCalculate.Action = UaMoa_CheckIsCalled;
			if(fbUaSrv_MethodOperateCalculate.Done == 1)
			{
				fbUaSrv_MethodOperateCalculate.Execute = 0;
				if(fbUaSrv_MethodOperateCalculate.IsCalled == 1)
				{
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausf�hren
					Step.eStepNr = eSTEP_EXECUTE;
				}
			}
			else if(fbUaSrv_MethodOperateCalculate.Error == 1)
			{
				fbUaSrv_MethodOperateCalculate.Execute = 0;
				Step.eErrorStep = Step.eStepNr;
				Step.eAction = fbUaSrv_MethodOperateCalculate.Action;
				Step.nErrorId = fbUaSrv_MethodOperateCalculate.ErrorID;
			}
			break;

		case eSTEP_EXECUTE:
			// Ausf�hren der Methode (Besetzen der Ausgangs-Argumente)
			MethCalculateArgs.Out.nAddition = MethCalculateArgs.In.nVal0 + MethCalculateArgs.In.nVal1;
			MethCalculateArgs.Out.nMultiplication = MethCalculateArgs.In.nVal0 * MethCalculateArgs.In.nVal1;
			brsmemcpy((UDINT)&MethCalculateArgs.Out.anArray, (UDINT)&MethCalculateArgs.In.anArray, sizeof(MethCalculateArgs.Out.anArray)); // In-Array auf Out-Array �bernehmen
			
			nMethCalculateCallCount += 1; // Nur zur Diagnose
			Step.eStepNr = eSTEP_FINSHED;
			break;

		case eSTEP_FINSHED:
			// R�ckmelden, dass Methode ausgef�hrt wurde. Zu diesem Zeitpunkt m�ssen die Ausgangs-Argumente besetzt sein und d�rfen nicht mehr ge�ndert werden
			fbUaSrv_MethodOperateCalculate.Execute = 1;
			fbUaSrv_MethodOperateCalculate.Action = UaMoa_Finished;
			if(fbUaSrv_MethodOperateCalculate.Done == 1)
			{
				fbUaSrv_MethodOperateCalculate.Execute = 0;
				Step.eStepNr = eSTEP_CHECK;
			}
			else if(fbUaSrv_MethodOperateCalculate.Error == 1)
			{
				// Fehler eintragen, aber trotzdem weiter machen
				fbUaSrv_MethodOperateCalculate.Execute = 0;
				Step.eErrorStep = Step.eStepNr;
				Step.eAction = fbUaSrv_MethodOperateCalculate.Action;
				Step.nErrorId = fbUaSrv_MethodOperateCalculate.ErrorID;
				Step.eStepNr = eSTEP_CHECK;
			}
			break;

	}

	// Aufruf aller PlcOpen-Funktionsbl�cke
	UaSrv_MethodOperate(&fbUaSrv_MethodOperateCalculate);
}

void _EXIT Exit(void)
{
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

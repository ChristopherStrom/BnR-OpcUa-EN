#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

// Prototypen
void InitAirCond(AirCond_TYP* pInstance, AirCondIntern_TYP* pIntern, STRING* pInstanceName, STRING* pMethodName, STRING* pEventFieldsBaseVarName, STRING* pEventFieldSourceNode);
void OperateAirCond(AirCond_TYP* pInstance, AirCondIntern_TYP* pIntern);
void SimulateAirCond(AirCond_TYP* pInstance, AirCondIntern_TYP* pIntern);
void GetOperationModeText(AirCondOperationMode_ENUM eOperationMode, STRING* pText);

void _INIT Init(void)
{
	// Initialisierung der einzelnen Instanzen
	InitAirCond(&AirCond_BedRoom, &AirCondIntern_BedRoom, "Bed room", "BedRoomSetOperationMode", "AirCondC:AirCondIntern_BedRoom.EvntOperationModeChanged.Fields", "5013");
	InitAirCond(&AirCond_Corridor, &AirCondIntern_Corridor, "Corridor", "CorridorSetOperationMode", "AirCondC:AirCondIntern_Corridor.EvntOperationModeChanged.Fields", "5017");
	InitAirCond(&AirCond_LivingRoom, &AirCondIntern_LivingRoom, "Living room", "LivingRoomSetOperationMode", "AirCondC:AirCondIntern_LivingRoom.EvntOperationModeChanged.Fields", "5020");
	
}

void _CYCLIC Cyclic(void)
{
	// Steuerung und Simulation der einzelnen Instanzen
	OperateAirCond(&AirCond_BedRoom, &AirCondIntern_BedRoom);
	OperateAirCond(&AirCond_Corridor, &AirCondIntern_Corridor);
	OperateAirCond(&AirCond_LivingRoom, &AirCondIntern_LivingRoom);
}

void _EXIT Exit(void)
{
}


// Initialisierung einer Instanz
void InitAirCond(AirCond_TYP* pInstance, AirCondIntern_TYP* pIntern, STRING* pInstanceName, STRING* pMethodName, STRING* pEventFieldsBaseVarName, STRING* pEventFieldSourceNode)
{
	// Logik
	pInstance->Act.eOperationMode = eAC_OPERATIONMODE_OFF;
	pInstance->Act.rTemperature = rAIR_COND_TEMP_OUTSIDE;
	pInstance->Act.nFanLevel = 0;
	pInstance->Set.rTemperature = 20.0f;	
	pInstance->Set.nFanLevel = 0;
	
	// Name der Instanz
	brsstrcpy((UDINT)&pInstance->sName, (UDINT)pInstanceName);	
	
	// Methode 'SetOperationMode'
	brsstrcpy((UDINT)&pIntern->MethSetOperationMode.fbUaSrv_MethodOperate.MethodName, (UDINT)pMethodName);

	// Event 'AirConditionOperationModeChanged'
	brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.sEventFieldsBaseVarName, (UDINT)pEventFieldsBaseVarName);
	brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.sEventFieldSourceNode, (UDINT)pEventFieldSourceNode);
	
}

// Steuerung einer Instanz
void OperateAirCond(AirCond_TYP* pInstance, AirCondIntern_TYP* pIntern)
{
	// Methode 'SetOperationMode'
	switch(pIntern->MethSetOperationMode.nStep)
	{
		case 0:
			// Prüfen, ob Methode von einem Client aufgerufen wurde
			pIntern->MethSetOperationMode.fbUaSrv_MethodOperate.Execute = 1;
			pIntern->MethSetOperationMode.fbUaSrv_MethodOperate.Action = UaMoa_CheckIsCalled;
			if(pIntern->MethSetOperationMode.fbUaSrv_MethodOperate.Done == 1)
			{
				pIntern->MethSetOperationMode.fbUaSrv_MethodOperate.Execute = 0;
				if(pIntern->MethSetOperationMode.fbUaSrv_MethodOperate.IsCalled == 1)
				{
					// Variablen der Eingans-Argumente sind besetzt -> Methode ausführen
					pIntern->MethSetOperationMode.nStep = 1;
				}
			}
			else if(pIntern->MethSetOperationMode.fbUaSrv_MethodOperate.Error == 1)
			{
				// Fehler, aber trotzdem weiter machen
				pIntern->MethSetOperationMode.fbUaSrv_MethodOperate.Execute = 0;
			}
			break;

		case 1:
			// Ausführen der Methode
			if(pIntern->MethSetOperationMode.ArgsIn.eOperationMode >= eAC_OPERATIONMODE_OFF && pIntern->MethSetOperationMode.ArgsIn.eOperationMode <= eAC_OPERATIONMODE_AUTO)
			{
				pInstance->Act.eOperationMode = pIntern->MethSetOperationMode.ArgsIn.eOperationMode;
				pIntern->MethSetOperationMode.ArgsOut.eStatus = eAC_METH_STATUS_OK;
			}
			else
			{
				pIntern->MethSetOperationMode.ArgsOut.eStatus = eAC_METH_STATUS_INVALID_OPMODE;
			}
			pIntern->MethSetOperationMode.nStep = 2;
			break;

		case 2:
			// Rückmelden, dass Methode ausgeführt wurde. Zu diesem Zeitpunkt müssen die Ausgangs-Argumente besetzt sein und dürfen nicht mehr geändert werden
			pIntern->MethSetOperationMode.fbUaSrv_MethodOperate.Execute = 1;
			pIntern->MethSetOperationMode.fbUaSrv_MethodOperate.Action = UaMoa_Finished;
			if(pIntern->MethSetOperationMode.fbUaSrv_MethodOperate.Done == 1)
			{
				pIntern->MethSetOperationMode.fbUaSrv_MethodOperate.Execute = 0;
				pIntern->MethSetOperationMode.nStep = 0;
			}
			else if(pIntern->MethSetOperationMode.fbUaSrv_MethodOperate.Error == 1)
			{
				// Fehler, aber trotzdem weiter machen
				pIntern->MethSetOperationMode.fbUaSrv_MethodOperate.Execute = 0;
				pIntern->MethSetOperationMode.nStep = 0;
			}
			break;

	}
	UaSrv_MethodOperate(&pIntern->MethSetOperationMode.fbUaSrv_MethodOperate);
	
	// Begrenzung der SetTemp
	if(pInstance->Set.rTemperature < rAIR_COND_TEMP_MIN)
	{
		pInstance->Set.rTemperature = rAIR_COND_TEMP_MIN;
	}
	else if(pInstance->Set.rTemperature > rAIR_COND_TEMP_OUTSIDE)
	{
		pInstance->Set.rTemperature = rAIR_COND_TEMP_OUTSIDE;
	}
	// Berechnung der internen Werte (Abweichung in Prozent)
	pIntern->rDiff = pInstance->Act.rTemperature - pInstance->Set.rTemperature;
	pIntern->rDiffPercent = pIntern->rDiff / pInstance->Act.rTemperature * 100.0f;
	// Steuern des Lüfters
	if(pInstance->Act.eOperationMode == eAC_OPERATIONMODE_OFF)
	{
		// Lüfter ausschalten
		pInstance->Act.nFanLevel = 0;
	}
	else if(pInstance->Act.eOperationMode == eAC_OPERATIONMODE_MANUAL)
	{
		// Lüfter-Stufe aus manueller Vorgabe übernehmen
		if(pInstance->Set.nFanLevel > 5)
		{
			pInstance->Act.nFanLevel = 5;
		}
		else
		{
			pInstance->Act.nFanLevel = pInstance->Set.nFanLevel;
		}
	}
	else if(pInstance->Act.eOperationMode == eAC_OPERATIONMODE_AUTO)
	{
		// Lüfter-Stufe je nach Temperatur-Differenz setzen
		if(pIntern->rDiffPercent <= 0.0f)
		{
			pInstance->Act.nFanLevel = 0;
		}
		else if(pIntern->rDiffPercent <= 10.0f)
		{
			pInstance->Act.nFanLevel = 1;
		}
		else if(pIntern->rDiffPercent <= 15.0f)
		{
			pInstance->Act.nFanLevel = 2;
		}
		else if(pIntern->rDiffPercent <= 20.0f)
		{
			pInstance->Act.nFanLevel = 3;
		}
		else if(pIntern->rDiffPercent <= 25.0f)
		{
			pInstance->Act.nFanLevel = 4;
		}
		else 
		{
			pInstance->Act.nFanLevel = 5;
		}
	}
	SimulateAirCond(pInstance, pIntern);

	// Event 'AirConditionOperationModeChanged'
	if(pInstance->Act.eOperationMode != pIntern->EvntOperationModeChanged.eOldOperationMode)
	{
		// Besetzen der Felder mit aktuellen Werten
		pIntern->EvntOperationModeChanged.Fields.OldOperationMode = pIntern->EvntOperationModeChanged.eOldOperationMode;
		pIntern->EvntOperationModeChanged.Fields.NewOperationMode = pInstance->Act.eOperationMode;
		STRING sMessageText[512];
		brsmemset((UDINT)&sMessageText, 0, sizeof(sMessageText));
		brsstrcpy((UDINT)&sMessageText, (UDINT)&"Operation mode of air condition '");
		brsstrcat((UDINT)&sMessageText, (UDINT)&pInstance->sName);
		brsstrcat((UDINT)&sMessageText, (UDINT)&"' has changed from '");
		GetOperationModeText(pIntern->EvntOperationModeChanged.Fields.OldOperationMode, sMessageText);
		brsstrcat((UDINT)&sMessageText, (UDINT)&"' to '");
		GetOperationModeText(pIntern->EvntOperationModeChanged.Fields.NewOperationMode, sMessageText);
		brsstrcat((UDINT)&sMessageText, (UDINT)&"' (C).");
		brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.Fields.Message.Text, (UDINT)&sMessageText);
		// Event feuern
		pIntern->EvntOperationModeChanged.bFire = 1;
	}
	pIntern->EvntOperationModeChanged.eOldOperationMode = pInstance->Act.eOperationMode;
	switch(pIntern->EvntOperationModeChanged.nStep)
	{
		case 0:
			// Ermitteln des Namespace-Index für Fremdmodell-Adressbereich am am B&R-Server
			pIntern->EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex.Execute = 1;
			brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex.NamespaceUri, (UDINT)&"http://br-automation.com/AirCondModel/");
			if(pIntern->EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex.Done == 1)
			{
				pIntern->EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex.Execute = 0;
				pIntern->EvntOperationModeChanged.nNamespaceIndexAirCond = pIntern->EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex.NamespaceIndex;
				brsitoa((DINT)pIntern->EvntOperationModeChanged.nNamespaceIndexAirCond, (UDINT)&pIntern->EvntOperationModeChanged.sNamespaceIndexAirCond);
				pIntern->EvntOperationModeChanged.nStep += 1;
			}
			else if(pIntern->EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex.Error == 1)
			{
				// Fehler
				pIntern->EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex.Execute = 0;
			}
			break;

		case 1:
			// Initialisierung zum Feuern des Events
			// Event-Typ
			pIntern->EvntOperationModeChanged.fbUaSrv_FireEvent.EventType.NamespaceIndex = pIntern->EvntOperationModeChanged.nNamespaceIndexAirCond;
			pIntern->EvntOperationModeChanged.fbUaSrv_FireEvent.EventType.IdentifierType = UAIdentifierType_Numeric;
			brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.fbUaSrv_FireEvent.EventType.Identifier, (UDINT)&"1002"); // = AirConditionOperationModeChanged
			// Event-Felder
			UINT nFieldIndex = 0;
			STRING sFieldNameTotal[128];
			brsmemset((UDINT)&sFieldNameTotal, 0, sizeof(sFieldNameTotal));
			STRING sVarNameTotal[255];
			brsmemset((UDINT)&sVarNameTotal, 0, sizeof(sVarNameTotal));
			// SourceNode
			brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].BrowsePath, (UDINT)&"/SourceNode");
			brsstrcpy((UDINT)&sVarNameTotal, (UDINT)pIntern->EvntOperationModeChanged.sEventFieldsBaseVarName);
			brsstrcat((UDINT)&sVarNameTotal, (UDINT)&".SourceNode");
			brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].Variable, (UDINT)&sVarNameTotal);
			pIntern->EvntOperationModeChanged.Fields.SourceNode.NamespaceIndex = pIntern->EvntOperationModeChanged.nNamespaceIndexAirCond;
			pIntern->EvntOperationModeChanged.Fields.SourceNode.IdentifierType = UAIdentifierType_Numeric;
			brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.Fields.SourceNode.Identifier, (UDINT)&pIntern->EvntOperationModeChanged.sEventFieldSourceNode);
			// Message
			nFieldIndex += 1;
			brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].BrowsePath, (UDINT)&"/Message");
			brsstrcpy((UDINT)&sVarNameTotal, (UDINT)pIntern->EvntOperationModeChanged.sEventFieldsBaseVarName);
			brsstrcat((UDINT)&sVarNameTotal, (UDINT)&".Message");
			brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].Variable, (UDINT)&sVarNameTotal);
			brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.Fields.Message.Text, (UDINT)&"Operation mode has changed.");
			// OldOperationMode
			nFieldIndex += 1;
			brsstrcpy((UDINT)&sFieldNameTotal, (UDINT)&"/");
			brsstrcat((UDINT)&sFieldNameTotal, (UDINT)pIntern->EvntOperationModeChanged.sNamespaceIndexAirCond);
			brsstrcat((UDINT)&sFieldNameTotal, (UDINT)&":OldOperationMode");
			brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].BrowsePath, (UDINT)&sFieldNameTotal);
			brsstrcpy((UDINT)&sVarNameTotal, (UDINT)pIntern->EvntOperationModeChanged.sEventFieldsBaseVarName);
			brsstrcat((UDINT)&sVarNameTotal, (UDINT)&".OldOperationMode");
			brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].Variable, (UDINT)&sVarNameTotal);
			// NewOperationMode
			nFieldIndex += 1;
			brsstrcpy((UDINT)&sFieldNameTotal, (UDINT)&"/");
			brsstrcat((UDINT)&sFieldNameTotal, (UDINT)pIntern->EvntOperationModeChanged.sNamespaceIndexAirCond);
			brsstrcat((UDINT)&sFieldNameTotal, (UDINT)&":NewOperationMode");
			brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].BrowsePath, (UDINT)&sFieldNameTotal);
			brsstrcpy((UDINT)&sVarNameTotal, (UDINT)pIntern->EvntOperationModeChanged.sEventFieldsBaseVarName);
			brsstrcat((UDINT)&sVarNameTotal, (UDINT)&".NewOperationMode");
			brsstrcpy((UDINT)&pIntern->EvntOperationModeChanged.Fields.FieldCfg[nFieldIndex].Variable, (UDINT)&sVarNameTotal);
			// Statische Funktionsblock-Eingänge
			pIntern->EvntOperationModeChanged.fbUaSrv_FireEvent.EventFieldCount = nFieldIndex+1;
			pIntern->EvntOperationModeChanged.fbUaSrv_FireEvent.EventFields = (UaSrv_FireEventFieldType*)&pIntern->EvntOperationModeChanged.Fields.FieldCfg;
			pIntern->EvntOperationModeChanged.nStep += 1;
			break;
			
		case 2:
			// Prüfen, ob Event gefeuert werden muss
			if(pIntern->EvntOperationModeChanged.bFire == 1)
			{
				pIntern->EvntOperationModeChanged.bFire = 0;
				pIntern->EvntOperationModeChanged.nStep += 1;
			}
			break;

		case 3:
			// Event feuern
			pIntern->EvntOperationModeChanged.fbUaSrv_FireEvent.Execute = 1;
			if(pIntern->EvntOperationModeChanged.fbUaSrv_FireEvent.Done == 1)
			{
				pIntern->EvntOperationModeChanged.fbUaSrv_FireEvent.Execute = 0;
				pIntern->EvntOperationModeChanged.nStep -= 1;
			}
			else if(pIntern->EvntOperationModeChanged.fbUaSrv_FireEvent.Error == 1)
			{
				// Fehler
			}
			break;

	}
	UaSrv_GetNamespaceIndex(&pIntern->EvntOperationModeChanged.fbUaSrv_GetNamespaceIndex);
	UaSrv_FireEvent(&pIntern->EvntOperationModeChanged.fbUaSrv_FireEvent);
}

// Simulation einer Instanz (Verändern der ActTemp)
void SimulateAirCond(AirCond_TYP* pInstance, AirCondIntern_TYP* pIntern)
{
	// Stetiges Angleichen an die Aussentemperatur
	pInstance->Act.rTemperature = pInstance->Act.rTemperature + 0.0005f;
	if(pInstance->Act.rTemperature > rAIR_COND_TEMP_OUTSIDE)
	{
		pInstance->Act.rTemperature = rAIR_COND_TEMP_OUTSIDE;
	}
	// Kühlen
	if(pInstance->Act.eOperationMode != eAC_OPERATIONMODE_OFF)
	{
		// Je nach Lüfter-Stufe kühlt die ActTemp runter
		pIntern->rCoolStepTemp = (REAL)pInstance->Act.nFanLevel * 0.005f;
		pInstance->Act.rTemperature = pInstance->Act.rTemperature - pIntern->rCoolStepTemp;
	}
	// Physikalische Begrenzung der ActTemp
	if(pInstance->Act.rTemperature < rAIR_COND_TEMP_MIN)
	{
		pInstance->Act.rTemperature = rAIR_COND_TEMP_MIN;
	}
}

// Wandeln des Betriebsmodus in Text
void GetOperationModeText(AirCondOperationMode_ENUM eOperationMode, STRING* pText)
{
	if(eOperationMode == eAC_OPERATIONMODE_OFF)
	{
		brsstrcat((UDINT)pText, (UDINT)&"Off");
	}
	else if(eOperationMode == eAC_OPERATIONMODE_MANUAL)
	{
		brsstrcat((UDINT)pText, (UDINT)&"Manual");
	}
	else if(eOperationMode == eAC_OPERATIONMODE_AUTO)
	{
		brsstrcat((UDINT)pText, (UDINT)&"Automatic");
	}
	else
	{
		brsstrcat((UDINT)pText, (UDINT)&"Unknown");
	}
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)


TYPE
	AirCond_TYP : 	STRUCT  (*Daten einer Klima-Anlage*)
		sName : STRING[32]; (*Name der Instanz*)
		Act : AirCondAct_TYP; (*Ist-Werte*)
		Set : AirCondSet_TYP; (*Soll-Werte*)
	END_STRUCT;
	AirCondAct_TYP : 	STRUCT  (*Ist-Werte*)
		eOperationMode : AirCondOperationMode_ENUM; (*Betriebs-Modus*)
		rTemperature : REAL; (*Temperatur in [�C]*)
		nFanLevel : USINT; (*L�fter-Stufe 0-5; 0=Off*)
	END_STRUCT;
	AirCondOperationMode_ENUM : 
		( (*Betriebs-Modus*)
		eAC_OPERATIONMODE_OFF, (*Aus*)
		eAC_OPERATIONMODE_MANUAL, (*Manuell*)
		eAC_OPERATIONMODE_AUTO (*Automatik*)
		);
	AirCondSet_TYP : 	STRUCT  (*Sollwerte*)
		rTemperature : REAL; (*Temperatur in [�C] f�r Automatik*)
		nFanLevel : USINT; (*L�fter-Stufe 0-5 f�r Manuell*)
	END_STRUCT;
	AirCondIntern_TYP : 	STRUCT  (*Interne Daten f�r Klima-Anlage*)
		rDiff : REAL; (*Differenz zwischen Soll- und Ist-Temperatur in [�C]*)
		rDiffPercent : REAL; (*Differenz zwischen Soll- und Ist-Temperatur in %*)
		rCoolStepTemp : REAL; (*Simulations-Dekrement zur K�hlung in [�C]*)
		MethSetOperationMode : AirCondIntMethSetOpMode_TYP; (*Daten f�r SetOperationMode*)
		EvntOperationModeChanged : AirCondIntEvntOpModeChanged_TYP;
	END_STRUCT;
	AirCondIntMethSetOpMode_TYP : 	STRUCT  (*Daten f�r SetOperationMode*)
		nStep : UINT; (*Schritt f�r die Schrittkette*)
		fbUaSrv_MethodOperate : UaSrv_MethodOperate; (*Funktionsblock zum Behandeln der Methode*)
		ArgsIn : AirCondIntMethSetOpModeIn_TYP; (*Eingangs-Argumente*)
		ArgsOut : AirCondIntMethSetOpModeOut_TYP; (*Ausgangs-Argumente*)
	END_STRUCT;
	AirCondIntMethSetOpModeIn_TYP : 	STRUCT  (*Eingangs-Argumente f�r SetOperationMode*)
		eOperationMode : AirCondOperationMode_ENUM; (*Betriebs-Modus*)
	END_STRUCT;
	AirCondMethodStatus_ENUM : 
		( (*Applikations-Status f�r SetOperationMode*)
		eAC_METH_STATUS_OK, (*Ok*)
		eAC_METH_STATUS_INVALID_OPMODE (*Betriebs-Modus ist nicht g�ltig*)
		);
	AirCondIntMethSetOpModeOut_TYP : 	STRUCT  (*Ausgangs-Argumente f�r SetOperationMode*)
		eStatus : AirCondMethodStatus_ENUM; (*Status*)
	END_STRUCT;
	AirCondIntEvntOpModeChanged_TYP : 	STRUCT 
		nStep : UINT; (*Schritt f�r die Schrittkette*)
		eOldOperationMode : AirCondOperationMode_ENUM; (*Betriebs-Modus*)
		bFire : BOOL; (*Kommando zum Feuern des Events*)
		fbUaSrv_GetNamespaceIndex : UaSrv_GetNamespaceIndex; (*Funktionsblock zum Ermitteln eines NamespaceIndex*)
		nNamespaceIndexAirCond : UINT; (*NamespaceIndex  des eigenen Modells*)
		sNamespaceIndexAirCond : STRING[3]; (*NamespaceIndex  des eigenen Modells*)
		sEventFieldsBaseVarName : STRING[128]; (*Beginn des Variablennamens zu den Feld-Werten*)
		sEventFieldSourceNode : STRING[64]; (*Numerische NodeId des Hauptknotens*)
		fbUaSrv_FireEvent : UaSrv_FireEvent; (*Funktionsblock zum Feuern des Events*)
		Fields : AirCondIntEvntOmcFields_TYP; (*Felder des Events*)
	END_STRUCT;
	AirCondIntEvntOmcFields_TYP : 	STRUCT  (*Felder des Events*)
		SourceNode : UANodeID;
		Message : UALocalizedText; (*Wert des Felds 'Message'*)
		OldOperationMode : AirCondOperationMode_ENUM; (*Wert des Felds 'OldOperationMode'*)
		NewOperationMode : AirCondOperationMode_ENUM; (*Wert des Felds 'NewOperationMode'*)
		FieldCfg : ARRAY[0..nAIR_COND_EVENT_FIELD_INDEX_MAX]OF UaSrv_FireEventFieldType; (*Konfiguration der Felder*)
	END_STRUCT;
END_TYPE

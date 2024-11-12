
TYPE
	Step_TYP : 	STRUCT 
		eStepNr : Steps_ENUM;
		eErrorStep : Steps_ENUM;
		nErrorId : DWORD;
		nFieldIndex : INT;
	END_STRUCT;
	Steps_ENUM : 
		(
		eSTEP_INIT,
		eSTEP_GET_NS_ORG,
		eSTEP_GET_NS_BR_PV,
		eSTEP_DELAY,
		eSTEP_SET_FIELD_VALUES,
		eSTEP_FIRE
		);
	Fields_TYP : 	STRUCT 
		Message : UALocalizedText;
		nSeverity : UINT;
		Context : EventFieldContext_TYP;
		nProgress : UINT;
		FieldCfg : ARRAY[0..nFIELD_INDEX_MAX]OF UaSrv_FireEventFieldType;
	END_STRUCT;
END_TYPE

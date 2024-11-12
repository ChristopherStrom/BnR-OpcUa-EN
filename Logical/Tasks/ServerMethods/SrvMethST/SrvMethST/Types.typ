
TYPE
	Step_TYP : 	STRUCT 
		eStepNr : Steps_ENUM;
		eErrorStep : Steps_ENUM;
		eAction : UaMethodOperateAction;
		nErrorId : DWORD;
	END_STRUCT;
	Steps_ENUM : 
		(
		eSTEP_NONE,
		eSTEP_CHECK,
		eSTEP_EXECUTE,
		eSTEP_FINSHED
		);
END_TYPE

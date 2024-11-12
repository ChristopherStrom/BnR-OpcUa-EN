
PROGRAM _INIT
	// Initialisierung der einzelnen Instanzen
	pInstance ACCESS ADR(AirCond_BedRoom);
	pIntern ACCESS ADR(AirCondIntern_BedRoom);
	InitAirCond;
	pInstance.sName := 'Bed room';
	pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.MethodName := 'BedRoomSetOperationMode';
	pIntern.EvntOperationModeChanged.sEventFieldsBaseVarName := 'AirCondST:AirCondIntern_BedRoom.EvntOperationModeChanged.Fields';
	pIntern.EvntOperationModeChanged.sEventFieldSourceNode := '5023';

	pInstance ACCESS ADR(AirCond_Corridor);
	pIntern ACCESS ADR(AirCondIntern_Corridor);
	InitAirCond;
	pInstance.sName := 'Corridor';
	pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.MethodName := 'CorridorSetOperationMode';
	pIntern.EvntOperationModeChanged.sEventFieldsBaseVarName := 'AirCondST:AirCondIntern_Corridor.EvntOperationModeChanged.Fields';
	pIntern.EvntOperationModeChanged.sEventFieldSourceNode := '5027';

	pInstance ACCESS ADR(AirCond_LivingRoom);
	pIntern ACCESS ADR(AirCondIntern_LivingRoom);
	InitAirCond;
	pInstance.sName := 'Living room';
	pIntern.MethSetOperationMode.fbUaSrv_MethodOperate.MethodName := 'LivingRoomSetOperationMode';
	pIntern.EvntOperationModeChanged.sEventFieldsBaseVarName := 'AirCondST:AirCondIntern_LivingRoom.EvntOperationModeChanged.Fields';
	pIntern.EvntOperationModeChanged.sEventFieldSourceNode := '5030';
END_PROGRAM

PROGRAM _CYCLIC
	// Steuerung und Simulation der einzelnen Instanzen
	pInstance ACCESS ADR(AirCond_BedRoom);
	pIntern ACCESS ADR(AirCondIntern_BedRoom);
	OperateAirCond;
	pInstance ACCESS ADR(AirCond_Corridor);
	pIntern ACCESS ADR(AirCondIntern_Corridor);
	OperateAirCond;
	pInstance ACCESS ADR(AirCond_LivingRoom);
	pIntern ACCESS ADR(AirCondIntern_LivingRoom);
	OperateAirCond;
END_PROGRAM

PROGRAM _EXIT
END_PROGRAM


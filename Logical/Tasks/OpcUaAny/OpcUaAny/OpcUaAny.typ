
TYPE
	DataVars_TYP : 	STRUCT 
		nUsint : USINT;
		nUint : UINT;
		nUdint : UDINT;
	END_STRUCT;
	DataReadWrite_TYP : 	STRUCT 
		Server : DataVars_TYP;
		Client : DataVars_TYP;
	END_STRUCT;
	Data_TYP : 	STRUCT 
		Read : DataReadWrite_TYP;
		Write : DataReadWrite_TYP;
	END_STRUCT;
END_TYPE

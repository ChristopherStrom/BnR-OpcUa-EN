
TYPE
	DynamicUintArrayLength_TYP : 	STRUCT 
		nLength : UAArrayLength;
		anData : ARRAY[0..9]OF UINT; (*nDYNAMIC_ARRAY_INDEX_MAX*)
	END_STRUCT;
	DynamicUintArrayElements_TYP : 	STRUCT 
		nLength : UANoOfElements;
		anData : ARRAY[0..9]OF UINT; (*nDYNAMIC_ARRAY_INDEX_MAX*)
	END_STRUCT;
	OpcUaTest_TYP : 	STRUCT 
		nUsint : USINT;
		rReal : REAL;
	END_STRUCT;
	DynamicStructArrayLength_TYP : 	STRUCT 
		nLength : UAArrayLength;
		Data : ARRAY[0..9]OF OpcUaTest_TYP; (*nDYNAMIC_ARRAY_INDEX_MAX*)
	END_STRUCT;
	DynamicStructArrayElements_TYP : 	STRUCT 
		nLength : UANoOfElements;
		Data : ARRAY[0..9]OF OpcUaTest_TYP; (*nDYNAMIC_ARRAY_INDEX_MAX*)
	END_STRUCT;
END_TYPE

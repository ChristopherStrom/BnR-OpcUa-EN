
TYPE
	SubscribedData_TYP : 	STRUCT 
		nUsint : USINT;
		nUint : UINT;
		nSint : SINT;
		nInt : INT;
		anInt : ARRAY[0..4]OF INT; (*INT[0..nOPCUA_ARRAY_INDEX_MAX]*)
	END_STRUCT;
END_TYPE

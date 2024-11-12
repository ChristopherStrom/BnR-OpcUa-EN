(* Helper function for modifying server variables *)
FUNCTION IncrementOpcUaTestDatatypes
	pDatatypes.bBool := NOT(pDatatypes.bBool);
	pDatatypes.nSint := pDatatypes.nSint + 1;
	pDatatypes.nInt := pDatatypes.nInt + 1;
	pDatatypes.nDint := pDatatypes.nDint + 1;
	pDatatypes.nUsint := pDatatypes.nUsint + 1;
	pDatatypes.nUint := pDatatypes.nUint + 1;
	pDatatypes.nUdint := pDatatypes.nUdint + 1;
	pDatatypes.rReal :=  pDatatypes.rReal + 0.1;
	pDatatypes.rLongReal := pDatatypes.rLongReal + 0.2;
	brsitoa(pDatatypes.nUsint, ADR(pDatatypes.sString));
	pDatatypes.tTime := pDatatypes.tTime + 1;
	pDatatypes.dtDateTime := pDatatypes.dtDateTime + 1;
	pDatatypes.anInt[0] := pDatatypes.anInt[0] + 1;
	pDatatypes.anInt[1] := pDatatypes.anInt[1] + 1;
	pDatatypes.anInt[2] := pDatatypes.anInt[2] + 1;
	pDatatypes.anInt[3] := pDatatypes.anInt[3] + 1;
	pDatatypes.anInt[4] := pDatatypes.anInt[4] + 1;
	
	IncrementOpcUaTestDatatypes := 0;
END_FUNCTION

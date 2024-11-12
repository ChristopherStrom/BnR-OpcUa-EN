
PROGRAM _INIT
	// Uint64 und Zähler-Grenzen setzen
	pUint64 ACCESS ADR(nUint64);
	BrbUint64FromString(pUint64, '0');
	pUint64CountMin ACCESS ADR(ChangeUint64Inst.nCountMin);
	BrbUint64FromString(pUint64CountMin, '5');
	pUint64CountMax ACCESS ADR(ChangeUint64Inst.nCountMax);
	BrbUint64FromString(pUint64CountMax, '18446744073709551610');
	ChangeUint64Inst.bCountPositive := 1;

	// Int64 und Zähler-Grenzen setzen
	pInt64 ACCESS ADR(nInt64);
	BrbInt64FromString(pInt64, '9223372036854775802');
	pInt64CountMin ACCESS ADR(ChangeInt64Inst.nCountMin);
	BrbInt64FromString(pInt64CountMin, '-9223372036854775803');
	pInt64CountMax ACCESS ADR(ChangeInt64Inst.nCountMax);
	BrbInt64FromString(pInt64CountMax, '9223372036854775802');
	ChangeInt64Inst.bCountPositive := 1;	
END_PROGRAM

PROGRAM _CYCLIC
	ChangeUint64; // Wert zyklisch ändern
	BrbUint64ToString(pUint64, sUint64, SIZEOF(sUint64)); // In Text für bessere Lesbarkeit wandeln

	ChangeInt64; // Wert zyklisch ändern
	BrbInt64ToString(pInt64, sInt64, SIZEOF(sInt64)); // In Text für bessere Lesbarkeit wandeln
END_PROGRAM

PROGRAM _EXIT
END_PROGRAM


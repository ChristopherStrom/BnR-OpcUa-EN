// Ändern des Uint64-Wertes
ACTION ChangeUint64: 
	IF ChangeUint64Inst.bCountPositive = 1 THEN
		BrbUint64Inc(pUint64);
		IF BrbUint64Compare(pUint64, pUint64CountMin) = 0 THEN
			ChangeUint64Inst.bCountPositive := 0;
		END_IF
	ELSE
		BrbUint64Dec(pUint64);
		IF BrbUint64Compare(pUint64, pUint64CountMax) = 0 THEN
			ChangeUint64Inst.bCountPositive := 1;
		END_IF
	END_IF
END_ACTION

// Ändern des Int64-Wertes
ACTION ChangeInt64: 
	IF ChangeInt64Inst.bCountPositive = 1 THEN
		BrbInt64Inc(pInt64);
		IF BrbInt64Compare(pInt64, pInt64CountMin) = 0 THEN
			ChangeInt64Inst.bCountPositive := 0;
		END_IF
	ELSE
		BrbInt64Dec(pInt64);
		IF BrbInt64Compare(pInt64, pInt64CountMax) = 0 THEN
			ChangeInt64Inst.bCountPositive := 1;
		END_IF
	END_IF
END_ACTION


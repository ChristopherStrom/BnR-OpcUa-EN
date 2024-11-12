#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLibUa.h"
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Gibt den Text eines Server-Zeitstempels zurück */
unsigned short BrbUaGetSrvTimeText(struct UaSrv_DateTimeType* pSrvTime, plcstring* pText, unsigned long nTextSize, signed short nTimeOffset, plcstring* pFormat)
{
	// Prüfung der Parameter
	if(pSrvTime == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	if(pText == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	if(nTextSize == 0)
	{
		return eBRB_ERR_INVALID_PARAMETER;
	}
	if(pFormat == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	// Zuerst die Werte umwandeln
	DTStructure DtStruct;
	DT_TO_DTStructure(pSrvTime->DateTime, (UDINT)&DtStruct);
	BrbDtStructAddMinutes(&DtStruct, nTimeOffset);
	UDINT nTotalNanoSeconds = pSrvTime->NanoSeconds;
	DtStruct.millisec = (UINT)(nTotalNanoSeconds / 1000000);
	nTotalNanoSeconds -= DtStruct.millisec * 1000000;
	DtStruct.microsec = (UINT)(nTotalNanoSeconds / 1000);
	nTotalNanoSeconds -= DtStruct.microsec * 1000;
	UINT nNanoSeconds = (UINT)nTotalNanoSeconds;
	// Alle Stellen werden mit führenden Nullen aufgefüllt
	memset((USINT*)pText, 0, nTextSize);
	BrbStringCopy(pText, pFormat, nTextSize);
	STRING sItoA[20];
	memset((USINT*)sItoA, 0, sizeof(sItoA));
	if(BrbStringGetAdrOf(pText, "mil", 0) != 0)
	{
		brsitoa((DINT)DtStruct.millisec, (UDINT)&sItoA);
		if(DtStruct.millisec < 10)
		{
			BrbStringInsert(sItoA, 0, "00");
		}
		else if(DtStruct.millisec < 100)
		{
			BrbStringInsert(sItoA, 0, "0");
		}
		BrbStringReplace(pText, "mil", sItoA);
	}
	if(BrbStringGetAdrOf(pText, "mic", 0) != 0)
	{
		brsitoa((DINT)DtStruct.microsec, (UDINT)&sItoA);
		if(DtStruct.microsec < 10)
		{
			BrbStringInsert(sItoA, 0, "00");
		}
		else if(DtStruct.microsec < 100)
		{
			BrbStringInsert(sItoA, 0, "0");
		}
		BrbStringReplace(pText, "mic", sItoA);
	}
	if(BrbStringGetAdrOf(pText, "nan", 0) != 0)
	{
		brsitoa((DINT)nNanoSeconds, (UDINT)&sItoA);
		if(nNanoSeconds < 10)
		{
			BrbStringInsert(sItoA, 0, "00");
		}
		else if(nNanoSeconds < 100)
		{
			BrbStringInsert(sItoA, 0, "0");
		}
		BrbStringReplace(pText, "nan", sItoA);
	}
	if(BrbStringGetAdrOf(pText, "yyyy", 0) != 0)
	{
		brsitoa((DINT)DtStruct.year, (UDINT)&sItoA);
		BrbStringPadLeft(sItoA, "0", 4);
		BrbStringReplace(pText, "yyyy", sItoA);
	}
	else if(BrbStringGetAdrOf(pText, "yy", 0) != 0)
	{
		DtStruct.year -= 2000;
		brsitoa((DINT)DtStruct.year, (UDINT)&sItoA);
		BrbStringPadLeft(sItoA, "0", 2);
		BrbStringReplace(pText, "yy", sItoA);
	}
	if(BrbStringGetAdrOf(pText, "mm", 0) != 0)
	{
		brsitoa((DINT)DtStruct.month, (UDINT)&sItoA);
		if(DtStruct.month < 10)
		{
			BrbStringInsert(sItoA, 0, "0");
		}
		BrbStringReplace(pText, "mm", sItoA);
	}
	else if(BrbStringGetAdrOf(pText, "m", 0) != 0)
	{
		brsitoa((DINT)DtStruct.month, (UDINT)&sItoA);
		BrbStringReplace(pText, "m", sItoA);
	}
	if(BrbStringGetAdrOf(pText, "dd", 0) != 0)
	{
		brsitoa((DINT)DtStruct.day, (UDINT)&sItoA);
		if(DtStruct.day < 10)
		{
			BrbStringInsert(sItoA, 0, "0");
		}
		BrbStringReplace(pText, "dd", sItoA);
	}
	else if(BrbStringGetAdrOf(pText, "d", 0) != 0)
	{
		brsitoa((DINT)DtStruct.day, (UDINT)&sItoA);
		BrbStringReplace(pText, "d", sItoA);
	}
	if(BrbStringGetAdrOf(pText, "hh", 0) != 0)
	{
		brsitoa((DINT)DtStruct.hour, (UDINT)&sItoA);
		if(DtStruct.hour < 10)
		{
			BrbStringInsert(sItoA, 0, "0");
		}
		BrbStringReplace(pText, "hh", sItoA);
	}
	else if(BrbStringGetAdrOf(pText, "h", 0) != 0)
	{
		brsitoa((DINT)DtStruct.hour, (UDINT)&sItoA);
		BrbStringReplace(pText, "h", sItoA);
	}
	if(BrbStringGetAdrOf(pText, "MM", 0) != 0)
	{
		brsitoa((DINT)DtStruct.minute, (UDINT)&sItoA);
		if(DtStruct.minute < 10)
		{
			BrbStringInsert(sItoA, 0, "0");
		}
		BrbStringReplace(pText, "MM", sItoA);
	}
	else if(BrbStringGetAdrOf(pText, "M", 0) != 0)
	{
		brsitoa((DINT)DtStruct.minute, (UDINT)&sItoA);
		BrbStringReplace(pText, "M", sItoA);
	}
	if(BrbStringGetAdrOf(pText, "ss", 0) != 0)
	{
		brsitoa((DINT)DtStruct.second, (UDINT)&sItoA);
		if(DtStruct.second < 10)
		{
			BrbStringInsert(sItoA, 0, "0");
		}
		BrbStringReplace(pText, "ss", sItoA);
	}
	else if(BrbStringGetAdrOf(pText, "s", 0) != 0)
	{
		brsitoa((DINT)DtStruct.second, (UDINT)&sItoA);
		BrbStringReplace(pText, "s", sItoA);
	}
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

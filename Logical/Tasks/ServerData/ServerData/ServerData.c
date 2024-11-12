#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

// Prototypen der lokalen Funktionen
void IncrementOpcUaTestDatatypes(OpcUaTestDatatypes_TYP* pDatatypes);
void ChangeDynamicArrays();

void _INIT Init(void)
{
	// Setzen der Test-Variablen
	brsmemset((UDINT)&gVarsGlobal, 0, sizeof(gVarsGlobal));
	brsstrcpy((UDINT)&gVarsGlobal.ReadOnly.sString, (UDINT)&"000");
	
	brsmemset((UDINT)&VarsLocal, 0, sizeof(VarsLocal));
	brsstrcpy((UDINT)&VarsLocal.ReadOnly.sString, (UDINT)&"000");

	brsmemset((UDINT)&WriteC, 0, sizeof(WriteC));
	brsmemset((UDINT)&WriteST, 0, sizeof(WriteST));
	
	// Diese Instanz der in den dynamischen Arrays verwendeten Struktur wird am Server freigegeben, damit dieser die Struktur-Definition veröffentlicht. Nur so kann ein Client diesen
	// benutzerdefinierten Datentypen auflösen.
	DummyStruct.nUsint = 0;
		
	DynamicUintArrayLength.nLength = 1;
	for(nIndex=0;nIndex<=nDYNAMIC_ARRAY_INDEX_MAX;nIndex++)
	{
		DynamicUintArrayLength.anData[nIndex] = nIndex;
	}
	DynamicUintArrayElements.nLength = 1;
	for(nIndex=0;nIndex<=nDYNAMIC_ARRAY_INDEX_MAX;nIndex++)
	{
		DynamicUintArrayElements.anData[nIndex] = nIndex;
	}
	DynamicStructArrayLength.nLength = 1;
	for(nIndex=0;nIndex<=nDYNAMIC_ARRAY_INDEX_MAX;nIndex++)
	{
		DynamicStructArrayLength.Data[nIndex].nUsint = (USINT)nIndex;
		DynamicStructArrayLength.Data[nIndex].rReal  = (REAL)nIndex + 0.1f;
	}
	DynamicStructArrayElements.nLength = 1;
	for(nIndex=0;nIndex<=nDYNAMIC_ARRAY_INDEX_MAX;nIndex++)
	{
		DynamicStructArrayElements.Data[nIndex].nUsint = (USINT)nIndex;
		DynamicStructArrayElements.Data[nIndex].rReal  = (REAL)nIndex + 0.1f;
	}
	
	nWritableAttributes = 123;
}

void _CYCLIC Cyclic(void)
{
	IncrementOpcUaTestDatatypes(&gVarsGlobal.ReadOnly);
	IncrementOpcUaTestDatatypes(&VarsLocal.ReadOnly);
	ChangeDynamicArrays();
}

void _EXIT Exit(void)
{
}

void IncrementOpcUaTestDatatypes(OpcUaTestDatatypes_TYP* pDatatypes)
{
	UINT		nStringLen;
	STRING	sHelpString[nOPCUA_STRING_CHAR_MAX];
	UINT		nHelpStringLen;

	pDatatypes->bBool = !pDatatypes->bBool;
	pDatatypes->nSint++;
	pDatatypes->nInt++;
	pDatatypes->nDint++;
	pDatatypes->nUsint++;
	pDatatypes->nUint++;
	pDatatypes->nUdint++;
	pDatatypes->rReal += 0.1f;
	pDatatypes->rLongReal += 0.2;
	pDatatypes->tTime++;
	pDatatypes->dtDateTime++;
	pDatatypes->anInt[0]++;
	pDatatypes->anInt[1]++;
	pDatatypes->anInt[2]++;
	pDatatypes->anInt[3]++;
	pDatatypes->anInt[4]++;

	nStringLen = (UINT)brsstrlen((UDINT)&pDatatypes->sString);
	brsitoa((DINT)pDatatypes->nUsint, (UDINT)&sHelpString);
	nHelpStringLen = (UINT)brsstrlen((UDINT)&sHelpString);
	if((nStringLen >= 3))
	{
		if(nHelpStringLen >= 3)
		{
			pDatatypes->sString[0] = sHelpString[0];
			pDatatypes->sString[1] = sHelpString[1];
			pDatatypes->sString[2] = sHelpString[2];
		}
		else if(nHelpStringLen == 2)
		{
			pDatatypes->sString[0] = 48;
			pDatatypes->sString[1] = sHelpString[0];
			pDatatypes->sString[2] = sHelpString[1];
		}
		else
		{
			pDatatypes->sString[0] = 48;
			pDatatypes->sString[1] = 48;
			pDatatypes->sString[2] = sHelpString[0];
		}
	}
	else if(nStringLen == 2)
	{
		if(nHelpStringLen >= 3)
		{
			pDatatypes->sString[0] = sHelpString[1];
			pDatatypes->sString[1] = sHelpString[2];
		}
		else if(nHelpStringLen == 2)
		{
			pDatatypes->sString[0] = sHelpString[0];
			pDatatypes->sString[1] = sHelpString[1];
		}
		else
		{
			pDatatypes->sString[0] = 48;
			pDatatypes->sString[1] = sHelpString[0];
		}
	}
	else if(nStringLen == 1)
	{
		if(nHelpStringLen >= 3)
		{
			pDatatypes->sString[0] = sHelpString[2];
		}
		else if(nHelpStringLen == 2)
		{
			pDatatypes->sString[0] = sHelpString[1];
		}
		else
		{
			pDatatypes->sString[0] = sHelpString[0];
		}
	}
}

void ChangeDynamicArrays()
{
	DynamicUintArrayLength.nLength = BrbGetRandomDint(1, 5);
	DynamicUintArrayElements.nLength = BrbGetRandomDint(1, 5);
	DynamicStructArrayLength.nLength = BrbGetRandomDint(1, 5);
	DynamicStructArrayElements.nLength = BrbGetRandomDint(1, 5);
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)



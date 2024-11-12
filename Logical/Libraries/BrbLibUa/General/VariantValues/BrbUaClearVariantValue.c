#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLibUa.h"
#include <AnsiCFunc.h>
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Löscht den Inhalt eines OpcUa-Values, aber nicht die Datentyp-Angabe */
plcdword BrbUaClearVariantValue(struct UAVariantData* pUaVariantData)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pUaVariantData != 0)
	{
		nStatus = 0x00000000; // = Good
		UAVariantType eVariantType = pUaVariantData->VariantType;
		memset(pUaVariantData, 0, sizeof(UAVariantData));
		pUaVariantData->VariantType = eVariantType;
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

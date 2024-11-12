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

/* Besetzt einen LocalizedText */
plcdword BrbUaSetLocalizedText(BrUaLocalizedText* pLocalizedText, plcstring* pLocale, plcstring* pText)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pLocalizedText != 0 && pLocale != 0 && pText != 0)
	{
		nStatus = 0x00000000; // = Good
		BrbStringCopy(pLocalizedText->Locale, pLocale, sizeof(pLocalizedText->Locale));
		BrbStringCopy(pLocalizedText->Text, pText, sizeof(pLocalizedText->Text));
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

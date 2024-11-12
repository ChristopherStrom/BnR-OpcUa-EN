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

/* Hängt den Text eines LocalizedText an */
plcdword BrbUaAddLocalizedTextText(BrUaLocalizedText* pLocalizedText, plcstring* pText, unsigned long nTextSize)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pLocalizedText != 0 && pText != 0)
	{
		nStatus = 0x00000000; // = Good
		if(strlen(pLocalizedText->Locale) > 0)
		{
			BrbStringCat(pText, pLocalizedText->Locale, nTextSize);
			BrbStringCat(pText, ":", nTextSize);
		}
		BrbStringCat(pText, pLocalizedText->Text, nTextSize);
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

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

/* Erezugt einen zufälligen LocalizedText */
plcdword BrbUaGetRandomLocalizedText(BrUaLocalizedText* pLocalizedText, unsigned short nLength)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pLocalizedText != 0)
	{
		nStatus = 0x00000000; // = Good
		STRING sLocale[6];
		UINT nLocale = (UINT)BrbGetRandomUdint(0,3);
		if(nLocale == 0)
		{
			BrbStringCopy(sLocale, "de", sizeof(sLocale));
		}
		else if(nLocale == 1)
		{
			BrbStringCopy(sLocale, "en", sizeof(sLocale));
		}
		else if(nLocale == 2)
		{
			BrbStringCopy(sLocale, "fr", sizeof(sLocale));
		}
		else if(nLocale == 3)
		{
			BrbStringCopy(sLocale, "es", sizeof(sLocale));
		}
		if(nLength > 255)
		{
			nLength = 255;
		}
		STRING sText[255];
		BrbGetRandomText((STRING*)&sText, sizeof(sText), nLength);
		BrbUaSetLocalizedText(pLocalizedText, sLocale, sText);
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

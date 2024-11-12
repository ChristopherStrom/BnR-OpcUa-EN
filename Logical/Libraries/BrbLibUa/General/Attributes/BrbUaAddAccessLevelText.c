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

/* Hängt den Text eines AccessLevels an */
plcdword BrbUaAddAccessLevelText(plcbyte nAccessLevel, plcstring* pText, unsigned long nTextSize)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pText != 0)
	{
		nStatus = 0x00000000; // = Good
		STRING sHelp[nBRBUA_VALUE_TEXT_CHAR_MAX];
		brsitoa((DINT)nAccessLevel, (UDINT)&sHelp);
		BrbStringCat(pText, sHelp, nTextSize);
		BrbStringCat(pText, "=", nTextSize);
		if(nAccessLevel == 0)
		{
			BrbStringCat(pText, " None", nTextSize);
		}
		else
		{
			if(BrbGetBitUsint(nAccessLevel, 0) == 1)
			{
				BrbStringCat(pText, " Read,", nTextSize);
			}
			if(BrbGetBitUsint(nAccessLevel, 1) == 1)
			{
				BrbStringCat(pText, " Write,", nTextSize);
			}
			if(BrbGetBitUsint(nAccessLevel, 2) == 1)
			{
				BrbStringCat(pText, " HistoryRead,", nTextSize);
			}
			if(BrbGetBitUsint(nAccessLevel, 3) == 1)
			{
				BrbStringCat(pText, " HistoryWrite,", nTextSize);
			}
			BrbStringTrimLeft(pText, " ");
			BrbStringTrimRight(pText, " ");
			BrbStringTrimRight(pText, ",");
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

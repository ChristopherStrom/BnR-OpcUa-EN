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

/* Hängt den Text für eine ArrayDimension an */
plcdword BrbUaAddArrayDimensionText(unsigned long* pArrayDimension, signed long nValueRank, plcstring* pText, unsigned long nTextSize)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pArrayDimension != 0 && pText != 0)
	{
		nStatus = 0x800F0000; // = Bad_NothingToDo
		if(nValueRank > 0)
		{
			nStatus = 0x00000000; // = Good
			DINT nIndex = 0;
			STRING sHelp[nBRBUA_VALUE_TEXT_CHAR_MAX];
			if(nValueRank > (DINT)MAX_ELEMENTS_ARRAYDIMENSION)
			{
				nValueRank = MAX_ELEMENTS_ARRAYDIMENSION;
			}
			for(nIndex=0; nIndex<=nValueRank-1; nIndex++)
			{
				UDINT* pDim = ((UDINT*)pArrayDimension) + nIndex;
				BrbUdintToAscii(*pDim, sHelp);
				BrbStringCat(pText, sHelp, nTextSize);
				BrbStringCat(pText, ";", nTextSize);
			}
			BrbStringTrimRight(pText, ";");
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

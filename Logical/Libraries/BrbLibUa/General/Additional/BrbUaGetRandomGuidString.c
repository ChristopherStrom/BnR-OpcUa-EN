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

/* Erzeugt einen zufälligen GuidString im Format '01234567-0123-0123-0123-0123456789AB' */
plcdword BrbUaGetRandomGuidString(BrUaGuidString* pGuidString, unsigned long nGuidStringSize, plcbit bWithSeparator)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pGuidString != 0)
	{
		nStatus = 0x00000000; // = Good
		STRING sSelection[64];
		BrbStringCopy(sSelection, "0123456789abcdef", sizeof(sSelection));
		STRING sGuidStringElement[13];
		BrbGetRandomStringExt(sGuidStringElement, sizeof(sGuidStringElement), 8, sSelection);
		BrbStringCopy((STRING*)pGuidString, sGuidStringElement, nGuidStringSize);
		if(bWithSeparator == 1)
		{
			BrbStringCat((STRING*)pGuidString, "-", nGuidStringSize);
		}
		BrbGetRandomStringExt(sGuidStringElement, sizeof(sGuidStringElement), 4, sSelection);
		BrbStringCat((STRING*)pGuidString, sGuidStringElement, nGuidStringSize);
		if(bWithSeparator == 1)
		{
			BrbStringCat((STRING*)pGuidString, "-", nGuidStringSize);
		}
		BrbGetRandomStringExt(sGuidStringElement, sizeof(sGuidStringElement), 4, sSelection);
		BrbStringCat((STRING*)pGuidString, sGuidStringElement, nGuidStringSize);
		if(bWithSeparator == 1)
		{
			BrbStringCat((STRING*)pGuidString, "-", nGuidStringSize);
		}
		BrbGetRandomStringExt(sGuidStringElement, sizeof(sGuidStringElement), 4, sSelection);
		BrbStringCat((STRING*)pGuidString, sGuidStringElement, nGuidStringSize);
		if(bWithSeparator == 1)
		{
			BrbStringCat((STRING*)pGuidString, "-", nGuidStringSize);
		}
		BrbGetRandomStringExt(sGuidStringElement, sizeof(sGuidStringElement), 12, sSelection);
		BrbStringCat((STRING*)pGuidString, sGuidStringElement, nGuidStringSize);

	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

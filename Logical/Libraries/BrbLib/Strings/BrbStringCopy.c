#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLib.h"
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Sicheres Kopieren eines Strings */
unsigned long BrbStringCopy(plcstring* pDest, plcstring* pSrc, unsigned long nDestSize)
{
	UDINT nTotalLen = 0;
	if(pDest != 0 && pSrc != 0 && nDestSize > 0)
	{
		// Quellstring kopieren
		UDINT nCopyLen = nTotalLen = strlen(pSrc);
		UDINT nDestLen = nDestSize-1;
		if(nCopyLen > nDestLen)
		{
			nCopyLen = nDestLen;
		}
		memcpy(pDest, pSrc, nCopyLen);
		// Zielstring mit 0 auffüllen (gleichzeitig wird auf jeden Fall der Null-Terminator gesetzt)
		memset((USINT*)pDest+nCopyLen, 0, nDestSize-nCopyLen);
	}
	return nTotalLen;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

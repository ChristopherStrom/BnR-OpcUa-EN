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

/* Sicheres Anh�ngen an einen String */
unsigned long BrbStringCat(plcstring* pDest, plcstring* pSrc, unsigned long nDestSize)
{
	UDINT nTotalLen = 0;
	if(pDest != 0 && pSrc != 0 && nDestSize > 0)
	{
		// Quellstring anh�ngen
		UDINT nDestLen = strlen(pDest);
		UDINT nSrcLen = strlen(pSrc);
		nTotalLen = nDestLen + nSrcLen;
		UDINT nSrcLenMax = nDestSize-nDestLen-1;
		if(nSrcLen > nSrcLenMax)
		{
			nSrcLen = nSrcLenMax;
		}
		memcpy(pDest+nDestLen, pSrc, nSrcLen);
		// Zielstring mit 0 auff�llen (gleichzeitig wird auf jeden Fall der Null-Terminator gesetzt)
		memset((USINT*)pDest+nDestLen+nSrcLen, 0, nDestSize-nDestLen-nSrcLen);
	}
	return nTotalLen;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)


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

/* Wiederholt eine Zeichenfolge bis zu einer angegebenen Zeichenanzahl */
unsigned long BrbStringRepeat(plcstring* pText, unsigned long nTextSize, plcstring* pRepeat, unsigned long nLen)
{
	UDINT nCharCount = 0;
	UDINT nTextOffset = strlen(pText);
	UDINT nRepeatLen = strlen(pRepeat);
	// L�nge limitieren
	if(nLen >= nTextSize)
	{
		nLen = nTextSize-1;
	}
	// Gesamten Wiederholtext wiederholend anh�ngen
	while(nTextOffset+nRepeatLen <= nLen)
	{
		BrbStringAppend(pText, pRepeat, &nTextOffset);
		nCharCount += nRepeatLen;
	}
	// Restliche Zeichen auff�llen
	DINT nCharCountLeft = (DINT)nLen - (DINT)nTextOffset;
	if(nCharCountLeft > 0)
	{
		UDINT nRepeatCharIndex = 0;
		for(nRepeatCharIndex=0; nRepeatCharIndex<(UDINT)nCharCountLeft; nRepeatCharIndex++)
		{
			*(pText + nTextOffset) = *(pRepeat + nRepeatCharIndex);
			nTextOffset++;
			nCharCount++;
		}
		*(pText + nTextOffset) = 0; // String-Abschluss
	}
	return nCharCount;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

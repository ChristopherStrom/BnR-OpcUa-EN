
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
unsigned long BrbWcStringRepeat(plcwstring* pText, unsigned long nTextSize, plcwstring* pRepeat, unsigned long nLen)
{
	UDINT nCharCount = 0;
	UDINT nTextOffset = brwcslen(pText);
	UDINT nRepeatLen = brwcslen(pRepeat);
	// Länge limitieren
	if(nLen * 2 >= nTextSize)
	{
		nLen = (nTextSize-2)/2;
	}
	// Gesamten Wiederholtext wiederholend anhängen
	while(nTextOffset+nRepeatLen <= nLen)
	{
		BrbWcStringAppend(pText, pRepeat, &nTextOffset);
		nCharCount += nRepeatLen;
	}
	// Restliche Zeichen auffüllen
	DINT nCharCountLeft = (DINT)nLen - (DINT)nTextOffset;
	if(nCharCountLeft > 0)
	{
		UDINT nRepeatCharIndex = 0;
		for(nRepeatCharIndex=0; nRepeatCharIndex<(UDINT)nCharCountLeft; nRepeatCharIndex++)
		{
			//*(pText + nTextOffset) = *(pRepeat + nRepeatCharIndex);
			memcpy(pText + nTextOffset, pRepeat + nRepeatCharIndex, 2);
			nTextOffset++;
			nCharCount++;
		}
		*(pText + nTextOffset) = 0; // String-Abschluss
	}
	return nCharCount;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbWcStringAppend.c
 * Author: niedermeierr
 * Created: May 02, 2016
 ********************************************************************
 * Implementation of library BrbLib
 ********************************************************************/

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

/* H�ngt eine Zeichenfolge an einen Text (Ersatz f�r brwcscat) */
unsigned long BrbWcStringAppend(plcwstring* pText, plcwstring* pTextAppend, unsigned long* pTextOffset)
{
	UDINT nAppendLen = brwcslen(pTextAppend);
	UDINT nAppendByteLen = nAppendLen * 2;
	memcpy(pText + *pTextOffset, pTextAppend, nAppendByteLen);
	*pTextOffset += nAppendLen;
	*(pText + *pTextOffset) = 0; // String-Abschluss
	return nAppendLen;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

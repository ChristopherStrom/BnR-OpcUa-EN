/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbStringAppend.c
 * Author: niedermeierr
 * Created: February 17, 2016
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

/* Hängt eine Zeichenfolge an einen Text (Ersatz für strcat) */
unsigned long BrbStringAppend(plcstring* pText, plcstring* pTextAppend, unsigned long* pTextOffset)
{
	UDINT nAppendLen = strlen(pTextAppend);
	memcpy(pText + *pTextOffset, pTextAppend, nAppendLen);
	*pTextOffset += nAppendLen;
	*(pText + *pTextOffset) = 0; // String-Abschluss
	return nAppendLen;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

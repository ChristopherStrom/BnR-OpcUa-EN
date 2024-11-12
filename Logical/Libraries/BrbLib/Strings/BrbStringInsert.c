/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbStringInsert.c
 * Author: niedermeierr
 * Created: July 05, 2013
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

/* Fügt eine Zeichenfolge in einen Text ein */
plcstring* BrbStringInsert(plcstring* pText, unsigned long nInsertIndex, plcstring* pInsert)
{
	STRING* pResult = 0;
	UDINT nTextLen = strlen(pText);
	UDINT nInsertLen = strlen(pInsert);
	UDINT nRestLen = nTextLen - nInsertIndex + 1;
	// Zeichen am Index nach hinten schieben
	memmove((pText + nInsertIndex + nInsertLen), (pText + nInsertIndex), nRestLen);
	memcpy((pText + nInsertIndex), pInsert, nInsertLen); // NOLINT(bugprone-not-null-terminated-result)
	pResult = pText + nInsertIndex + nInsertLen;
	return pResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbCheckFileEnding.c
 * Author: niedermeierr
 * Created: July 26, 2013
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

/* Prüft die Endung eines Datei-Namens und berichtigt sie gegebenenfalls */
plcbit BrbCheckFileEnding(plcstring* pFileName, plcstring* pEnding)
{
	// Prüfung der Parameter
	if(pFileName == 0)
	{
		return 0;
	}
	if(pEnding == 0)
	{
		return 0;
	}
	// Check
	BOOL bResult = 0;
	if(BrbStringEndsWith(pFileName, pEnding) == 0)
	{
		STRING* pFileNameDotAdr = BrbStringGetAdrOf(pFileName, ".", 0);
		if(pFileNameDotAdr != 0)
		{
			// Wegschneiden der vorhandenen Endung
			STRING sFileNameWithoutEnding[nBRB_FILE_NAME_CHAR_MAX];
			BrbStringGetSubTextByAdr(pFileName, pFileNameDotAdr, sFileNameWithoutEnding);
			strcpy(pFileName, sFileNameWithoutEnding); // NOLINT(clang-analyzer-security.insecureAPI.strcpy)
		}
		STRING* pEndingDotAdr = BrbStringGetAdrOf(pEnding, ".", 0);
		if(pEndingDotAdr != 0)
		{
			// Endung beinhaltet den Punkt schon
			strcat(pFileName, pEnding); // NOLINT(clang-analyzer-security.insecureAPI.strcpy)
		}
		else
		{
			// Endung beinhaltet den Punkt noch nicht
			strcat(pFileName, "."); // NOLINT(clang-analyzer-security.insecureAPI.strcpy)
			strcat(pFileName, pEnding); // NOLINT(clang-analyzer-security.insecureAPI.strcpy)
		}
		bResult = 1;
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

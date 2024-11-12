/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbCombinePath.c
 * Author: niedermeierr
 * Created: November 02, 2014
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

/* Fügt zwei Pfade oder einen Pfad und eine Datei-Namen zusammen */
unsigned short BrbCombinePath(plcstring* pPath, plcstring* pFilename, plcstring* pFilenameWithPath)
{
	// Prüfung der Parameter
	if(pPath == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	if(pFilename == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	if(pFilenameWithPath == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	// Check
	STRING sFileWithPath[nBRB_FILE_NAME_CHAR_MAX];
	memset(sFileWithPath, 0, sizeof(sFileWithPath));
	if(strlen(pPath) > 0)
	{
		BrbStringCat(sFileWithPath, pPath, sizeof(sFileWithPath));
		if(BrbStringEndsWith(pPath, "\\") == 0)
		{
			BrbStringCat(sFileWithPath, "\\", sizeof(sFileWithPath));
		}
	}
	BrbStringCat(sFileWithPath, pFilename, sizeof(sFileWithPath));
	strcpy(pFilenameWithPath, sFileWithPath); // NOLINT(clang-analyzer-security.insecureAPI.strcpy)
	return 0;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

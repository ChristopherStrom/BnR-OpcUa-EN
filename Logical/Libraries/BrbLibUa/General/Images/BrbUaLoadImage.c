#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLibUa.h"
#include <string.h>
#include <AnsiCFunc.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

// Eigene Enums und Typen
enum Steps_ENUM
{
	eSTEP_INIT,
	eSTEP_LOAD_FILE,
	eSTEP_LOAD_FILE_WAT,
};

/* Lädt ein Image */
void BrbUaLoadImage(struct BrbUaLoadImage* inst)
{
	switch(inst->eStep)
	{
		case eSTEP_INIT:
			// Fub initialisieren
			inst->nStatus =  65535;
			if(inst->pDevice != 0 && inst->pFile != 0 && inst->pImageData != 0 && inst->pImageLength != 0)
			{
				memset(&inst->fbBrbLoadFileBin, 0, sizeof(inst->fbBrbLoadFileBin));
				inst->eStep = eSTEP_LOAD_FILE;
			}
			else
			{
				inst->nStatus = eBRB_ERR_NULL_POINTER;
			}
			break;

		case eSTEP_LOAD_FILE:
			// Datei laden
			inst->nStatus  = eBRB_ERR_BUSY;
			inst->fbBrbLoadFileBin.pDevice = (STRING*)inst->pDevice;
			inst->fbBrbLoadFileBin.pFile = (STRING*)inst->pFile;
			inst->fbBrbLoadFileBin.pVar = (USINT*)inst->pImageData;
			inst->fbBrbLoadFileBin.nVarSize = inst->nImageDataSize;
			inst->eStep = eSTEP_LOAD_FILE_WAT;
			break;

		case eSTEP_LOAD_FILE_WAT:
			// Warten, bis Datei geladen ist
			BrbLoadFileBin(&inst->fbBrbLoadFileBin);
			if(inst->fbBrbLoadFileBin.nStatus == 0)
			{
				inst->nStatus = inst->fbBrbLoadFileBin.nStatus;
				*inst->pImageLength = (DINT)inst->fbBrbLoadFileBin.nValidBytes;
				inst->eStep = eSTEP_INIT;
			}
			else if(inst->fbBrbLoadFileBin.nStatus != 65535)
			{
				inst->nStatus = inst->fbBrbLoadFileBin.nStatus;
				*inst->pImageLength = 0;
				inst->eStep = eSTEP_INIT;
			}
			break;

	}
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

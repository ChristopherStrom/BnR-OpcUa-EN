/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbLoadVarBin.c
 * Author: niedermeierr
 * Created: June 11, 2013
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

// Eigene Enums und Typen
enum Steps_ENUM
{
	eSTEP_INIT,
	eSTEP_OPEN_FILE,
	eSTEP_TEST_SIZE,
	eSTEP_READ_FILE,
	eSTEP_CLOSE_FILE,
};

/* L�dt eine Bin�r-Datei mit Variablen-Werten */
void BrbLoadVarBin(struct BrbLoadVarBin* inst) // NOLINT(readability-function-cognitive-complexity)
{
	// Pr�fung der Parameter
	if(inst->pDevice == 0)
	{
		inst->nStatus = eBRB_ERR_NULL_POINTER;
		return;
	}
	if(inst->pFile == 0)
	{
		inst->nStatus = eBRB_ERR_NULL_POINTER;
		return;
	}

	UINT	nFuncStatus = 0;
	switch(inst->eStep)
	{
		case eSTEP_INIT:
			// Fub initialisieren
			inst->nStatus = eBRB_ERR_BUSY;
			inst->nStatusIntern = 0;
			memset(&inst->fbFileOpen, 0, sizeof(inst->fbFileOpen));
			memset(&inst->PvInfo, 0, sizeof(inst->PvInfo));
			memset(&inst->fbFileRead, 0, sizeof(inst->fbFileRead));
			memset(&inst->fbFileClose, 0, sizeof(inst->fbFileClose));
			inst->eStep = eSTEP_OPEN_FILE;
			break;

		case eSTEP_OPEN_FILE:
			// Datei �ffnen
			inst->nStatus = eBRB_ERR_BUSY;
			inst->fbFileOpen.enable = 1;
			inst->fbFileOpen.pDevice = (UDINT)inst->pDevice;
			inst->fbFileOpen.pFile = (UDINT)inst->pFile;
			FileOpen(&inst->fbFileOpen);
			if(inst->fbFileOpen.status == 0)
			{
				inst->eStep = eSTEP_TEST_SIZE;
			}
			else if(inst->fbFileOpen.status != eBRB_ERR_BUSY)
			{
				inst->nStatus = inst->fbFileOpen.status;
				inst->eStep = eSTEP_INIT;
			}
			break;

		case eSTEP_TEST_SIZE:
			// Pr�fen, ob die Dateigr��e zur Gr��e der Variable passt
			inst->nStatus = eBRB_ERR_BUSY;
			// Adresse der Variable holen
			nFuncStatus = PV_xgetadr((STRING*)inst->pVarName, &inst->PvInfo.nAdr, &inst->PvInfo.nLen);
			if(nFuncStatus == 0)
			{
				// Gr��e der Variable holen
				nFuncStatus = PV_ninfo((STRING*)inst->pVarName, &inst->PvInfo.nDataType, &inst->PvInfo.nLen, &inst->PvInfo.nDimension);
				if(nFuncStatus == 0)
				{
					if(inst->bAllowBiggerVar == 1)
					{
						if(inst->PvInfo.nLen >= inst->fbFileOpen.filelen)
						{
							inst->eStep = eSTEP_READ_FILE;
						}
						else
						{
							// Fehler merken
							inst->nStatusIntern = ERR_BUR_ILLLEN; // = Ung�ltige L�ngenangabe
							// Datei mu� auf jeden Fall geschlossen werden
							inst->eStep = eSTEP_CLOSE_FILE;
						}
					}
					else
					{
						if(inst->PvInfo.nLen == inst->fbFileOpen.filelen)
						{
							inst->eStep = eSTEP_READ_FILE;
						}
						else
						{
							// Fehler merken
							inst->nStatusIntern = ERR_BUR_ILLLEN; // = Ung�ltige L�ngenangabe
							// Datei mu� auf jeden Fall geschlossen werden
							inst->eStep = eSTEP_CLOSE_FILE;
						}
					}
				}
				else
				{
					// Fehler merken
					inst->nStatusIntern = nFuncStatus;
					// Datei mu� auf jeden Fall geschlossen werden
					inst->eStep = eSTEP_CLOSE_FILE;
				}
			}
			else
			{
				// Fehler merken
				inst->nStatusIntern = nFuncStatus;
				// Datei mu� auf jeden Fall geschlossen werden
				inst->eStep = eSTEP_CLOSE_FILE;
			}
			break;

		case eSTEP_READ_FILE:
			// Einlesen der Datei auf die Variablen-Adresse
			inst->nStatus = eBRB_ERR_BUSY;
			inst->fbFileRead.enable = 1;
			inst->fbFileRead.ident = inst->fbFileOpen.ident;
			inst->fbFileRead.offset = 0;
			inst->fbFileRead.pDest = inst->PvInfo.nAdr;
			inst->fbFileRead.len = inst->PvInfo.nLen;
			FileRead(&inst->fbFileRead);
			if(inst->fbFileRead.status == 0)
			{
				inst->eStep = eSTEP_CLOSE_FILE;
			}
			else if(inst->fbFileRead.status != eBRB_ERR_BUSY)
			{
				// Fehler merken
				inst->nStatusIntern = inst->fbFileRead.status;
				// Datei mu� auf jeden Fall geschlossen werden
				inst->eStep = eSTEP_CLOSE_FILE;
			}
			break;

		case eSTEP_CLOSE_FILE:
			// Datei schliessen
			inst->nStatus = eBRB_ERR_BUSY;
			inst->fbFileClose.enable = 1;
			inst->fbFileClose.ident = inst->fbFileOpen.ident;
			FileClose(&inst->fbFileClose);
			if(inst->fbFileClose.status == 0)
			{
				// Pr�fen, ob vorher schon ein Fehler aufgetreten ist
				if(inst->nStatusIntern > 0)
				{
					inst->nStatus = inst->nStatusIntern;
					inst->eStep = eSTEP_INIT;
				}
				else
				{
					inst->nStatus = 0;
					inst->eStep = eSTEP_INIT;
				}
			}
			else if(inst->fbFileClose.status != eBRB_ERR_BUSY)
			{
				// Pr�fen, ob vorher schon ein Fehler aufgetreten ist
				if(inst->nStatusIntern > 0)
				{
					inst->nStatus = inst->nStatusIntern;
					inst->eStep = eSTEP_INIT;
				}
				else
				{
					inst->nStatus = inst->fbFileClose.status;
					inst->eStep = eSTEP_INIT;
				}
			}
			break;

	}
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

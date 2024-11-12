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
	eSTEP_FREE_EVENTS,
	eSTEP_FINISHED,
};

/* Exilisiert eine Client-Instanz */
void BrbUaRunServerExit(struct BrbUaRunServerExit* inst)
{
	switch(inst->eStep)
	{
		case eSTEP_INIT:
			// Fub initialisieren
			inst->nStatus =  eBRB_ERR_BUSY;
			// Client-Pointer prüfen
			if(inst->pRunServer != 0)
			{
				inst->pRunServer->State.eState = eBRB_RSSTATE_EXITING;
				inst->pRunServer->State.nErroId = 0x00000000;
				strcpy(inst->pRunServer->State.sErrorText, "");
				inst->nEventIndex = 0;
				inst->eStep = eSTEP_FREE_EVENTS;
			}
			else
			{
				inst->nStatus = eBRB_ERR_NULL_POINTER;
				inst->eStep = eSTEP_INIT;
			}
			break;

		case eSTEP_FREE_EVENTS:
			// Speicher für alle Events freigeben
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->pRunServer->Events.nEventCount > 0 && inst->pRunServer->Events.pEvents != 0 && inst->pRunServer->Events.nMemLen > 0)
			{
				inst->nFreeStatus = TMP_free(inst->pRunServer->Events.nMemLen, (void*)inst->pRunServer->Events.pEvents);
				if(inst->nFreeStatus == 0)
				{
					inst->pRunServer->Events.nEventCount = 0;
					inst->pRunServer->Events.pEvents = 0;
					inst->pRunServer->Events.nMemLen = 0;
					inst->eStep = eSTEP_FINISHED;
				}
				else
				{
					// Fehler
					inst->nStatus = inst->nFreeStatus;
					inst->pRunServer->State.nErroId = inst->nStatus;
					strcpy(inst->pRunServer->State.sErrorText, "Exit error on freeing memory for events");
					inst->pRunServer->State.eState = eBRB_RSSTATE_EXIT_ERROR;
					inst->eStep = eSTEP_INIT;
				}
			}
			else
			{
				// Keine Events angegeben
				inst->eStep = eSTEP_FINISHED;
			}
			break;

		case eSTEP_FINISHED:
			inst->nStatus = 0;
			inst->pRunServer->State.eState = eBRB_RSSTATE_EXIT_DONE;
			inst->eStep = eSTEP_INIT;
			break;

	}

}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

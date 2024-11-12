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
	eSTEP_FIRE,
	eSTEP_FIRE_WAIT,
};

/* Liest eine WriteBlock vom Server */
void BrbUaRsFireEvent(struct BrbUaRsFireEvent* inst)
{
	switch(inst->eStep)
	{
		case eSTEP_INIT:
			// Fub initialisieren
			inst->nStatus =  eBRB_ERR_BUSY;
			inst->nErrorId = 0x00000000; // Good
			BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
			memset(&inst->fbUaSrv_FireEvent, 0, sizeof(inst->fbUaSrv_FireEvent));
			inst->bInit = 0;
			// Parameter prüfen
			if(inst->pRunServer != 0)
			{
				if(inst->pRunServer->State.eState == eBRB_RSSTATE_RUNNING)
				{
					if(inst->pRunServer->Events.nEventCount > 0 && inst->pRunServer->Events.pEvents != 0)
					{
						if(inst->nEventIndex < inst->pRunServer->Events.nEventCount)
						{
							inst->bInit = 1;
							inst->eStep = eSTEP_FIRE;
						}
						else
						{
							inst->nStatus = eBRB_ERR_UA_INVALID_INDEX;
						}
					}
					else
					{
						inst->nStatus = eBRB_ERR_UA_NO_ELEMENTS;
					}
				}
				else
				{
					inst->nStatus = eBRB_ERR_UA_NOT_RUNNING;
				}
			}
			else
			{
				inst->nStatus = eBRB_ERR_NULL_POINTER;
			}
			break;

		case eSTEP_FIRE:
			// Event feuern
			inst->nStatus  = eBRB_ERR_BUSY;
			inst->bInit = 0;
			{
				BrbUaRsEventIntern_TYP* pEvent = (((BrbUaRsEventIntern_TYP*)inst->pRunServer->Events.pEvents)  + inst->nEventIndex);
				inst->fbUaSrv_FireEvent.Execute = 1;
				memcpy(&inst->fbUaSrv_FireEvent.EventType, &pEvent->TypeNodeId, sizeof(UANodeID));
				inst->fbUaSrv_FireEvent.EventFieldCount = pEvent->nFieldCount;
				inst->fbUaSrv_FireEvent.EventFields = (void*)pEvent->pFields;
			}
			inst->eStep = eSTEP_FIRE_WAIT;
			break;
		
		case eSTEP_FIRE_WAIT:
			// Warten, bis Block gelesen wurde
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->fbUaSrv_FireEvent.Done == 1)
			{
				inst->fbUaSrv_FireEvent.Execute = 0;
				inst->nStatus  = eBRB_ERR_OK;
				inst->nErrorId = inst->fbUaSrv_FireEvent.ErrorID;
				BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
				inst->nFireCount++;
				inst->eStep = eSTEP_INIT;
			}
			else if(inst->fbUaSrv_FireEvent.Error == 1)
			{
				inst->fbUaSrv_FireEvent.Execute = 0;
				inst->nStatus  = eBRB_ERR_UA_ERROR;
				inst->nErrorId = inst->fbUaSrv_FireEvent.ErrorID;
				if(inst->nErrorId == 0)
				{
					// Fehler trat bei einem Field auf
					BrbUaRsEventIntern_TYP* pEvent = (((BrbUaRsEventIntern_TYP*)inst->pRunServer->Events.pEvents)  + inst->nEventIndex);
					UINT nEventFieldIndex = 0;
					for(nEventFieldIndex=0; nEventFieldIndex<pEvent->nFieldCount; nEventFieldIndex++)
					{
						UaSrv_FireEventFieldType* pEventField = ((UaSrv_FireEventFieldType*)pEvent->pFields) + nEventFieldIndex;
						if(pEventField->ErrorID != 0)
						{
							inst->nErrorId = pEventField->ErrorID;
							break;
						}
					}
				}
				BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
				inst->eStep = eSTEP_INIT;
			}
			break;

	}

	// Aufruf aller FB's
	UaSrv_FireEvent(&inst->fbUaSrv_FireEvent);
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

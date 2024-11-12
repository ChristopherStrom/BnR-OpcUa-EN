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

/* Gibt ein ermitteltes Event zurück */
unsigned short BrbUaRsGetEvent(struct BrbUaRunServer_TYP* pRunServer, unsigned short nEventIndex, struct BrbUaRsEvent_TYP* pEvent, struct BrbUaRsEventIntern_TYP* pEventIntern)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunServer != 0 && pEvent != 0)
	{
		memset(pEvent, 0, sizeof(BrbUaRsEvent_TYP));
		nStatus = eBRB_ERR_UA_NO_ELEMENTS;
		if(pRunServer->Events.nEventCount > 0 && pRunServer->Events.pEvents != 0)
		{
			nStatus = eBRB_ERR_UA_INVALID_INDEX;
			if(nEventIndex < pRunServer->Events.nEventCount)
			{
				nStatus = eBRB_ERR_OK;
				BrbUaRsEventIntern_TYP* pEventInternOri = ((BrbUaRsEventIntern_TYP*)pRunServer->Events.pEvents) + nEventIndex;
				pEvent->nFieldCount = pEventInternOri->nFieldCount;
				memcpy(&pEvent->TypeNodeId, &pEventInternOri->TypeNodeId, sizeof(UANodeID));
				if(pEventIntern != 0)
				{
					memcpy(pEventIntern, pEventInternOri, sizeof(BrbUaRsEventIntern_TYP));
				}
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

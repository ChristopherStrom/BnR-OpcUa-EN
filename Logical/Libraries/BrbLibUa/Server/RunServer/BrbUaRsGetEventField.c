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

/* Gibt ein ermitteltes Field zurück */
unsigned short BrbUaRsGetEventField(struct BrbUaRunServer_TYP* pRunServer, unsigned short nEventIndex, unsigned short nEventFieldIndex, struct UaSrv_FireEventFieldType* pEventField)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunServer != 0 && pEventField != 0)
	{
		memset(pEventField, 0, sizeof(UaSrv_FireEventFieldType));
		nStatus = eBRB_ERR_UA_NO_ELEMENTS;
		if(pRunServer->Events.nEventCount > 0 && pRunServer->Events.pEvents != 0)
		{
			nStatus = eBRB_ERR_UA_INVALID_INDEX;
			if(nEventIndex < pRunServer->Events.nEventCount)
			{
				nStatus = eBRB_ERR_UA_NO_ELEMENTS;
				BrbUaRsEventIntern_TYP* pEventIntern = ((BrbUaRsEventIntern_TYP*)pRunServer->Events.pEvents) + nEventIndex;
				if(pEventIntern->nFieldCount > 0 && pEventIntern->pFields)
				{
					nStatus = eBRB_ERR_UA_INVALID_INDEX;
					if(nEventFieldIndex < pEventIntern->nFieldCount)
					{
						nStatus = eBRB_ERR_OK;
						UaSrv_FireEventFieldType* pEventFieldOri = ((UaSrv_FireEventFieldType*)pEventIntern->pFields) + nEventFieldIndex;
						memcpy(pEventField, pEventFieldOri, sizeof(UaSrv_FireEventFieldType));
					}
				}
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

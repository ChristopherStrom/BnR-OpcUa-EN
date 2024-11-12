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

/* Zeigt die Inhalte des internen Speichers */
unsigned short BrbUaRsMonitor(struct BrbUaRunServer_TYP* pRunServer, struct BrbUaRsMonitor_TYP* pMonitor)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunServer != 0 && pMonitor != 0)
	{
		nStatus = eBRB_ERR_NOT_ENABLED;
		if(pMonitor->bEnable == 1)
		{
			nStatus = eBRB_ERR_OK;
			brsmemset((UDINT)&pMonitor->Namespace.Namespace, 0, sizeof(pMonitor->Namespace.Namespace));
			BrbUaRsGetNamespace(pRunServer, pMonitor->Namespace.nDatObjNamespaceIndex, &pMonitor->Namespace.Namespace);

			brsmemset((UDINT)&pMonitor->Event.Event, 0, sizeof(pMonitor->Event.Event));
			brsmemset((UDINT)&pMonitor->Event.EventIntern, 0, sizeof(pMonitor->Event.EventIntern));
			pMonitor->Event.nMonitorStatus = BrbUaRsGetEvent(pRunServer, pMonitor->Event.nEventIndex, &pMonitor->Event.Event, &pMonitor->Event.EventIntern);
			
			brsmemset((UDINT)&pMonitor->EventField.Field, 0, sizeof(pMonitor->EventField.Field));
			pMonitor->EventField.nMonitorStatus = BrbUaRsGetEventField(pRunServer, pMonitor->EventField.nEventIndex, pMonitor->EventField.nEventFieldIndex, &pMonitor->EventField.Field);
		}
		else
		{
			brsmemset((UDINT)&pMonitor->Namespace.Namespace, 0, sizeof(pMonitor->Namespace.Namespace));
			pMonitor->Event.nMonitorStatus = eBRB_ERR_NOT_ENABLED;
			brsmemset((UDINT)&pMonitor->Event.Event, 0, sizeof(pMonitor->Event.Event));
			brsmemset((UDINT)&pMonitor->Event.EventIntern, 0, sizeof(pMonitor->Event.EventIntern));
			pMonitor->EventField.nMonitorStatus = eBRB_ERR_NOT_ENABLED;
			brsmemset((UDINT)&pMonitor->EventField.Field, 0, sizeof(pMonitor->EventField.Field));
		}
		pMonitor->nMonitorStatus = nStatus;
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

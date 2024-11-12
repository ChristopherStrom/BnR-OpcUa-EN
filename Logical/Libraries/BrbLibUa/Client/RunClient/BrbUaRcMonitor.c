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
unsigned short BrbUaRcMonitor(struct BrbUaRunClient_TYP* pRunClient, struct BrbUaRcMonitor_TYP* pMonitor)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunClient != 0 && pMonitor != 0)
	{
		nStatus = eBRB_ERR_NOT_ENABLED;
		if(pMonitor->bEnable == 1)
		{
			nStatus = eBRB_ERR_OK;
			brsmemset((UDINT)&pMonitor->Namespace.Namespace , 0, sizeof(pMonitor->Namespace.Namespace));
			BrbUaRcGetSrvNamespace(pRunClient, pMonitor->Namespace.nDatObjNamespaceIndex, &pMonitor->Namespace.Namespace);

			brsmemset((UDINT)&pMonitor->NodeHandle.NodeHandle , 0, sizeof(pMonitor->NodeHandle.NodeHandle));
			pMonitor->NodeHandle.nMonitorStatus = BrbUaRcGetNodeHandle(pRunClient, pMonitor->NodeHandle.nNodeHandleIndex, &pMonitor->NodeHandle.NodeHandle);
			
			brsmemset((UDINT)&pMonitor->ReadBlock.ReadBlock, 0, sizeof(pMonitor->ReadBlock.ReadBlock));
			brsmemset((UDINT)&pMonitor->ReadBlock.ReadBlockIntern, 0, sizeof(pMonitor->ReadBlock.ReadBlockIntern));
			pMonitor->ReadBlock.nMonitorStatus = BrbUaRcGetReadBlock(pRunClient, pMonitor->ReadBlock.nReadBlockIndex, &pMonitor->ReadBlock.ReadBlock, &pMonitor->ReadBlock.ReadBlockIntern);

			brsmemset((UDINT)&pMonitor->ReadItem.ReadItem, 0, sizeof(pMonitor->ReadItem.ReadItem));
			pMonitor->ReadItem.nMonitorStatus = BrbUaRcGetReadItem(pRunClient, pMonitor->ReadItem.nReadBlockIndex, pMonitor->ReadItem.nReadItemIndex, &pMonitor->ReadItem.ReadItem);

			brsmemset((UDINT)&pMonitor->WriteBlock.WriteBlock, 0, sizeof(pMonitor->WriteBlock.WriteBlock));
			brsmemset((UDINT)&pMonitor->WriteBlock.WriteBlockIntern, 0, sizeof(pMonitor->WriteBlock.WriteBlockIntern));
			pMonitor->WriteBlock.nMonitorStatus = BrbUaRcGetWriteBlock(pRunClient, pMonitor->WriteBlock.nWriteBlockIndex, &pMonitor->WriteBlock.WriteBlock, &pMonitor->WriteBlock.WriteBlockIntern);

			brsmemset((UDINT)&pMonitor->WriteItem.WriteItem, 0, sizeof(pMonitor->WriteItem.WriteItem));
			pMonitor->WriteItem.nMonitorStatus = BrbUaRcGetWriteItem(pRunClient, pMonitor->WriteItem.nWriteBlockIndex, pMonitor->WriteItem.nWriteItemIndex, &pMonitor->WriteItem.WriteItem);

			brsmemset((UDINT)&pMonitor->Method.Method, 0, sizeof(pMonitor->Method.Method));
			pMonitor->Method.nMonitorStatus = BrbUaRcGetMethod(pRunClient, pMonitor->Method.nMethodIndex, &pMonitor->Method.Method, & pMonitor->Method.MethodIntern);

			brsmemset((UDINT)&pMonitor->Argument.Argument, 0, sizeof(pMonitor->Argument.Argument));
			pMonitor->Argument.nMonitorStatus = BrbUaRcGetArgument(pRunClient, pMonitor->Argument.nMethodIndex, pMonitor->Argument.bOutput, pMonitor->Argument.nArgumentIndex, &pMonitor->Argument.Argument);
			
			brsmemset((UDINT)&pMonitor->Subscription.Subscription, 0, sizeof(pMonitor->Subscription.Subscription));
			brsmemset((UDINT)&pMonitor->Subscription.SubscriptionIntern, 0, sizeof(pMonitor->Subscription.SubscriptionIntern));
			pMonitor->Subscription.nMonitorStatus = BrbUaRcGetSubscription(pRunClient, pMonitor->Subscription.nSubscriptionIndex, &pMonitor->Subscription.Subscription, &pMonitor->Subscription.SubscriptionIntern);

			brsmemset((UDINT)&pMonitor->MonitoredItem.MonitoredItem, 0, sizeof(pMonitor->MonitoredItem.MonitoredItem));
			pMonitor->MonitoredItem.nMonitorStatus = BrbUaRcGetMonitoredItem(pRunClient, pMonitor->MonitoredItem.nSubscriptionIndex, pMonitor->MonitoredItem.nMonitoredItemIndex, &pMonitor->MonitoredItem.MonitoredItem);

			brsmemset((UDINT)&pMonitor->EventItem.EventItem, 0, sizeof(pMonitor->EventItem.EventItem));
			brsmemset((UDINT)&pMonitor->EventItem.EventItemIntern, 0, sizeof(pMonitor->EventItem.EventItemIntern));
			pMonitor->EventItem.nMonitorStatus = BrbUaRcGetEventItem(pRunClient, pMonitor->EventItem.nSubscriptionIndex, pMonitor->EventItem.nEventItemIndex, &pMonitor->EventItem.EventItem, &pMonitor->EventItem.EventItemIntern);

			brsmemset((UDINT)&pMonitor->EventField.EventField, 0, sizeof(pMonitor->EventField.EventField));
			pMonitor->EventField.nMonitorStatus = BrbUaRcGetEventField(pRunClient, pMonitor->EventField.nSubscriptionIndex, pMonitor->EventField.nEventItemIndex, pMonitor->EventField.nEventFieldIndex, &pMonitor->EventField.EventField);
		}
		else
		{
			brsmemset((UDINT)&pMonitor->Namespace.Namespace , 0, sizeof(pMonitor->Namespace.Namespace));
			pMonitor->NodeHandle.nMonitorStatus = eBRB_ERR_NOT_ENABLED;
			brsmemset((UDINT)&pMonitor->NodeHandle.NodeHandle , 0, sizeof(pMonitor->NodeHandle.NodeHandle));
			pMonitor->ReadBlock.nMonitorStatus = eBRB_ERR_NOT_ENABLED;
			brsmemset((UDINT)&pMonitor->ReadBlock.ReadBlock, 0, sizeof(pMonitor->ReadBlock.ReadBlock));
			brsmemset((UDINT)&pMonitor->ReadBlock.ReadBlockIntern, 0, sizeof(pMonitor->ReadBlock.ReadBlockIntern));
			pMonitor->ReadItem.nMonitorStatus = eBRB_ERR_NOT_ENABLED;
			brsmemset((UDINT)&pMonitor->ReadItem.ReadItem, 0, sizeof(pMonitor->ReadItem.ReadItem));
			pMonitor->WriteBlock.nMonitorStatus = eBRB_ERR_NOT_ENABLED;
			brsmemset((UDINT)&pMonitor->WriteBlock.WriteBlock, 0, sizeof(pMonitor->WriteBlock.WriteBlock));
			brsmemset((UDINT)&pMonitor->WriteBlock.WriteBlockIntern, 0, sizeof(pMonitor->WriteBlock.WriteBlockIntern));
			pMonitor->WriteItem.nMonitorStatus = eBRB_ERR_NOT_ENABLED;
			brsmemset((UDINT)&pMonitor->WriteItem.WriteItem, 0, sizeof(pMonitor->WriteItem.WriteItem));
			pMonitor->Method.nMonitorStatus = eBRB_ERR_NOT_ENABLED;
			brsmemset((UDINT)&pMonitor->Method.Method, 0, sizeof(pMonitor->Method.Method));
			pMonitor->Argument.nMonitorStatus = eBRB_ERR_NOT_ENABLED;
			brsmemset((UDINT)&pMonitor->Argument.Argument, 0, sizeof(pMonitor->Argument.Argument));
			pMonitor->Subscription.nMonitorStatus = eBRB_ERR_NOT_ENABLED;
			brsmemset((UDINT)&pMonitor->Subscription.Subscription, 0, sizeof(pMonitor->Subscription.Subscription));
			brsmemset((UDINT)&pMonitor->Subscription.SubscriptionIntern, 0, sizeof(pMonitor->Subscription.SubscriptionIntern));
			pMonitor->MonitoredItem.nMonitorStatus = eBRB_ERR_NOT_ENABLED;
			brsmemset((UDINT)&pMonitor->MonitoredItem.MonitoredItem, 0, sizeof(pMonitor->MonitoredItem.MonitoredItem));
			pMonitor->EventItem.nMonitorStatus = eBRB_ERR_NOT_ENABLED;
			brsmemset((UDINT)&pMonitor->EventItem.EventItem, 0, sizeof(pMonitor->EventItem.EventItem));
			brsmemset((UDINT)&pMonitor->EventItem.EventItemIntern, 0, sizeof(pMonitor->EventItem.EventItemIntern));
			pMonitor->EventField.nMonitorStatus = eBRB_ERR_NOT_ENABLED;
			brsmemset((UDINT)&pMonitor->EventField.EventField, 0, sizeof(pMonitor->EventField.EventField));
		}
		pMonitor->nMonitorStatus = nStatus;
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

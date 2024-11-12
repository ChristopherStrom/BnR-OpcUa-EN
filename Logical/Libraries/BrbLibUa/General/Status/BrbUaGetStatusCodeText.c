#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLibUa.h"
#include <AnsiCFunc.h>
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Gibt den symbolischen Text für einen Ua-Status-Code zurück */
plcdword BrbUaGetStatusCodeText(unsigned long nStatusCode, plcstring* pStatusText, unsigned long nStatusTextSize)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pStatusText != 0)
	{
		nStatus = 0x00000000; // = Good
		memset(pStatusText, 0, nStatusTextSize);
		BrbUdintToHex(nStatusCode, pStatusText, nStatusTextSize, 1);
		switch(nStatusCode)
		{
			case 0:
				BrbStringCat(pStatusText, " = Good", nStatusTextSize);
				break;
			case 0x002D0000:
				BrbStringCat(pStatusText, " = Good_SubscriptionTransferred", nStatusTextSize);
				break;
			case 0x002E0000:
				BrbStringCat(pStatusText, " = Good_CompletesAsynchronously", nStatusTextSize);
				break;
			case 0x002F0000:
				BrbStringCat(pStatusText, " = Good_Overload", nStatusTextSize);
				break;
			case 0x00300000:
				BrbStringCat(pStatusText, " = Good_Clamped", nStatusTextSize);
				break;
			case 0x00960000:
				BrbStringCat(pStatusText, " = Good_LocalOverride", nStatusTextSize);
				break;
			case 0x00A20000 :
				BrbStringCat(pStatusText, " = Good_EntryInserted", nStatusTextSize);
				break;
			case 0x00A30000:
				BrbStringCat(pStatusText, " = Good_EntryReplaced", nStatusTextSize);
				break;
			case 0x00A50000:
				BrbStringCat(pStatusText, " = Good_NoData", nStatusTextSize);
				break;
			case 0x00A60000:
				BrbStringCat(pStatusText, " = Good_MoreData", nStatusTextSize);
				break;
			case 0x00A70000:
				BrbStringCat(pStatusText, " = Good_CommunicationEvent", nStatusTextSize);
				break;
			case 0x00A80000:
				BrbStringCat(pStatusText, " = Good_ShutdownEvent", nStatusTextSize);
				break;
			case 0x00A90000:
				BrbStringCat(pStatusText, " = Good_CallAgain", nStatusTextSize);
				break;
			case 0x00AA0000:
				BrbStringCat(pStatusText, " = Good_NonCriticalTimeout", nStatusTextSize);
				break;
			case 0x00BA0000:
				BrbStringCat(pStatusText, " = Good_ResultsMayBeIncomplete", nStatusTextSize);
				break;
			case 0x00D90000:
				BrbStringCat(pStatusText, " = Good_DataIgnored", nStatusTextSize);
				break;
		
		
			case 0x406C0000:
				BrbStringCat(pStatusText, " = Uncertain_ReferenceOutOfServer", nStatusTextSize);
				break;
			case 0x408F0000:
				BrbStringCat(pStatusText, " = Uncertain_NoCommunicationLastUsableValue", nStatusTextSize);
				break;
			case 0x40900000:
				BrbStringCat(pStatusText, " = Uncertain_LastUsableValue", nStatusTextSize);
				break;
			case 0x40910000:
				BrbStringCat(pStatusText, " = Uncertain_SubstituteValue", nStatusTextSize);
				break;
			case 0x40920000:
				BrbStringCat(pStatusText, " = Uncertain_InitialValue", nStatusTextSize);
				break;
			case 0x40930000:
				BrbStringCat(pStatusText, " = Uncertain_SensorNotAccurate", nStatusTextSize);
				break;
			case 0x40940000:
				BrbStringCat(pStatusText, " = Uncertain_EngineeringUnitsExceeded", nStatusTextSize);
				break;
			case 0x40950000:
				BrbStringCat(pStatusText, " = Uncertain_SubNormal", nStatusTextSize);
				break;
			case 0x40A40000:
				BrbStringCat(pStatusText, " = Uncertain_DataSubNormal", nStatusTextSize);
				break;
			case 0x40BC0000:
				BrbStringCat(pStatusText, " = Uncertain_ReferenceNotDeleted", nStatusTextSize);
				break;
			case 0x40C00000:
				BrbStringCat(pStatusText, " = Uncertain_NotAllNodesAvailable", nStatusTextSize);
				break;

		
			case 0x80000000:
				BrbStringCat(pStatusText, " = Bad", nStatusTextSize);
				break;
			case 0x80010000:
				BrbStringCat(pStatusText, " = Bad_UnexpectedError", nStatusTextSize);
				break;
			case 0x80020000:
				BrbStringCat(pStatusText, " = Bad_InternalError", nStatusTextSize);
				break;
			case 0x80030000:
				BrbStringCat(pStatusText, " = Bad_OutOfMemory", nStatusTextSize);
				break;
			case 0x80040000:
				BrbStringCat(pStatusText, " = Bad_ResourceUnavailable", nStatusTextSize);
				break;
			case 0x80050000:
				BrbStringCat(pStatusText, " = Bad_CommunicationError", nStatusTextSize);
				break;
			case 0x80060000:
				BrbStringCat(pStatusText, " = Bad_EncodingError", nStatusTextSize);
				break;
			case 0x80070000:
				BrbStringCat(pStatusText, " = Bad_DecodingError", nStatusTextSize);
				break;
			case 0x80080000:
				BrbStringCat(pStatusText, " = Bad_EncodingLimitsExceeded", nStatusTextSize);
				break;
			case 0x80090000:
				BrbStringCat(pStatusText, " = Bad_UnknownResponse", nStatusTextSize);
				break;
			case 0x800A0000:
				BrbStringCat(pStatusText, " = Bad_Timeout", nStatusTextSize);
				break;
			case 0x800B0000:
				BrbStringCat(pStatusText, " = Bad_ServiceUnsupported", nStatusTextSize);
				break;
			case 0x800C0000:
				BrbStringCat(pStatusText, " = Bad_Shutdown", nStatusTextSize);
				break;
			case 0x800D0000:
				BrbStringCat(pStatusText, " = Bad_ServerNotConnected", nStatusTextSize);
				break;
			case 0x800E0000:
				BrbStringCat(pStatusText, " = Bad_ServerHalted", nStatusTextSize);
				break;
			case 0x800F0000:
				BrbStringCat(pStatusText, " = Bad_NothingToDo", nStatusTextSize);
				break;
			case 0x80100000:
				BrbStringCat(pStatusText, " = Bad_TooManyOperations", nStatusTextSize);
				break;
			case 0x80110000:
				BrbStringCat(pStatusText, " = Bad_DataTypeIdUnknown", nStatusTextSize);
				break;
			case 0x80120000:
				BrbStringCat(pStatusText, " = Bad_CertificateInvalid", nStatusTextSize);
				break;
			case 0x80130000:
				BrbStringCat(pStatusText, " = Bad_SecurityChecksFailed", nStatusTextSize);
				break;
			case 0x80140000:
				BrbStringCat(pStatusText, " = Bad_CertificateTimeInvalid", nStatusTextSize);
				break;
			case 0x80150000:
				BrbStringCat(pStatusText, " = Bad_CertificateIssuerTimeInvalid", nStatusTextSize);
				break;
			case 0x80160000:
				BrbStringCat(pStatusText, " = Bad_CertificateHostNameInvalid", nStatusTextSize);
				break;
			case 0x80170000:
				BrbStringCat(pStatusText, " = Bad_CertificateUriInvalid", nStatusTextSize);
				break;
			case 0x80180000:
				BrbStringCat(pStatusText, " = Bad_CertificateUseNotAllowed", nStatusTextSize);
				break;
			case 0x80190000:
				BrbStringCat(pStatusText, " = Bad_CertificateIssuerUseNotAllowed", nStatusTextSize);
				break;
			case 0x801A0000:
				BrbStringCat(pStatusText, " = Bad_CertificateUntrusted", nStatusTextSize);
				break;
			case 0x801B0000:
				BrbStringCat(pStatusText, " = Bad_CertificateRevocationUnknown", nStatusTextSize);
				break;
			case 0x801C0000:
				BrbStringCat(pStatusText, " = Bad_CertificateIssuerRevocationUnknown", nStatusTextSize);
				break;
			case 0x801D0000:
				BrbStringCat(pStatusText, " = Bad_CertificateRevoked", nStatusTextSize);
				break;
			case 0x801E0000:
				BrbStringCat(pStatusText, " = Bad_CertificateIssuerRevoked", nStatusTextSize);
				break;
			case 0x801F0000:
				BrbStringCat(pStatusText, " = Bad_UserAccessDenied", nStatusTextSize);
				break;
			case 0x80200000:
				BrbStringCat(pStatusText, " = Bad_IdentityTokenInvalid", nStatusTextSize);
				break;
			case 0x80210000:
				BrbStringCat(pStatusText, " = Bad_IdentityTokenRejected", nStatusTextSize);
				break;
			case 0x80220000:
				BrbStringCat(pStatusText, " = Bad_SecureChannelIdInvalid", nStatusTextSize);
				break;
			case 0x80230000:
				BrbStringCat(pStatusText, " = Bad_InvalidTimestamp", nStatusTextSize);
				break;
			case 0x80240000:
				BrbStringCat(pStatusText, " = Bad_NonceInvalid", nStatusTextSize);
				break;
			case 0x80250000:
				BrbStringCat(pStatusText, " = Bad_SessionIdInvalid", nStatusTextSize);
				break;
			case 0x80260000:
				BrbStringCat(pStatusText, " = Bad_SessionClosed", nStatusTextSize);
				break;
			case 0x80270000:
				BrbStringCat(pStatusText, " = Bad_SessionNotActivated", nStatusTextSize);
				break;
			case 0x80280000:
				BrbStringCat(pStatusText, " = Bad_SubscriptionIdInvalid", nStatusTextSize);
				break;
			case 0x802A0000:
				BrbStringCat(pStatusText, " = Bad_RequestHeaderInvalid", nStatusTextSize);
				break;
			case 0x802B0000:
				BrbStringCat(pStatusText, " = Bad_TimestampsToReturnInvalid", nStatusTextSize);
				break;
			case 0x802C0000:
				BrbStringCat(pStatusText, " = Bad_RequestCancelledByClient", nStatusTextSize);
				break;
			case 0x80310000:
				BrbStringCat(pStatusText, " = Bad_NoCommunication", nStatusTextSize);
				break;
			case 0x80320000:
				BrbStringCat(pStatusText, " = Bad_WaitingForInitialData", nStatusTextSize);
				break;
			case 0x80330000:
				BrbStringCat(pStatusText, " = Bad_NodeIdInvalid", nStatusTextSize);
				break;
			case 0x80340000:
				BrbStringCat(pStatusText, " = Bad_NodeIdUnknown", nStatusTextSize);
				break;
			case 0x80350000:
				BrbStringCat(pStatusText, " = Bad_AttributeIdInvalid", nStatusTextSize);
				break;
			case 0x80360000:
				BrbStringCat(pStatusText, " = Bad_IndexRangeInvalid", nStatusTextSize);
				break;
			case 0x80370000:
				BrbStringCat(pStatusText, " = Bad_IndexRangeNoData", nStatusTextSize);
				break;
			case 0x80380000:
				BrbStringCat(pStatusText, " = Bad_DataEncodingInvalid", nStatusTextSize);
				break;
			case 0x80390000:
				BrbStringCat(pStatusText, " = Bad_DataEncodingUnsupported", nStatusTextSize);
				break;
			case 0x803A0000:
				BrbStringCat(pStatusText, " = Bad_NotReadable", nStatusTextSize);
				break;
			case 0x803B0000:
				BrbStringCat(pStatusText, " = Bad_NotWritable", nStatusTextSize);
				break;
			case 0x803C0000:
				BrbStringCat(pStatusText, " = Bad_OutOfRange", nStatusTextSize);
				break;
			case 0x803D0000:
				BrbStringCat(pStatusText, " = Bad_NotSupported", nStatusTextSize);
				break;
			case 0x803E0000:
				BrbStringCat(pStatusText, " = Bad_NotFound", nStatusTextSize);
				break;
			case 0x803F0000:
				BrbStringCat(pStatusText, " = Bad_ObjectDeleted", nStatusTextSize);
				break;
			case 0x80400000:
				BrbStringCat(pStatusText, " = Bad_NotImplemented", nStatusTextSize);
				break;
			case 0x80410000:
				BrbStringCat(pStatusText, " = Bad_MonitoringModeInvalid", nStatusTextSize);
				break;
			case 0x80420000:
				BrbStringCat(pStatusText, " = Bad_MonitoredItemIdInvalid", nStatusTextSize);
				break;
			case 0x80430000:
				BrbStringCat(pStatusText, " = Bad_MonitoredItemFilterInvalid", nStatusTextSize);
				break;
			case 0x80440000:
				BrbStringCat(pStatusText, " = Bad_MonitoredItemFilterUnsupported", nStatusTextSize);
				break;
			case 0x80450000:
				BrbStringCat(pStatusText, " = Bad_FilterNotAllowed", nStatusTextSize);
				break;
			case 0x80460000:
				BrbStringCat(pStatusText, " = Bad_StructureMissing", nStatusTextSize);
				break;
			case 0x80470000:
				BrbStringCat(pStatusText, " = Bad_EventFilterInvalid", nStatusTextSize);
				break;
			case 0x80480000:
				BrbStringCat(pStatusText, " = Bad_ContentFilterInvalid", nStatusTextSize);
				break;
			case 0x80490000:
				BrbStringCat(pStatusText, " = Bad_FilterOperandInvalid", nStatusTextSize);
				break;
			case 0x804A0000:
				BrbStringCat(pStatusText, " = Bad_ContinuationPointInvalid", nStatusTextSize);
				break;
			case 0x804B0000:
				BrbStringCat(pStatusText, " = Bad_NoContinuationPoints", nStatusTextSize);
				break;
			case 0x804C0000:
				BrbStringCat(pStatusText, " = Bad_ReferenceTypeIdInvalid", nStatusTextSize);
				break;
			case 0x804D0000:
				BrbStringCat(pStatusText, " = Bad_BrowseDirectionInvalid", nStatusTextSize);
				break;
			case 0x804E0000:
				BrbStringCat(pStatusText, " = Bad_NodeNotInView", nStatusTextSize);
				break;
			case 0x804F0000:
				BrbStringCat(pStatusText, " = Bad_ServerUriInvalid", nStatusTextSize);
				break;
			case 0x80500000:
				BrbStringCat(pStatusText, " = Bad_ServerNameMissing", nStatusTextSize);
				break;
			case 0x80510000:
				BrbStringCat(pStatusText, " = Bad_DiscoveryUrlMissing", nStatusTextSize);
				break;
			case 0x80520000:
				BrbStringCat(pStatusText, " = Bad_SempahoreFileMissing", nStatusTextSize);
				break;
			case 0x80530000:
				BrbStringCat(pStatusText, " = Bad_RequestTypeInvalid", nStatusTextSize);
				break;
			case 0x80540000:
				BrbStringCat(pStatusText, " = Bad_SecurityModeRejected", nStatusTextSize);
				break;
			case 0x80550000:
				BrbStringCat(pStatusText, " = Bad_SecurityPolicyRejected", nStatusTextSize);
				break;
			case 0x80560000:
				BrbStringCat(pStatusText, " = Bad_TooManySessions", nStatusTextSize);
				break;
			case 0x80570000:
				BrbStringCat(pStatusText, " = Bad_UserSignatureInvalid", nStatusTextSize);
				break;
			case 0x80580000:
				BrbStringCat(pStatusText, " = Bad_ApplicationSignatureInvalid", nStatusTextSize);
				break;
			case 0x80590000:
				BrbStringCat(pStatusText, " = Bad_NoValidCertificates", nStatusTextSize);
				break;
			case 0x805A0000:
				BrbStringCat(pStatusText, " = Bad_RequestCancelledByRequest", nStatusTextSize);
				break;
			case 0x805B0000:
				BrbStringCat(pStatusText, " = Bad_ParentNodeIdInvalid", nStatusTextSize);
				break;
			case 0x805C0000:
				BrbStringCat(pStatusText, " = Bad_ReferenceNotAllowed", nStatusTextSize);
				break;
			case 0x805D0000:
				BrbStringCat(pStatusText, " = Bad_NodeIdRejected", nStatusTextSize);
				break;
			case 0x805E0000:
				BrbStringCat(pStatusText, " = Bad_NodeIdExists", nStatusTextSize);
				break;
			case 0x805F0000:
				BrbStringCat(pStatusText, " = Bad_NodeClassInvalid", nStatusTextSize);
				break;
			case 0x80600000:
				BrbStringCat(pStatusText, " = Bad_BrowseNameInvalid", nStatusTextSize);
				break;
			case 0x80610000:
				BrbStringCat(pStatusText, " = Bad_BrowseNameDuplicated", nStatusTextSize);
				break;
			case 0x80620000:
				BrbStringCat(pStatusText, " = Bad_NodeAttributesInvalid", nStatusTextSize);
				break;
			case 0x80630000:
				BrbStringCat(pStatusText, " = Bad_TypeDefinitionInvalid", nStatusTextSize);
				break;
			case 0x80640000:
				BrbStringCat(pStatusText, " = Bad_SourceNodeIdInvalid", nStatusTextSize);
				break;
			case 0x80650000:
				BrbStringCat(pStatusText, " = Bad_TargetNodeIdInvalid", nStatusTextSize);
				break;
			case 0x80660000:
				BrbStringCat(pStatusText, " = Bad_DuplicateReferenceNotAllowed", nStatusTextSize);
				break;
			case 0x80670000:
				BrbStringCat(pStatusText, " = Bad_InvalidSelfReference", nStatusTextSize);
				break;
			case 0x80680000:
				BrbStringCat(pStatusText, " = Bad_ReferenceLocalOnly", nStatusTextSize);
				break;
			case 0x80690000:
				BrbStringCat(pStatusText, " = Bad_NoDeleteRights", nStatusTextSize);
				break;
			case 0x806A0000:
				BrbStringCat(pStatusText, " = Bad_ServerIndexInvalid", nStatusTextSize);
				break;
			case 0x806B0000:
				BrbStringCat(pStatusText, " = Bad_ViewIdUnknown", nStatusTextSize);
				break;
			case 0x806D0000:
				BrbStringCat(pStatusText, " = Bad_TooManyMatches", nStatusTextSize);
				break;
			case 0x806E0000:
				BrbStringCat(pStatusText, " = Bad_QueryTooComplex", nStatusTextSize);
				break;
			case 0x806F0000:
				BrbStringCat(pStatusText, " = Bad_NoMatch", nStatusTextSize);
				break;
			case 0x80700000:
				BrbStringCat(pStatusText, " = Bad_MaxAgeInvalid", nStatusTextSize);
				break;
			case 0x80710000:
				BrbStringCat(pStatusText, " = Bad_HistoryOperationInvalid", nStatusTextSize);
				break;
			case 0x80720000:
				BrbStringCat(pStatusText, " = Bad_HistoryOperationUnsupported", nStatusTextSize);
				break;
			case 0x80730000:
				BrbStringCat(pStatusText, " = Bad_WriteNotSupported", nStatusTextSize);
				break;
			case 0x80740000:
				BrbStringCat(pStatusText, " = Bad_TypeMismatch", nStatusTextSize);
				break;
			case 0x80750000:
				BrbStringCat(pStatusText, " = Bad_MethodInvalid", nStatusTextSize);
				break;
			case 0x80760000:
				BrbStringCat(pStatusText, " = Bad_ArgumentsMissing", nStatusTextSize);
				break;
			case 0x80770000:
				BrbStringCat(pStatusText, " = Bad_TooManySubscriptions", nStatusTextSize);
				break;
			case 0x80780000:
				BrbStringCat(pStatusText, " = Bad_TooManyPublishRequests", nStatusTextSize);
				break;
			case 0x80790000:
				BrbStringCat(pStatusText, " = Bad_NoSubscription", nStatusTextSize);
				break;
			case 0x807A0000:
				BrbStringCat(pStatusText, " = Bad_SequenceNumberUnknown", nStatusTextSize);
				break;
			case 0x807B0000:
				BrbStringCat(pStatusText, " = Bad_MessageNotAvailable", nStatusTextSize);
				break;
			case 0x807C0000:
				BrbStringCat(pStatusText, " = Bad_InsufficientClientProfile", nStatusTextSize);
				break;
			case 0x807D0000:
				BrbStringCat(pStatusText, " = Bad_TcpServerTooBusy", nStatusTextSize);
				break;
			case 0x807E0000:
				BrbStringCat(pStatusText, " = Bad_TcpMessageTypeInvalid", nStatusTextSize);
				break;
			case 0x807F0000:
				BrbStringCat(pStatusText, " = Bad_TcpSecureChannelUnknown", nStatusTextSize);
				break;
			case 0x80800000:
				BrbStringCat(pStatusText, " = Bad_TcpMessageTooLarge", nStatusTextSize);
				break;
			case 0x80810000:
				BrbStringCat(pStatusText, " = Bad_TcpNotEnoughResources", nStatusTextSize);
				break;
			case 0x80820000:
				BrbStringCat(pStatusText, " = Bad_TcpInternalError", nStatusTextSize);
				break;
			case 0x80830000:
				BrbStringCat(pStatusText, " = Bad_TcpEndpointUrlInvalid", nStatusTextSize);
				break;
			case 0x80840000:
				BrbStringCat(pStatusText, " = Bad_RequestInterrupted", nStatusTextSize);
				break;
			case 0x80850000:
				BrbStringCat(pStatusText, " = Bad_RequestTimeout", nStatusTextSize);
				break;
			case 0x80860000:
				BrbStringCat(pStatusText, " = Bad_SecureChannelClosed", nStatusTextSize);
				break;
			case 0x80870000:
				BrbStringCat(pStatusText, " = Bad_SecureChannelTokenUnknown", nStatusTextSize);
				break;
			case 0x80880000:
				BrbStringCat(pStatusText, " = Bad_SequenceNumberInvalid", nStatusTextSize);
				break;
			case 0x80890000:
				BrbStringCat(pStatusText, " = Bad_ConfigurationError", nStatusTextSize);
				break;
			case 0x808A0000:
				BrbStringCat(pStatusText, " = Bad_NotConnected", nStatusTextSize);
				break;
			case 0x808B0000:
				BrbStringCat(pStatusText, " = Bad_DeviceFailure", nStatusTextSize);
				break;
			case 0x808C0000:
				BrbStringCat(pStatusText, " = Bad_SensorFailure", nStatusTextSize);
				break;
			case 0x808D0000:
				BrbStringCat(pStatusText, " = Bad_OutOfService", nStatusTextSize);
				break;
			case 0x808E0000:
				BrbStringCat(pStatusText, " = Bad_DeadbandFilterInvalid", nStatusTextSize);
				break;
			case 0x80970000:
				BrbStringCat(pStatusText, " = Bad_RefreshInProgress", nStatusTextSize);
				break;
			case 0x80980000:
				BrbStringCat(pStatusText, " = Bad_ConditionAlreadyDisabled", nStatusTextSize);
				break;
			case 0x80990000:
				BrbStringCat(pStatusText, " = Bad_ConditionDisabled", nStatusTextSize);
				break;
			case 0x809A0000:
				BrbStringCat(pStatusText, " = Bad_EventIdUnknown", nStatusTextSize);
				break;
			case 0x809B0000:
				BrbStringCat(pStatusText, " = Bad_NoData", nStatusTextSize);
				break;
			case 0x809D0000:
				BrbStringCat(pStatusText, " = Bad_DataLost", nStatusTextSize);
				break;
			case 0x809E0000:
				BrbStringCat(pStatusText, " = Bad_DataUnavailable", nStatusTextSize);
				break;
			case 0x809F0000:
				BrbStringCat(pStatusText, " = Bad_EntryExists", nStatusTextSize);
				break;
			case 0x80A00000:
				BrbStringCat(pStatusText, " = Bad_NoEntryExists", nStatusTextSize);
				break;
			case 0x80A10000:
				BrbStringCat(pStatusText, " = Bad_TimestampNotSupported", nStatusTextSize);
				break;
			case 0x80AB0000:
				BrbStringCat(pStatusText, " = Bad_InvalidArgument", nStatusTextSize);
				break;
			case 0x80AC0000:
				BrbStringCat(pStatusText, " = Bad_ConnectionRejected", nStatusTextSize);
				break;
			case 0x80AD0000:
				BrbStringCat(pStatusText, " = Bad_Disconnect", nStatusTextSize);
				break;
			case 0x80AE0000:
				BrbStringCat(pStatusText, " = Bad_ConnectionClosed", nStatusTextSize);
				break;
			case 0x80AF0000:
				BrbStringCat(pStatusText, " = Bad_InvalidState", nStatusTextSize);
				break;
			case 0x80B00000:
				BrbStringCat(pStatusText, " = Bad_EndOfStream", nStatusTextSize);
				break;
			case 0x80B10000:
				BrbStringCat(pStatusText, " = Bad_NoDataAvailable", nStatusTextSize);
				break;
			case 0x80B20000:
				BrbStringCat(pStatusText, " = Bad_WaitingForResponse", nStatusTextSize);
				break;
			case 0x80B30000:
				BrbStringCat(pStatusText, " = Bad_OperationAbandoned", nStatusTextSize);
				break;
			case 0x80B40000:
				BrbStringCat(pStatusText, " = Bad_ExpectedStreamToBlock", nStatusTextSize);
				break;
			case 0x80B50000:
				BrbStringCat(pStatusText, " = Bad_WouldBlock", nStatusTextSize);
				break;
			case 0x80B60000:
				BrbStringCat(pStatusText, " = Bad_SyntaxError", nStatusTextSize);
				break;
			case 0x80B70000:
				BrbStringCat(pStatusText, " = Bad_MaxConnectionsReached", nStatusTextSize);
				break;
			case 0x80B80000:
				BrbStringCat(pStatusText, " = Bad_RequestTooLarge", nStatusTextSize);
				break;
			case 0x80B90000:
				BrbStringCat(pStatusText, " = Bad_ResponseTooLarge", nStatusTextSize);
				break;
			case 0x80BB0000:
				BrbStringCat(pStatusText, " = Bad_EventNotAcknowledgeable", nStatusTextSize);
				break;
			case 0x80BD0000:
				BrbStringCat(pStatusText, " = Bad_InvalidTimestampArgument", nStatusTextSize);
				break;
			case 0x80BE0000:
				BrbStringCat(pStatusText, " = Bad_ProtocolVersionUnsupported", nStatusTextSize);
				break;
			case 0x80BF0000:
				BrbStringCat(pStatusText, " = Bad_StateNotActive", nStatusTextSize);
				break;
			case 0x80C10000:
				BrbStringCat(pStatusText, " = Bad_FilterOperatorInvalid", nStatusTextSize);
				break;
			case 0x80C20000:
				BrbStringCat(pStatusText, " = Bad_FilterOperatorUnsupported", nStatusTextSize);
				break;
			case 0x80C30000:
				BrbStringCat(pStatusText, " = Bad_FilterOperandCountMismatch", nStatusTextSize);
				break;
			case 0x80C40000:
				BrbStringCat(pStatusText, " = Bad_FilterElementInvalid", nStatusTextSize);
				break;
			case 0x80C50000:
				BrbStringCat(pStatusText, " = Bad_FilterLiteralInvalid", nStatusTextSize);
				break;
			case 0x80C60000:
				BrbStringCat(pStatusText, " = Bad_IdentityChangeNotSupported", nStatusTextSize);
				break;
			case 0x80C80000:
				BrbStringCat(pStatusText, " = Bad_NotTypeDefinition", nStatusTextSize);
				break;
			case 0x80C90000:
				BrbStringCat(pStatusText, " = Bad_ViewTimestampInvalid", nStatusTextSize);
				break;
			case 0x80CA0000:
				BrbStringCat(pStatusText, " = Bad_ViewParameterMismatch", nStatusTextSize);
				break;
			case 0x80CB0000:
				BrbStringCat(pStatusText, " = Bad_ViewVersionInvalid", nStatusTextSize);
				break;
			case 0x80CC0000:
				BrbStringCat(pStatusText, " = Bad_ConditionAlreadyEnabled", nStatusTextSize);
				break;
			case 0x80CD0000:
				BrbStringCat(pStatusText, " = Bad_DialogNotActive", nStatusTextSize);
				break;
			case 0x80CE0000:
				BrbStringCat(pStatusText, " = Bad_DialogResponseInvalid", nStatusTextSize);
				break;
			case 0x80CF0000:
				BrbStringCat(pStatusText, " = Bad_ConditionBranchAlreadyAcked", nStatusTextSize);
				break;
			case 0x80D00000:
				BrbStringCat(pStatusText, " = Bad_ConditionBranchAlreadyConfirmed", nStatusTextSize);
				break;
			case 0x80D10000:
				BrbStringCat(pStatusText, " = Bad_ConditionAlreadyShelved", nStatusTextSize);
				break;
			case 0x80D20000:
				BrbStringCat(pStatusText, " = Bad_ConditionNotShelved", nStatusTextSize);
				break;
			case 0x80D30000:
				BrbStringCat(pStatusText, " = Bad_ShelvingTimeOutOfRange", nStatusTextSize);
				break;
			case 0x80D40000:
				BrbStringCat(pStatusText, " = Bad_AggregateListMismatch", nStatusTextSize);
				break;
			case 0x80D50000:
				BrbStringCat(pStatusText, " = Bad_AggregateNotSupported", nStatusTextSize);
				break;
			case 0x80D60000:
				BrbStringCat(pStatusText, " = Bad_AggregateInvalidInputs", nStatusTextSize);
				break;
			case 0x80D70000:
				BrbStringCat(pStatusText, " = Bad_BoundNotFound", nStatusTextSize);
				break;
			case 0x80D80000:
				BrbStringCat(pStatusText, " = Bad_BoundNotSupported", nStatusTextSize);
				break;
			case 0x80DA0000:
				BrbStringCat(pStatusText, " = Bad_AggregateConfigurationRejected", nStatusTextSize);
				break;
			case 0x80DB0000:
				BrbStringCat(pStatusText, " = Bad_TooManyMonitoredItems", nStatusTextSize);
				break;


			case 0x81010000:
				BrbStringCat(pStatusText, " = Bad_SignatureInvalid", nStatusTextSize);
				break;
			case 0x81040000:
				BrbStringCat(pStatusText, " = Bad_ExtensibleParameterInvalid", nStatusTextSize);
				break;
			case 0x81050000:
				BrbStringCat(pStatusText, " = Bad_ExtensibleParameterUnsupported", nStatusTextSize);
				break;
			case 0x81060000:
				BrbStringCat(pStatusText, " = Bad_HostUnknown", nStatusTextSize);
				break;
			case 0x81070000:
				BrbStringCat(pStatusText, " = Bad_TooManyPosts", nStatusTextSize);
				break;
			case 0x81080000:
				BrbStringCat(pStatusText, " = Bad_SecurityConfig", nStatusTextSize);
				break;
			case 0x81090000:
				BrbStringCat(pStatusText, " = Bad_FileNotFound", nStatusTextSize);
				break;
			case 0x810A0000:
				BrbStringCat(pStatusText, " = Bad_FileExists", nStatusTextSize);
				break;
		
		
			case 0xA0010000:
				BrbStringCat(pStatusText, " = PlcOpen_BadFwPermanentError", nStatusTextSize);
				break;
			case 0xA0020000:
				BrbStringCat(pStatusText, " = PlcOpen_BadFwTempError", nStatusTextSize);
				break;
			case 0xA0030000:
				BrbStringCat(pStatusText, " = PlcOpen_BadConnectionError", nStatusTextSize);
				break;
			case 0xA0040000:
				BrbStringCat(pStatusText, " = PlcOpen_BadHostNotFound", nStatusTextSize);
				break;
			case 0xA0050000:
				BrbStringCat(pStatusText, " = PlcOpen_BadAlreadyConnected", nStatusTextSize);
				break;
			case 0xA0060000:
				BrbStringCat(pStatusText, " = PlcOpen_BadSecurityFailed", nStatusTextSize);
				break;
			case 0xA0070000:
				BrbStringCat(pStatusText, " = PlcOpen_BadSuspended", nStatusTextSize);
				break;
			case 0xA0080000:
				BrbStringCat(pStatusText, " = PlcOpen_BadConnectionInvalidHdl", nStatusTextSize);
				break;
			case 0xA0090000:
				BrbStringCat(pStatusText, " = PlcOpen_BadNsNotFound", nStatusTextSize);
				break;
			case 0xA00A0000:
				BrbStringCat(pStatusText, " = PlcOpen_BadResultTooLong", nStatusTextSize);
				break;
			case 0xA00B0000:
				BrbStringCat(pStatusText, " = PlcOpen_BadInvalidType", nStatusTextSize);
				break;
			case 0xA00C0000:
				BrbStringCat(pStatusText, " = PlcOpen_BadNodeInvalidHdl", nStatusTextSize);
				break;
			case 0xA00D0000:
				BrbStringCat(pStatusText, " = PlcOpen_BadMethodInvalidHdl", nStatusTextSize);
				break;
			case 0xA00E0000:
				BrbStringCat(pStatusText, " = PlcOpen_BadReadFailed", nStatusTextSize);
				break;
			case 0xA00F0000:
				BrbStringCat(pStatusText, " = PlcOpen_BadWriteFailed", nStatusTextSize);
				break;
			case 0xA0100000:
				BrbStringCat(pStatusText, " = PlcOpen_BadCallFailed", nStatusTextSize);
				break;
			case 0xA0110000:
				BrbStringCat(pStatusText, " = PlcOpen_BadInParamFailed", nStatusTextSize);
				break;
			case 0xA0120000:
				BrbStringCat(pStatusText, " = PlcOpen_BadOutParamFailed", nStatusTextSize);
				break;
			case 0xA0130000:
				BrbStringCat(pStatusText, " = PlcOpen_BadSubscriptionInvalidHdl", nStatusTextSize);
				break;
			case 0xA0140000:
				BrbStringCat(pStatusText, " = PlcOpen_BadMonitoredItemInvalidHdl", nStatusTextSize);
				break;
			case 0xA0150000:
				BrbStringCat(pStatusText, " = PlcOpen_BadMonitoredItemSyncMismatch", nStatusTextSize);
				break;


			case 0xB0020000:
				BrbStringCat(pStatusText, " = PlcOpen_BadUnexpectedNoOfResults", nStatusTextSize);
				break;
			case 0xB0030000:
				BrbStringCat(pStatusText, " = PlcOpen_BadIndexOutOfRange", nStatusTextSize);
				break;
			case 0xB0040000:
				BrbStringCat(pStatusText, " = PlcOpen_BadVariableNameInvalid", nStatusTextSize);
				break;
			case 0xB0050000:
				BrbStringCat(pStatusText, " = PlcOpen_BadTypeNameInvalid", nStatusTextSize);
				break;
			case 0xB0060000:
				BrbStringCat(pStatusText, " = PlcOpen_BadBrowseNameNotFound", nStatusTextSize);
				break;
			case 0xB0070000:
				BrbStringCat(pStatusText, " = PlcOpen_BadConfigAmbiguity", nStatusTextSize);
				break;
			case 0xB0080000:
				BrbStringCat(pStatusText, " = PlcOpen_BadEventFieldSelection", nStatusTextSize);
				break;
			case 0xB0090000:
				BrbStringCat(pStatusText, " = PlcOpen_BadEventContentFilter", nStatusTextSize);
				break;
			case 0xB00C0000:
				BrbStringCat(pStatusText, " = PlcOpen_BadElementCount", nStatusTextSize);
				break;
			case 0xB00D0000:
				BrbStringCat(pStatusText, " = PlcOpen_BadMonitoringQueueSize", nStatusTextSize);
				break;
			case 0xB00E0000:
				BrbStringCat(pStatusText, " = PlcOpen_BadServerNotRunning", nStatusTextSize);
				break;
			case 0xB00F0000:
				BrbStringCat(pStatusText, " = PlcOpen_BadNodeIdAlreayUsed", nStatusTextSize);
				break;
			case 0xB0100000:
				BrbStringCat(pStatusText, " = PlcOpen_BadMethodCallHandleInvalid", nStatusTextSize);
				break;
			case 0xB0110000:
				BrbStringCat(pStatusText, " = PlcOpen_BadMethodNameInvalid", nStatusTextSize);
				break;
			case 0xB0190000:
				BrbStringCat(pStatusText, " = PlcOpen_BadInvalidEventFieldValue", nStatusTextSize);
				break;
		
			case 0xB00B0000:
				BrbStringCat(pStatusText, " = Bad_InvalidNodeCount", nStatusTextSize);
				break;
			case 0xB0120000:
				BrbStringCat(pStatusText, " = Bad_NoAuthorization", nStatusTextSize);
				break;
			case 0xB0130000:
				BrbStringCat(pStatusText, " = Bad_UnknownRole", nStatusTextSize);
				break;
			case 0xB0140000:
				BrbStringCat(pStatusText, " = Bad_UnknownAccessRight", nStatusTextSize);
				break;
			case 0xB0150000:
				BrbStringCat(pStatusText, " = Bad_NoRoles", nStatusTextSize);
				break;
			case 0xB0160000:
				BrbStringCat(pStatusText, " = Bad_TooManyRoles", nStatusTextSize);
				break;
			case 0xB0170000:
				BrbStringCat(pStatusText, " = Bad_DuplicateRole", nStatusTextSize);
				break;
			case 0xB0180000:
				BrbStringCat(pStatusText, " = Bad_InvisibleNode", nStatusTextSize);
				break;
			
			default:
				nStatus = 0x803D0000; // Bad_NotSupported
				break;
			
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

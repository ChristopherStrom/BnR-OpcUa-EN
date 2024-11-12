#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLibUa.h"
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Gibt eine Liste mit Attribut-Texten zurück */
plcdword BrbUaGetAttributeList(struct UANodeInfo* pNodeInfo, struct BrbUaNodeInfoAttributes_TYP* pAttributes)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pAttributes != 0)
	{
		memset(pAttributes, 0, sizeof(BrbUaNodeInfoAttributes_TYP));
		BrbStringCat(pAttributes->Attribute[UAAI_Default].sName, "Default", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_NodeId].sName, "NodeId", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_NodeClass].sName, "NodeClass", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_BrowseName].sName, "BrowseName", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_DisplayName].sName, "DisplayName", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_Description].sName, "Description", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_WriteMask].sName, "WriteMask", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_UserWriteMask].sName, "UserWriteMask", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_IsAbstract].sName, "IsAbstract", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_Symmetric].sName, "Symmetric", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_InverseName].sName, "InverseName", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_ContainsNoLoops].sName, "ContainsNoLoops", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_EventNotifier].sName, "EventNotifier", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_Value].sName, "Value", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_DataType].sName, "DataType", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_ValueRank].sName, "ValueRank", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_ArrayDimensions].sName, "ArrayDimensions", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_AccessLevel].sName, "AccessLevel", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_UserAccessLevel].sName, "UserAccessLevel", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_MinimumSamplingInterval].sName, "MinimumSamplingInterval", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_Historizing].sName, "Historizing", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_Executable].sName, "Executable", sizeof(pAttributes->Attribute[0].sName));
		BrbStringCat(pAttributes->Attribute[UAAI_UserExecutable].sName, "UserExecutable", sizeof(pAttributes->Attribute[0].sName));
		if(pNodeInfo != 0)
		{
			STRING sHelp[nBRBUA_VALUE_TEXT_CHAR_MAX];
			// Default bleibt leer
			BrbUaAddNodeIdText(&pNodeInfo->NodeID, pAttributes->Attribute[UAAI_NodeId].sValue, sizeof(pAttributes->Attribute[UAAI_NodeId].sValue));
			BrbUaAddNodeClassText(pNodeInfo->NodeClass, pAttributes->Attribute[UAAI_NodeClass].sValue, sizeof(pAttributes->Attribute[UAAI_NodeClass].sValue));
			BrbStringCat(pAttributes->Attribute[UAAI_BrowseName].sValue, pNodeInfo->BrowseName, sizeof(pAttributes->Attribute[0].sValue));
			BrbStringCat(pAttributes->Attribute[UAAI_DisplayName].sValue, pNodeInfo->DisplayName.Text, sizeof(pAttributes->Attribute[0].sValue));
			BrbStringCat(pAttributes->Attribute[UAAI_Description].sValue, pNodeInfo->Description.Text, sizeof(pAttributes->Attribute[0].sValue));
			BrbUdintToAscii(pNodeInfo->WriteMask, pAttributes->Attribute[UAAI_WriteMask].sValue);
			BrbUdintToAscii(pNodeInfo->UserWriteMask, pAttributes->Attribute[UAAI_UserWriteMask].sValue);
			BrbUaAddBooleanText(pNodeInfo->IsAbstract, pAttributes->Attribute[UAAI_IsAbstract].sValue, sizeof(pAttributes->Attribute[UAAI_IsAbstract].sValue));
			BrbUaAddBooleanText(pNodeInfo->Symmetric, pAttributes->Attribute[UAAI_Symmetric].sValue, sizeof(pAttributes->Attribute[UAAI_Symmetric].sValue));
			BrbStringCat(pAttributes->Attribute[UAAI_InverseName].sValue, pNodeInfo->InverseName, sizeof(pAttributes->Attribute[0].sValue));
			BrbUaAddBooleanText(pNodeInfo->ContainsNoLoops, pAttributes->Attribute[UAAI_ContainsNoLoops].sValue, sizeof(pAttributes->Attribute[UAAI_ContainsNoLoops].sValue));
			BrbUaAddEventNotifierText(pNodeInfo->EventNotifier, pAttributes->Attribute[UAAI_EventNotifier].sValue, sizeof(pAttributes->Attribute[UAAI_EventNotifier].sValue));
			// Value bleibt leer
			UDINT nDatatypeId = BrbAsciiToUdint(pNodeInfo->DataType.Identifier);
			BrbUaAddDatatypeIdText(nDatatypeId, pAttributes->Attribute[UAAI_DataType].sValue, sizeof(pAttributes->Attribute[UAAI_DataType].sValue));
			brsitoa((DINT)pNodeInfo->ValueRank, (UDINT)&sHelp);
			BrbStringCat(pAttributes->Attribute[UAAI_ValueRank].sValue, sHelp, sizeof(pAttributes->Attribute[0].sValue));
			BrbUaAddArrayDimensionText((UDINT*)&pNodeInfo->ArrayDimension, pNodeInfo->ValueRank, pAttributes->Attribute[UAAI_ArrayDimensions].sValue, sizeof(pAttributes->Attribute[UAAI_ArrayDimensions].sValue));
			BrbUaAddAccessLevelText(pNodeInfo->AccessLevel, pAttributes->Attribute[UAAI_AccessLevel].sValue, sizeof(pAttributes->Attribute[UAAI_AccessLevel].sValue));
			BrbUaAddAccessLevelText(pNodeInfo->UserAccessLevel, pAttributes->Attribute[UAAI_UserAccessLevel].sValue, sizeof(pAttributes->Attribute[UAAI_UserAccessLevel].sValue));
			BrbUdintToAscii((UDINT)pNodeInfo->MinimumSamplingInterval, sHelp);
			BrbStringCat(pAttributes->Attribute[UAAI_MinimumSamplingInterval].sValue, sHelp, sizeof(pAttributes->Attribute[0].sValue));
			BrbUaAddBooleanText(pNodeInfo->Historizing, pAttributes->Attribute[UAAI_Historizing].sValue, sizeof(pAttributes->Attribute[UAAI_Historizing].sValue));
			BrbUaAddBooleanText(pNodeInfo->Executable, pAttributes->Attribute[UAAI_Executable].sValue, sizeof(pAttributes->Attribute[UAAI_Executable].sValue));
			BrbUaAddBooleanText(pNodeInfo->UserExecutable, pAttributes->Attribute[UAAI_UserExecutable].sValue, sizeof(pAttributes->Attribute[UAAI_UserExecutable].sValue));
			nStatus = 0x00000000; // = Good
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

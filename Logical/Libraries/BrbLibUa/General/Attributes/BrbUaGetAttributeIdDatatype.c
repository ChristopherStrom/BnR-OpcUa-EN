#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLibUa.h"

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Gibt den OpcUa-Datentyp für ein Attribut zurück */
enum UAVariantType BrbUaGetAttributeIdDatatype(enum UAAttributeId eAttributeId)
{
	UAVariantType eResult = UAVariantType_Null;
	// NOLINTBEGIN(bugprone-branch-clone)
	switch(eAttributeId) // NOLINT(hicpp-multiway-paths-covered)
	{
		case UAAI_Default:
			eResult = UAVariantType_Null;
			break;
		case UAAI_NodeId:
			eResult = UAVariantType_NodeId;
			break;
		case UAAI_NodeClass:
			eResult = UAVariantType_Int32;
			break;
		case UAAI_BrowseName:
			eResult = UAVariantType_QualifiedName;
			break;
		case UAAI_DisplayName:
			eResult = UAVariantType_LocalizedText;
			break;
		case UAAI_Description:
			eResult = UAVariantType_LocalizedText;
			break;
		case UAAI_WriteMask:
			eResult = UAVariantType_UInt32;
			break;
		case UAAI_UserWriteMask:
			eResult = UAVariantType_UInt32;
			break;
		case UAAI_IsAbstract:
			eResult = UAVariantType_Boolean;
			break;
		case UAAI_Symmetric:
			eResult = UAVariantType_Boolean;
			break;
		case UAAI_InverseName:
			eResult = UAVariantType_LocalizedText;
			break;
		case UAAI_ContainsNoLoops:
			eResult = UAVariantType_Boolean;
			break;
		case UAAI_EventNotifier:
			eResult = UAVariantType_Byte;
			break;
		case UAAI_Value:
			eResult = UAVariantType_Null;
			break;
		case UAAI_DataType:
			eResult = UAVariantType_NodeId;
			break;
		case UAAI_ValueRank:
			eResult = UAVariantType_Int32;
			break;
		case UAAI_ArrayDimensions:
			break;
		case UAAI_AccessLevel:
			eResult = UAVariantType_Byte;
			break;
		case UAAI_UserAccessLevel:
			eResult = UAVariantType_Byte;
			break;
		case UAAI_MinimumSamplingInterval:
			eResult = UAVariantType_Double;
			break;
		case UAAI_Historizing:
			eResult = UAVariantType_Boolean;
			break;
		case UAAI_Executable:
			eResult = UAVariantType_Boolean;
			break;
		case UAAI_UserExecutable:
			eResult = UAVariantType_Boolean;
			break;
	}
	// NOLINTEND(bugprone-branch-clone)
	return eResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

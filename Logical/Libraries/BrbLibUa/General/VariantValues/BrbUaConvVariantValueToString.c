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

/* Wandelt einen Text in einen OpcUa-Value */
plcdword BrbUaConvVariantValueToString(struct UAVariantData* pUaVariantData, plcstring* pValueText, unsigned long nValueTextSize)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pUaVariantData != 0 && pValueText != 0)
	{
		nStatus = 0x00000000; // = Good
		STRING sHelp[255];
		memset(pValueText, 0, nValueTextSize);
		switch(pUaVariantData->VariantType)
		{
			case UAVariantType_Null:
				BrbStringCopy(pValueText, "Null", nValueTextSize);
				break;

			case UAVariantType_Boolean:
				if(pUaVariantData->Boolean == 1)
				{
					BrbStringCopy(pValueText, "True", nValueTextSize);
				}
				else
				{
					BrbStringCopy(pValueText, "False", nValueTextSize);
				}
				break;

			case UAVariantType_SByte:
				brsitoa((DINT)pUaVariantData->SByte, (UDINT)pValueText);
				break;

			case UAVariantType_Byte:
				brsitoa((DINT)pUaVariantData->Byte, (UDINT)pValueText);
				break;

			case UAVariantType_Int16:
				brsitoa((DINT)pUaVariantData->Int16, (UDINT)pValueText);
				break;

			case UAVariantType_UInt16:
				brsitoa((DINT)pUaVariantData->UInt16, (UDINT)pValueText);
				break;

			case UAVariantType_Int32:
				brsitoa((DINT)pUaVariantData->Int32, (UDINT)pValueText);
				break;

			case UAVariantType_UInt32:
				BrbUdintToAscii(pUaVariantData->UInt32, pValueText);
				break;

			case UAVariantType_Int64:
				BrbStringCopy(pValueText, "Int64 not supported!", nValueTextSize);
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

			case UAVariantType_UInt64:
				BrbStringCopy(pValueText, "UInt64 not supported!", nValueTextSize);
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

			case UAVariantType_Float:
				brsftoa(pUaVariantData->Float, (UDINT)pValueText);
				break;

			case UAVariantType_Double:
				// Es gibt (noch) keine Umwandlungsfunktion von LREAL auf STRING
				// Deshalb wird zuerst in einen REAL gewandelt
				brsftoa((REAL)pUaVariantData->Double, (UDINT)pValueText);
				break;

			case UAVariantType_String:
				BrbStringCopy(pValueText, pUaVariantData->String, nValueTextSize);
				break;

			case UAVariantType_DateTime:
				BrbGetTimeTextDt(pUaVariantData->DateTime, pValueText, nValueTextSize, sBRBUA_TIMESTAMP_FORMAT);
				break;

			case UAVariantType_Guid:
				BrbStringCopy(pValueText, pUaVariantData->String, nValueTextSize);
				break;

			case UAVariantType_ByteString:
				BrbStringCopy(pValueText, "Conversion of ByteString not supported!", nValueTextSize);
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

			case UAVariantType_XmlElement:
				BrbStringCopy(pValueText, "Conversion of XmlElement not supported!", nValueTextSize);
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

			case UAVariantType_NodeId:
				if(pUaVariantData->NodeId.IdentifierType == UAIdentifierType_String)
				{
					BrbStringCopy(pValueText, "ns=", nValueTextSize);
					brsitoa((DINT)pUaVariantData->NodeId.NamespaceIndex, (UDINT)&sHelp);
					BrbStringCat(pValueText, sHelp, nValueTextSize);
					BrbStringCat(pValueText, ";s=", nValueTextSize);
					BrbStringCat(pValueText, pUaVariantData->NodeId.Identifier, nValueTextSize);
				}
				else if(pUaVariantData->NodeId.IdentifierType == UAIdentifierType_Numeric)
				{
					BrbStringCopy(pValueText, "ns=", nValueTextSize);
					brsitoa((DINT)pUaVariantData->NodeId.NamespaceIndex, (UDINT)&sHelp);
					BrbStringCat(pValueText, sHelp, nValueTextSize);
					BrbStringCat(pValueText, ";i=", nValueTextSize);
					BrbStringCat(pValueText, pUaVariantData->NodeId.Identifier, nValueTextSize);
				}
				else if(pUaVariantData->NodeId.IdentifierType == UAIdentifierType_GUID)
				{
					BrbStringCopy(pValueText, "ns=", nValueTextSize);
					brsitoa((DINT)pUaVariantData->NodeId.NamespaceIndex, (UDINT)&sHelp);
					BrbStringCat(pValueText, sHelp, nValueTextSize);
					BrbStringCat(pValueText, ";g=", nValueTextSize);
					BrbStringCat(pValueText, pUaVariantData->NodeId.Identifier, nValueTextSize);
				}
				else if(pUaVariantData->NodeId.IdentifierType == UAIdentifierType_Opaque)
				{
					BrbStringCopy(pValueText, "Conversion of opaque node id not supported!", nValueTextSize);
					nStatus = 0x803D0000; // = Bad_NotSupported
				}
				break;

			case UAVariantType_ExpandedNodeId:
				BrbStringCopy(pValueText, "Conversion of expanded node id not supported!", nValueTextSize);
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

			case UAVariantType_StatusCode:
				BrbUaGetStatusCodeText(pUaVariantData->UInt32, pValueText, nValueTextSize);
				break;

			case UAVariantType_QualifiedName:
				brsitoa((DINT)pUaVariantData->QualifiedName.NamespaceIndex, (UDINT)pValueText);
				BrbStringCat(pValueText, ":", nValueTextSize);
				BrbStringCat(pValueText, pUaVariantData->QualifiedName.Name, nValueTextSize);
				break;

			case UAVariantType_LocalizedText:
				if(strlen(pUaVariantData->LocalizedText.Locale) > 0)
				{
					BrbStringCopy(pValueText, pUaVariantData->LocalizedText.Locale, nValueTextSize);
					BrbStringCat(pValueText, ":", nValueTextSize);
					BrbStringCat(pValueText, pUaVariantData->LocalizedText.Text, nValueTextSize);
				}
				else
				{
					BrbStringCopy(pValueText, pUaVariantData->LocalizedText.Text, nValueTextSize);
				}
				break;

		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

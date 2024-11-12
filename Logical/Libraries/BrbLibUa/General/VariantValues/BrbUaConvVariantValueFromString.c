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

/* Wandelt einen OpcUa-Value in einen Text */
plcdword BrbUaConvVariantValueFromString(struct UAVariantData* pUaVariantData, plcstring* pValueText)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pUaVariantData != 0 && pValueText != 0)
	{
		nStatus = 0x00000000; // = Good
		// NOLINTBEGIN(bugprone-branch-clone)
		switch(pUaVariantData->VariantType)
		{
			case UAVariantType_Null:
				// Not supported by library
				BrbUaClearVariantValue(pUaVariantData);
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

			case UAVariantType_Boolean:
				BrbUaClearVariantValue(pUaVariantData);
				if(strcmp(pValueText, "True") == 0 || strcmp(pValueText, "true") == 0 || strcmp(pValueText, "1") == 0)
				{
					pUaVariantData->Boolean = 1;
				}
				else
				{
					pUaVariantData->Boolean = 0;
				}
				break;

			case UAVariantType_SByte:
				BrbUaClearVariantValue(pUaVariantData);
				pUaVariantData->SByte = (SINT)brsatoi((UDINT)pValueText);
				break;

			case UAVariantType_Byte:
				BrbUaClearVariantValue(pUaVariantData);
				pUaVariantData->Byte = (USINT)brsatoi((UDINT)pValueText);
				break;

			case UAVariantType_Int16:
				BrbUaClearVariantValue(pUaVariantData);
				pUaVariantData->Int16 = (INT)brsatoi((UDINT)pValueText);
				break;

			case UAVariantType_UInt16:
				BrbUaClearVariantValue(pUaVariantData);
				pUaVariantData->UInt16 = (UINT)brsatoi((UDINT)pValueText);
				break;

			case UAVariantType_Int32:
				BrbUaClearVariantValue(pUaVariantData);
				pUaVariantData->Int32 = brsatoi((UDINT)pValueText);
				break;

			case UAVariantType_UInt32:
				BrbUaClearVariantValue(pUaVariantData);
				pUaVariantData->UInt32 = BrbAsciiToUdint(pValueText);
				break;

			case UAVariantType_Int64:
				// No Element in structure
				BrbUaClearVariantValue(pUaVariantData);
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

			case UAVariantType_UInt64:
				// No Element in structure
				BrbUaClearVariantValue(pUaVariantData);
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

			case UAVariantType_Float:
				BrbUaClearVariantValue(pUaVariantData);
				BrbStringReplace(pValueText, ",", ".");
				pUaVariantData->Float = brsatof((UDINT)pValueText);
				break;

			case UAVariantType_Double:
				// Es gibt (noch) keine Umwandlungsfunktion von STRING auf LREAL
				// Deshalb wird zuerst in einen REAL gewandelt
				BrbUaClearVariantValue(pUaVariantData);
				BrbStringReplace(pValueText, ",", ".");
				pUaVariantData->Double = (LREAL)brsatof((UDINT)pValueText);
				break;

			case UAVariantType_String:
				BrbUaClearVariantValue(pUaVariantData);
				BrbStringCopy(pUaVariantData->String, pValueText, sizeof(pUaVariantData->String));
				break;

			case UAVariantType_DateTime:
				BrbUaClearVariantValue(pUaVariantData);
				pUaVariantData->DateTime = BrbGetDtFromTimeText(pValueText, sBRBUA_DATETIME_FORMAT);
				break;

			case UAVariantType_Guid:
				// Guid wird im String-Element gesetzt
				BrbUaClearVariantValue(pUaVariantData);
				BrbStringCopy(pUaVariantData->String, pValueText, sizeof(pUaVariantData->String));
				break;

			case UAVariantType_ByteString:
				// Not supported by library
				BrbUaClearVariantValue(pUaVariantData);
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

			case UAVariantType_XmlElement:
				// Not supported by library
				BrbUaClearVariantValue(pUaVariantData);
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

			case UAVariantType_NodeId:
				BrbUaClearVariantValue(pUaVariantData);
				pUaVariantData->NodeId.NamespaceIndex = 0;
				UDINT nTextLen = brsstrlen((UDINT)pValueText);
				DINT nEndCharIndexNs = 0;
				// NamespaceIndex
				if(BrbStringStartsWith(pValueText, "ns=") == 1)
				{
					nEndCharIndexNs = BrbStringGetIndexOf(pValueText, ";", nTextLen);
					if(nEndCharIndexNs > 3)
					{
						STRING sNamespaceIndex[32];
						BrbStringGetSubText((STRING*)pValueText, 3, (UDINT)nEndCharIndexNs-3, sNamespaceIndex);
						pUaVariantData->NodeId.NamespaceIndex = (UINT)brsatoi((UDINT)&sNamespaceIndex);
					}
					else if(nEndCharIndexNs == -1)
					{
						// Nur NamespaceIndex
						nEndCharIndexNs = (DINT)nTextLen-1;
						STRING sNamespaceIndex[32];
						BrbStringGetSubText((STRING*)pValueText, 3, (UDINT)nEndCharIndexNs-2, sNamespaceIndex);
						pUaVariantData->NodeId.NamespaceIndex = (UINT)brsatoi((UDINT)&sNamespaceIndex);
					}
				}
				// Identifier
				DINT nEndCharIndexId = (DINT)nTextLen-1;
				DINT nStartCharIndexId = BrbStringGetIndexOf(pValueText + nEndCharIndexNs, "i=", nTextLen);
				if(nStartCharIndexId > -1 && nEndCharIndexId > nStartCharIndexId+2)
				{
					pUaVariantData->NodeId.IdentifierType = UAIdentifierType_Numeric;
					STRING sIdentifier[255];
					nStartCharIndexId += 2;
					BrbStringGetSubText((STRING*)pValueText + nEndCharIndexNs, (UDINT)nStartCharIndexId, (UDINT)(nEndCharIndexId-nStartCharIndexId+1), sIdentifier);
					BrbStringCopy(pUaVariantData->NodeId.Identifier, sIdentifier, sizeof(pUaVariantData->NodeId.Identifier));
				}
				else
				{
					nStartCharIndexId = BrbStringGetIndexOf(pValueText + nEndCharIndexNs, "s=", nTextLen);
					if(nStartCharIndexId > -1 && nEndCharIndexId > nStartCharIndexId+2)
					{
						pUaVariantData->NodeId.IdentifierType = UAIdentifierType_String;
						STRING sIdentifier[255];
						nStartCharIndexId += 2;
						BrbStringGetSubText((STRING*)pValueText + nEndCharIndexNs, (UDINT)nStartCharIndexId, (UDINT)(nEndCharIndexId-nStartCharIndexId+1), sIdentifier);
						BrbStringCopy(pUaVariantData->NodeId.Identifier, sIdentifier, sizeof(pUaVariantData->NodeId.Identifier));
					}
					else
					{
						nStartCharIndexId = BrbStringGetIndexOf(pValueText + nEndCharIndexNs, "g=", nTextLen);
						if(nStartCharIndexId > -1 && nEndCharIndexId > nStartCharIndexId+2)
						{
							pUaVariantData->NodeId.IdentifierType = UAIdentifierType_GUID;
							STRING sIdentifier[255];
							nStartCharIndexId += 2;
							BrbStringGetSubText((STRING*)pValueText + nEndCharIndexNs, (UDINT)nStartCharIndexId, (UDINT)(nEndCharIndexId-nStartCharIndexId+1), sIdentifier);
							BrbStringCopy(pUaVariantData->NodeId.Identifier, sIdentifier, sizeof(pUaVariantData->NodeId.Identifier));
						}
					}
				}
				if(nStartCharIndexId == -1)
				{
					// Kein gültiger Identifier
					nStatus = 0x80330000 ; // = Bad_NodeIdInvalid
				}
				break;

			case UAVariantType_ExpandedNodeId:
				// Not supported by library
				BrbUaClearVariantValue(pUaVariantData);
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

			case UAVariantType_StatusCode:
				BrbUaClearVariantValue(pUaVariantData);
				if(BrbStringStartsWith(pValueText, "0x") == 1)
				{
					pUaVariantData->UInt32 = BrbHexToUdint(pValueText+2);
				}
				else
				{
					pUaVariantData->UInt32 = BrbAsciiToUdint(pValueText);
				}
				break;

			case UAVariantType_QualifiedName:
				// Not supported by library
				BrbUaClearVariantValue(pUaVariantData);
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

			case UAVariantType_LocalizedText:
				// Not supported by library
				BrbUaClearVariantValue(pUaVariantData);
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

		}
		// NOLINTEND(bugprone-branch-clone)
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

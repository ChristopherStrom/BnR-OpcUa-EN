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

/* Hängt den Element-Namen eines OpcUa-Values anhand des Datentypen an einen Text an */
plcdword BrbUaAddVariantValueSubName(enum UAVariantType eVariantType, plcstring* pText, unsigned long nTextSize)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pText != 0)
	{
		nStatus = 0x00000000; // = Good
		// NOLINTBEGIN(bugprone-branch-clone)
		switch(eVariantType) // NOLINT(hicpp-multiway-paths-covered)
		{
			case UAVariantType_Null:
				// Not supported
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

			case UAVariantType_Boolean:
				BrbStringCat(pText, ".Boolean", nTextSize);
				break;

			case UAVariantType_SByte:
				BrbStringCat(pText, ".SByte", nTextSize);
				break;

			case UAVariantType_Byte:
				BrbStringCat(pText, ".Byte", nTextSize);
				break;

			case UAVariantType_Int16:
				BrbStringCat(pText, ".Int16", nTextSize);
				break;

			case UAVariantType_UInt16:
				BrbStringCat(pText, ".UInt16", nTextSize);
				break;

			case UAVariantType_Int32:
				BrbStringCat(pText, ".Int32", nTextSize);
				break;

			case UAVariantType_UInt32:
				BrbStringCat(pText, ".UInt32", nTextSize);
				break;

			case UAVariantType_Int64:
				BrbStringCat(pText, ".Int64", nTextSize);
				break;

			case UAVariantType_UInt64:
				BrbStringCat(pText, ".UInt64", nTextSize);
				break;

			case UAVariantType_Float:
				BrbStringCat(pText, ".Float", nTextSize);
				break;

			case UAVariantType_Double:
				BrbStringCat(pText, ".Double", nTextSize);
				break;

			case UAVariantType_String:
				BrbStringCat(pText, ".String", nTextSize);
				break;

			case UAVariantType_DateTime:
				BrbStringCat(pText, ".DateTime", nTextSize);
				break;

			case UAVariantType_Guid:
				BrbStringCat(pText, ".String", nTextSize);
				break;

			case UAVariantType_ByteString:
				BrbStringCat(pText, ".String", nTextSize);
				break;

			case UAVariantType_XmlElement:
				// Not supported
				nStatus = 0x803D0000; // = Bad_NotSupported
				break;

			case UAVariantType_NodeId:
				BrbStringCat(pText, ".NodeId", nTextSize);
				break;

			case UAVariantType_ExpandedNodeId:
				BrbStringCat(pText, ".ExpandedNodeId", nTextSize);
				break;

			case UAVariantType_StatusCode:
				BrbStringCat(pText, ".StatusCode", nTextSize);
				break;

			case UAVariantType_QualifiedName:
				BrbStringCat(pText, ".QualifiedName", nTextSize);
				break;

			case UAVariantType_LocalizedText:
				BrbStringCat(pText, ".LocalizedText", nTextSize);
				break;

		}
		// NOLINTEND(bugprone-branch-clone)
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

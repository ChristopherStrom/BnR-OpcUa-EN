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

/* Erzeugt eine zufällige NodeId */
plcdword BrbUaGetRandomNodeId(struct UANodeID* pNodeId, enum UAIdentifierType eIdentifierType)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pNodeId != 0)
	{
		nStatus = 0x00000000; // = Good
		UINT nNamespaceIndex = (UINT)BrbGetRandomDint(0, 10);
		if(eIdentifierType == UAIdentifierType_String)
		{
			pNodeId->IdentifierType = UAIdentifierType_String;
			pNodeId->NamespaceIndex = nNamespaceIndex;
			BrbGetRandomString(pNodeId->Identifier, sizeof(pNodeId->Identifier), 20, eBRB_RANDOM_STRING_UPPER_LETTERS + eBRB_RANDOM_STRING_LOWER_LETTERS); // NOLINT(clang-diagnostic-assign-enum)
		}
		else if(eIdentifierType == UAIdentifierType_GUID)
		{
			pNodeId->IdentifierType = UAIdentifierType_GUID;
			pNodeId->NamespaceIndex = nNamespaceIndex;
			BrbUaGetRandomGuidString((BrUaGuidString*)&pNodeId->Identifier, sizeof(pNodeId->Identifier), 1);
		}
		else if(eIdentifierType == UAIdentifierType_Opaque)
		{
			pNodeId->IdentifierType = UAIdentifierType_Opaque;
			pNodeId->NamespaceIndex = nNamespaceIndex;
			BrbStringCopy((STRING*)&pNodeId->Identifier, "", sizeof(pNodeId->Identifier));
			nStatus = 0x803D0000; // = Bad_NotSupported
		}
		else
		{
			pNodeId->IdentifierType = UAIdentifierType_Numeric;
			DINT nType = BrbGetRandomDint(0,2);
			if(nType == 0)
			{
				// 2 Byte
				pNodeId->NamespaceIndex = 0;
				UDINT nIdentifier = (UDINT)BrbGetRandomUdint(0,255);
				BrbUdintToAscii(nIdentifier, pNodeId->Identifier);
			}
			else if(nType == 1)
			{
				// 4 Byte
				pNodeId->NamespaceIndex = nNamespaceIndex;
				UDINT nIdentifier = (UINT)BrbGetRandomDint(4096, 65535);
				BrbUdintToAscii(nIdentifier, pNodeId->Identifier);
			}
			else
			{
				// 8 Byte
				pNodeId->NamespaceIndex = nNamespaceIndex;
				UDINT nIdentifier = BrbGetRandomUdint(65535, 4294967295UL);
				BrbUdintToAscii(nIdentifier, pNodeId->Identifier);
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

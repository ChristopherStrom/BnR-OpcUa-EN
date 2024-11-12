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

/* Hängt den Text einer NodeId an */
plcdword BrbUaAddNodeIdText(struct UANodeID* pNodeId, plcstring* pText, unsigned long nTextSize)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pNodeId != 0 && pText != 0)
	{
		nStatus = 0x00000000; // = Good
		STRING sHelp[nBRBUA_VALUE_TEXT_CHAR_MAX];
		BrbStringCat(pText, "ns=", nTextSize);
		brsitoa((DINT)pNodeId->NamespaceIndex, (UDINT)&sHelp);
		BrbStringCat(pText, sHelp, nTextSize);
		if(pNodeId->IdentifierType == UAIdentifierType_Numeric)
		{
			BrbStringCat(pText, ";i=", nTextSize);
		}
		else if(pNodeId->IdentifierType == UAIdentifierType_String)
		{
			BrbStringCat(pText, ";s=", nTextSize);
		}
		else if(pNodeId->IdentifierType == UAIdentifierType_GUID)
		{
			BrbStringCat(pText, ";g=", nTextSize);
		}
		else if(pNodeId->IdentifierType == UAIdentifierType_Opaque)
		{
			BrbStringCat(pText, ";o=", nTextSize);
		}
		else
		{
			BrbStringCat(pText, ";?=", nTextSize);
		}
		BrbStringCat(pText, pNodeId->Identifier, nTextSize);
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

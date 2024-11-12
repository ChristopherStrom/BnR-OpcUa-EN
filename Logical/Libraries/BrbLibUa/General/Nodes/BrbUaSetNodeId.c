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

/* Besetzt eine textuelle NodeId */
plcdword BrbUaSetNodeId(struct UANodeID* pNodeId, plcstring* sIdentifier, unsigned short nNamespaceIndex)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pNodeId != 0)
	{
		nStatus = 0x00000000; // = Good
		BrbStringCopy(pNodeId->Identifier, sIdentifier, sizeof(pNodeId->Identifier));
		pNodeId->NamespaceIndex = nNamespaceIndex;
		if(BrbStringIsNumerical(sIdentifier) == 1)
		{
			pNodeId->IdentifierType = UAIdentifierType_Numeric;
		}
		else
		{
			pNodeId->IdentifierType = UAIdentifierType_String;
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

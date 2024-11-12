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

/* Gibt den Server-Namespace aufgrund des DatObj-NamespaceIndex zurück */
unsigned short BrbUaRcGetSrvNamespace(struct BrbUaRunClient_TYP* pRunClient, unsigned short nDatObjNamespaceIndex, struct BrbUaRcNamespace_TYP* pServerNamespace)
{
	UINT nServerNamespaceIndex = 0;
	if(pRunClient != 0)
	{
		if(pRunClient->Namespaces.nNamespaceCount > 0 && pRunClient->Namespaces.pNamespaces != 0)
		{
			if(nDatObjNamespaceIndex < pRunClient->Namespaces.nNamespaceCount)
			{
				BrbUaRcNamespace_TYP* pNamespace = ((BrbUaRcNamespace_TYP*)pRunClient->Namespaces.pNamespaces) + nDatObjNamespaceIndex;
				nServerNamespaceIndex = pNamespace->nNamespaceIndex;
				if(pServerNamespace != 0)
				{
					memcpy(pServerNamespace, (USINT*)(((BrbUaRcNamespace_TYP*)pRunClient->Namespaces.pNamespaces) + nDatObjNamespaceIndex), sizeof(BrbUaRcNamespace_TYP));
				}
			}
		}
	}
	return nServerNamespaceIndex;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

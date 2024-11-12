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

/* Gibt den Server-Namespace aufgrund des DataObjekt-NamespaceIndex zurück */
unsigned short BrbUaRsGetNamespace(struct BrbUaRunServer_TYP* pRunServer, unsigned short nDatObjNamespaceIndex, struct BrbUaRsNamespace_TYP* pServerNamespace)
{
	UINT nServerNamespaceIndex = 0;
	if(pRunServer != 0)
	{
		if(pRunServer->Namespaces.nNamespaceCount > 0 && pRunServer->Namespaces.pNamespaces != 0)
		{
			if(nDatObjNamespaceIndex < pRunServer->Namespaces.nNamespaceCount)
			{
				BrbUaRsNamespace_TYP* pNamespace = ((BrbUaRsNamespace_TYP*)pRunServer->Namespaces.pNamespaces) + nDatObjNamespaceIndex;
				nServerNamespaceIndex = pNamespace->nNamespaceIndex;
				if(pServerNamespace != 0)
				{
					memcpy(pServerNamespace, (USINT*)(((BrbUaRsNamespace_TYP*)pRunServer->Namespaces.pNamespaces) + nDatObjNamespaceIndex), sizeof(BrbUaRsNamespace_TYP));
				}
			}
		}
	}
	return nServerNamespaceIndex;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

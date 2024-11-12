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

/* Gibt eine ermittelte Methode zuück */
unsigned short BrbUaRcGetMethod(struct BrbUaRunClient_TYP* pRunClient, unsigned short nMethodIndex, struct BrbUaRcMethod_TYP* pMethod, struct BrbUaRcMethodIntern_TYP* pMethodIntern)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunClient != 0 && pMethod != 0)
	{
		memset(pMethod, 0, sizeof(BrbUaRcMethod_TYP));
		nStatus = eBRB_ERR_UA_NO_ELEMENTS;
		if(pRunClient->Methods.nMethodCount > 0 && pRunClient->Methods.pMethods != 0)
		{
			nStatus = eBRB_ERR_UA_INVALID_INDEX;
			if(nMethodIndex < pRunClient->Methods.nMethodCount)
			{
				nStatus = eBRB_ERR_OK;
				BrbUaRcMethodIntern_TYP* pMethodInternOri = (((BrbUaRcMethodIntern_TYP*)pRunClient->Methods.pMethods)  + nMethodIndex);
				pMethod->nDatObjNamespaceIndex = pMethodInternOri->nDatObjNamespaceIndex;
				memcpy(&pMethod->ObjectNodeId, &pMethodInternOri->ObjectNodeId, sizeof(UANodeID));
				memcpy(&pMethod->MethodNodeId, &pMethodInternOri->MethodNodeId, sizeof(UANodeID));
				pMethod->tTimeout = pMethodInternOri->tTimeout;
				pMethod->nInputArgsCount = pMethodInternOri->nInputArgsCount;
				pMethod->nOutputArgsCount = pMethodInternOri->nOutputArgsCount;
				pMethod->nErrorId = pMethodInternOri->nErrorId;
				pMethod->nMethodHandle = pMethodInternOri->nMethodHandle;
				if(pMethodIntern != 0)
				{
					memcpy(pMethodIntern, pMethodInternOri, sizeof(BrbUaRcMethodIntern_TYP));
				}
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

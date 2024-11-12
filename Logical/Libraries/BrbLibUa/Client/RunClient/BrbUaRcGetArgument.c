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

/* Gibt ein ermitteltes ReadItem zurück */
unsigned short BrbUaRcGetArgument(struct BrbUaRunClient_TYP* pRunClient, unsigned short nMethodIndex, plcbit bOutput, unsigned short nArgumentIndex, struct UAMethodArgument* pArgument)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunClient != 0 && pArgument != 0)
	{
		memset(pArgument, 0, sizeof(UAMethodArgument));
		nStatus = eBRB_ERR_UA_NO_ELEMENTS;
		if(pRunClient->Methods.nMethodCount > 0 && pRunClient->Methods.pMethods != 0)
		{
			nStatus = eBRB_ERR_UA_INVALID_INDEX;
			if(nMethodIndex < pRunClient->Methods.nMethodCount)
			{
				nStatus = eBRB_ERR_UA_NO_ELEMENTS;
				BrbUaRcMethodIntern_TYP* pMethod = (((BrbUaRcMethodIntern_TYP*)pRunClient->Methods.pMethods) + nMethodIndex);
				if(bOutput == 0)
				{
					if(pMethod->nInputArgsCount > 0 && pMethod->pInputArguments != 0)
					{
						nStatus = eBRB_ERR_UA_INVALID_INDEX;
						if(nArgumentIndex < pMethod->nInputArgsCount)
						{
							nStatus = eBRB_ERR_OK;
							UAMethodArgument* pArgumentIntern = ((UAMethodArgument*)pMethod->pInputArguments) + nArgumentIndex;
							memcpy(pArgument, pArgumentIntern, sizeof(UAMethodArgument));
						}
					}
				}
				else
				{
					if(pMethod->nOutputArgsCount > 0 && pMethod->pOutputArguments != 0)
					{
						nStatus = eBRB_ERR_UA_INVALID_INDEX;
						if(nArgumentIndex < pMethod->nOutputArgsCount)
						{
							nStatus = eBRB_ERR_OK;
							UAMethodArgument* pArgumentIntern = ((UAMethodArgument*)pMethod->pOutputArguments) + nArgumentIndex;
							memcpy(pArgument, pArgumentIntern, sizeof(UAMethodArgument));
						}
					}
				}
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

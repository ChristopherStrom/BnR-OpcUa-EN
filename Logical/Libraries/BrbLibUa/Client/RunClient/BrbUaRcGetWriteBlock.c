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

/* Gibt einen ermittelten WriteBlock zurück */
unsigned short BrbUaRcGetWriteBlock(struct BrbUaRunClient_TYP* pRunClient, unsigned short nWriteBlockIndex, struct BrbUaRcWriteBlock_TYP* pWriteBlock, struct BrbUaRcWriteBlockIntern_TYP* pWriteBlockIntern)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunClient != 0 && pWriteBlock != 0)
	{
		memset(pWriteBlock, 0, sizeof(BrbUaRcWriteBlock_TYP));
		nStatus = eBRB_ERR_UA_NO_ELEMENTS;
		if(pRunClient->WriteBlocks.nBlockCount > 0 && pRunClient->WriteBlocks.pBlocks != 0)
		{
			nStatus = eBRB_ERR_UA_INVALID_INDEX;
			if(nWriteBlockIndex < pRunClient->WriteBlocks.nBlockCount)
			{
				nStatus = eBRB_ERR_OK;
				BrbUaRcWriteBlockIntern_TYP* pWriteBlockInternOri = ((BrbUaRcWriteBlockIntern_TYP*)pRunClient->WriteBlocks.pBlocks) + nWriteBlockIndex;
				pWriteBlock->nWriteItemCount = pWriteBlockInternOri->nWriteItemCount;
				if(pWriteBlockIntern != 0)
				{
					memcpy(pWriteBlockIntern, pWriteBlockInternOri, sizeof(BrbUaRcWriteBlockIntern_TYP));
				}
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

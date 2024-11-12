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

/* Gibt einen ermittelten ReadBlock zurück */
unsigned short BrbUaRcGetReadBlock(struct BrbUaRunClient_TYP* pRunClient, unsigned short nReadBlockIndex, struct BrbUaRcReadBlock_TYP* pReadBlock, struct BrbUaRcReadBlockIntern_TYP* pReadBlockIntern)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunClient != 0 && pReadBlock != 0)
	{
		memset(pReadBlock, 0, sizeof(BrbUaRcReadBlock_TYP));
		nStatus = eBRB_ERR_UA_NO_ELEMENTS;
		if(pRunClient->ReadBlocks.nBlockCount > 0 && pRunClient->ReadBlocks.pBlocks != 0)
		{
			nStatus = eBRB_ERR_UA_INVALID_INDEX;
			if(nReadBlockIndex < pRunClient->ReadBlocks.nBlockCount)
			{
				nStatus = eBRB_ERR_OK;
				BrbUaRcReadBlockIntern_TYP* pReadBlockInternOri = ((BrbUaRcReadBlockIntern_TYP*)pRunClient->ReadBlocks.pBlocks) + nReadBlockIndex;
				pReadBlock->nReadItemCount = pReadBlockInternOri->nReadItemCount;
				if(pReadBlockIntern != 0)
				{
					memcpy(pReadBlockIntern, pReadBlockInternOri, sizeof(BrbUaRcReadBlockIntern_TYP));
				}
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

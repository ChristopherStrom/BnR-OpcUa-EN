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

// Eigene Enums und Typen
enum Steps_ENUM
{
	eSTEP_INIT,
	eSTEP_WRITE,
	eSTEP_WRITE_WAIT,
};

/* Liest eine WriteBlock vom Server */
void BrbUaRcWriteBlock(struct BrbUaRcWriteBlock* inst)
{
	switch(inst->eStep)
	{
		case eSTEP_INIT:
			// Fub initialisieren
			inst->nStatus =  eBRB_ERR_BUSY;
			inst->nErrorId = 0x00000000; // Good
			BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
			memset(&inst->fbUaClt_WriteBulk, 0, sizeof(inst->fbUaClt_WriteBulk));
			// Parameter prüfen
			if(inst->pRunClient != 0)
			{
				if(inst->pRunClient->State.eClientState == eBRB_RCCLTSTATE_CONNECTED && inst->pRunClient->Connection.nConnectionHandle != 0)
				{
					if(inst->pRunClient->WriteBlocks.nBlockCount > 0 && inst->pRunClient->WriteBlocks.pBlocks != 0)
					{
						if(inst->nWriteBlockIndex < inst->pRunClient->WriteBlocks.nBlockCount)
						{
							inst->eStep = eSTEP_WRITE;
						}
						else
						{
							inst->nStatus = eBRB_ERR_UA_INVALID_INDEX;
						}
					}
					else
					{
						inst->nStatus = eBRB_ERR_UA_NO_ELEMENTS;
					}
				}
				else
				{
					inst->nStatus = eBRB_ERR_UA_NOT_CONNECTED;
				}
			}
			else
			{
				inst->nStatus = eBRB_ERR_NULL_POINTER;
			}
			break;

		case eSTEP_WRITE:
			// Block lesen
			inst->nStatus  = eBRB_ERR_BUSY;
			{
				BrbUaRcWriteBlockIntern_TYP* pWriteBlock = (((BrbUaRcWriteBlockIntern_TYP*)inst->pRunClient->WriteBlocks.pBlocks)  + inst->nWriteBlockIndex);
				inst->fbUaClt_WriteBulk.Execute = 1;
				inst->fbUaClt_WriteBulk.ConnectionHdl = inst->pRunClient->Connection.nConnectionHandle;
				inst->fbUaClt_WriteBulk.NodeIDCount = pWriteBlock->nWriteItemCount;
				inst->fbUaClt_WriteBulk.NodeIDs = pWriteBlock->pWiNodeIds;
				inst->fbUaClt_WriteBulk.NodeAddInfo = pWriteBlock->pWiNodeAddInfos;
				inst->fbUaClt_WriteBulk.Variables = pWriteBlock->pWiVariables;
				inst->fbUaClt_WriteBulk.NodeErrorIDs = pWriteBlock->pWiNodeErrorIds;
				inst->fbUaClt_WriteBulk.Timeout = inst->pRunClient->Cfg.tAccessTimeout;
			}
			inst->eStep = eSTEP_WRITE_WAIT;
			break;
		
		case eSTEP_WRITE_WAIT:
			// Warten, bis Block gelesen wurde
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->fbUaClt_WriteBulk.Done == 1)
			{
				inst->fbUaClt_WriteBulk.Execute = 0;
				inst->nStatus  = eBRB_ERR_OK;
				inst->nErrorId = inst->fbUaClt_WriteBulk.ErrorID;
				BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
				inst->nWriteCount++;
				inst->eStep = eSTEP_INIT;
			}
			else if(inst->fbUaClt_WriteBulk.Error == 1)
			{
				inst->fbUaClt_WriteBulk.Execute = 0;
				inst->nStatus  = eBRB_ERR_UA_ERROR;
				inst->nErrorId = inst->fbUaClt_WriteBulk.ErrorID;
				if(inst->nErrorId == 0)
				{
					// Fehler trat bei einem Item auf
					BrbUaRcWriteBlockIntern_TYP* pWriteBlock = (((BrbUaRcWriteBlockIntern_TYP*)inst->pRunClient->WriteBlocks.pBlocks)  + inst->nWriteBlockIndex);
					UINT nItemIndex = 0;
					for(nItemIndex=0; nItemIndex<pWriteBlock->nWriteItemCount; nItemIndex++)
					{
						DWORD nErrorId = *(((DWORD*)pWriteBlock->pWiNodeErrorIds) + nItemIndex);
						if(nErrorId != 0)
						{
							inst->nErrorId = nErrorId;
							break;
						}
					}
				}
				BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
				inst->eStep = eSTEP_INIT;
			}
			break;

	}

	// Aufruf aller FB's
	UaClt_WriteBulk(&inst->fbUaClt_WriteBulk);
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

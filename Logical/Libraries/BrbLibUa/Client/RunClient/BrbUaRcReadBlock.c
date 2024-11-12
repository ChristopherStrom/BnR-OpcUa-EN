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
	eSTEP_READ,
	eSTEP_READ_WAIT,
};

/* Liest eine ReadBlock vom Server */
void BrbUaRcReadBlock(struct BrbUaRcReadBlock* inst)
{
	switch(inst->eStep)
	{
		case eSTEP_INIT:
			// Fub initialisieren
			inst->nStatus =  eBRB_ERR_BUSY;
			inst->nErrorId = 0x00000000; // Good
			BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
			memset(&inst->fbUaClt_ReadBulk, 0, sizeof(inst->fbUaClt_ReadBulk));
			// Parameter prüfen
			if(inst->pRunClient != 0)
			{
				if(inst->pRunClient->State.eClientState == eBRB_RCCLTSTATE_CONNECTED && inst->pRunClient->Connection.nConnectionHandle != 0)
				{
					if(inst->pRunClient->ReadBlocks.nBlockCount > 0 && inst->pRunClient->ReadBlocks.pBlocks != 0)
					{
						if(inst->nReadBlockIndex < inst->pRunClient->ReadBlocks.nBlockCount)
						{
							inst->eStep = eSTEP_READ;
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

		case eSTEP_READ:
			// Block lesen
			inst->nStatus  = eBRB_ERR_BUSY;
			{
				BrbUaRcReadBlockIntern_TYP* pReadBlock = (((BrbUaRcReadBlockIntern_TYP*)inst->pRunClient->ReadBlocks.pBlocks)  + inst->nReadBlockIndex);
				inst->fbUaClt_ReadBulk.Execute = 1;
				inst->fbUaClt_ReadBulk.ConnectionHdl = inst->pRunClient->Connection.nConnectionHandle;
				inst->fbUaClt_ReadBulk.NodeIDCount = pReadBlock->nReadItemCount;
				inst->fbUaClt_ReadBulk.NodeIDs = pReadBlock->pRiNodeIds;
				inst->fbUaClt_ReadBulk.NodeAddInfo = pReadBlock->pRiNodeAddInfos;
				inst->fbUaClt_ReadBulk.Variables = pReadBlock->pRiVariables;
				inst->fbUaClt_ReadBulk.NodeErrorIDs = pReadBlock->pRiNodeErrorIds;
				inst->fbUaClt_ReadBulk.TimeStamps = pReadBlock->pRiTimestamps;
				inst->fbUaClt_ReadBulk.Timeout = inst->pRunClient->Cfg.tAccessTimeout;
			}
			inst->eStep = eSTEP_READ_WAIT;
			break;
		
		case eSTEP_READ_WAIT:
			// Warten, bis Block gelesen wurde
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->fbUaClt_ReadBulk.Done == 1)
			{
				inst->fbUaClt_ReadBulk.Execute = 0;
				inst->nStatus  = eBRB_ERR_OK;
				inst->nErrorId = inst->fbUaClt_ReadBulk.ErrorID;
				BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
				inst->nReadCount++;
				inst->eStep = eSTEP_INIT;
			}
			else if(inst->fbUaClt_ReadBulk.Error == 1)
			{
				inst->fbUaClt_ReadBulk.Execute = 0;
				inst->nStatus  = eBRB_ERR_UA_ERROR;
				inst->nErrorId = inst->fbUaClt_ReadBulk.ErrorID;
				if(inst->nErrorId == 0)
				{
					// Fehler trat bei einem Item auf
					BrbUaRcReadBlockIntern_TYP* pReadBlock = (((BrbUaRcReadBlockIntern_TYP*)inst->pRunClient->ReadBlocks.pBlocks)  + inst->nReadBlockIndex);
					UINT nItemIndex = 0;
					for(nItemIndex=0; nItemIndex<pReadBlock->nReadItemCount; nItemIndex++)
					{
						DWORD nErrorId = *(((DWORD*)pReadBlock->pRiNodeErrorIds) + nItemIndex);
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
	UaClt_ReadBulk(&inst->fbUaClt_ReadBulk);
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

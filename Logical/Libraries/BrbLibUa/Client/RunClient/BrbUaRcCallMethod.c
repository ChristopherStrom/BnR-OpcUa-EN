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
	eSTEP_CALL,
	eSTEP_CALL_WAIT,
};

/* Liest eine WriteBlock vom Server */
void BrbUaRcCallMethod(struct BrbUaRcCallMethod* inst)
{
	switch(inst->eStep)
	{
		case eSTEP_INIT:
			// Fub initialisieren
			inst->nStatus =  eBRB_ERR_BUSY;
			inst->nErrorId = 0x00000000; // Good
			BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
			memset(&inst->fbUA_MethodCall, 0, sizeof(inst->fbUA_MethodCall));
			inst->bInit = 0;
			// Parameter prüfen
			if(inst->pRunClient != 0)
			{
				if(inst->pRunClient->State.eClientState == eBRB_RCCLTSTATE_CONNECTED && inst->pRunClient->Connection.nConnectionHandle != 0)
				{
					if(inst->pRunClient->Methods.nMethodCount > 0 && inst->pRunClient->Methods.pMethods != 0)
					{
						if(inst->nMethodIndex < inst->pRunClient->Methods.nMethodCount)
						{
							inst->bInit = 1;
							inst->eStep = eSTEP_CALL;
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

		case eSTEP_CALL:
			// Methode aufrufen
			inst->nStatus  = eBRB_ERR_BUSY;
			inst->bInit = 0;
			BrbUaRcMethodIntern_TYP* pMethod = (((BrbUaRcMethodIntern_TYP*)inst->pRunClient->Methods.pMethods)  + inst->nMethodIndex);
			inst->fbUA_MethodCall.Execute = 1;
			inst->fbUA_MethodCall.ConnectionHdl = inst->pRunClient->Connection.nConnectionHandle;
			inst->fbUA_MethodCall.MethodHdl = pMethod->nMethodHandle;
			inst->fbUA_MethodCall.Timeout = pMethod->tTimeout;
			memset(&inst->aInputArguments, 0, sizeof(inst->aInputArguments));
			inst->fbUA_MethodCall.InputArguments = (void*)&inst->aInputArguments;
			if(pMethod->nInputArgsCount > 0 && pMethod->pInputArguments != 0)
			{
				for(inst->nArgumentIndex=0; inst->nArgumentIndex<pMethod->nInputArgsCount; inst->nArgumentIndex++)
				{
					UAMethodArgument* pArgument = ((UAMethodArgument*)pMethod->pInputArguments) + inst->nArgumentIndex;
					memcpy(&inst->aInputArguments[inst->nArgumentIndex], pArgument, sizeof(UAMethodArgument));
				}
			}
			memset(&inst->aOutputArguments, 0, sizeof(inst->aOutputArguments));
			inst->fbUA_MethodCall.OutputArguments = (void*)&inst->aOutputArguments;
			if(pMethod->nOutputArgsCount > 0 && pMethod->pOutputArguments != 0)
			{
				for(inst->nArgumentIndex=0; inst->nArgumentIndex<pMethod->nOutputArgsCount; inst->nArgumentIndex++)
				{
					UAMethodArgument* pArgument = ((UAMethodArgument*)pMethod->pOutputArguments) + inst->nArgumentIndex;
					memcpy(&inst->aOutputArguments[inst->nArgumentIndex], pArgument, sizeof(UAMethodArgument));
				}
			}
			inst->eStep = eSTEP_CALL_WAIT;
			break;
		
		case eSTEP_CALL_WAIT:
			// Warten, bis Block gelesen wurde
			inst->nStatus  = eBRB_ERR_BUSY;
			if(inst->fbUA_MethodCall.Done == 1)
			{
				inst->fbUA_MethodCall.Execute = 0;
				inst->nStatus  = eBRB_ERR_OK;
				inst->nErrorId = inst->fbUA_MethodCall.ErrorID;
				BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
				inst->nCallCount++;
				inst->eStep = eSTEP_INIT;
			}
			else if(inst->fbUA_MethodCall.Error == 1)
			{
				inst->fbUA_MethodCall.Execute = 0;
				inst->nStatus  = eBRB_ERR_UA_ERROR;
				inst->nErrorId = inst->fbUA_MethodCall.ErrorID;
				BrbUaGetStatusCodeText(inst->nErrorId, inst->sErrorId, sizeof(inst->nErrorId));
				inst->eStep = eSTEP_INIT;
			}
			break;

	}

	// Aufruf aller FB's
	UA_MethodCall(&inst->fbUA_MethodCall);
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

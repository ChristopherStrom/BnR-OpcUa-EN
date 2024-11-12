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

/* Gibt ein ermitteltes EventField zurück */
unsigned short BrbUaRcGetEventField(struct BrbUaRunClient_TYP* pRunClient, unsigned short nSubscriptionIndex, unsigned short nEventItemIndex, unsigned short nEventFieldIndex, struct BrbUaRcEventField_TYP* pEventField)
{
	UINT nStatus = eBRB_ERR_NULL_POINTER;
	if(pRunClient != 0 && pEventField != 0)
	{
		memset(pEventField, 0, sizeof(BrbUaRcEventField_TYP));
		nStatus = eBRB_ERR_UA_NO_ELEMENTS;
		if(pRunClient->Subscriptions.nSubscriptionCount > 0 && pRunClient->Subscriptions.pSubscriptions != 0)
		{
			nStatus = eBRB_ERR_UA_INVALID_INDEX;
			if(nSubscriptionIndex < pRunClient->Subscriptions.nSubscriptionCount)
			{
				nStatus = eBRB_ERR_UA_NO_ELEMENTS;
				BrbUaRcSubscriptionIntern_TYP* pSubscription = ((BrbUaRcSubscriptionIntern_TYP*)pRunClient->Subscriptions.pSubscriptions) + nSubscriptionIndex;
				if(pSubscription->nEventItemCount > 0 && pSubscription->pEventItems != 0)
				{
					nStatus = eBRB_ERR_UA_INVALID_INDEX;
					if(nEventItemIndex < pSubscription->nEventItemCount)
					{
						nStatus = eBRB_ERR_UA_NO_ELEMENTS;
						BrbUaRcEventItemIntern_TYP* pEventItem = ((BrbUaRcEventItemIntern_TYP*)pSubscription->pEventItems) + nEventItemIndex;
						if(pEventItem->nEventFieldCount > 0 && pEventItem->pEfFieldSelections != 0 && pEventItem->pEfFieldVars != 0)
						{
							nStatus = eBRB_ERR_UA_INVALID_INDEX;
							if(nEventFieldIndex < pEventItem->nEventFieldCount)
							{
								nStatus = eBRB_ERR_OK;
								pEventField->nDatObjNamespaceIndex = *(((UINT*)pEventItem->pEfDatObjNamespaceIndices) + nEventFieldIndex);
								UARelativePath* pSelection = ((UARelativePath*)pEventItem->pEfFieldSelections) + nEventFieldIndex;
								memcpy(&pEventField->FieldSelection, pSelection, sizeof(UARelativePath));
								STRING sVarName[nBRBUA_VARNAME_TEXT_CHAR_MAX+1];
								STRING* pVar = (STRING*)((USINT*)pEventItem->pEfFieldVars) + (nEventFieldIndex * sizeof(sVarName));
								BrbStringCopy(pEventField->sVar, pVar, sizeof(pEventField->sVar));
							}
						}
					}
				}
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

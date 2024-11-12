/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbIpToNumericalArray.c
 * Author: niedermeierr
 * Created: July 05, 2022
 ********************************************************************
 * Implementation of library BrbLib
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLib.h"
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Wandelt eine textuelle Ip-Adresse in ein USINT-Array */
unsigned short BrbIpToNumericalArray(plcstring* pIp, unsigned long pUsintArray)
{
	// Prüfung der Parameter
	if(pIp == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	if(pUsintArray == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	// Die einzelnen Segemente in ein String-Array kopieren
	STRING asIp[4][nBRB_IP_ADR_CHAR_MAX];
	BrbStringSplitEmpty(pIp, ".", (UDINT)&asIp, 3, sizeof(asIp[0]));
	// Die einzelnen Segemente in USINT wandeln
	UINT nIndex = 0;
	for(nIndex=0; nIndex<=3; nIndex++)
	{
		*(((USINT*)pUsintArray)+nIndex) = (USINT)brsatoi((UDINT)&asIp[nIndex]);
	}
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbCheckIpEqualSubnet.c
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

/* Prüft, ob zwei Ip-Adressen im selben Subnet sind */
plcbit BrbCheckIpEqualSubnet(plcstring* pIp1, plcstring* pSubnet1, plcstring* pIp2, plcstring* pSubnet2)
{
	BOOL bResult = 1;
	// Ip's und Subnets in numerische Arrays wandeln
	USINT anIp1[4];			BrbIpToNumericalArray(pIp1, (UDINT)&anIp1);
	USINT anSubnet1[4];	BrbIpToNumericalArray(pSubnet1, (UDINT)&anSubnet1);
	USINT anIp2[4];			BrbIpToNumericalArray(pIp2, (UDINT)&anIp2);
	USINT anSubnet2[4];	BrbIpToNumericalArray(pSubnet2, (UDINT)&anSubnet2);
	// Vergleich der Netz-Anteile (durch Verundung mit dem Subnet wird der Host-Anteil elimniert)
	UINT nIndex = 0;
	for(nIndex=0; nIndex<=3; nIndex++)
	{
		// Subnet verodern (das Subnet gibt den Netz-Anteil an, somit wird der gemeinsame Netz-Anteil zum Vergleich verwendet)
		USINT nSubnet = anSubnet1[nIndex] | anSubnet2[nIndex];
		// Vergleich
		USINT nIp1 = anIp1[nIndex] & nSubnet;
		USINT nIp2 = anIp2[nIndex] & nSubnet;
		if(nIp1 != nIp2)
		{
			bResult = 0;
			break;
		}
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

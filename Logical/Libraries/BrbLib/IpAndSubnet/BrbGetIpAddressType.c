/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbGetIpAddressType.c
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

/* Gibt den Typen einer Ip-Adresse zurück (Netzwerk-oder Broadcast-Adresse) */
enum BrbIpAdrType_ENUM BrbGetIpAddressType(plcstring* pIp, plcstring* pSubnet)
{
	BrbIpAdrType_ENUM eResult = eBRB_IP_ADR_TYPE_UNKNOWN;
	// Ip und Subnet in numerische Arrays wandeln
	USINT anIp[4];			BrbIpToNumericalArray(pIp, (UDINT)&anIp);
	USINT anSubnet[4];	BrbIpToNumericalArray(pSubnet, (UDINT)&anSubnet);
	USINT anSubnetComplement[4];
	USINT anNetworkIp[4];
	USINT anBroadcastIp[4];
	UINT nIndex = 0;
	for(nIndex=0; nIndex<=3; nIndex++)
	{
		// Komplement des Subnets bilden (Bits umkehren), um so den Host-Anteil zu bekommen
		anSubnetComplement[nIndex] = ~anSubnet[nIndex];
		// Netzwerk-Adresse aufgrund des Subnets ermitteln (kleinste Adresse des Host-Bereichs)
		anNetworkIp[nIndex] = (anIp[nIndex] & anSubnet[nIndex]);
		// Broadcast-Adresse aufgrund des Subnets ermitteln (größte Adresse des Host-Bereichs)
		anBroadcastIp[nIndex] = (anIp[nIndex] & anSubnet[nIndex]) | anSubnetComplement[nIndex]; // NOLINT(hicpp-signed-bitwise)
	}
	// Vergleich mit den ermittelten Adressen
	UDINT* pIpUdint = (UDINT*)&anIp; // NOLINT(clang-diagnostic-cast-align)
	UDINT* pNetworkIpUdint = (UDINT*)&anNetworkIp; // NOLINT(clang-diagnostic-cast-align)
	UDINT* pBroadcastIpUdint = (UDINT*)&anBroadcastIp; // NOLINT(clang-diagnostic-cast-align)
	// Da auf direkte Gleichheit geprüft werden muss, können die 4 Byte-Segmente jeweils vereinfacht als UDINT (ebenfalls 4 Byte) verglichen werden
	// NOLINTBEGIN(bugprone-branch-clone)
	if(*pIpUdint == 0)
	{
		eResult = eBRB_IP_ADR_TYPE_UNKNOWN;
	}
	else if(*pIpUdint == nBRB_UDINT_MAX)
	{
		eResult = eBRB_IP_ADR_TYPE_UNKNOWN;
	}
	else if(*pIpUdint == *pNetworkIpUdint)
	{
		eResult = eBRB_IP_ADR_TYPE_NETWORK;
	}
	else if(*pIpUdint == *pBroadcastIpUdint)
	{
		eResult = eBRB_IP_ADR_TYPE_BROADCAST;
	}
	else
	{
		eResult = eBRB_IP_ADR_TYPE_HOST;
	}
	// NOLINTEND(bugprone-branch-clone)
	return eResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbCheckSubnet.c
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

/* Prüft eine Subnet-Angabe auf Gültigkeit */
plcbit BrbCheckSubnet(plcstring* pSubnet)
{
	BOOL bResult = 1;
	// Subnet in numerisches Array wandeln
	USINT anSubnet[4];	BrbIpToNumericalArray(pSubnet, (UDINT)&anSubnet);
	// Sobald eine Null im Bitmuster gesetzt ist, dürfen nur noch Nullen folgen 
	UINT nIndex = 0;
	BOOL bFollowingBitsMustBeZero = 0;
	for(nIndex=0; nIndex<=3; nIndex++)
	{
		// Es dürfen nur bestimmte Bitmuster in einem Segment gesetzt sein (nur führende Einsen)
		// NOLINTBEGIN(bugprone-branch-clone)
		if(bFollowingBitsMustBeZero && anSubnet[nIndex] != 0)
		{
			// Keine führende 1
			bResult = 0;
			break;
		}
		else if(anSubnet[nIndex] == 255)
		{
			// Alle Bits des Netzwerk-Anteils gesetzt -> Passt
		}
		else if(anSubnet[nIndex] == 0
		|| anSubnet[nIndex] == 128	// #1000 0000
		|| anSubnet[nIndex] == 192	// #1100 0000
		|| anSubnet[nIndex] == 224	// #1110 0000
		|| anSubnet[nIndex] == 240	// #1111 0000
		|| anSubnet[nIndex] == 248	// #1111 1000
		|| anSubnet[nIndex] == 252	// #1111 1100
		|| anSubnet[nIndex] == 254	// #1111 1110
		)
		{
			// Nur führende Einsen -> Nachfolgende Segmente dürfen kein Bit gesetzt haben
			bFollowingBitsMustBeZero = 1;
		}
		else
		{
			// Keine führende 1
			bResult = 0;
			break;
		}
		// NOLINTEND(bugprone-branch-clone)
	}
	// Zusätzliche Prüfungen
	UDINT* pSubnetUdint = (UDINT*)&anSubnet; // NOLINT(clang-diagnostic-cast-align)
	if(*pSubnetUdint == 0)
	{
		// Nur Nullen sind nicht erlaubt
		bResult = 0;
	}
	if(*pSubnetUdint == nBRB_UDINT_MAX)
	{
		// Nur Einsen sind nicht erlaubt
		bResult = 0;
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbGetStructMemberOffset.c
 * Author: niedermeierr
 * Created: December 21, 2015
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

/* Gibt den Offset eines Struktur-Members zurück */
unsigned short BrbGetStructMemberOffset(plcstring* pStructName, plcstring* pMemberName, unsigned long* pOffset)
{
	UINT nStatus = 0;
	*pOffset = 0;
	// Adresse der Struktur-Instanz ermitteln
	UDINT nAddressStruct = 0;
	UDINT nLen = 0;
	nStatus = PV_xgetadr((STRING*)pStructName, (UDINT*)&nAddressStruct, (UDINT*)&nLen);
	if(nStatus == 0)
	{
		// Adresse der Struktur-Member ermitteln
		UDINT nAddressMember = 0;
		STRING sMember[nBRB_PVNAME_CHAR_MAX];
		BrbStringCopy(sMember, pStructName, sizeof(sMember));
		BrbStringCat(sMember, ".", sizeof(sMember));
		BrbStringCat(sMember, pMemberName, sizeof(sMember));
		nStatus = PV_xgetadr((STRING*)&sMember, (UDINT*)&nAddressMember, (UDINT*)&nLen);
		if(nStatus == 0)
		{
			// Differenz ergibt Offset
			*pOffset = nAddressMember - nAddressStruct;
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

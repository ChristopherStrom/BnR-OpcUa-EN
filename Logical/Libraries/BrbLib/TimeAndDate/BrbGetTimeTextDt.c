/********************************************************************
 * COPYRIGHT -- Bernecker + Rainer
 ********************************************************************
 * Library: BrbLib
 * File: BrbGetTimeTextDt.c
 * Author: niedermeierr
 * Created: June 11, 2013
 ********************************************************************
 * Implementation of library BrbLib
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLib.h"

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Gibt die angegebene DT-Zeit als Text zurück */
unsigned short BrbGetTimeTextDt(plcdt dtTime, plcstring* pText, unsigned long nTextSize, plcstring* pFormat)
{
	if(pText == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	if(nTextSize == 0)
	{
		return eBRB_ERR_INVALID_PARAMETER;
	}
	if(pFormat == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	// Text ermitteln
	DTStructure DtStruct;
	DT_TO_DTStructure(dtTime, (UDINT)&DtStruct);	
	return BrbGetTimeTextDtStruct(&DtStruct, pText, nTextSize, pFormat);
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

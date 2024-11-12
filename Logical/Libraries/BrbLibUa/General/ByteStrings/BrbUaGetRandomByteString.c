#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLibUa.h"
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Erzeugt einen zufälligen ByteString */
plcdword BrbUaGetRandomByteString(unsigned char* pData, signed long nLength)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pData != 0)
	{
		nStatus = 0x803C0000; // = Bad_OutOfRange
		if(nLength > 0)
		{
			nStatus = 0x00000000; // = Good
			DINT nIndex = 0;
			for(nIndex=0; nIndex<nLength; nIndex++)
			{
				*(pData + nIndex) = (USINT)BrbGetRandomDint(0, 255);
			}
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

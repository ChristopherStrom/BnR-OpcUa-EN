#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLibUa.h"
#include <AnsiCFunc.h>
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Inkrementiert einen ByteString */
plcdword BrbUaIncByteString(unsigned char* pData, signed long nLength)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pData != 0)
	{
		nStatus = 0x803C0000; // = Bad_OutOfRange
		if(nLength > 0)
		{
			nStatus = 0x00000000; // = Good
			DINT nIndex = nLength - 1;
			BOOL bLeave = 0;
			do
			{
				USINT* pValue = (USINT*)pData + nIndex;
				if(*pValue < 255)
				{
					*pValue += 1;
					bLeave = 1;
				}
				else
				{
					*pValue = 0;
					nIndex -= 1;
					if(nIndex < 0)
					{
						// Überlauf -> Wieder bei 0 beginnen
						memset(pData, 0, (UDINT)nLength);
						nStatus = 0xB00C0000; // = PlcOpen_BadElementCount
						bLeave = 1;
					}
				}
			} while (bLeave == 0);
		}
	}
	return nStatus;	
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

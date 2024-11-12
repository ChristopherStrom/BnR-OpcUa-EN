
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

/* Gibt ein Bit eines bitcodierten Byte-Arrays zurück */
plcbit BrbGetByteArrayBit(unsigned long pByteArray, unsigned long nIndexMax, unsigned long nBitNumber)
{
	BOOL bResult = 0;
	if(pByteArray != 0)
	{
		UINT nByteIndex = (UINT)(nBitNumber / nBRB_BITS_PER_BYTE);
		if(nByteIndex <= nIndexMax)
		{
			UINT nByteBitNumber = (UINT)(nBitNumber - (nByteIndex * nBRB_BITS_PER_BYTE));
			USINT* pByte = ((USINT*)pByteArray) + nByteIndex;
			bResult = (*pByte & ((USINT)1 << nByteBitNumber)) > 0; // NOLINT(hicpp-signed-bitwise)
		}
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

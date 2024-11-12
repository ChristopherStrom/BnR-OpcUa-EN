
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

/* Setzt ein Bit in einem bitcodierten Byte-Array */
plcbit BrbSetByteArrayBit(unsigned long pByteArray, unsigned long nIndexMax, unsigned long nBitNumber, plcbit bBit)
{
	BOOL bResult = 0;
	if(pByteArray != 0)
	{
		UINT nByteIndex = (UINT)(nBitNumber / nBRB_BITS_PER_BYTE);
		if(nByteIndex <= nIndexMax)
		{
			UINT nByteBitNumber = (UINT)(nBitNumber - ((UDINT)nByteIndex * (UDINT)nBRB_BITS_PER_BYTE));
			USINT* pByte = ((USINT*)pByteArray) + nByteIndex;
			bResult = (*pByte & ((USINT)1 << nByteBitNumber)) > 0; // NOLINT(hicpp-signed-bitwise)
			if(bBit == 1)
			{
				*pByte = *pByte | (USINT)((USINT)1 << nByteBitNumber); // NOLINT(hicpp-signed-bitwise)
			}
			else
			{
				*pByte = *pByte & ~(USINT)((USINT)1 << nByteBitNumber); // NOLINT(hicpp-signed-bitwise)
			}
		}
	}
	return bResult;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

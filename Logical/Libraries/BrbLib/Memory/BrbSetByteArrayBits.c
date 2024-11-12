
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

/* Setzte Bits in einem bitcodierten Byte-Array */
plcbit BrbSetByteArrayBits(unsigned long pByteArray, unsigned long nIndexMax, unsigned long nBitNumberFrom, unsigned long nBitNumberTo, plcbit bBit)
{
	if(pByteArray != 0)
	{
		if(nBitNumberTo < nBitNumberFrom)
		{
			UDINT nHelp = nBitNumberTo;
			nBitNumberTo = nBitNumberFrom;
			nBitNumberFrom = nHelp;
		}
		UDINT nBitNumber = 0;
		for(nBitNumber=nBitNumberFrom; nBitNumber<=nBitNumberTo; nBitNumber++)
		{
			UINT nByteIndex = (UINT)(nBitNumber / nBRB_BITS_PER_BYTE);
			if(nByteIndex <= nIndexMax)
			{
				UINT nByteBitNumber = (UINT)(nBitNumber - ((UDINT)nByteIndex * (UDINT)nBRB_BITS_PER_BYTE));
				USINT* pByte = ((USINT*)pByteArray) + nByteIndex;
				if(bBit == 1)
				{
					*pByte = *pByte | (USINT)((USINT)1 << nByteBitNumber); // NOLINT(hicpp-signed-bitwise)
				}
				else
				{
					*pByte = *pByte & ~(USINT)((USINT)1 << nByteBitNumber); // NOLINT(hicpp-signed-bitwise)
				}
			}
			else
			{
				break;
			}
		}
	}
	return bBit;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

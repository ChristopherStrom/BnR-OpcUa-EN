
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

/* Addiert zwei Zahlen, welche als Byte-Array abgelegt sind */
signed long BrbByteArrayAdd(unsigned char* pByteArray0, unsigned long nLength0, unsigned char* pByteArray1, unsigned long nLength1)
{
	if(pByteArray0 == 0 || pByteArray1 == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	UDINT nLength = nLength0;
	if(nLength1 > nLength0)
	{
		nLength = nLength1;
	}
	UDINT nBitNumberMax = nLength * nBRB_BITS_PER_BYTE;
	UDINT nBitNumber = 0;
	BOOL bBitOverflow = 0;
	for(nBitNumber=0; nBitNumber<nBitNumberMax; nBitNumber++)
	{
		BOOL bBitValue0 = BrbGetByteArrayBit((UDINT)pByteArray0, nBitNumberMax, nBitNumber);
		BOOL bBitValue1 = BrbGetByteArrayBit((UDINT)pByteArray1, nBitNumberMax, nBitNumber);
		BOOL bBitResult = bBitValue0 ^ bBitValue1; // XOR rechnet beide Operanden
		bBitResult = bBitResult ^ bBitOverflow; // XOR rechnet Overflow ein
		BrbSetByteArrayBit((UDINT)pByteArray0, nBitNumberMax, nBitNumber, bBitResult);
		USINT nOverflow = (USINT)bBitValue0 + (USINT)bBitValue1 + (USINT)bBitOverflow;
		// Overflow für die nächste Stelle ermitteln
		bBitOverflow = 0;
		if(nOverflow > 1)
		{
			// Mehr als 1 Bit gesetzt -> Overflow für die nächste Stelle
			bBitOverflow = 1;
		}
	}
	if(bBitOverflow == 1)
	{
		return eBRB_ERR_OVERFLOW;	
	}
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

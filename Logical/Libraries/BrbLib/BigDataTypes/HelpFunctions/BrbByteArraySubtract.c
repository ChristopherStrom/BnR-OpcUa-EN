
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

/* Subtrahiert zwei Zahlen, welche als Byte-Array abgelegt sind */
signed long BrbByteArraySubtract(unsigned char* pByteArray0, unsigned long nLength0, unsigned char* pByteArray1, unsigned long nLength1)
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
		SINT nResult = (SINT)bBitValue0 - (SINT)bBitValue1 - (SINT)bBitOverflow; // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)
		BOOL bBitResult = 0;
		bBitOverflow = 0;
		if(nResult == 1)
		{
			bBitResult = 1;
		}
		else if(nResult == 0)
		{
			bBitResult = 0;
		}
		else if(nResult == -1)
		{
			bBitResult = 1;
			bBitOverflow = 1;
		}
		else
		{
			bBitResult = 0;
			bBitOverflow = 1;
		}
		BrbSetByteArrayBit((UDINT)pByteArray0, nBitNumberMax, nBitNumber, bBitResult);
	}
	if(bBitOverflow == 1)
	{
		return eBRB_ERR_OVERFLOW;	
	}
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

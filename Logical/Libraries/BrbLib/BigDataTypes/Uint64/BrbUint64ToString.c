
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

typedef struct BrbUint64ToStringMatrixEntry_TYP
{	
	unsigned long nBitMask;
	STRING sValueHigh[nBRB_UINT64_CHAR_MAX];
} BrbUint64ToStringMatrixEntry_TYP;

// Die Matrix enthält für alle Bit-Wertigkeiten (0..31) den IntegerString für High
const BrbUint64ToStringMatrixEntry_TYP BRBR_UINT64_TOSTRING_MATRIX[32] = 
	{
	//							 nBitMask,	 sValueHigh
	/* Bit0  */			{0x00000001, "4294967296"},
	/* Bit1  */			{0x00000002, "8589934592"},
	/* Bit2  */			{0x00000004, "17179869184"},
	/* Bit3  */			{0x00000008, "34359738368"},
	/* Bit4  */			{0x00000010, "68719476736"},
	/* Bit5  */			{0x00000020, "137438953472"},
	/* Bit6  */			{0x00000040, "274877906944"},
	/* Bit7  */			{0x00000080, "549755813888"},
	/* Bit8  */			{0x00000100, "1099511627776"},
	/* Bit9  */			{0x00000200, "2199023255552"},
	/* Bit10 */			{0x00000400, "4398046511104"},
	/* Bit11 */			{0x00000800, "8796093022208"},
	/* Bit12 */			{0x00001000, "17592186044416"},
	/* Bit13 */			{0x00002000, "35184372088832"},
	/* Bit14 */			{0x00004000, "70368744177664"},
	/* Bit15 */			{0x00008000, "140737488355328"},
	/* Bit16 */			{0x00010000, "281474976710656"},
	/* Bit17 */			{0x00020000, "562949953421312"},
	/* Bit18 */			{0x00040000, "1125899906842624"},
	/* Bit19 */			{0x00080000, "2251799813685248"},
	/* Bit20 */			{0x00100000, "4503599627370496"},
	/* Bit21 */			{0x00200000, "9007199254740992"},
	/* Bit22 */			{0x00400000, "18014398509481984"},
	/* Bit23 */			{0x00800000, "36028797018963968"},
	/* Bit24 */			{0x01000000, "72057594037927936"},
	/* Bit25 */			{0x02000000, "144115188075855872"},
	/* Bit26 */			{0x04000000, "288230376151711744"},
	/* Bit27 */			{0x08000000, "576460752303423488"},
	/* Bit28 */			{0x10000000, "1152921504606846976"},
	/* Bit29 */			{0x20000000, "2305843009213693952"},
	/* Bit30 */			{0x40000000, "4611686018427387904"},
	/* Bit31 */			{0x80000000, "9223372036854775808"},
	};

/* Wandelt einen Uint64-Wert zu einem String */
signed long BrbUint64ToString(struct BrbUint64_TYP* pUint64, plcstring* pText, unsigned long nTextSize)
{
	if(pUint64 == 0 || pText == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	if(nTextSize < nBRB_UINT64_CHAR_MAX)
	{
		return eBRB_ERR_STRING_TOO_SHORT;
	}
	// Wandlung Low
	BrbUdintToAscii(pUint64->nLow, pText);
	// Wandlung High
	// Der C-Befehl sprintf ist leider auf der Sps nicht erlaubt. Daher wird für jedes der 32 Bits die Wertigkeit addiert.
	USINT nBit = 0;
	for(nBit=0; nBit<=31; nBit++)
	{
		const BrbUint64ToStringMatrixEntry_TYP* pMatrixEntry = &BRBR_UINT64_TOSTRING_MATRIX[nBit];
		if(pUint64->nHigh & pMatrixEntry->nBitMask)
		{
			BrbIntegerStringAdd(pText, (STRING*)&pMatrixEntry->sValueHigh, nBRB_UINT64_CHAR_MAX);
		}
	}
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

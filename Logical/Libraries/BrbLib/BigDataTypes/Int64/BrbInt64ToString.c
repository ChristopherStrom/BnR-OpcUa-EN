
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
	STRING sValueLow[nBRB_INT64_CHAR_MAX];
	STRING sValueHigh[nBRB_INT64_CHAR_MAX];
} BrbInt64ToStringMatrixEntry_TYP;

// Die Matrix enthält für alle Bit-Wertigkeiten (0..31) den IntegerString für Low und High
const BrbInt64ToStringMatrixEntry_TYP BRBR_INT64_TOSTRING_MATRIX[32] = 
	{
	//							 nBitMask,	 sValueLow,			sValueHigh
	/* Bit0  */			{0x00000001, "1",						"4294967296"},
	/* Bit1  */			{0x00000002, "2",						"8589934592"},
	/* Bit2  */			{0x00000004, "4",						"17179869184"},
	/* Bit3  */			{0x00000008, "8",						"34359738368"},
	/* Bit4  */			{0x00000010, "16",					"68719476736"},
	/* Bit5  */			{0x00000020, "32",					"137438953472"},
	/* Bit6  */			{0x00000040, "64",					"274877906944"},
	/* Bit7  */			{0x00000080, "128",					"549755813888"},
	/* Bit8  */			{0x00000100, "256",					"1099511627776"},
	/* Bit9  */			{0x00000200, "512",					"2199023255552"},
	/* Bit10 */			{0x00000400, "1024",				"4398046511104"},
	/* Bit11 */			{0x00000800, "2048",				"8796093022208"},
	/* Bit12 */			{0x00001000, "4096",				"17592186044416"},
	/* Bit13 */			{0x00002000, "8192",				"35184372088832"},
	/* Bit14 */			{0x00004000, "16384",				"70368744177664"},
	/* Bit15 */			{0x00008000, "32768",				"140737488355328"},
	/* Bit16 */			{0x00010000, "65536",				"281474976710656"},
	/* Bit17 */			{0x00020000, "131072",			"562949953421312"},
	/* Bit18 */			{0x00040000, "262144",			"1125899906842624"},
	/* Bit19 */			{0x00080000, "524288",			"2251799813685248"},
	/* Bit20 */			{0x00100000, "1048576",			"4503599627370496"},
	/* Bit21 */			{0x00200000, "2097152",			"9007199254740992"},
	/* Bit22 */			{0x00400000, "4194304",			"18014398509481984"},
	/* Bit23 */			{0x00800000, "8388608",			"36028797018963968"},
	/* Bit24 */			{0x01000000, "16777216",		"72057594037927936"},
	/* Bit25 */			{0x02000000, "33554432",		"144115188075855872"},
	/* Bit26 */			{0x04000000, "67108864",		"288230376151711744"},
	/* Bit27 */			{0x08000000, "134217728",		"576460752303423488"},
	/* Bit28 */			{0x10000000, "268435456",		"1152921504606846976"},
	/* Bit29 */			{0x20000000, "536870912",		"2305843009213693952"},
	/* Bit30 */			{0x40000000, "1073741824",	"4611686018427387904"},
	/* Bit31 */			{0x80000000, "2147483648",	"0"}
	};

/* Wandelt einen Int64-Wert zu einem String */
signed long BrbInt64ToString(struct BrbInt64_TYP* pInt64, plcstring* pText, unsigned long nTextSize) // NOLINT(readability-function-cognitive-complexity)
{
	if(pInt64 == 0 || pText == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	if(nTextSize < nBRB_INT64_CHAR_MAX)
	{
		return eBRB_ERR_STRING_TOO_SHORT;
	}
	// Der C-Befehl sprintf ist leider auf der Sps nicht erlaubt.  Daher wird für jedes der 31 Bits die Wertigkeit addiert.
	if((pInt64->nHigh & 0x80000000) == 0)
	{
		// Positiv
		// Wandlung Low
		BrbUdintToAscii(pInt64->nLow, pText);
		// Wandlung High
		USINT nBit = 0;
		for(nBit=0; nBit<=30; nBit++)
		{
			const BrbInt64ToStringMatrixEntry_TYP* pMatrixEntry = &BRBR_INT64_TOSTRING_MATRIX[nBit];
			if(pInt64->nHigh & pMatrixEntry->nBitMask)
			{
				BrbIntegerStringAdd(pText, (STRING*)&pMatrixEntry->sValueHigh, nBRB_INT64_CHAR_MAX);
			}
		}
	}
	else
	{
		// Negativ
		// Wandlung Low
		BrbStringCopy(pText, "0", nBRB_INT64_CHAR_MAX+1);
		BrbIntegerStringAdd(pText, "1", nBRB_INT64_CHAR_MAX+1);
		USINT nBit = 0;
		for(nBit=0; nBit<=31; nBit++)
		{
			const BrbInt64ToStringMatrixEntry_TYP* pMatrixEntry = &BRBR_INT64_TOSTRING_MATRIX[nBit];
			if((pInt64->nLow & pMatrixEntry->nBitMask) == 0)
			{
				BrbIntegerStringAdd(pText, (STRING*)&pMatrixEntry->sValueLow, nBRB_INT64_CHAR_MAX);
			}
		}
		// Wandlung High
		for(nBit=0; nBit<=30; nBit++)
		{
			const BrbInt64ToStringMatrixEntry_TYP* pMatrixEntry = &BRBR_INT64_TOSTRING_MATRIX[nBit];
			if((pInt64->nHigh & pMatrixEntry->nBitMask) == 0)
			{
				BrbIntegerStringAdd(pText, (STRING*)&pMatrixEntry->sValueHigh, nBRB_INT64_CHAR_MAX);
			}
		}
		// Minuszeichen
		BrbStringInsert(pText, 0, "-");
	}
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

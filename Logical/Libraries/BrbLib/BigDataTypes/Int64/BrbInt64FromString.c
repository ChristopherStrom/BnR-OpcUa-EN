
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLib.h"
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

// Die Matrix enthält für alle Dezimal-Wertigkeiten (0..9) jeder Stelle (0..19) die Bit-Wertigkeiten für Low+High
const BrbInt64_TYP nBRB_INT64_VALENCY_MATRIX[19][10] = 
	{
	//																0	Low      , High					1	Low      , High					2	Low      , High					3	Low      , High					4	Low      , High					5	Low      , High					6	Low      , High					7	Low      , High					8	Low      , High					9	Low      , High
	/* 00 = 1  */										{	{0x00000000, 0x00000000}, {0x00000001, 0x00000000}, {0x00000002, 0x00000000}, {0x00000003, 0x00000000}, {0x00000004, 0x00000000}, {0x00000005, 0x00000000}, {0x00000006, 0x00000000}, {0x00000007, 0x00000000}, {0x00000008, 0x00000000}, {0x00000009, 0x00000000}},
	/* 01 = 10 */										{	{0x00000000, 0x00000000}, {0x0000000A, 0x00000000}, {0x00000014, 0x00000000}, {0x0000001E, 0x00000000}, {0x00000028, 0x00000000}, {0x00000032, 0x00000000}, {0x0000003C, 0x00000000}, {0x00000046, 0x00000000}, {0x00000050, 0x00000000}, {0x0000005A, 0x00000000}},
	/* 02 = 100 */									{	{0x00000000, 0x00000000}, {0x00000064, 0x00000000}, {0x000000C8, 0x00000000}, {0x0000012C, 0x00000000}, {0x00000190, 0x00000000}, {0x000001F4, 0x00000000}, {0x00000258, 0x00000000}, {0x000002BC, 0x00000000}, {0x00000320, 0x00000000}, {0x00000384, 0x00000000}},
	/* 03 = 1000 */									{	{0x00000000, 0x00000000}, {0x000003E8, 0x00000000}, {0x000007D0, 0x00000000}, {0x00000BB8, 0x00000000}, {0x00000FA0, 0x00000000}, {0x00001388, 0x00000000}, {0x00001770, 0x00000000}, {0x00001B58, 0x00000000}, {0x00001F40, 0x00000000}, {0x00002328, 0x00000000}},
	/* 04 = 10000 */								{	{0x00000000, 0x00000000}, {0x00002710, 0x00000000}, {0x00004E20, 0x00000000}, {0x00007530, 0x00000000}, {0x00009C40, 0x00000000}, {0x0000C350, 0x00000000}, {0x0000EA60, 0x00000000}, {0x00011170, 0x00000000}, {0x00013880, 0x00000000}, {0x00015F90, 0x00000000}},
	/* 05 = 100000 */								{	{0x00000000, 0x00000000}, {0x000186A0, 0x00000000}, {0x00030D40, 0x00000000}, {0x000493E0, 0x00000000}, {0x00061A80, 0x00000000}, {0x0007A120, 0x00000000}, {0x000927C0, 0x00000000}, {0x000AAE60, 0x00000000}, {0x000C3500, 0x00000000}, {0x000DBBA0, 0x00000000}},
	/* 06 = 1000000 */							{	{0x00000000, 0x00000000}, {0x000F4240, 0x00000000}, {0x001E8480, 0x00000000}, {0x002DC6C0, 0x00000000}, {0x003D0900, 0x00000000}, {0x004C4B40, 0x00000000}, {0x005B8D80, 0x00000000}, {0x006ACFC0, 0x00000000}, {0x007A1200, 0x00000000}, {0x00895440, 0x00000000}},
	/* 07 = 10000000 */							{	{0x00000000, 0x00000000}, {0x00989680, 0x00000000}, {0x01312D00, 0x00000000}, {0x01C9C380, 0x00000000}, {0x02625A00, 0x00000000}, {0x02FAF080, 0x00000000}, {0x03938700, 0x00000000}, {0x042C1D80, 0x00000000}, {0x04C4B400, 0x00000000}, {0x055D4A80, 0x00000000}},
	/* 08 = 100000000 */						{	{0x00000000, 0x00000000}, {0x05F5E100, 0x00000000}, {0x0BEBC200, 0x00000000}, {0x11E1A300, 0x00000000}, {0x17D78400, 0x00000000}, {0x1DCD6500, 0x00000000}, {0x23C34600, 0x00000000}, {0x29B92700, 0x00000000}, {0x2FAF0800, 0x00000000}, {0x35A4E900, 0x00000000}},
	/* 09 = 1000000000 */						{	{0x00000000, 0x00000000}, {0x3B9ACA00, 0x00000000}, {0x77359400, 0x00000000}, {0xB2D05E00, 0x00000000}, {0xEE6B2800, 0x00000000}, {0x2A05F200, 0x00000001}, {0x65A0BC00, 0x00000001}, {0xA13B8600, 0x00000001}, {0xDCD65000, 0x00000001}, {0x18711A00, 0x00000002}},
	/* 10 = 10000000000 */					{	{0x00000000, 0x00000000}, {0x540BE400, 0x00000002}, {0xA817C800, 0x00000004}, {0xFC23AC00, 0x00000006}, {0x502F9000, 0x00000009}, {0xA43B7400, 0x0000000B}, {0xF8475800, 0x0000000D}, {0x4C533C00, 0x00000010}, {0xA05F2000, 0x00000012}, {0xF46B0400, 0x00000014}},
	/* 11 = 100000000000 */					{	{0x00000000, 0x00000000}, {0x4876E800, 0x00000017}, {0x90EDD000, 0x0000002E}, {0xD964B800, 0x00000045}, {0x21DBA000, 0x0000005D}, {0x6A528800, 0x00000074}, {0xB2C97000, 0x0000008B}, {0xFB405800, 0x000000A2}, {0x43B74000, 0x000000BA}, {0x8C2E2800, 0x000000D1}},
	/* 12 = 1000000000000 */				{	{0x00000000, 0x00000000}, {0xD4A51000, 0x000000E8}, {0xA94A2000, 0x000001D1}, {0x7DEF3000, 0x000002BA}, {0x52944000, 0x000003A3}, {0x27395000, 0x0000048C}, {0xFBDE6000, 0x00000574}, {0xD0837000, 0x0000065D}, {0xA5288000, 0x00000746}, {0x79CD9000, 0x0000082F}},
	/* 13 = 10000000000000 */				{	{0x00000000, 0x00000000}, {0x4E72A000, 0x00000918}, {0x9CE54000, 0x00001230}, {0xEB57E000, 0x00001B48}, {0x39CA8000, 0x00002461}, {0x883D2000, 0x00002D79}, {0xD6AFC000, 0x00003691}, {0x25226000, 0x00003FAA}, {0x73950000, 0x000048C2}, {0xC207A000, 0x000051DA}},
	/* 14 = 100000000000000 */			{	{0x00000000, 0x00000000}, {0x107A4000, 0x00005AF3}, {0x20F48000, 0x0000B5E6}, {0x316EC000, 0x000110D9}, {0x41E90000, 0x00016BCC}, {0x52634000, 0x0001C6BF}, {0x62DD8000, 0x000221B2}, {0x7357C000, 0x00027CA5}, {0x83D20000, 0x0002D798}, {0x944C4000, 0x0003328B}},
	/* 15 = 1000000000000000 */			{	{0x00000000, 0x00000000}, {0xA4C68000, 0x00038D7E}, {0x498D0000, 0x00071AFD}, {0xEE538000, 0x000AA87B}, {0x931A0000, 0x000E35FA}, {0x37E08000, 0x0011C379}, {0xDCA70000, 0x001550F7}, {0x816D8000, 0x0018DE76}, {0x26340000, 0x001C6BF5}, {0xCAFA8000, 0x001FF973}},
	/* 16 = 10000000000000000 */		{	{0x00000000, 0x00000000}, {0x6FC10000, 0x002386F2}, {0xDF820000, 0x00470DE4}, {0x4F430000, 0x006A94D7}, {0xBF040000, 0x008E1BC9}, {0x2EC50000, 0x00B1A2BC}, {0x9E860000, 0x00D529AE}, {0x0E470000, 0x00F8B0A1}, {0x7E080000, 0x011C3793}, {0xEDC90000, 0x013FBE85}},
	/* 17 = 100000000000000000 */		{	{0x00000000, 0x00000000}, {0x5D8A0000, 0x01634578}, {0xBB140000, 0x02C68AF0}, {0x189E0000, 0x0429D069}, {0x76280000, 0x058D15E1}, {0xD3B20000, 0x06F05B59}, {0x313C0000, 0x0853A0D2}, {0x8EC60000, 0x09B6E64A}, {0xEC500000, 0x0B1A2BC2}, {0x49DA0000, 0x0C7D713B}},
	/* 18 = 1000000000000000000 */	{	{0x00000000, 0x00000000}, {0xA7640000, 0x0DE0B6B3}, {0x4EC80000, 0x1BC16D67}, {0xF62C0000, 0x29A2241A}, {0x9D900000, 0x3782DACE}, {0x44F40000, 0x45639182}, {0xEC580000, 0x53444835}, {0x93BC0000, 0x6124FEE9}, {0x3B200000, 0x6F05B59D}, {0xE2840000, 0x7CE66C50}},
	};

/* Wandelt einen Int64-Wert zu einem String */
signed long BrbInt64FromString(struct BrbInt64_TYP* pInt64, plcstring* pText) // NOLINT(readability-function-cognitive-complexity)
{
	if(pInt64 == 0 || pText == 0)
	{
		return eBRB_ERR_NULL_POINTER;
	}
	UDINT nTextLen = strlen(pText);
	if(BrbStringStartsWith(pText, "-") == 1)
	{
		// Negative Zahl
		if(nTextLen >= nBRB_INT64_CHAR_MAX)
		{
			return eBRB_ERR_STRING_TOO_LONG;
		}
		pInt64->nLow = 0;
		pInt64->nHigh = 0;
		UDINT nDigit = 0; // Stelle von hinten
		STRING* pChar = 0;
		USINT nDigitVal = 0; // Wert der Stelle als Einer-Wertigkeit
		const BrbInt64_TYP* pOperand = 0; // Zeiger auf die Wertigkeits-Matrix
		for(nDigit=0; nDigit<nTextLen; nDigit++)
		{
			pChar = (STRING*)pText+(nTextLen-1-nDigit);
			if(*pChar >= '0' && *pChar <= '9')
			{
				// Zeichen ist eine Nummer
				nDigitVal = (USINT)(*pChar-'0'); // Wert als Einer-Stelle
				pOperand = &nBRB_INT64_VALENCY_MATRIX[nDigit][nDigitVal];
				BrbByteArraySubtract((USINT*)pInt64, 8, (USINT*)pOperand, 8);
			}
			else
			{
				// Zeichen ist keine Nummer -> Abbrechen
				break;
			}
		}
		if((pInt64->nHigh & 0x80000000) == 0)
		{
			// Unterlauf
			return eBRB_ERR_OVERFLOW;
		}
	}
	else
	{
		// Postive Zahl
		if(nTextLen >= nBRB_INT64_CHAR_MAX-1)
		{
			return eBRB_ERR_STRING_TOO_LONG;
		}
		pInt64->nLow = 0;
		pInt64->nHigh = 0;
		UDINT nDigit = 0; // Stelle von hinten
		STRING* pChar = 0;
		USINT nDigitVal = 0; // Wert der Stelle als Einer-Wertigkeit
		const BrbInt64_TYP* pOperand = 0; // Zeiger auf die Wertigkeits-Matrix
		for(nDigit=0; nDigit<nTextLen; nDigit++)
		{
			pChar = (STRING*)pText+(nTextLen-1-nDigit);
			if(*pChar >= '0' && *pChar <= '9')
			{
				// Zeichen ist eine Nummer
				nDigitVal = (USINT)(*pChar-'0'); // Wert als Einer-Stelle
				pOperand = &nBRB_INT64_VALENCY_MATRIX[nDigit][nDigitVal];
				BrbByteArrayAdd((USINT*)pInt64, 8, (USINT*)pOperand, 8);
				if((pInt64->nHigh & 0x80000000) > 0)
				{
					// Überlauf -> Abbrechen
					return eBRB_ERR_OVERFLOW;
				}
			}
			else
			{
				// Zeichen ist keine Nummer -> Abbrechen
				break;
			}
		}
	}
	return eBRB_ERR_OK;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)


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

/* Erzeugt einen Zufallstext mit bestimmter Länge aus einer Zeichenblockauswahl */
unsigned long BrbGetRandomString(plcstring* pText, unsigned long nTextSize, unsigned long nTextLength, enum BrbRandomString_ENUM eSelection)
{
	USINT anSelection[256];
	memset((USINT*)&anSelection, 0, sizeof(anSelection));
	UINT nChar = 0;
	UINT nSelectionLength = 0;
	if((eSelection & eBRB_RANDOM_STRING_NUMBERS) == eBRB_RANDOM_STRING_NUMBERS) // NOLINT(hicpp-signed-bitwise)
	{
		// 0123456789
		for(nChar=48;nChar<=57;nChar++)
		{
			anSelection[nSelectionLength] = (USINT)nChar;
			nSelectionLength++;
		}
	}
	if((eSelection & eBRB_RANDOM_STRING_UPPER_LETTERS) == eBRB_RANDOM_STRING_UPPER_LETTERS) // NOLINT(hicpp-signed-bitwise)
	{
		//ABCDEFGHIJKLMNOPQRSTUVWXYZ
		for(nChar=65;nChar<=90;nChar++)
		{
			anSelection[nSelectionLength] = (USINT)nChar;
			nSelectionLength++;
		}
	}
	if((eSelection & eBRB_RANDOM_STRING_LOWER_LETTERS) == eBRB_RANDOM_STRING_LOWER_LETTERS) // NOLINT(hicpp-signed-bitwise)
	{
		//abcdefghijklmnopqrstuvwxyz
		for(nChar=97;nChar<=122;nChar++)
		{
			anSelection[nSelectionLength] = (USINT)nChar;
			nSelectionLength++;
		}
	}
	if((eSelection & eBRB_RANDOM_STRING_SPACE) == eBRB_RANDOM_STRING_SPACE) // NOLINT(hicpp-signed-bitwise)
	{
		//" "
		anSelection[nSelectionLength] = 32;
		nSelectionLength++;
	}
	if((eSelection & eBRB_RANDOM_STRING_PUNCTUATION) == eBRB_RANDOM_STRING_PUNCTUATION) // NOLINT(hicpp-signed-bitwise)
	{
		//!"#$%&'()*+,-./
		for(nChar=33;nChar<=47;nChar++)
		{
			anSelection[nSelectionLength] = (USINT)nChar;
			nSelectionLength++;
		}
		//:;<=>?@
		for(nChar=58;nChar<=64;nChar++)
		{
			anSelection[nSelectionLength] = (USINT)nChar;
			nSelectionLength++;
		}
		//[\]^_`
		for(nChar=91;nChar<=96;nChar++)
		{
			anSelection[nSelectionLength] = (USINT)nChar;
			nSelectionLength++;
		}
		// {|}~
		for(nChar=123;nChar<=126;nChar++)
		{
			anSelection[nSelectionLength] = (USINT)nChar;
			nSelectionLength++;
		}
	}
	if((eSelection & eBRB_RANDOM_STRING_SYMBOLS) == eBRB_RANDOM_STRING_SYMBOLS) // NOLINT(hicpp-signed-bitwise)
	{
		for(nChar=128;nChar<=255;nChar++)
		{
			anSelection[nSelectionLength] = (USINT)nChar;
			nSelectionLength++;
		}
	}
	if((eSelection & eBRB_RANDOM_STRING_CONTROLCHARS) == eBRB_RANDOM_STRING_CONTROLCHARS) // NOLINT(hicpp-signed-bitwise)
	{
		// <127=DEL>
		anSelection[nSelectionLength] = 127;
		nSelectionLength++;
		// <1=SOH><2=STX><3=ETX><4=EOT><5=ENQ><6=ACK><7=BEL><8=BS><9=TAB><10=LF><11=VT><12=FF><13=CR><14=SO><15=SI><16=DLE>
		// <17=DC1><18=DC2><19=DC3><20=DC4><21=NAK><22=SYN><23=ETB><24=CAN><25=EM><26=SUB>27=ESC<28=FS><29=GS><30=RS><31=US>
		for(nChar=1;nChar<=31;nChar++)
		{
			anSelection[nSelectionLength] = (USINT)nChar;
			nSelectionLength++;
		}
	}
	return BrbGetRandomStringExt(pText, nTextSize, nTextLength, (STRING*)&anSelection);
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

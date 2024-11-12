#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLibUa.h"
#include <string.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Hängt den Text zu einem Datentyp-Identifier an */
plcdword BrbUaAddDatatypeIdText(unsigned long nDatatypeId, plcstring* pText, unsigned long nTextSize)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pText != 0)
	{
		nStatus = 0x00000000; // = Good
		if(nDatatypeId == 1)
		{
			BrbStringCat(pText, "1=Boolean", nTextSize);
		}
		else if(nDatatypeId == 2) 
		{
			BrbStringCat(pText, "2=SByte", nTextSize);
		}
		else if(nDatatypeId == 3) 
		{
			BrbStringCat(pText, "3=Byte", nTextSize);
		}
		else if(nDatatypeId == 4) 
		{
			BrbStringCat(pText, "4=Int16", nTextSize);
		}
		else if(nDatatypeId == 5) 
		{
			BrbStringCat(pText, "5=UInt16", nTextSize);
		}
		else if(nDatatypeId == 6) 
		{
			BrbStringCat(pText, "6=Int32", nTextSize);
		}
		else if(nDatatypeId == 7) 
		{
			BrbStringCat(pText, "7=UInt32", nTextSize);
		}
		else if(nDatatypeId == 8) 
		{
			BrbStringCat(pText, "8=Int64", nTextSize);
		}
		else if(nDatatypeId == 9) 
		{
			BrbStringCat(pText, "9=UInt64", nTextSize);
		}
		else if(nDatatypeId == 10) 
		{
			BrbStringCat(pText, "10=Float", nTextSize);
		}
		else if(nDatatypeId == 11) 
		{
			BrbStringCat(pText, "11=Double", nTextSize);
		}
		else if(nDatatypeId == 12) 
		{
			BrbStringCat(pText, "12=String", nTextSize);
		}
		else if(nDatatypeId == 13) 
		{
			BrbStringCat(pText, "13=DateTime", nTextSize);
		}
		else if(nDatatypeId == 14) 
		{
			BrbStringCat(pText, "14=Guid", nTextSize);
		}
		else if(nDatatypeId == 15) 
		{
			BrbStringCat(pText, "15=ByteString", nTextSize);
		}
		else if(nDatatypeId == 16) 
		{
			BrbStringCat(pText, "16=XmlElement", nTextSize);
		}
		else if(nDatatypeId == 17) 
		{
			BrbStringCat(pText, "17=NodeId", nTextSize);
		}
		else if(nDatatypeId == 18) 
		{
			BrbStringCat(pText, "18=ExpandedNodeId", nTextSize);
		}
		else if(nDatatypeId == 19) 
		{
			BrbStringCat(pText, "19=StatusCode", nTextSize);
		}
		else if(nDatatypeId == 20) 
		{
			BrbStringCat(pText, "20=QualifiedName", nTextSize);
		}
		else if(nDatatypeId == 21) 
		{
			BrbStringCat(pText, "21=LocalizedText", nTextSize);
		}
		else if(nDatatypeId == 22) 
		{
			BrbStringCat(pText, "22=Structure", nTextSize);
		}
		else if(nDatatypeId == 23) 
		{
			BrbStringCat(pText, "23=DataValue", nTextSize);
		}
		else if(nDatatypeId == 25) 
		{
			BrbStringCat(pText, "25=DiagnosticInfo", nTextSize);
		}
		else if(nDatatypeId == 26) 
		{
			BrbStringCat(pText, "26=Number", nTextSize);
		}
		else if(nDatatypeId == 29) 
		{
			BrbStringCat(pText, "29=Enumeration", nTextSize);
		}
		else if(nDatatypeId == 121) 
		{
			BrbStringCat(pText, "121=Decimal128", nTextSize);
		}
		else
		{
			STRING sHelp[nBRBUA_VALUE_TEXT_CHAR_MAX];
			BrbUdintToAscii(nDatatypeId, sHelp);
			BrbStringCat(pText, sHelp, nTextSize);
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)


#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "BrbLibUa.h"
#ifdef __cplusplus
	};
#endif

#include <string.h>

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Erzeugt ein zufälliges XmlElement im Format '<Tag Attribute="X">Value</Tag>' */
plcdword BrbUaGetRandomXmlElement(BrUaXmlElement* pXmlElement)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pXmlElement != 0)
	{
		nStatus = 0x00000000; // = Good
		BrbStringCopy(pXmlElement->Data, "<Tag Attribute=", sizeof(pXmlElement->Data));
		BrbStringCat(pXmlElement->Data, (STRING*)&sBRB_QM, sizeof(pXmlElement->Data));
		UDINT nNumber = (UDINT)BrbGetRandomDint(0, 255);
		STRING sNumber[12];
		brsitoa((DINT)nNumber, (UDINT)&sNumber);
		BrbStringCat(pXmlElement->Data, sNumber, sizeof(pXmlElement->Data));
		BrbStringCat(pXmlElement->Data, (STRING*)&sBRB_QM, sizeof(pXmlElement->Data));
		BrbStringCat(pXmlElement->Data, ">Value</Tag>", sizeof(pXmlElement->Data));
		pXmlElement->Length = (DINT)strlen((STRING*)&pXmlElement->Data);
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

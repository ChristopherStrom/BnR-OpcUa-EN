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

/* Hängt den Text einer NodeClass an */
plcdword BrbUaAddNodeClassText(enum UANodeClass eNodeClass, plcstring* pText, unsigned long nTextSize)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pText != 0)
	{
		nStatus = 0x00000000; // = Good
		switch(eNodeClass)
		{
			case UANodeClass_None:
				BrbStringCat(pText, "None", nTextSize);
				break;

			case UANodeClass_Object:
				BrbStringCat(pText, "Object", nTextSize);
				break;

			case UANodeClass_Variable:
				BrbStringCat(pText, "Variable", nTextSize);
				break;

			case UANodeClass_Method:
				BrbStringCat(pText, "Method", nTextSize);
				break;

			case UANodeClass_ObjectType:
				BrbStringCat(pText, "ObjectType", nTextSize);
				break;

			case UANodeClass_VariableType:
				BrbStringCat(pText, "VariableType", nTextSize);
				break;

			case UANodeClass_ReferenceType:
				BrbStringCat(pText, "ReferenceType", nTextSize);
				break;

			case UANodeClass_DataType:
				BrbStringCat(pText, "DataType", nTextSize);
				break;

			case UANodeClass_View:
				BrbStringCat(pText, "View", nTextSize);
				break;

			case UANodeClass_All:
				BrbStringCat(pText, "All", nTextSize);
				break;

			default: // NOLINT(clang-diagnostic-covered-switch-default)
				BrbStringCat(pText, "Unknown", nTextSize);
				break;

		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

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

/* Besetzt einen QualifiedName */
plcdword BrbUaSetQualifedName(BrUaQualifiedName* pQualifiedName, unsigned short nNamespaceIndex, plcstring* pName)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pQualifiedName != 0 && pName != 0)
	{
		nStatus = 0x00000000; // = Good
		pQualifiedName->NamespaceIndex = nNamespaceIndex;
		BrbStringCopy(pQualifiedName->Name, pName, sizeof(pQualifiedName->Name));
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

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

/* Erzeugt einen zufälligen QualifiedName */
plcdword BrbUaGetRandomQualifiedName(BrUaQualifiedName* pQualifiedName, unsigned short nLength)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pQualifiedName != 0)
	{
		nStatus = 0x00000000; // = Good
		UINT nNamespaceIndex = (UINT)BrbGetRandomUdint(0,65535);
		if(nLength > 255)
		{
			nLength = 255;
		}
		STRING sName[255];
		BrbGetRandomText((STRING*)&sName, sizeof(sName), nLength);
		BrbUaSetQualifedName(pQualifiedName, nNamespaceIndex, sName);
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

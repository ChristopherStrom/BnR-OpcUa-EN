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

/* Gibt den Text einer MethodOperateAction zurück */
plcdword BrbUaSrvGetMethodOperateText(enum UaMethodOperateAction eAction, plcstring* pActionText, unsigned long nActionTextSize)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pActionText != 0)
	{
		nStatus = 0x00000000; // = Good
		memset(pActionText, 0, nActionTextSize);
		switch(eAction) // NOLINT(hicpp-multiway-paths-covered)
		{
			case UaMoa_CheckIsCalled:
				BrbStringCat(pActionText, "CheckIsCalled", nActionTextSize);
				break;	

			case UaMoa_Finished:
				BrbStringCat(pActionText, "Finished", nActionTextSize);
				break;	

		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

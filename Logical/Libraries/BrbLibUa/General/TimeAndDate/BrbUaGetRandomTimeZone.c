#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLibUa.h"

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Erzeugt eine zufällige TimeZone */
plcdword BrbUaGetRandomTimeZone(BrUaTimeZoneDataType* pTimeZone)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pTimeZone != 0)
	{
		nStatus = 0x00000000; // = Good
		pTimeZone->TimeOffset = (INT)BrbGetRandomDint(-12,12);
		pTimeZone->DaylightSaving = BrbGetRandomBool();
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

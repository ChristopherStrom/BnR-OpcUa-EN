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

/* Gibt einen Verbindungs-Status als Text zurück */
plcdword BrbUaGetConnectionStatusText(enum UAConnectionStatus eConnectionStatus, plcstring* pStatusText, unsigned long nStatusTextSize)
{
	DWORD nStatus = 0x80460000; // = Bad_StructureMissing
	if(pStatusText != 0)
	{
		nStatus = 0x00000000; // = Good
		memset(pStatusText, 0, nStatusTextSize);
		switch(eConnectionStatus) // NOLINT(hicpp-multiway-paths-covered)
		{
			case UACS_Connected:
				BrbStringCopy(pStatusText, "Connected", nStatusTextSize);
				break;	

			case UACS_ConnectionError:
				BrbStringCopy(pStatusText, "ConnectionError", nStatusTextSize);
				break;	

			case UACS_Shutdown:
				BrbStringCopy(pStatusText, "Shutdown", nStatusTextSize);
				break;	
		}
	}
	return nStatus;
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

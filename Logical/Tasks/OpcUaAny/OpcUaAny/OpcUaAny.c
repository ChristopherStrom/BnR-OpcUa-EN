#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

void _INIT Init(void)
{
	// Initialize Data structure by setting all fields to 0
	brsmemset((UDINT)&Data, 0, sizeof(Data));
}

void _CYCLIC Cyclic(void)
{
	// Modify server data read by the OpcUaAny client
	Data.Read.Server.nUsint += 1;
	Data.Read.Server.nUint += 1;
	Data.Read.Server.nUdint += 1;

	// Modify client data written to the server
	Data.Write.Client.nUsint += 2;
	Data.Write.Client.nUint += 2;
	Data.Write.Client.nUdint += 2;
}

void _EXIT Exit(void)
{
	// No specific actions on exit
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

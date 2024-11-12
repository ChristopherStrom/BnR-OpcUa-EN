
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

void _INIT ProgramInit(void)
{

}

void _CYCLIC ProgramCyclic(void)
{
	// Diagnose-Zähler der empfangenen Messages
	SubscriberDiagData.UdpMessage.nTotal = ArPubSubDGetUdpMsgReceiveTotal();
	SubscriberDiagData.UdpMessage.nError = ArPubSubDGetUdpMsgReceiveError();
	// Diagnose-Zähler der empfangenen DataSets
	SubscriberDiagData.DataSet.nTotal = ArPubSubDGetDataSetReceiveTotal();
	SubscriberDiagData.DataSet.nError = ArPubSubDGetDataSetReceiveError();
}

void _EXIT ProgramExit(void)
{

}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)


#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

void _INIT ProgramInit(void)
{
	// Variable verwenden, damit sie zumindest einmal im Code vorkommt und nicht vom Kompiler wegoptimiert wird
	brsmemset((UDINT)&SubscribedData, 0, sizeof(SubscribedData));
}

void _CYCLIC ProgramCyclic(void)
{
	// Dieser Task enthält keinen Code, sondern nur die Variablen-Deklaration zur Aufnahme der empfangenen Werte.
}

void _EXIT ProgramExit(void)
{

}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

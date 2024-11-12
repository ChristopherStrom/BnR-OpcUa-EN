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

/* Gibt zurück, ob zwei NodeIds gleich sind */
plcbit BrbUaAreNodeIdsEqual(struct UANodeID* pNodeId1, struct UANodeID* pNodeId2)
{
	if(pNodeId1 == 0)
	{
		return 0;
	}
	if(pNodeId2 == 0)
	{
		return 0;
	}	
	return (memcmp(pNodeId1, pNodeId2, sizeof(UANodeID)) == 0); // NOLINT(bugprone-suspicious-memory-comparison,cert-exp42-c,cert-flp37-c)
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

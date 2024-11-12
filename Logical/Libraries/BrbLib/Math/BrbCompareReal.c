
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "BrbLib.h"
#include "limits.h"
#include <math.h>

#ifdef __cplusplus
	};
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Vergleicht zwei REAL-Werte */
signed short BrbCompareReal(float rValue1, float rValue2)
{
	// Union zur Interpretation der verschiedenen Datentypen
	typedef union
	{
		REAL rReal;
		DINT nDint;
		UDINT nUdint;
     
	} BrbValueUnion_TYP;
	BrbValueUnion_TYP	Value1 = {}; // NOLINT(clang-diagnostic-gnu-empty-initializer)
	BrbValueUnion_TYP	Value2 = {}; // NOLINT(clang-diagnostic-gnu-empty-initializer)
     
	// Werte wandeln in Union
	Value1.rReal = rValue1;
	Value2.rReal = rValue2;
	
	// NAN (Not A Number = Keine Zahl) oder INF (Infinity = Unendlich)
	if((isnan(Value1.rReal) != 0) ||
		(isinf(Value1.rReal) != 0))
	{
		return(nBRB_INT_MIN);
	}
	if((isnan(Value2.rReal) != 0) ||
		(isinf(Value2.rReal) != 0))
	{
		return(nBRB_INT_MAX);
	}
	
	// Behandlung Werte = -0.0
	if(Value1.nUdint == 0x80000000)
	{
		Value1.nUdint = 0;
	}
	if(Value2.nUdint == 0x80000000)
	{
		Value2.nUdint = 0;
	}
	
	// Vorzeichen unterschiedlich?
	if((Value1.nDint < 0) != (Value2.nDint < 0))
	{
		return (INT)(((Value1.nDint >= 0) ? 1 : -1));
	}
	
	// Werte haben das gleiche Vorzeichen
	// Werte negativ? 
	if(Value1.nDint < 0)
	{
		// Werte positiv wandeln 
		Value1.nUdint = -Value1.nUdint;
		Value2.nUdint = -Value2.nUdint;
	}
	
	// Werte vergleichen 
	return (INT)((Value1.nUdint > Value2.nUdint) - (Value1.nUdint < Value2.nUdint));
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

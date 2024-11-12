
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

#define LINT          signed long long
#define ULINT         unsigned long long

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

/* Vergleicht zwei LREAL-Werte */
signed short BrbCompareLReal(double rValue1, double rValue2)
{
	// Union zur Interpretation der verschiedenen Datentypen
	typedef union
	{
		LREAL rLreal;
		LINT nLint;
		ULINT nUlint;
     
	} BrbValueUnion_TYP;
	BrbValueUnion_TYP	Value1 = {}; // NOLINT(clang-diagnostic-gnu-empty-initializer)
	BrbValueUnion_TYP	Value2 = {}; // NOLINT(clang-diagnostic-gnu-empty-initializer)
     
	// Werte wandeln in Union
	Value1.rLreal = rValue1;
	Value2.rLreal = rValue2;
	
	// NAN (Not A Number = Keine Zahl) oder INF (Infinity = Unendlich)
	if((isnan(Value1.rLreal) != 0) ||
		(isinf(Value1.rLreal) != 0))
	{
		return(nBRB_INT_MIN);
	}
	if((isnan(Value2.rLreal) != 0) ||
		(isinf(Value2.rLreal) != 0))
	{
		return(nBRB_INT_MAX);
	}
	
	// Behandlung Werte = -0.0
	if(Value1.nUlint == 0x8000000000000000LL)
	{
		Value1.nUlint = 0;
	}
	if(Value2.nUlint == 0x8000000000000000LL)
	{
		Value2.nUlint = 0;
	}
	
	// Vorzeichen unterschiedlich?
	if((Value1.nLint < 0) != (Value2.nLint < 0))
	{
		return (INT)(((Value1.nLint >= 0) ? 1 : -1));
	}
	
	// Werte haben das gleiche Vorzeichen
	// Werte negativ? 
	if(Value1.nLint < 0)
	{
		// Werte positiv wandeln 
		Value1.nUlint = -Value1.nUlint;
		Value2.nUlint = -Value2.nUlint;
	}
	
	// Werte vergleichen 
	return (INT)((Value1.nUlint > Value2.nUlint) - (Value1.nUlint < Value2.nUlint));
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, hicpp-uppercase-literal-suffix, cppcoreguidelines-*, performance-*)

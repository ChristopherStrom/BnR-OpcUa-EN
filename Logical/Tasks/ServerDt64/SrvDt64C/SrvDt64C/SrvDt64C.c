#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

// NOLINTBEGIN(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

// Prototypes of local functions
void ChangeUint64();
void ChangeInt64();

void _INIT Init(void)
{
    // Set Uint64 and counter limits
    BrbUint64FromString(&nUint64, "0");
    BrbUint64FromString(&ChangeUint64Inst.nCountMin, "5");
    BrbUint64FromString(&ChangeUint64Inst.nCountMax, "18446744073709551610");
    ChangeUint64Inst.bCountPositive = 1;
	
    // Set Int64 and counter limits
    BrbInt64FromString(&nInt64, "9223372036854775802");
    BrbInt64FromString(&ChangeInt64Inst.nCountMin, "-9223372036854775803");
    BrbInt64FromString(&ChangeInt64Inst.nCountMax, "9223372036854775802");
    ChangeInt64Inst.bCountPositive = 1;
}

void _CYCLIC Cyclic(void)
{
    ChangeUint64(); // Change value cyclically
    BrbUint64ToString(&nUint64, sUint64, sizeof(sUint64)); // Convert to text for better readability

    ChangeInt64(); // Change value cyclically
    BrbInt64ToString(&nInt64, sInt64, sizeof(sInt64)); // Convert to text for better readability
}

void _EXIT Exit(void)
{
}

// Change Uint64 value
void ChangeUint64()
{
    if(ChangeUint64Inst.bCountPositive == 1)
    {
        BrbUint64Inc(&nUint64);
        if(BrbUint64Compare(&nUint64, &ChangeUint64Inst.nCountMin) == 0)
        {
            ChangeUint64Inst.bCountPositive = 0;
        }
    }
    else
    {
        BrbUint64Dec(&nUint64);
        if(BrbUint64Compare(&nUint64, &ChangeUint64Inst.nCountMax) == 0)
        {
            ChangeUint64Inst.bCountPositive = 1;
        }
    }
}

// Change Int64 value
void ChangeInt64()
{
    if(ChangeInt64Inst.bCountPositive == 1)
    {
        BrbInt64Inc(&nInt64);
        if(BrbInt64Compare(&nInt64, &ChangeInt64Inst.nCountMin) == 0)
        {
            ChangeInt64Inst.bCountPositive = 0;
        }
    }
    else
    {
        BrbInt64Dec(&nInt64);
        if(BrbInt64Compare(&nInt64, &ChangeInt64Inst.nCountMax) == 0)
        {
            ChangeInt64Inst.bCountPositive = 1;
        }
    }
}

// NOLINTEND(readability-*, bugprone-easily-swappable-parameters, bugprone-branch-clone, clang-diagnostic-invalid-utf8, clang-diagnostic-invalid-source-encoding, clang-diagnostic-pointer-arith, clang-diagnostic-strict-prototypes, clang-diagnostic-shadow, clang-diagnostic-bad-function-cast, clang-analyzer-security.insecureAPI.*, hicpp-uppercase-literal-suffix, hicpp-function-size, cppcoreguidelines-*, performance-*)

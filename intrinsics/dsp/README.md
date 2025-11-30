# DSP Intrinsics

This directory will contain intrinsics for the DSP extension available on Cortex-M4 and Cortex-M7.

## Planned Files

- `saturating_arith.hpp` - Saturating arithmetic (qadd, qsub, qdadd, qdsub)
- `simd_arith.hpp` - SIMD arithmetic (sadd16, sadd8, ssub16, etc.)
- `simd_multiply.hpp` - SIMD multiply-accumulate (smuad, smusd, smlad, etc.)
- `packing.hpp` - Packing/unpacking operations (pkhbt, pkhtb, sxtab, etc.)
- `misc.hpp` - Miscellaneous DSP (sel, usad8, etc.)

## Namespace

All DSP intrinsics will be in `Cortex::Intrinsics::DSP`.

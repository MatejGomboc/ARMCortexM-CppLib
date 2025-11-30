# FPU Intrinsics

This directory will contain intrinsics for the Floating Point Unit available on Cortex-M4F and Cortex-M7.

## Planned Files

- `single_precision.hpp` - Single-precision (float32) FPU operations
- `double_precision.hpp` - Double-precision (float64) operations (Cortex-M7 only)

## Namespace

All FPU intrinsics will be in `Cortex::Intrinsics::FPU`.

## Note

The FPU must be enabled via the CPACR register before using these intrinsics.

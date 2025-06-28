# ARMCortexM-CppLib

CMSIS-like C++ library for ARM Cortex-M microcontrollers

## Features

### Cortex-M0 Support

The library provides the following components for ARM Cortex-M0:

- **Memory Barriers** (`barriers.hpp`): DSB, ISB, DMB, and compiler barriers
- **Exception Handling** (`exceptions.hpp`): Enable/disable exceptions, exception numbers
- **NVIC** (`nvic.hpp`): Nested Vectored Interrupt Controller functions
- **SCB** (`scb.hpp`): System Control Block register access
- **Special Registers** (`special_regs.hpp`): Access to PSR, PRIMASK, CONTROL, MSP, PSP registers
- **SysTick** (`systick.hpp`): System timer functions
- **Intrinsics** (`intrinsics.hpp`): CPU intrinsic functions including:
  - `SendEvent()` - SEV instruction
  - `WaitForEvent()` - WFE instruction  
  - `WaitForInterrupt()` - WFI instruction
  - `Nop()` - NOP instruction
  - `Yield()` - YIELD instruction
  - `Breakpoint(value)` - BKPT instruction
  - `ReverseBytes(value)` - REV instruction
  - `ReverseBytes16(value)` - REV16 instruction
  - `ReverseBytesSignedHalfword(value)` - REVSH instruction
  - `CountLeadingZeros(value)` - CLZ instruction (if available)
  - `UnsignedSaturate(value, bits)` - Software implementation of USAT
  - `SignedSaturate(value, bits)` - Software implementation of SSAT

## License

This library is licensed under Apache License Version 2.0.  
Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexM-CppLib>.  
See the attached [LICENCE](./LICENCE) file for more info.

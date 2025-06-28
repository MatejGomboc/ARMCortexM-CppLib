/*
    Example usage of ARM Cortex-M0 intrinsic functions
    
    Copyright (C) 2025 Matej Gomboc <https://github.com/MatejGomboc/ARMCortexM-CppLib>
    Licensed under the Apache License, Version 2.0
*/

#include "cortexm0/intrinsics.hpp"
#include "cortexm0/exceptions.hpp"
#include <cstdint>

// Example 1: Using WFI for low-power idle
void low_power_idle()
{
    // Disable interrupts temporarily
    CortexM0::disableExceptions();
    
    // Configure any wake-up sources here
    // ...
    
    // Re-enable interrupts
    CortexM0::enableExceptions();
    
    // Wait for interrupt - CPU will sleep until an interrupt occurs
    CortexM0::WaitForInterrupt();
}

// Example 2: Using SEV/WFE for simple synchronization
volatile bool event_flag = false;

void producer_task()
{
    // Do some work
    // ...
    
    // Signal that work is complete
    event_flag = true;
    CortexM0::SendEvent();
}

void consumer_task()
{
    // Wait for producer to complete
    while (!event_flag) {
        CortexM0::WaitForEvent();
    }
    
    // Process the data
    // ...
    
    event_flag = false;
}

// Example 3: Using byte reversal for endianness conversion
uint32_t convert_endianness(uint32_t value)
{
    // Convert between big-endian and little-endian
    return CortexM0::ReverseBytes(value);
}

// Example 4: Network byte order conversion
uint16_t htons(uint16_t host_short)
{
    // Host to network short (16-bit)
    uint32_t result = CortexM0::ReverseBytes16(host_short);
    return static_cast<uint16_t>(result);
}

// Example 5: Saturating arithmetic for signal processing
int16_t saturate_to_int16(int32_t value)
{
    // Saturate 32-bit value to 16-bit range
    return static_cast<int16_t>(CortexM0::SignedSaturate(value, 16));
}

// Example 6: Debug breakpoint
void debug_assert(bool condition)
{
    if (!condition) {
        // Trigger debugger with specific code
        CortexM0::Breakpoint(0x42);
    }
}

// Example 7: Precise timing delays
void delay_cycles(uint32_t cycles)
{
    // Each iteration is approximately 4 cycles
    cycles = cycles / 4;
    
    for (uint32_t i = 0; i < cycles; i++) {
        CortexM0::Nop();
    }
}

// Example 8: Cooperative multitasking hint
void background_task()
{
    while (true) {
        // Do some non-critical work
        // ...
        
        // Hint to scheduler that we can be preempted
        CortexM0::Yield();
    }
}

// Example 9: Finding highest bit set
uint32_t find_highest_bit(uint32_t value)
{
    if (value == 0) {
        return 0;
    }
    
    // CLZ returns number of leading zeros
    // So 31 - CLZ gives the position of the highest bit set
    // Note: CLZ may not be available on all Cortex-M0 devices
    return 31 - CortexM0::CountLeadingZeros(value);
}

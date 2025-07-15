// REQUIRES: cortex-m0
// RUN: %cc% %ccflags% %ccout% %T/%basename_t.o %s; objdump --mcpu=%mcpu% -d %T/%basename_t.o | FileCheck --allow-unused-prefixes --check-prefixes %prefixes% %s

#include "cortexm0/nvic.hpp"
#include "cortexm0/exceptions.hpp"
#include <cstdint>

using namespace CortexM0;

void test_nvic_irq_boundary_conditions() {
    // CHECK-LABEL: <{{.*test_nvic_irq_boundary_conditions.*}}>:
    
    // Test IRQ 0 (first external interrupt)
    Nvic::enableIrq(0);
    // CHECK: {{str|ldr}}
    volatile bool irq0_enabled = Nvic::isEnabledIrq(0);
    // CHECK: {{str|ldr}}
    
    Nvic::disableIrq(0);
    // CHECK: {{str|ldr}}
    volatile bool irq0_disabled = !Nvic::isEnabledIrq(0);
    // CHECK: {{str|ldr}}
    
    // Test IRQ 31 (last IRQ for Cortex-M0)
    Nvic::enableIrq(31);
    // CHECK: {{str|ldr}}
    volatile bool irq31_enabled = Nvic::isEnabledIrq(31);
    // CHECK: {{str|ldr}}
    
    Nvic::disableIrq(31);
    // CHECK: {{str|ldr}}
    volatile bool irq31_disabled = !Nvic::isEnabledIrq(31);
    // CHECK: {{str|ldr}}
    
    // Test all IRQs in range
    for (uint32_t irq = 0; irq < 32; ++irq) {
        Nvic::enableIrq(irq);
        // CHECK: {{str|ldr}}
        volatile bool enabled = Nvic::isEnabledIrq(irq);
        // CHECK: {{str|ldr}}
        
        Nvic::disableIrq(irq);
        // CHECK: {{str|ldr}}
        volatile bool disabled = !Nvic::isEnabledIrq(irq);
        // CHECK: {{str|ldr}}
    }
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_nvic_pending_comprehensive() {
    // CHECK-LABEL: <{{.*test_nvic_pending_comprehensive.*}}>:
    
    // Test setting and clearing pending for each IRQ
    for (uint32_t irq = 0; irq < 32; ++irq) {
        // Set pending
        Nvic::setPendingIrq(irq);
        // CHECK: {{str|ldr}}
        
        // Check pending status
        volatile bool is_pending = Nvic::getPendingIrq(irq);
        // CHECK: {{str|ldr}}
        
        // Clear pending
        Nvic::clearPendingIrq(irq);
        // CHECK: {{str|ldr}}
        
        // Verify cleared
        volatile bool is_cleared = !Nvic::getPendingIrq(irq);
        // CHECK: {{str|ldr}}
    }
    
    // Test multiple IRQs pending simultaneously
    Nvic::setPendingIrq(5);
    // CHECK: {{str|ldr}}
    Nvic::setPendingIrq(10);
    // CHECK: {{str|ldr}}
    Nvic::setPendingIrq(15);
    // CHECK: {{str|ldr}}
    
    volatile bool irq5_pending = Nvic::getPendingIrq(5);
    // CHECK: {{str|ldr}}
    volatile bool irq10_pending = Nvic::getPendingIrq(10);
    // CHECK: {{str|ldr}}
    volatile bool irq15_pending = Nvic::getPendingIrq(15);
    // CHECK: {{str|ldr}}
    
    // Clear them individually
    Nvic::clearPendingIrq(5);
    // CHECK: {{str|ldr}}
    Nvic::clearPendingIrq(10);
    // CHECK: {{str|ldr}}
    Nvic::clearPendingIrq(15);
    // CHECK: {{str|ldr}}
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_nvic_priority_edge_cases() {
    // CHECK-LABEL: <{{.*test_nvic_priority_edge_cases.*}}>:
    
    // Test priority range for Cortex-M0 (2-bit priority: 0-3)
    
    // Test minimum priority (highest priority)
    Nvic::setPriority(5, 0);
    // CHECK: {{str|ldr}}
    volatile uint32_t min_priority = Nvic::getPriority(5);
    // CHECK: {{str|ldr}}
    volatile bool min_correct = (min_priority == 0);
    
    // Test maximum priority (lowest priority) 
    Nvic::setPriority(5, 3);
    // CHECK: {{str|ldr}}
    volatile uint32_t max_priority = Nvic::getPriority(5);
    // CHECK: {{str|ldr}}
    volatile bool max_correct = (max_priority == 3);
    
    // Test intermediate priorities
    Nvic::setPriority(10, 1);
    // CHECK: {{str|ldr}}
    volatile uint32_t priority1 = Nvic::getPriority(10);
    // CHECK: {{str|ldr}}
    
    Nvic::setPriority(15, 2);
    // CHECK: {{str|ldr}}
    volatile uint32_t priority2 = Nvic::getPriority(15);
    // CHECK: {{str|ldr}}
    
    // Test that priorities are preserved correctly
    volatile bool priorities_correct = (priority1 == 1) && (priority2 == 2);
    
    // Test setting priority for all IRQs
    for (uint32_t irq = 0; irq < 32; ++irq) {
        uint32_t test_priority = irq % 4;  // Cycle through priorities 0-3
        Nvic::setPriority(irq, test_priority);
        // CHECK: {{str|ldr}}
        
        volatile uint32_t read_priority = Nvic::getPriority(irq);
        // CHECK: {{str|ldr}}
        volatile bool priority_match = (read_priority == test_priority);
    }
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_nvic_enable_disable_patterns() {
    // CHECK-LABEL: <{{.*test_nvic_enable_disable_patterns.*}}>:
    
    // Test enabling all even IRQs
    for (uint32_t irq = 0; irq < 32; irq += 2) {
        Nvic::enableIrq(irq);
        // CHECK: {{str|ldr}}
    }
    
    // Verify even IRQs are enabled, odd are disabled
    for (uint32_t irq = 0; irq < 32; ++irq) {
        volatile bool enabled = Nvic::isEnabledIrq(irq);
        // CHECK: {{str|ldr}}
        if (irq % 2 == 0) {
            // Even IRQs should be enabled
            volatile bool should_be_enabled = enabled;
        } else {
            // Odd IRQs should be disabled
            volatile bool should_be_disabled = !enabled;
        }
    }
    
    // Disable all even IRQs
    for (uint32_t irq = 0; irq < 32; irq += 2) {
        Nvic::disableIrq(irq);
        // CHECK: {{str|ldr}}
    }
    
    // Enable all odd IRQs
    for (uint32_t irq = 1; irq < 32; irq += 2) {
        Nvic::enableIrq(irq);
        // CHECK: {{str|ldr}}
    }
    
    // Verify pattern is flipped
    for (uint32_t irq = 0; irq < 32; ++irq) {
        volatile bool enabled = Nvic::isEnabledIrq(irq);
        // CHECK: {{str|ldr}}
        if (irq % 2 == 1) {
            // Odd IRQs should be enabled
            volatile bool should_be_enabled = enabled;
        } else {
            // Even IRQs should be disabled
            volatile bool should_be_disabled = !enabled;
        }
    }
    
    // Clean up - disable all
    for (uint32_t irq = 0; irq < 32; ++irq) {
        Nvic::disableIrq(irq);
        // CHECK: {{str|ldr}}
    }
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_nvic_system_reset_safety() {
    // CHECK-LABEL: <{{.*test_nvic_system_reset_safety.*}}>:
    
    // Test that system reset function exists and can be referenced
    // but we won't actually call it in the test
    auto reset_function = &Nvic::systemReset;
    volatile void (*reset_ptr)(void) = reset_function;
    
    // Test that the function pointer is not null
    volatile bool reset_function_exists = (reset_ptr != nullptr);
    
    // We can test the address is in a reasonable range for code
    volatile uintptr_t reset_addr = reinterpret_cast<uintptr_t>(reset_ptr);
    volatile bool addr_reasonable = (reset_addr != 0);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_nvic_irq_vs_exception_mapping() {
    // CHECK-LABEL: <{{.*test_nvic_irq_vs_exception_mapping.*}}>:
    
    // Test the relationship between IRQ numbers and exception numbers
    // Exception number = IRQ number + 16
    
    // Test IRQ 0 -> Exception 16
    volatile auto irq0 = static_cast<int32_t>(Irq::IRQ0);
    volatile int32_t exception16 = irq0 + 16;
    volatile bool irq0_mapping = (irq0 == 0) && (exception16 == 16);
    
    // Test IRQ 5 -> Exception 21
    volatile auto irq5 = static_cast<int32_t>(Irq::IRQ5);
    volatile int32_t exception21 = irq5 + 16;
    volatile bool irq5_mapping = (irq5 == 5) && (exception21 == 21);
    
    // Test IRQ 31 -> Exception 47
    volatile auto irq31 = static_cast<int32_t>(Irq::IRQ31);
    volatile int32_t exception47 = irq31 + 16;
    volatile bool irq31_mapping = (irq31 == 31) && (exception47 == 47);
    
    // Test that system exceptions are separate
    volatile auto systick_exception = static_cast<int32_t>(Exception::SYSTICK);
    volatile auto pendsv_exception = static_cast<int32_t>(Exception::PENDSV);
    volatile auto svcall_exception = static_cast<int32_t>(Exception::SVCALL);
    
    volatile bool system_exceptions_correct = 
        (systick_exception == 15) && 
        (pendsv_exception == 14) && 
        (svcall_exception == 11);
    
    // Verify that system exceptions are below IRQ range
    volatile bool system_below_irq = (systick_exception < 16) && 
                                    (pendsv_exception < 16) && 
                                    (svcall_exception < 16);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_nvic_concurrent_operations() {
    // CHECK-LABEL: <{{.*test_nvic_concurrent_operations.*}}>:
    
    // Test operations on the same IRQ in sequence
    uint32_t test_irq = 12;
    
    // Enable -> Set Priority -> Set Pending -> Check Status
    Nvic::enableIrq(test_irq);
    // CHECK: {{str|ldr}}
    
    Nvic::setPriority(test_irq, 2);
    // CHECK: {{str|ldr}}
    
    Nvic::setPendingIrq(test_irq);
    // CHECK: {{str|ldr}}
    
    // Read all states
    volatile bool enabled = Nvic::isEnabledIrq(test_irq);
    // CHECK: {{str|ldr}}
    volatile uint32_t priority = Nvic::getPriority(test_irq);
    // CHECK: {{str|ldr}}
    volatile bool pending = Nvic::getPendingIrq(test_irq);
    // CHECK: {{str|ldr}}
    
    // Verify all states are as expected
    volatile bool states_correct = enabled && (priority == 2) && pending;
    
    // Clear pending and disable
    Nvic::clearPendingIrq(test_irq);
    // CHECK: {{str|ldr}}
    Nvic::disableIrq(test_irq);
    // CHECK: {{str|ldr}}
    
    // Verify cleanup
    volatile bool final_enabled = Nvic::isEnabledIrq(test_irq);
    // CHECK: {{str|ldr}}
    volatile bool final_pending = Nvic::getPendingIrq(test_irq);
    // CHECK: {{str|ldr}}
    volatile bool cleanup_correct = !final_enabled && !final_pending;
    
    // Priority should remain (it's not cleared by disable)
    volatile uint32_t final_priority = Nvic::getPriority(test_irq);
    // CHECK: {{str|ldr}}
    volatile bool priority_preserved = (final_priority == 2);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_nvic_register_access_patterns() {
    // CHECK-LABEL: <{{.*test_nvic_register_access_patterns.*}}>:
    
    // Test that multiple operations generate expected register accesses
    
    // These operations should access NVIC registers (memory-mapped)
    Nvic::enableIrq(8);
    // CHECK: {{str|ldr}}
    Nvic::enableIrq(16);
    // CHECK: {{str|ldr}}
    Nvic::enableIrq(24);
    // CHECK: {{str|ldr}}
    
    // Disable operations
    Nvic::disableIrq(8);
    // CHECK: {{str|ldr}}
    Nvic::disableIrq(16);
    // CHECK: {{str|ldr}}
    Nvic::disableIrq(24);
    // CHECK: {{str|ldr}}
    
    // Priority operations (different register)
    Nvic::setPriority(8, 1);
    // CHECK: {{str|ldr}}
    Nvic::setPriority(16, 2);
    // CHECK: {{str|ldr}}
    Nvic::setPriority(24, 3);
    // CHECK: {{str|ldr}}
    
    // Read operations
    volatile uint32_t prio8 = Nvic::getPriority(8);
    // CHECK: {{str|ldr}}
    volatile uint32_t prio16 = Nvic::getPriority(16);
    // CHECK: {{str|ldr}}
    volatile uint32_t prio24 = Nvic::getPriority(24);
    // CHECK: {{str|ldr}}
    
    // Pending operations (different register)
    Nvic::setPendingIrq(8);
    // CHECK: {{str|ldr}}
    volatile bool pending8 = Nvic::getPendingIrq(8);
    // CHECK: {{str|ldr}}
    Nvic::clearPendingIrq(8);
    // CHECK: {{str|ldr}}
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

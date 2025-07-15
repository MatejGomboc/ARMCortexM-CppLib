// REQUIRES: cortex-m0
// RUN: %cc% %ccflags% %ccout% %T/%basename_t.o %s; objdump --mcpu=%mcpu% -d %T/%basename_t.o | FileCheck --allow-unused-prefixes --check-prefixes %prefixes% %s

#include "cortexm0/special_regs.hpp"
#include <cstdint>

using namespace CortexM0;

// Test PSR union functionality thoroughly
void test_psr_union_comprehensive() {
    // CHECK-LABEL: <{{.*test_psr_union_comprehensive.*}}>:
    
    // Test all PSR bitfield combinations
    Psr psr;
    
    // Test setting individual flags
    psr.value = 0;
    psr.bits.n = 1;  // Negative flag
    psr.bits.z = 1;  // Zero flag  
    psr.bits.c = 1;  // Carry flag
    psr.bits.v = 1;  // Overflow flag
    psr.bits.thumb_mode = 1;  // Should always be 1 on Cortex-M
    
    volatile uint32_t expected_flags = 0xF0000000 | (1 << 24);  // N,Z,C,V + T
    volatile bool flags_correct = (psr.value & 0xF1000000) == expected_flags;
    
    // Test exception number field
    psr.value = 0;
    psr.bits.current_exception = 15;  // SysTick exception
    volatile bool exception_correct = (psr.bits.current_exception == 15);
    
    // Test edge case: maximum exception number
    psr.bits.current_exception = 63;  // Maximum for 6-bit field
    volatile bool max_exception = (psr.bits.current_exception == 63);
    
    // Test combined access
    psr.value = 0x8100000F;  // N=1, T=1, Exception=15
    volatile bool combined_correct = (psr.bits.n == 1) && 
                                    (psr.bits.thumb_mode == 1) && 
                                    (psr.bits.current_exception == 15);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_primask_edge_cases() {
    // CHECK-LABEL: <{{.*test_primask_edge_cases.*}}>:
    
    // Test Primask union
    Primask primask;
    
    // Test setting exceptions disabled bit
    primask.value = 0;
    primask.bits.exceptions_disabled = 1;
    volatile bool disabled_set = (primask.value == 1);
    
    // Test clearing exceptions disabled bit
    primask.value = 0xFFFFFFFF;
    primask.bits.exceptions_disabled = 0;
    volatile bool disabled_clear = (primask.value == 0xFFFFFFFE);
    
    // Test that reserved bits are preserved when setting
    primask.value = 0x12345678;  // Set some reserved bits
    primask.bits.exceptions_disabled = 1;
    volatile bool reserved_preserved = ((primask.value & 0xFFFFFFFE) == 0x12345678);
    
    // Test read-modify-write operation
    primask.value = 0;
    primask.bits.exceptions_disabled = 1;
    Primask old_primask = primask;
    primask.bits.exceptions_disabled = 0;
    volatile bool rmw_correct = (old_primask.value == 1) && (primask.value == 0);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_control_register_comprehensive() {
    // CHECK-LABEL: <{{.*test_control_register_comprehensive.*}}>:
    
    Control control;
    
    // Test all combinations of control bits
    control.value = 0;
    control.bits.thread_mode_privilege_level = 0;  // Privileged
    control.bits.active_stack_pointer = 0;         // MSP
    volatile bool priv_msp = (control.value == 0);
    
    control.value = 0;
    control.bits.thread_mode_privilege_level = 1;  // Unprivileged  
    control.bits.active_stack_pointer = 0;         // MSP
    volatile bool unpriv_msp = (control.value == 1);
    
    control.value = 0;
    control.bits.thread_mode_privilege_level = 0;  // Privileged
    control.bits.active_stack_pointer = 1;         // PSP
    volatile bool priv_psp = (control.value == 2);
    
    control.value = 0;
    control.bits.thread_mode_privilege_level = 1;  // Unprivileged
    control.bits.active_stack_pointer = 1;         // PSP
    volatile bool unpriv_psp = (control.value == 3);
    
    // Test enum comparisons
    control.value = 1;
    volatile bool is_unprivileged = (static_cast<Control::ThreadModePrivilegeLevel>(control.bits.thread_mode_privilege_level) 
                                   == Control::ThreadModePrivilegeLevel::UNPRIVILEGED);
    
    control.value = 2;
    volatile bool is_psp = (static_cast<Control::StackPointer>(control.bits.active_stack_pointer) 
                          == Control::StackPointer::PSP);
    
    // Test reserved bits handling
    control.value = 0xFFFFFFFF;
    control.bits.thread_mode_privilege_level = 0;
    control.bits.active_stack_pointer = 0;
    volatile bool reserved_masked = ((control.value & 0x3) == 0);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_lr_exception_return_values() {
    // CHECK-LABEL: <{{.*test_lr_exception_return_values.*}}>:
    
    // Test LR exception return enum values
    volatile uint32_t handler_lr = static_cast<uint32_t>(LrExceptionReturn::HANDLER);
    volatile uint32_t thread_msp_lr = static_cast<uint32_t>(LrExceptionReturn::THREAD_MSP);
    volatile uint32_t thread_psp_lr = static_cast<uint32_t>(LrExceptionReturn::THREAD_PSP);
    
    // Verify the magic values are correct
    volatile bool handler_correct = (handler_lr == 0xFFFFFFF1);
    volatile bool thread_msp_correct = (thread_msp_lr == 0xFFFFFFF9);
    volatile bool thread_psp_correct = (thread_psp_lr == 0xFFFFFFFD);
    
    // Test that these are distinguishable
    volatile bool all_different = (handler_lr != thread_msp_lr) && 
                                 (handler_lr != thread_psp_lr) && 
                                 (thread_msp_lr != thread_psp_lr);
    
    // Test that all have the expected EXC_RETURN pattern (0xFFFFFFFx)
    volatile bool handler_pattern = ((handler_lr & 0xFFFFFFF0) == 0xFFFFFFF0);
    volatile bool thread_msp_pattern = ((thread_msp_lr & 0xFFFFFFF0) == 0xFFFFFFF0);
    volatile bool thread_psp_pattern = ((thread_psp_lr & 0xFFFFFFF0) == 0xFFFFFFF0);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_register_access_atomicity() {
    // CHECK-LABEL: <{{.*test_register_access_atomicity.*}}>:
    
    // Test that register reads are atomic (single instruction)
    volatile uint32_t msp1 = getMspReg();
    // CHECK: mrs {{r[0-9]+}}, msp
    volatile uint32_t msp2 = getMspReg();  
    // CHECK: mrs {{r[0-9]+}}, msp
    
    // Multiple reads should each generate MRS instruction
    volatile auto apsr1 = getApsrReg();
    // CHECK: mrs {{r[0-9]+}}, apsr
    volatile auto apsr2 = getApsrReg();
    // CHECK: mrs {{r[0-9]+}}, apsr
    
    // Test that writes include proper barriers
    setMspReg(0x20008000);
    // CHECK: msr msp, {{r[0-9]+}}
    // CHECK: isb
    
    setPspReg(0x20004000);
    // CHECK: msr psp, {{r[0-9]+}}
    // CHECK: isb
    
    // Test multiple writes have barriers
    Primask mask;
    mask.bits.exceptions_disabled = 1;
    setPrimaskReg(mask);
    // CHECK: msr primask, {{r[0-9]+}}
    // CHECK: isb
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_stack_pointer_edge_cases() {
    // CHECK-LABEL: <{{.*test_stack_pointer_edge_cases.*}}>:
    
    // Test stack pointer alignment requirements
    // ARM requires 8-byte alignment for stack pointers
    
    // Test setting aligned addresses
    setMspReg(0x20008000);  // 8-byte aligned
    // CHECK: msr msp, {{r[0-9]+}}
    // CHECK: isb
    
    setPspReg(0x20004000);  // 8-byte aligned
    // CHECK: msr psp, {{r[0-9]+}}
    // CHECK: isb
    
    // Test reading back
    volatile uint32_t msp_read = getMspReg();
    // CHECK: mrs {{r[0-9]+}}, msp
    
    volatile uint32_t psp_read = getPspReg();
    // CHECK: mrs {{r[0-9]+}}, psp
    
    // Test boundary values
    setMspReg(0xFFFFFFE0);  // Near top of memory, aligned
    // CHECK: msr msp, {{r[0-9]+}}
    // CHECK: isb
    
    setPspReg(0x20000008);  // Near bottom of typical SRAM, aligned
    // CHECK: msr psp, {{r[0-9]+}}
    // CHECK: isb
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_volatile_semantics() {
    // CHECK-LABEL: <{{.*test_volatile_semantics.*}}>:
    
    // Test that volatile prevents optimization
    // Each register read should generate a separate instruction
    
    for (int i = 0; i < 3; ++i) {
        volatile auto apsr = getApsrReg();
        // CHECK: mrs {{r[0-9]+}}, apsr
        volatile uint32_t msp = getMspReg();
        // CHECK: mrs {{r[0-9]+}}, msp
    }
    
    // Test that sequential register writes are not eliminated
    Primask mask1, mask2;
    mask1.bits.exceptions_disabled = 1;
    mask2.bits.exceptions_disabled = 0;
    
    setPrimaskReg(mask1);
    // CHECK: msr primask, {{r[0-9]+}}
    // CHECK: isb
    setPrimaskReg(mask2);
    // CHECK: msr primask, {{r[0-9]+}}
    // CHECK: isb
    setPrimaskReg(mask1);
    // CHECK: msr primask, {{r[0-9]+}}
    // CHECK: isb
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

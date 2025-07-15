// Cross-device integration test
// REQUIRES: thumbv6m
// RUN: %cc% %ccflags% %ccout% %T/%basename_t.o %s; objdump --mcpu=%mcpu% -d %T/%basename_t.o | FileCheck --allow-unused-prefixes --check-prefixes %prefixes% %s

#include "utils.hpp"

// Include device-specific headers based on device defines
#if defined(__CM0_REV)
    #include "cortexm0/special_regs.hpp"
    #include "cortexm0/barriers.hpp"
    #include "cortexm0/misc.hpp"
    using namespace CortexM0;
#elif defined(__CM0PLUS_REV)
    #include "cortexm0plus/special_regs.hpp"
    #include "cortexm0plus/barriers.hpp"
    #include "cortexm0plus/misc.hpp"
    using namespace CortexM0plus;
#elif defined(__CM1_REV)
    #include "cortexm1/special_regs.hpp"
    #include "cortexm1/barriers.hpp"
    #include "cortexm1/misc.hpp"
    using namespace CortexM1;
#elif defined(__CM3_REV)
    #include "cortexm3/special_regs.hpp"
    #include "cortexm3/barriers.hpp"
    #include "cortexm3/misc.hpp"
    using namespace CortexM3;
#endif

void test_universal_utilities() {
    // CHECK-LABEL: <{{.*test_universal_utilities.*}}>:
    
    // Test utilities that should work on all devices
    volatile auto ceil_div_result = Utils::intCeilDiv(1000, 7);
    
    uint32_t bit_test_value = 0x12345678;
    Utils::setBit(bit_test_value, 10);
    volatile bool bit_10_set = Utils::isBitSet(bit_test_value, 10);
    
    Utils::clearBit(bit_test_value, 5);
    volatile bool bit_5_clear = !Utils::isBitSet(bit_test_value, 5);
    
    // Test edge cases
    volatile auto edge_case_1 = Utils::intCeilDiv(1, 1000);  // Should be 1
    volatile auto edge_case_2 = Utils::intCeilDiv(0, 5);     // Should be 0
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_common_cortex_m_features() {
    // CHECK-LABEL: <{{.*test_common_cortex_m_features.*}}>:
    
    // Test features common to all Cortex-M processors
    
    // Memory barriers (available on all Cortex-M)
    InstrSyncBarrier();
    // CHECK: isb
    DataSyncBarrier();
    // CHECK: dsb
    DataMemBarrier();
    // CHECK: dmb
    
    // Special registers (available on all Cortex-M)
    volatile auto apsr = getApsrReg();
    // CHECK: mrs {{r[0-9]+}}, apsr
    volatile auto msp = getMspReg();
    // CHECK: mrs {{r[0-9]+}}, msp
    volatile auto psp = getPspReg();
    // CHECK: mrs {{r[0-9]+}}, psp
    volatile auto primask = getPrimaskReg();
    // CHECK: mrs {{r[0-9]+}}, primask
    volatile auto control = getControlReg();
    // CHECK: mrs {{r[0-9]+}}, control
    
    // Low power instructions
    waitForEvent();
    // CHECK: wfe
    sendEvent();
    // CHECK: sev
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_register_state_consistency() {
    // CHECK-LABEL: <{{.*test_register_state_consistency.*}}>:
    
    // Test that register operations maintain consistency
    
    // Save initial states
    volatile auto initial_msp = getMspReg();
    // CHECK: mrs {{r[0-9]+}}, msp
    volatile auto initial_psp = getPspReg();
    // CHECK: mrs {{r[0-9]+}}, psp
    volatile auto initial_control = getControlReg();
    // CHECK: mrs {{r[0-9]+}}, control
    volatile auto initial_primask = getPrimaskReg();
    // CHECK: mrs {{r[0-9]+}}, primask
    
    // Modify stack pointers
    setMspReg(0x20008000);
    // CHECK: msr msp, {{r[0-9]+}}
    // CHECK: isb
    setPspReg(0x20004000);
    // CHECK: msr psp, {{r[0-9]+}}
    // CHECK: isb
    
    // Verify changes
    volatile auto new_msp = getMspReg();
    // CHECK: mrs {{r[0-9]+}}, msp
    volatile auto new_psp = getPspReg();
    // CHECK: mrs {{r[0-9]+}}, psp
    
    volatile bool msp_changed = (new_msp == 0x20008000);
    volatile bool psp_changed = (new_psp == 0x20004000);
    
    // Test PRIMASK disable/enable
    Primask disable_mask;
    disable_mask.bits.exceptions_disabled = 1;
    setPrimaskReg(disable_mask);
    // CHECK: msr primask, {{r[0-9]+}}
    // CHECK: isb
    
    volatile auto disabled_primask = getPrimaskReg();
    // CHECK: mrs {{r[0-9]+}}, primask
    volatile bool exceptions_disabled = disabled_primask.bits.exceptions_disabled;
    
    Primask enable_mask;
    enable_mask.bits.exceptions_disabled = 0;
    setPrimaskReg(enable_mask);
    // CHECK: msr primask, {{r[0-9]+}}
    // CHECK: isb
    
    volatile auto enabled_primask = getPrimaskReg();
    // CHECK: mrs {{r[0-9]+}}, primask
    volatile bool exceptions_enabled = !enabled_primask.bits.exceptions_disabled;
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_device_specific_conditionals() {
    // CHECK-LABEL: <{{.*test_device_specific_conditionals.*}}>:
    
    // Test conditional compilation based on device features
    volatile uint32_t feature_flags = 0;
    
    #if defined(__MPU_PRESENT) && (__MPU_PRESENT == 1)
        feature_flags |= 0x01;  // MPU present
    #endif
    
    #if defined(__VTOR_PRESENT) && (__VTOR_PRESENT == 1)
        feature_flags |= 0x02;  // VTOR present
    #endif
    
    #if defined(__NVIC_PRIO_BITS)
        if (__NVIC_PRIO_BITS == 2) {
            feature_flags |= 0x10;  // 2-bit priorities (M0, M0+, M1)
        } else if (__NVIC_PRIO_BITS == 3) {
            feature_flags |= 0x20;  // 3-bit priorities (M3, M4, etc.)
        }
    #endif
    
    // Test device revision checking
    #if defined(__CM0_REV)
        feature_flags |= 0x100;
    #elif defined(__CM0PLUS_REV)
        feature_flags |= 0x200;
    #elif defined(__CM1_REV)
        feature_flags |= 0x300;
    #elif defined(__CM3_REV)
        feature_flags |= 0x400;
    #endif
    
    volatile uint32_t final_flags = feature_flags;
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_optimization_across_devices() {
    // CHECK-LABEL: <{{.*test_optimization_across_devices.*}}>:
    
    // Test that optimizations work consistently across devices
    
    // Bit operations should be efficient on all devices
    uint32_t value = 0;
    for (uint8_t i = 0; i < 16; ++i) {
        Utils::setBit(value, i);
    }
    
    for (uint8_t i = 16; i < 32; ++i) {
        Utils::clearBit(value, i);
    }
    
    // Should result in 0x0000FFFF
    volatile bool pattern_correct = (value == 0x0000FFFF);
    
    // Integer ceiling division with constants should optimize well
    constexpr auto const_result = Utils::intCeilDiv(1000, 7);
    volatile auto runtime_copy = const_result;
    
    // Register access should be single instructions
    volatile auto quick_apsr1 = getApsrReg();
    // CHECK: mrs {{r[0-9]+}}, apsr
    volatile auto quick_apsr2 = getApsrReg();
    // CHECK: mrs {{r[0-9]+}}, apsr
    
    // Barriers should be single instructions
    DataMemBarrier();
    // CHECK: dmb
    DataSyncBarrier();
    // CHECK: dsb
    InstrSyncBarrier();
    // CHECK: isb
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

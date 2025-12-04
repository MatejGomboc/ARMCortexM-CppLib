#include "armcortex/m3/systick.hpp"

// Test reading CTRL register
extern "C" [[gnu::naked]] void test_read_ctrl() {
    auto ctrl = ArmCortex::SysTick::CTRL(ArmCortex::SYS_TICK->CTRL);
    (void)ctrl;
}

// CHECK-LABEL: <test_read_ctrl>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #0]
// CHECK-NEXT: .word 0xe000e010
// CHECK-EMPTY:

// Test writing CTRL register
extern "C" [[gnu::naked]] void test_write_ctrl() {
    ArmCortex::SysTick::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.TICKINT = 1;
    ctrl.bits.CLKSOURCE = 1;
    ArmCortex::SYS_TICK->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_write_ctrl>:
// CHECK: movs r{{[0-9]}}, #7
// CHECK: str r{{[0-9]}}, [r{{[0-9]}}, #0]
// CHECK: .word 0xe000e010
// CHECK-EMPTY:

// Test reading LOAD register
extern "C" [[gnu::naked]] void test_read_load() {
    uint32_t load = ArmCortex::SYS_TICK->LOAD;
    (void)load;
}

// CHECK-LABEL: <test_read_load>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #4]
// CHECK-NEXT: .word 0xe000e010
// CHECK-EMPTY:

// Test writing LOAD register
extern "C" [[gnu::naked]] void test_write_load() {
    ArmCortex::SYS_TICK->LOAD = 0xFFFFFF;
}

// CHECK-LABEL: <test_write_load>:
// CHECK: str r{{[0-9]}}, [r{{[0-9]}}, #4]
// CHECK: .word 0xe000e010
// CHECK: .word 0x00ffffff
// CHECK-EMPTY:

// Test reading VAL register
extern "C" [[gnu::naked]] void test_read_val() {
    uint32_t val = ArmCortex::SYS_TICK->VAL;
    (void)val;
}

// CHECK-LABEL: <test_read_val>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #8]
// CHECK-NEXT: .word 0xe000e010
// CHECK-EMPTY:

// Test writing VAL register (clears counter)
extern "C" [[gnu::naked]] void test_write_val() {
    ArmCortex::SYS_TICK->VAL = 0;
}

// CHECK-LABEL: <test_write_val>:
// CHECK: movs r{{[0-9]}}, #0
// CHECK: str r{{[0-9]}}, [r{{[0-9]}}, #8]
// CHECK: .word 0xe000e010
// CHECK-EMPTY:

// Test reading CALIB register
extern "C" [[gnu::naked]] void test_read_calib() {
    auto calib = ArmCortex::SysTick::CALIB(ArmCortex::SYS_TICK->CALIB);
    (void)calib;
}

// CHECK-LABEL: <test_read_calib>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #12]
// CHECK-NEXT: .word 0xe000e010
// CHECK-EMPTY:

// Test enabling SysTick with CPU clock
extern "C" [[gnu::naked]] void test_enable_systick() {
    ArmCortex::SysTick::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.CLKSOURCE = static_cast<uint32_t>(ArmCortex::SysTick::CTRL::CLKSOURCE::CPU);
    ArmCortex::SYS_TICK->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_enable_systick>:
// CHECK: movs r{{[0-9]}}, #5
// CHECK: str r{{[0-9]}}, [r{{[0-9]}}, #0]
// CHECK: .word 0xe000e010
// CHECK-EMPTY:

// Test disabling SysTick
extern "C" [[gnu::naked]] void test_disable_systick() {
    ArmCortex::SysTick::CTRL ctrl;
    ctrl.bits.ENABLE = 0;
    ArmCortex::SYS_TICK->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_disable_systick>:
// CHECK: movs r{{[0-9]}}, #0
// CHECK: str r{{[0-9]}}, [r{{[0-9]}}, #0]
// CHECK: .word 0xe000e010
// CHECK-EMPTY:

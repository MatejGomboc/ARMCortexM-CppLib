#include "m0plus/systick.hpp"

// Test reading CTRL register
extern "C" [[gnu::naked]] void test_read_ctrl() {
    auto ctrl = Cortex::M0Plus::SysTick::CTRL(Cortex::M0Plus::SYS_TICK->CTRL);
    (void)ctrl;
}

// CHECK-LABEL: <test_read_ctrl>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #0]
// CHECK-NEXT: .word 0xe000e010
// CHECK-EMPTY:

// Test writing CTRL register
extern "C" [[gnu::naked]] void test_write_ctrl() {
    Cortex::M0Plus::SysTick::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.TICKINT = 1;
    ctrl.bits.CLKSOURCE = 1;
    Cortex::M0Plus::SYS_TICK->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_write_ctrl>:
// CHECK-NEXT: movs r2, #7
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: str r2, [r3, #0]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000e010
// CHECK-EMPTY:

// Test reading LOAD register
extern "C" [[gnu::naked]] void test_read_load() {
    auto load = Cortex::M0Plus::SYS_TICK->LOAD;
    (void)load;
}

// CHECK-LABEL: <test_read_load>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #4]
// CHECK-NEXT: .word 0xe000e010
// CHECK-EMPTY:

// Test writing LOAD register
extern "C" [[gnu::naked]] void test_write_load() {
    Cortex::M0Plus::SYS_TICK->LOAD = 0xFFFFFF;
}

// CHECK-LABEL: <test_write_load>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr r2, [pc, #8]
// CHECK-NEXT: str r2, [r3, #4]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000e010
// CHECK-NEXT: .word 0x00ffffff
// CHECK-EMPTY:

// Test reading VAL register
extern "C" [[gnu::naked]] void test_read_val() {
    auto val = Cortex::M0Plus::SYS_TICK->VAL;
    (void)val;
}

// CHECK-LABEL: <test_read_val>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #8]
// CHECK-NEXT: .word 0xe000e010
// CHECK-EMPTY:

// Test writing VAL register (clears counter)
extern "C" [[gnu::naked]] void test_write_val() {
    Cortex::M0Plus::SYS_TICK->VAL = 0;
}

// CHECK-LABEL: <test_write_val>:
// CHECK-NEXT: movs r2, #0
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: str r2, [r3, #8]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000e010
// CHECK-EMPTY:

// Test reading CALIB register
extern "C" [[gnu::naked]] void test_read_calib() {
    auto calib = Cortex::M0Plus::SysTick::CALIB(Cortex::M0Plus::SYS_TICK->CALIB);
    (void)calib;
}

// CHECK-LABEL: <test_read_calib>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #12]
// CHECK-NEXT: .word 0xe000e010
// CHECK-EMPTY:

// Test enabling SysTick with CPU clock
extern "C" [[gnu::naked]] void test_enable_systick() {
    Cortex::M0Plus::SysTick::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.CLKSOURCE = static_cast<uint32_t>(Cortex::M0Plus::SysTick::CTRL::CLKSOURCE::CPU);
    Cortex::M0Plus::SYS_TICK->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_enable_systick>:
// CHECK-NEXT: movs r2, #5
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: str r2, [r3, #0]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000e010
// CHECK-EMPTY:

// Test disabling SysTick
extern "C" [[gnu::naked]] void test_disable_systick() {
    Cortex::M0Plus::SysTick::CTRL ctrl;
    ctrl.bits.ENABLE = 0;
    Cortex::M0Plus::SYS_TICK->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_disable_systick>:
// CHECK-NEXT: movs r2, #0
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: str r2, [r3, #0]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000e010
// CHECK-EMPTY:

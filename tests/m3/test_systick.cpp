#include "armcortex/m3/systick.hpp"

// Test reading CTRL register
extern "C" [[gnu::naked]] void test_read_ctrl() {
    auto ctrl = ArmCortex::SysTick::CTRL(ArmCortex::SYS_TICK->CTRL);
    (void)ctrl;
}

// CHECK-LABEL: <test_read_ctrl>:
// CHECK-NEXT: mov.w r3, #3758153728
// CHECK-NEXT: ldr r3, [r3, #16]
// MAXSPEED-CHECK-NEXT: nop
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
// CHECK-NEXT: mov.w r3, #3758153728
// CHECK-NEXT: movs r2, #7
// CHECK-NEXT: str r2, [r3, #16]
// CHECK-EMPTY:

// Test reading LOAD register
extern "C" [[gnu::naked]] void test_read_load() {
    uint32_t load = ArmCortex::SYS_TICK->LOAD;
    (void)load;
}

// CHECK-LABEL: <test_read_load>:
// CHECK-NEXT: mov.w r3, #3758153728
// CHECK-NEXT: ldr r3, [r3, #20]
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// Test writing LOAD register
extern "C" [[gnu::naked]] void test_write_load() {
    ArmCortex::SYS_TICK->LOAD = 0xFFFFFF;
}

// CHECK-LABEL: <test_write_load>:
// CHECK-NEXT: mov.w r3, #3758153728
// CHECK-NEXT: mvn.w r2, #4278190080
// CHECK-NEXT: str r2, [r3, #20]
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// Test reading VAL register
extern "C" [[gnu::naked]] void test_read_val() {
    uint32_t val = ArmCortex::SYS_TICK->VAL;
    (void)val;
}

// CHECK-LABEL: <test_read_val>:
// CHECK-NEXT: mov.w r3, #3758153728
// CHECK-NEXT: ldr r3, [r3, #24]
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// Test writing VAL register (clears counter)
extern "C" [[gnu::naked]] void test_write_val() {
    ArmCortex::SYS_TICK->VAL = 0;
}

// CHECK-LABEL: <test_write_val>:
// CHECK-NEXT: mov.w r3, #3758153728
// CHECK-NEXT: movs r2, #0
// CHECK-NEXT: str r2, [r3, #24]
// CHECK-EMPTY:

// Test reading CALIB register
extern "C" [[gnu::naked]] void test_read_calib() {
    auto calib = ArmCortex::SysTick::CALIB(ArmCortex::SYS_TICK->CALIB);
    (void)calib;
}

// CHECK-LABEL: <test_read_calib>:
// CHECK-NEXT: mov.w r3, #3758153728
// CHECK-NEXT: ldr r3, [r3, #28]
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// Test enabling SysTick with CPU clock
extern "C" [[gnu::naked]] void test_enable_systick() {
    ArmCortex::SysTick::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.CLKSOURCE = static_cast<uint32_t>(ArmCortex::SysTick::CTRL::CLKSOURCE::CPU);
    ArmCortex::SYS_TICK->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_enable_systick>:
// CHECK-NEXT: mov.w r3, #3758153728
// CHECK-NEXT: movs r2, #5
// CHECK-NEXT: str r2, [r3, #16]
// CHECK-EMPTY:

// Test disabling SysTick
extern "C" [[gnu::naked]] void test_disable_systick() {
    ArmCortex::SysTick::CTRL ctrl;
    ctrl.bits.ENABLE = 0;
    ArmCortex::SYS_TICK->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_disable_systick>:
// CHECK-NEXT: mov.w r3, #3758153728
// CHECK-NEXT: movs r2, #0
// CHECK-NEXT: str r2, [r3, #16]
// CHECK-EMPTY:

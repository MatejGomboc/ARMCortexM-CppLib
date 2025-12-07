#include "armcortex/m3/systick.hpp"

// Test reading CTRL register
extern "C" [[gnu::naked]] auto test_read_ctrl() {
    return ArmCortex::SysTick::CTRL(ArmCortex::SYS_TICK->CTRL);
}

// CHECK-LABEL: <test_read_ctrl>:
// CHECK-NEXT: mov.w r3, #3758153728
// CHECK-NEXT: ldr r0, [r3, #16]
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
extern "C" [[gnu::naked]] uint32_t test_read_load() {
    return ArmCortex::SYS_TICK->LOAD;
}

// CHECK-LABEL: <test_read_load>:
// CHECK-NEXT: mov.w r3, #3758153728
// CHECK-NEXT: ldr r0, [r3, #20]
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
extern "C" [[gnu::naked]] uint32_t test_read_val() {
    return ArmCortex::SYS_TICK->VAL;
}

// CHECK-LABEL: <test_read_val>:
// CHECK-NEXT: mov.w r3, #3758153728
// CHECK-NEXT: ldr r0, [r3, #24]
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
extern "C" [[gnu::naked]] auto test_read_calib() {
    return ArmCortex::SysTick::CALIB(ArmCortex::SYS_TICK->CALIB);
}

// CHECK-LABEL: <test_read_calib>:
// CHECK-NEXT: mov.w r3, #3758153728
// CHECK-NEXT: ldr r0, [r3, #28]
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

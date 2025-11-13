#include "m0plus/systick.hpp"

// Test reading CTRL register
extern "C" [[gnu::naked]] void test_read_ctrl() {
    auto ctrl = Cortex::M0Plus::SysTick::CTRL(Cortex::M0Plus::SYS_TICK->CTRL);
    (void)ctrl;
}

// CHECK-LABEL: <test_read_ctrl>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: ldr{{.*}} r0, [r{{[0-9]+}}]
// CHECK: bx lr

// Test writing CTRL register
extern "C" [[gnu::naked]] void test_write_ctrl() {
    Cortex::M0Plus::SysTick::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.TICKINT = 1;
    ctrl.bits.CLKSOURCE = 1;
    Cortex::M0Plus::SYS_TICK->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_write_ctrl>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: mov{{.*}} r{{[0-9]+}}, #7
// CHECK: str{{.*}} r{{[0-9]+}}, [r{{[0-9]+}}]
// CHECK: bx lr

// Test reading LOAD register
extern "C" [[gnu::naked]] void test_read_load() {
    auto load = Cortex::M0Plus::SYS_TICK->LOAD;
    (void)load;
}

// CHECK-LABEL: <test_read_load>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: ldr{{.*}} r0, [r{{[0-9]+}}, #4]
// CHECK: bx lr

// Test writing LOAD register
extern "C" [[gnu::naked]] void test_write_load() {
    Cortex::M0Plus::SYS_TICK->LOAD = 0xFFFFFF;
}

// CHECK-LABEL: <test_write_load>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: str{{.*}} r{{[0-9]+}}, [r{{[0-9]+}}, #4]
// CHECK: bx lr

// Test reading VAL register
extern "C" [[gnu::naked]] void test_read_val() {
    auto val = Cortex::M0Plus::SYS_TICK->VAL;
    (void)val;
}

// CHECK-LABEL: <test_read_val>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: ldr{{.*}} r0, [r{{[0-9]+}}, #8]
// CHECK: bx lr

// Test writing VAL register (clears counter)
extern "C" [[gnu::naked]] void test_write_val() {
    Cortex::M0Plus::SYS_TICK->VAL = 0;
}

// CHECK-LABEL: <test_write_val>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: mov{{.*}} r{{[0-9]+}}, #0
// CHECK: str{{.*}} r{{[0-9]+}}, [r{{[0-9]+}}, #8]
// CHECK: bx lr

// Test reading CALIB register
extern "C" [[gnu::naked]] void test_read_calib() {
    auto calib = Cortex::M0Plus::SysTick::CALIB(Cortex::M0Plus::SYS_TICK->CALIB);
    (void)calib;
}

// CHECK-LABEL: <test_read_calib>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: ldr{{.*}} r0, [r{{[0-9]+}}, #12]
// CHECK: bx lr

// Test enabling SysTick with CPU clock
extern "C" [[gnu::naked]] void test_enable_systick() {
    Cortex::M0Plus::SysTick::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.CLKSOURCE = static_cast<uint32_t>(Cortex::M0Plus::SysTick::CTRL::CLKSOURCE::CPU);
    Cortex::M0Plus::SYS_TICK->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_enable_systick>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: mov{{.*}} r{{[0-9]+}}, #5
// CHECK: str{{.*}} r{{[0-9]+}}, [r{{[0-9]+}}]
// CHECK: bx lr

// Test disabling SysTick
extern "C" [[gnu::naked]] void test_disable_systick() {
    Cortex::M0Plus::SysTick::CTRL ctrl;
    ctrl.bits.ENABLE = 0;
    Cortex::M0Plus::SYS_TICK->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_disable_systick>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: mov{{.*}} r{{[0-9]+}}, #0
// CHECK: str{{.*}} r{{[0-9]+}}, [r{{[0-9]+}}]
// CHECK: bx lr

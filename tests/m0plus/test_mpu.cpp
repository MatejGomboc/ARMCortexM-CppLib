#include "m0plus/mpu.hpp"

// Test reading TYPE register
extern "C" [[gnu::naked]] void test_read_type() {
    auto type = Cortex::M0Plus::Mpu::TYPE(Cortex::M0Plus::MPU->TYPE);
    (void)type;
}

// CHECK-LABEL: <test_read_type>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: ldr{{.*}} r0, [r{{[0-9]+}}]
// CHECK: bx lr

// Test reading CTRL register
extern "C" [[gnu::naked]] void test_read_ctrl() {
    auto ctrl = Cortex::M0Plus::Mpu::CTRL(Cortex::M0Plus::MPU->CTRL);
    (void)ctrl;
}

// CHECK-LABEL: <test_read_ctrl>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: ldr{{.*}} r0, [r{{[0-9]+}}, #4]
// CHECK: bx lr

// Test writing CTRL register
extern "C" [[gnu::naked]] void test_write_ctrl() {
    Cortex::M0Plus::Mpu::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.PRIVDEFENA = 1;
    Cortex::M0Plus::MPU->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_write_ctrl>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: mov{{.*}} r{{[0-9]+}}, #5
// CHECK: str{{.*}} r{{[0-9]+}}, [r{{[0-9]+}}, #4]
// CHECK: bx lr

// Test reading RNR register
extern "C" [[gnu::naked]] void test_read_rnr() {
    auto rnr = Cortex::M0Plus::MPU->RNR;
    (void)rnr;
}

// CHECK-LABEL: <test_read_rnr>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: ldr{{.*}} r0, [r{{[0-9]+}}, #8]
// CHECK: bx lr

// Test writing RNR register
extern "C" [[gnu::naked]] void test_write_rnr() {
    Cortex::M0Plus::MPU->RNR = 3;
}

// CHECK-LABEL: <test_write_rnr>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: mov{{.*}} r{{[0-9]+}}, #3
// CHECK: str{{.*}} r{{[0-9]+}}, [r{{[0-9]+}}, #8]
// CHECK: bx lr

// Test reading RBAR register
extern "C" [[gnu::naked]] void test_read_rbar() {
    auto rbar = Cortex::M0Plus::Mpu::RBAR(Cortex::M0Plus::MPU->RBAR);
    (void)rbar;
}

// CHECK-LABEL: <test_read_rbar>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: ldr{{.*}} r0, [r{{[0-9]+}}, #12]
// CHECK: bx lr

// Test writing RBAR register
extern "C" [[gnu::naked]] void test_write_rbar() {
    Cortex::M0Plus::Mpu::RBAR rbar;
    rbar.bits.ADDR = 0x20000000 >> 5;
    rbar.bits.VALID = 1;
    rbar.bits.REGION = 2;
    Cortex::M0Plus::MPU->RBAR = rbar.value;
}

// CHECK-LABEL: <test_write_rbar>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: str{{.*}} r{{[0-9]+}}, [r{{[0-9]+}}, #12]
// CHECK: bx lr

// Test reading RASR register
extern "C" [[gnu::naked]] void test_read_rasr() {
    auto rasr = Cortex::M0Plus::Mpu::RASR(Cortex::M0Plus::MPU->RASR);
    (void)rasr;
}

// CHECK-LABEL: <test_read_rasr>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: ldr{{.*}} r0, [r{{[0-9]+}}, #16]
// CHECK: bx lr

// Test writing RASR register
extern "C" [[gnu::naked]] void test_write_rasr() {
    Cortex::M0Plus::Mpu::RASR rasr;
    rasr.bits.ENABLE = 1;
    rasr.bits.SIZE = 10;  // 2KB region
    rasr.bits.AP = static_cast<uint32_t>(Cortex::M0Plus::Mpu::RASR::AP::RW);
    rasr.setScbFlags(Cortex::M0Plus::Mpu::RASR::SCB::INTERN_SRAM);
    Cortex::M0Plus::MPU->RASR = rasr.value;
}

// CHECK-LABEL: <test_write_rasr>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: str{{.*}} r{{[0-9]+}}, [r{{[0-9]+}}, #16]
// CHECK: bx lr

// Test configureRegion function
extern "C" [[gnu::naked]] void test_configure_region() {
    Cortex::M0Plus::Mpu::RASR rasr;
    rasr.bits.ENABLE = 1;
    rasr.bits.SIZE = 12;
    rasr.bits.AP = static_cast<uint32_t>(Cortex::M0Plus::Mpu::RASR::AP::PRIV_RW);
    rasr.setScbFlags(Cortex::M0Plus::Mpu::RASR::SCB::FLASH);
    Cortex::M0Plus::Mpu::configureRegion(0, 0x08000000, rasr);
}

// CHECK-LABEL: <test_configure_region>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: mov{{.*}} r{{[0-9]+}}, #0
// CHECK: str{{.*}} r{{[0-9]+}}, [r{{[0-9]+}}, #8]
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: str{{.*}} r{{[0-9]+}}, [r{{[0-9]+}}, #12]
// CHECK: str{{.*}} r{{[0-9]+}}, [r{{[0-9]+}}, #16]
// CHECK: dsb sy
// CHECK: isb sy
// CHECK: bx lr

// Test enabling MPU
extern "C" [[gnu::naked]] void test_enable_mpu() {
    Cortex::M0Plus::Mpu::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.PRIVDEFENA = 1;
    Cortex::M0Plus::MPU->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_enable_mpu>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: mov{{.*}} r{{[0-9]+}}, #5
// CHECK: str{{.*}} r{{[0-9]+}}, [r{{[0-9]+}}, #4]
// CHECK: bx lr

// Test disabling MPU
extern "C" [[gnu::naked]] void test_disable_mpu() {
    Cortex::M0Plus::Mpu::CTRL ctrl;
    ctrl.bits.ENABLE = 0;
    Cortex::M0Plus::MPU->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_disable_mpu>:
// CHECK: ldr{{.*}} r{{[0-9]+}}, {{.*}}
// CHECK: mov{{.*}} r{{[0-9]+}}, #0
// CHECK: str{{.*}} r{{[0-9]+}}, [r{{[0-9]+}}, #4]
// CHECK: bx lr

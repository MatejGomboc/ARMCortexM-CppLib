#include "armcortex/m3/mpu.hpp"

// Test reading TYPE register
extern "C" [[gnu::naked]] void test_read_type() {
    auto type = ArmCortex::Mpu::TYPE(ArmCortex::MPU->TYPE);
    (void)type;
}

// CHECK-LABEL: <test_read_type>:
// CHECK: ldr r3,
// CHECK: .word 0xe000ed90
// CHECK-EMPTY:

// Test reading CTRL register
extern "C" [[gnu::naked]] void test_read_ctrl() {
    auto ctrl = ArmCortex::Mpu::CTRL(ArmCortex::MPU->CTRL);
    (void)ctrl;
}

// CHECK-LABEL: <test_read_ctrl>:
// CHECK: ldr r3,
// CHECK: .word 0xe000ed90
// CHECK-EMPTY:

// Test writing CTRL register
extern "C" [[gnu::naked]] void test_write_ctrl() {
    ArmCortex::Mpu::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.PRIVDEFENA = 1;
    ArmCortex::MPU->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_write_ctrl>:
// CHECK: movs r{{[0-9]}}, #5
// CHECK: str r{{[0-9]}},
// CHECK: .word 0xe000ed90
// CHECK-EMPTY:

// Test reading RNR register
extern "C" [[gnu::naked]] void test_read_rnr() {
    uint32_t rnr = ArmCortex::MPU->RNR;
    (void)rnr;
}

// CHECK-LABEL: <test_read_rnr>:
// CHECK: ldr r3,
// CHECK: .word 0xe000ed90
// CHECK-EMPTY:

// Test writing RNR register
extern "C" [[gnu::naked]] void test_write_rnr() {
    ArmCortex::MPU->RNR = 3;
}

// CHECK-LABEL: <test_write_rnr>:
// CHECK: movs r{{[0-9]}}, #3
// CHECK: str r{{[0-9]}},
// CHECK: .word 0xe000ed90
// CHECK-EMPTY:

// Test reading RBAR register
extern "C" [[gnu::naked]] void test_read_rbar() {
    auto rbar = ArmCortex::Mpu::RBAR(ArmCortex::MPU->RBAR);
    (void)rbar;
}

// CHECK-LABEL: <test_read_rbar>:
// CHECK: ldr r3,
// CHECK: .word 0xe000ed90
// CHECK-EMPTY:

// Test writing RBAR register
extern "C" [[gnu::naked]] void test_write_rbar() {
    ArmCortex::Mpu::RBAR rbar;
    rbar.bits.ADDR = 0x20000000 >> 5;
    rbar.bits.VALID = 1;
    rbar.bits.REGION = 2;
    ArmCortex::MPU->RBAR = rbar.value;
}

// CHECK-LABEL: <test_write_rbar>:
// CHECK: str r{{[0-9]}},
// CHECK: .word 0xe000ed90
// CHECK: .word 0x20000012
// CHECK-EMPTY:

// Test reading RASR register
extern "C" [[gnu::naked]] void test_read_rasr() {
    auto rasr = ArmCortex::Mpu::RASR(ArmCortex::MPU->RASR);
    (void)rasr;
}

// CHECK-LABEL: <test_read_rasr>:
// CHECK: ldr r3,
// CHECK: .word 0xe000ed90
// CHECK-EMPTY:

// Test writing RASR register
extern "C" [[gnu::naked]] void test_write_rasr() {
    ArmCortex::Mpu::RASR rasr;
    rasr.bits.ENABLE = 1;
    rasr.bits.SIZE = 10; // 2KB region
    rasr.bits.AP = static_cast<uint32_t>(ArmCortex::Mpu::RASR::AP::RW);
    rasr.setTexScbFlags(ArmCortex::Mpu::RASR::TEXSCB::INTERN_SRAM);
    ArmCortex::MPU->RASR = rasr.value;
}

// CHECK-LABEL: <test_write_rasr>:
// CHECK: str r{{[0-9]}},
// CHECK: .word 0xe000ed90
// CHECK: .word 0x03060015
// CHECK-EMPTY:

// Test configureRegion function
extern "C" [[gnu::naked]] void test_configure_region() {
    ArmCortex::Mpu::RASR rasr;
    rasr.bits.ENABLE = 1;
    rasr.bits.SIZE = 12;
    rasr.bits.AP = static_cast<uint32_t>(ArmCortex::Mpu::RASR::AP::PRIV_RW);
    rasr.setTexScbFlags(ArmCortex::Mpu::RASR::TEXSCB::FLASH);
    ArmCortex::Mpu::configureRegion(0, 0x08000000, rasr);
}

// CHECK-LABEL: <test_configure_region>:
// CHECK: str r{{[0-9]}},
// CHECK: dsb sy
// CHECK: isb sy
// CHECK: .word 0xe000ed90
// CHECK: .word 0x01020019
// CHECK-EMPTY:

// Test enabling MPU
extern "C" [[gnu::naked]] void test_enable_mpu() {
    ArmCortex::Mpu::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.PRIVDEFENA = 1;
    ArmCortex::MPU->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_enable_mpu>:
// CHECK: movs r{{[0-9]}}, #5
// CHECK: str r{{[0-9]}},
// CHECK: .word 0xe000ed90
// CHECK-EMPTY:

// Test disabling MPU
extern "C" [[gnu::naked]] void test_disable_mpu() {
    ArmCortex::Mpu::CTRL ctrl;
    ctrl.bits.ENABLE = 0;
    ArmCortex::MPU->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_disable_mpu>:
// CHECK: movs r{{[0-9]}}, #0
// CHECK: str r{{[0-9]}},
// CHECK: .word 0xe000ed90
// CHECK-EMPTY:

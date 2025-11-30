#include "m0plus/mpu.hpp"

// Test reading TYPE register
extern "C" [[gnu::naked]] void test_read_type() {
    auto type = ArmCortex::M0Plus::Mpu::TYPE(Cortex::M0Plus::MPU->TYPE);
    (void)type;
}

// CHECK-LABEL: <test_read_type>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #0]
// CHECK-NEXT: .word 0xe000ed90
// CHECK-EMPTY:

// Test reading CTRL register
extern "C" [[gnu::naked]] void test_read_ctrl() {
    auto ctrl = ArmCortex::M0Plus::Mpu::CTRL(Cortex::M0Plus::MPU->CTRL);
    (void)ctrl;
}

// CHECK-LABEL: <test_read_ctrl>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #4]
// CHECK-NEXT: .word 0xe000ed90
// CHECK-EMPTY:

// Test writing CTRL register
extern "C" [[gnu::naked]] void test_write_ctrl() {
    ArmCortex::M0Plus::Mpu::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.PRIVDEFENA = 1;
    ArmCortex::M0Plus::MPU->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_write_ctrl>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #5
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000ed90

// MINSIZE-CHECK-NEXT: movs r2, #5
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000ed90

// MAXSPEED-CHECK-NEXT: movs r2, #5
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000ed90

// CHECK-EMPTY:

// Test reading RNR register
extern "C" [[gnu::naked]] void test_read_rnr() {
    uint32_t rnr = ArmCortex::M0Plus::MPU->RNR;
    (void)rnr;
}

// CHECK-LABEL: <test_read_rnr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #8]
// CHECK-NEXT: .word 0xe000ed90
// CHECK-EMPTY:

// Test writing RNR register
extern "C" [[gnu::naked]] void test_write_rnr() {
    ArmCortex::M0Plus::MPU->RNR = 3;
}

// CHECK-LABEL: <test_write_rnr>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #3
// DEBUG-CHECK-NEXT: str r2, [r3, #8]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000ed90

// MINSIZE-CHECK-NEXT: movs r2, #3
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str r2, [r3, #8]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000ed90

// MAXSPEED-CHECK-NEXT: movs r2, #3
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #8]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000ed90

// CHECK-EMPTY:

// Test reading RBAR register
extern "C" [[gnu::naked]] void test_read_rbar() {
    auto rbar = ArmCortex::M0Plus::Mpu::RBAR(Cortex::M0Plus::MPU->RBAR);
    (void)rbar;
}

// CHECK-LABEL: <test_read_rbar>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #12]
// CHECK-NEXT: .word 0xe000ed90
// CHECK-EMPTY:

// Test writing RBAR register
extern "C" [[gnu::naked]] void test_write_rbar() {
    ArmCortex::M0Plus::Mpu::RBAR rbar;
    rbar.bits.ADDR = 0x20000000 >> 5;
    rbar.bits.VALID = 1;
    rbar.bits.REGION = 2;
    ArmCortex::M0Plus::MPU->RBAR = rbar.value;
}

// CHECK-LABEL: <test_write_rbar>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr r2, [pc, #8]
// CHECK-NEXT: str r2, [r3, #12]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed90
// CHECK-NEXT: .word 0x20000012
// CHECK-EMPTY:

// Test reading RASR register
extern "C" [[gnu::naked]] void test_read_rasr() {
    auto rasr = ArmCortex::M0Plus::Mpu::RASR(Cortex::M0Plus::MPU->RASR);
    (void)rasr;
}

// CHECK-LABEL: <test_read_rasr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #16]
// CHECK-NEXT: .word 0xe000ed90
// CHECK-EMPTY:

// Test writing RASR register
extern "C" [[gnu::naked]] void test_write_rasr() {
    ArmCortex::M0Plus::Mpu::RASR rasr;
    rasr.bits.ENABLE = 1;
    rasr.bits.SIZE = 10; // 2KB region
    rasr.bits.AP = static_cast<uint32_t>(Cortex::M0Plus::Mpu::RASR::AP::RW);
    rasr.setScbFlags(Cortex::M0Plus::Mpu::RASR::SCB::INTERN_SRAM);
    ArmCortex::M0Plus::MPU->RASR = rasr.value;
}

// CHECK-LABEL: <test_write_rasr>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr r2, [pc, #8]
// CHECK-NEXT: str r2, [r3, #16]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed90
// CHECK-NEXT: .word 0x03050015
// CHECK-EMPTY:

// Test configureRegion function
extern "C" [[gnu::naked]] void test_configure_region() {
    ArmCortex::M0Plus::Mpu::RASR rasr;
    rasr.bits.ENABLE = 1;
    rasr.bits.SIZE = 12;
    rasr.bits.AP = static_cast<uint32_t>(Cortex::M0Plus::Mpu::RASR::AP::PRIV_RW);
    rasr.setScbFlags(Cortex::M0Plus::Mpu::RASR::SCB::FLASH);
    ArmCortex::M0Plus::Mpu::configureRegion(0, 0x08000000, rasr);
}

// CHECK-LABEL: <test_configure_region>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #20]
// DEBUG-CHECK-NEXT: movs r2, #0
// DEBUG-CHECK-NEXT: str r2, [r3, #8]
// DEBUG-CHECK-NEXT: movs r2, #128
// DEBUG-CHECK-NEXT: lsls r2, r2, #20
// DEBUG-CHECK-NEXT: str r2, [r3, #12]
// DEBUG-CHECK-NEXT: ldr r2, [pc, #12]
// DEBUG-CHECK-NEXT: str r2, [r3, #16]
// DEBUG-CHECK-NEXT: dsb sy
// DEBUG-CHECK-NEXT: isb sy
// DEBUG-CHECK-NEXT: .word 0xe000ed90
// DEBUG-CHECK-NEXT: .word 0x01040019

// MINSIZE-CHECK-NEXT: movs r2, #0
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #20]
// MINSIZE-CHECK-NEXT: str r2, [r3, #8]
// MINSIZE-CHECK-NEXT: movs r2, #128
// MINSIZE-CHECK-NEXT: lsls r2, r2, #20
// MINSIZE-CHECK-NEXT: str r2, [r3, #12]
// MINSIZE-CHECK-NEXT: ldr r2, [pc, #12]
// MINSIZE-CHECK-NEXT: str r2, [r3, #16]
// MINSIZE-CHECK-NEXT: dsb sy
// MINSIZE-CHECK-NEXT: isb sy
// MINSIZE-CHECK-NEXT: .word 0xe000ed90
// MINSIZE-CHECK-NEXT: .word 0x01040019

// MAXSPEED-CHECK-NEXT: movs r2, #0
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #20]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #8]
// MAXSPEED-CHECK-NEXT: movs r2, #128
// MAXSPEED-CHECK-NEXT: lsls r2, r2, #20
// MAXSPEED-CHECK-NEXT: str r2, [r3, #12]
// MAXSPEED-CHECK-NEXT: ldr r2, [pc, #12]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #16]
// MAXSPEED-CHECK-NEXT: dsb sy
// MAXSPEED-CHECK-NEXT: isb sy
// MAXSPEED-CHECK-NEXT: .word 0xe000ed90
// MAXSPEED-CHECK-NEXT: .word 0x01040019

// CHECK-EMPTY:

// Test enabling MPU
extern "C" [[gnu::naked]] void test_enable_mpu() {
    ArmCortex::M0Plus::Mpu::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.PRIVDEFENA = 1;
    ArmCortex::M0Plus::MPU->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_enable_mpu>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #5
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000ed90

// MINSIZE-CHECK-NEXT: movs r2, #5
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000ed90

// MAXSPEED-CHECK-NEXT: movs r2, #5
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000ed90

// CHECK-EMPTY:

// Test disabling MPU
extern "C" [[gnu::naked]] void test_disable_mpu() {
    ArmCortex::M0Plus::Mpu::CTRL ctrl;
    ctrl.bits.ENABLE = 0;
    ArmCortex::M0Plus::MPU->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_disable_mpu>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #0
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000ed90

// MINSIZE-CHECK-NEXT: movs r2, #0
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000ed90

// MAXSPEED-CHECK-NEXT: movs r2, #0
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000ed90

// CHECK-EMPTY:

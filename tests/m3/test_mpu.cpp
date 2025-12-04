#include "armcortex/m3/mpu.hpp"

// Test reading TYPE register
extern "C" [[gnu::naked]] void test_read_type() {
    auto type = ArmCortex::Mpu::TYPE(ArmCortex::MPU->TYPE);
    (void)type;
}

// CHECK-LABEL: <test_read_type>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr.w r3, [r3, #144]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading CTRL register
extern "C" [[gnu::naked]] void test_read_ctrl() {
    auto ctrl = ArmCortex::Mpu::CTRL(ArmCortex::MPU->CTRL);
    (void)ctrl;
}

// CHECK-LABEL: <test_read_ctrl>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr.w r3, [r3, #148]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing CTRL register
extern "C" [[gnu::naked]] void test_write_ctrl() {
    ArmCortex::Mpu::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.PRIVDEFENA = 1;
    ArmCortex::MPU->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_write_ctrl>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #5
// DEBUG-CHECK-NEXT: str.w r2, [r3, #148]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: movs r2, #5
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str.w r2, [r3, #148]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #5
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str.w r2, [r3, #148]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test reading RNR register
extern "C" [[gnu::naked]] void test_read_rnr() {
    uint32_t rnr = ArmCortex::MPU->RNR;
    (void)rnr;
}

// CHECK-LABEL: <test_read_rnr>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr.w r3, [r3, #152]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing RNR register
extern "C" [[gnu::naked]] void test_write_rnr() {
    ArmCortex::MPU->RNR = 3;
}

// CHECK-LABEL: <test_write_rnr>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #3
// DEBUG-CHECK-NEXT: str.w r2, [r3, #152]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: movs r2, #3
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str.w r2, [r3, #152]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #3
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str.w r2, [r3, #152]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test reading RBAR register
extern "C" [[gnu::naked]] void test_read_rbar() {
    auto rbar = ArmCortex::Mpu::RBAR(ArmCortex::MPU->RBAR);
    (void)rbar;
}

// CHECK-LABEL: <test_read_rbar>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr.w r3, [r3, #156]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
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

// DEBUG-CHECK-NEXT: movs r3, #0
// DEBUG-CHECK-NEXT: ldr r3, [pc, #8]
// DEBUG-CHECK-NEXT: ldr r2, [pc, #8]
// DEBUG-CHECK-NEXT: str.w r2, [r3, #156]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000ed00
// DEBUG-CHECK-NEXT: .word 0x20000012

// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: ldr r2, [pc, #8]
// MINSIZE-CHECK-NEXT: str.w r2, [r3, #156]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-NEXT: .word 0x20000012

// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: ldr r2, [pc, #8]
// MAXSPEED-CHECK-NEXT: str.w r2, [r3, #156]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-NEXT: .word 0x20000012

// CHECK-EMPTY:

// Test reading RASR register
extern "C" [[gnu::naked]] void test_read_rasr() {
    auto rasr = ArmCortex::Mpu::RASR(ArmCortex::MPU->RASR);
    (void)rasr;
}

// CHECK-LABEL: <test_read_rasr>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr.w r3, [r3, #160]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
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

// DEBUG-CHECK-NEXT: movs r3, #1
// DEBUG-CHECK-NEXT: ldr r3, [pc, #8]
// DEBUG-CHECK-NEXT: ldr r2, [pc, #8]
// DEBUG-CHECK-NEXT: str.w r2, [r3, #160]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000ed00
// DEBUG-CHECK-NEXT: .word 0x03060015

// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: ldr r2, [pc, #8]
// MINSIZE-CHECK-NEXT: str.w r2, [r3, #160]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-NEXT: .word 0x03060015

// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: ldr r2, [pc, #8]
// MAXSPEED-CHECK-NEXT: str.w r2, [r3, #160]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-NEXT: .word 0x03060015

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

// DEBUG-CHECK-NEXT: movs r3, #1
// DEBUG-CHECK-NEXT: ldr r3, [pc, #28]
// DEBUG-CHECK-NEXT: movs r2, #0
// DEBUG-CHECK-NEXT: str.w r2, [r3, #152]
// DEBUG-CHECK-NEXT: mov.w r2, #134217728
// DEBUG-CHECK-NEXT: str.w r2, [r3, #156]
// DEBUG-CHECK-NEXT: ldr r2, [pc, #16]
// DEBUG-CHECK-NEXT: str.w r2, [r3, #160]
// DEBUG-CHECK-NEXT: dsb sy
// DEBUG-CHECK-NEXT: isb sy
// DEBUG-CHECK-NEXT: .word 0xe000ed00
// DEBUG-CHECK-NEXT: .word 0x01020019

// MINSIZE-CHECK-NEXT: movs r2, #0
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #28]
// MINSIZE-CHECK-NEXT: str.w r2, [r3, #152]
// MINSIZE-CHECK-NEXT: mov.w r2, #134217728
// MINSIZE-CHECK-NEXT: str.w r2, [r3, #156]
// MINSIZE-CHECK-NEXT: ldr r2, [pc, #16]
// MINSIZE-CHECK-NEXT: str.w r2, [r3, #160]
// MINSIZE-CHECK-NEXT: dsb sy
// MINSIZE-CHECK-NEXT: isb sy
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-NEXT: .word 0x01020019

// MAXSPEED-CHECK-NEXT: movs r0, #0
// MAXSPEED-CHECK-NEXT: mov.w r1, #134217728
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #24]
// MAXSPEED-CHECK-NEXT: ldr r2, [pc, #24]
// MAXSPEED-CHECK-NEXT: str.w r0, [r3, #152]
// MAXSPEED-CHECK-NEXT: str.w r1, [r3, #156]
// MAXSPEED-CHECK-NEXT: str.w r2, [r3, #160]
// MAXSPEED-CHECK-NEXT: dsb sy
// MAXSPEED-CHECK-NEXT: isb sy
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-NEXT: .word 0x01020019

// CHECK-EMPTY:

// Test enabling MPU
extern "C" [[gnu::naked]] void test_enable_mpu() {
    ArmCortex::Mpu::CTRL ctrl;
    ctrl.bits.ENABLE = 1;
    ctrl.bits.PRIVDEFENA = 1;
    ArmCortex::MPU->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_enable_mpu>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #5
// DEBUG-CHECK-NEXT: str.w r2, [r3, #148]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: movs r2, #5
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str.w r2, [r3, #148]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #5
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str.w r2, [r3, #148]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test disabling MPU
extern "C" [[gnu::naked]] void test_disable_mpu() {
    ArmCortex::Mpu::CTRL ctrl;
    ctrl.bits.ENABLE = 0;
    ArmCortex::MPU->CTRL = ctrl.value;
}

// CHECK-LABEL: <test_disable_mpu>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #0
// DEBUG-CHECK-NEXT: str.w r2, [r3, #148]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: movs r2, #0
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str.w r2, [r3, #148]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #0
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str.w r2, [r3, #148]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

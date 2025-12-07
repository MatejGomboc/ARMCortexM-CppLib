#include "armcortex/m0/scb.hpp"

// Test reading CPUID register
extern "C" [[gnu::naked]] void test_read_cpuid() {
    auto cpuid = ArmCortex::Scb::CPUID(ArmCortex::SCB->CPUID);
    (void)cpuid;
}

// CHECK-LABEL: <test_read_cpuid>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #0]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading ICSR register
extern "C" [[gnu::naked]] void test_read_icsr() {
    auto icsr = ArmCortex::Scb::ICSR(ArmCortex::SCB->ICSR);
    (void)icsr;
}

// CHECK-LABEL: <test_read_icsr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #4]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing ICSR register
extern "C" [[gnu::naked]] void test_write_icsr() {
    ArmCortex::Scb::ICSR icsr;
    icsr.bits.PENDSTSET = 1;
    ArmCortex::SCB->ICSR = icsr.value;
}

// CHECK-LABEL: <test_write_icsr>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #128
// DEBUG-CHECK-NEXT: lsls r2, r2, #19
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: .word 0xe000ed00
// DEBUG-CHECK-EMPTY:

// MINSIZE-CHECK-NEXT: movs r2, #128
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: lsls r2, r2, #19
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-EMPTY:

// MAXSPEED-CHECK-NEXT: movs r2, #128
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: lsls r2, r2, #19
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-EMPTY:

// Note: M0 does not have VTOR register (unlike M0Plus)

// Test reading AIRCR register
extern "C" [[gnu::naked]] void test_read_aircr() {
    auto aircr = ArmCortex::Scb::AIRCR(ArmCortex::SCB->AIRCR);
    (void)aircr;
}

// CHECK-LABEL: <test_read_aircr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #12]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing AIRCR register (with VECTKEY)
extern "C" [[gnu::naked]] void test_write_aircr() {
    ArmCortex::Scb::AIRCR aircr;
    aircr.bits.SYSRESETREQ = 1;
    aircr.bits.VECTKEY = ArmCortex::Scb::AIRCR::VECTKEY_VALUE;
    ArmCortex::SCB->AIRCR = aircr.value;
}

// CHECK-LABEL: <test_write_aircr>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr r2, [pc, #8]
// CHECK-NEXT: str r2, [r3, #12]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
// CHECK-NEXT: .word 0x05fa0004
// CHECK-EMPTY:

// Test reading SCR register
extern "C" [[gnu::naked]] void test_read_scr() {
    auto scr = ArmCortex::Scb::SCR(ArmCortex::SCB->SCR);
    (void)scr;
}

// CHECK-LABEL: <test_read_scr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #16]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing SCR register
extern "C" [[gnu::naked]] void test_write_scr() {
    ArmCortex::Scb::SCR scr;
    scr.bits.SLEEPDEEP = 1;
    ArmCortex::SCB->SCR = scr.value;
}

// CHECK-LABEL: <test_write_scr>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #4
// DEBUG-CHECK-NEXT: str r2, [r3, #16]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000ed00
// DEBUG-CHECK-EMPTY:

// MINSIZE-CHECK-NEXT: movs r2, #4
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str r2, [r3, #16]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-EMPTY:

// MAXSPEED-CHECK-NEXT: movs r2, #4
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #16]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-EMPTY:

// Test reading CCR register
extern "C" [[gnu::naked]] void test_read_ccr() {
    auto ccr = ArmCortex::Scb::CCR(ArmCortex::SCB->CCR);
    (void)ccr;
}

// CHECK-LABEL: <test_read_ccr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #20]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading SHPR2 register
extern "C" [[gnu::naked]] void test_read_shpr2() {
    auto shpr2 = ArmCortex::Scb::SHPR2(ArmCortex::SCB->SHPR2);
    (void)shpr2;
}

// CHECK-LABEL: <test_read_shpr2>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #28]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing SHPR2 register
extern "C" [[gnu::naked]] void test_write_shpr2() {
    ArmCortex::Scb::SHPR2 shpr2;
    shpr2.bits.PRI_11 = 0x80;
    ArmCortex::SCB->SHPR2 = shpr2.value;
}

// CHECK-LABEL: <test_write_shpr2>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #128
// DEBUG-CHECK-NEXT: lsls r2, r2, #24
// DEBUG-CHECK-NEXT: str r2, [r3, #28]
// DEBUG-CHECK-NEXT: .word 0xe000ed00
// DEBUG-CHECK-EMPTY:

// MINSIZE-CHECK-NEXT: movs r2, #128
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: lsls r2, r2, #24
// MINSIZE-CHECK-NEXT: str r2, [r3, #28]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-EMPTY:

// MAXSPEED-CHECK-NEXT: movs r2, #128
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: lsls r2, r2, #24
// MAXSPEED-CHECK-NEXT: str r2, [r3, #28]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-EMPTY:

// Test reading SHPR3 register
extern "C" [[gnu::naked]] void test_read_shpr3() {
    auto shpr3 = ArmCortex::Scb::SHPR3(ArmCortex::SCB->SHPR3);
    (void)shpr3;
}

// CHECK-LABEL: <test_read_shpr3>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #32]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing SHPR3 register
extern "C" [[gnu::naked]] void test_write_shpr3() {
    ArmCortex::Scb::SHPR3 shpr3;
    shpr3.bits.PRI_14 = 0xC0;
    shpr3.bits.PRI_15 = 0x40;
    ArmCortex::SCB->SHPR3 = shpr3.value;
}

// CHECK-LABEL: <test_write_shpr3>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr r2, [pc, #8]
// CHECK-NEXT: str r2, [r3, #32]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
// CHECK-NEXT: .word 0x40c00000
// CHECK-EMPTY:

// Test reading SHCSR register
extern "C" [[gnu::naked]] void test_read_shcsr() {
    auto shcsr = ArmCortex::Scb::SHCSR(ArmCortex::SCB->SHCSR);
    (void)shcsr;
}

// CHECK-LABEL: <test_read_shcsr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #36]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing SHCSR register
extern "C" [[gnu::naked]] void test_write_shcsr() {
    ArmCortex::Scb::SHCSR shcsr;
    shcsr.bits.SVCALLPENDED = 1;
    ArmCortex::SCB->SHCSR = shcsr.value;
}

// CHECK-LABEL: <test_write_shcsr>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #128
// DEBUG-CHECK-NEXT: lsls r2, r2, #8
// DEBUG-CHECK-NEXT: str r2, [r3, #36]
// DEBUG-CHECK-NEXT: .word 0xe000ed00
// DEBUG-CHECK-EMPTY:

// MINSIZE-CHECK-NEXT: movs r2, #128
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: lsls r2, r2, #8
// MINSIZE-CHECK-NEXT: str r2, [r3, #36]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-EMPTY:

// MAXSPEED-CHECK-NEXT: movs r2, #128
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: lsls r2, r2, #8
// MAXSPEED-CHECK-NEXT: str r2, [r3, #36]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-EMPTY:

// Test systemReset() function (always inlined with [[gnu::always_inline]])
extern "C" [[gnu::naked]] void test_system_reset() {
    ArmCortex::Scb::systemReset();
}

// CHECK-LABEL: <test_system_reset>:
// CHECK-NEXT: dsb sy

// DEBUG-CHECK-NEXT: ldr r1, [pc, #28]
// DEBUG-CHECK-NEXT: ldr r3, [r1, #12]
// DEBUG-CHECK-NEXT: movs r2, #2
// DEBUG-CHECK-NEXT: bics r3, r2
// DEBUG-CHECK-NEXT: adds r2, #2
// DEBUG-CHECK-NEXT: orrs r3, r2
// DEBUG-CHECK-NEXT: lsls r3, r3, #16
// DEBUG-CHECK-NEXT: lsrs r3, r3, #16
// DEBUG-CHECK-NEXT: ldr r2, [pc, #16]
// DEBUG-CHECK-NEXT: orrs r3, r2
// DEBUG-CHECK-NEXT: str r3, [r1, #12]
// DEBUG-CHECK-NEXT: dsb sy
// DEBUG-CHECK-NEXT: isb sy
// DEBUG-CHECK-NEXT: b.n
// DEBUG-CHECK-NEXT: .word 0xe000ed00
// DEBUG-CHECK-NEXT: .word 0x05fa0000
// DEBUG-CHECK-EMPTY:

// MINSIZE-CHECK-NEXT: ldr r1, [pc, #20]
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #24]
// MINSIZE-CHECK-NEXT: ldr r2, [r1, #12]
// MINSIZE-CHECK-NEXT: ands r2, r3
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #20]
// MINSIZE-CHECK-NEXT: orrs r3, r2
// MINSIZE-CHECK-NEXT: str r3, [r1, #12]
// MINSIZE-CHECK-NEXT: dsb sy
// MINSIZE-CHECK-NEXT: isb sy
// MINSIZE-CHECK-NEXT: b.n
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-NEXT: .word 0x0000fff9
// MINSIZE-CHECK-NEXT: .word 0x05fa0004
// MINSIZE-CHECK-EMPTY:

// MAXSPEED-CHECK-NEXT: ldr r1, [pc, #20]
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #24]
// MAXSPEED-CHECK-NEXT: ldr r2, [r1, #12]
// MAXSPEED-CHECK-NEXT: ands r2, r3
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #20]
// MAXSPEED-CHECK-NEXT: orrs r3, r2
// MAXSPEED-CHECK-NEXT: str r3, [r1, #12]
// MAXSPEED-CHECK-NEXT: dsb sy
// MAXSPEED-CHECK-NEXT: isb sy
// MAXSPEED-CHECK-NEXT: b.n
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-NEXT: .word 0x0000fff9
// MAXSPEED-CHECK-NEXT: .word 0x05fa0004
// MAXSPEED-CHECK-EMPTY:

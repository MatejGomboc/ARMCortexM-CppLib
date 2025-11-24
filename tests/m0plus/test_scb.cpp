#include "m0plus/scb.hpp"

// Test reading CPUID register
extern "C" [[gnu::naked]] void test_read_cpuid() {
    auto cpuid = Cortex::M0Plus::Scb::CPUID(Cortex::M0Plus::SCB->CPUID);
    (void)cpuid;
}

// CHECK-LABEL: <test_read_cpuid>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #0]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading ICSR register
extern "C" [[gnu::naked]] void test_read_icsr() {
    auto icsr = Cortex::M0Plus::Scb::ICSR(Cortex::M0Plus::SCB->ICSR);
    (void)icsr;
}

// CHECK-LABEL: <test_read_icsr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #4]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing ICSR register
extern "C" [[gnu::naked]] void test_write_icsr() {
    Cortex::M0Plus::Scb::ICSR icsr;
    icsr.bits.PENDSTSET = 1;
    Cortex::M0Plus::SCB->ICSR = icsr.value;
}

// CHECK-LABEL: <test_write_icsr>:
// CHECK-NEXT: movs r2, #128
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: lsls r2, r2, #19
// CHECK-NEXT: str r2, [r3, #4]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading VTOR register
extern "C" [[gnu::naked]] void test_read_vtor() {
    auto vtor = Cortex::M0Plus::SCB->VTOR;
    (void)vtor;
}

// CHECK-LABEL: <test_read_vtor>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #8]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing VTOR register
extern "C" [[gnu::naked]] void test_write_vtor() {
    Cortex::M0Plus::SCB->VTOR = 0x20000000;
}

// CHECK-LABEL: <test_write_vtor>:
// CHECK-NEXT: movs r2, #128
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: lsls r2, r2, #22
// CHECK-NEXT: str r2, [r3, #8]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading AIRCR register
extern "C" [[gnu::naked]] void test_read_aircr() {
    auto aircr = Cortex::M0Plus::Scb::AIRCR(Cortex::M0Plus::SCB->AIRCR);
    (void)aircr;
}

// CHECK-LABEL: <test_read_aircr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #12]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading SCR register
extern "C" [[gnu::naked]] void test_read_scr() {
    auto scr = Cortex::M0Plus::Scb::SCR(Cortex::M0Plus::SCB->SCR);
    (void)scr;
}

// CHECK-LABEL: <test_read_scr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #16]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing SCR register
extern "C" [[gnu::naked]] void test_write_scr() {
    Cortex::M0Plus::Scb::SCR scr;
    scr.bits.SLEEPDEEP = 1;
    Cortex::M0Plus::SCB->SCR = scr.value;
}

// CHECK-LABEL: <test_write_scr>:
// CHECK-NEXT: movs r2, #4
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: str r2, [r3, #16]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading CCR register
extern "C" [[gnu::naked]] void test_read_ccr() {
    auto ccr = Cortex::M0Plus::Scb::CCR(Cortex::M0Plus::SCB->CCR);
    (void)ccr;
}

// CHECK-LABEL: <test_read_ccr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #20]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading SHPR2 register
extern "C" [[gnu::naked]] void test_read_shpr2() {
    auto shpr2 = Cortex::M0Plus::Scb::SHPR2(Cortex::M0Plus::SCB->SHPR2);
    (void)shpr2;
}

// CHECK-LABEL: <test_read_shpr2>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #28]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing SHPR2 register
extern "C" [[gnu::naked]] void test_write_shpr2() {
    Cortex::M0Plus::Scb::SHPR2 shpr2;
    shpr2.bits.PRI_11 = 0x80;
    Cortex::M0Plus::SCB->SHPR2 = shpr2.value;
}

// CHECK-LABEL: <test_write_shpr2>:
// CHECK-NEXT: movs r2, #128
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: lsls r2, r2, #24
// CHECK-NEXT: str r2, [r3, #28]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading SHPR3 register
extern "C" [[gnu::naked]] void test_read_shpr3() {
    auto shpr3 = Cortex::M0Plus::Scb::SHPR3(Cortex::M0Plus::SCB->SHPR3);
    (void)shpr3;
}

// CHECK-LABEL: <test_read_shpr3>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #32]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing SHPR3 register
extern "C" [[gnu::naked]] void test_write_shpr3() {
    Cortex::M0Plus::Scb::SHPR3 shpr3;
    shpr3.bits.PRI_14 = 0xC0;
    shpr3.bits.PRI_15 = 0x40;
    Cortex::M0Plus::SCB->SHPR3 = shpr3.value;
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
    auto shcsr = Cortex::M0Plus::Scb::SHCSR(Cortex::M0Plus::SCB->SHCSR);
    (void)shcsr;
}

// CHECK-LABEL: <test_read_shcsr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #36]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

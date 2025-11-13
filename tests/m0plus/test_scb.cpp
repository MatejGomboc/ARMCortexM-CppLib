#include "m0plus/scb.hpp"

// Test reading CPUID register
extern "C" [[gnu::naked]] void test_read_cpuid() {
    auto cpuid = Cortex::M0Plus::Scb::CPUID(Cortex::M0Plus::SCB->CPUID);
    (void)cpuid;
}

// CHECK-LABEL: <test_read_cpuid>:
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #0]

// Test reading ICSR register
extern "C" [[gnu::naked]] void test_read_icsr() {
    auto icsr = Cortex::M0Plus::Scb::ICSR(Cortex::M0Plus::SCB->ICSR);
    (void)icsr;
}

// CHECK-LABEL: <test_read_icsr>:
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #4]

// Test writing ICSR register
extern "C" [[gnu::naked]] void test_write_icsr() {
    Cortex::M0Plus::Scb::ICSR icsr;
    icsr.bits.PENDSTSET = 1;
    Cortex::M0Plus::SCB->ICSR = icsr.value;
}

// CHECK-LABEL: <test_write_icsr>:
// CHECK: movs r{{[0-9]+}}, #{{128|0x80}}
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: lsls r{{[0-9]+}}, r{{[0-9]+}}, #19
// CHECK: str r{{[0-9]+}}, [r{{[0-9]+}}, #4]

// Test reading VTOR register
extern "C" [[gnu::naked]] void test_read_vtor() {
    auto vtor = Cortex::M0Plus::SCB->VTOR;
    (void)vtor;
}

// CHECK-LABEL: <test_read_vtor>:
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #8]

// Test writing VTOR register
extern "C" [[gnu::naked]] void test_write_vtor() {
    Cortex::M0Plus::SCB->VTOR = 0x20000000;
}

// CHECK-LABEL: <test_write_vtor>:
// CHECK: movs r{{[0-9]+}}, #{{128|0x80}}
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: lsls r{{[0-9]+}}, r{{[0-9]+}}, #22
// CHECK: str r{{[0-9]+}}, [r{{[0-9]+}}, #8]

// Test reading AIRCR register
extern "C" [[gnu::naked]] void test_read_aircr() {
    auto aircr = Cortex::M0Plus::Scb::AIRCR(Cortex::M0Plus::SCB->AIRCR);
    (void)aircr;
}

// CHECK-LABEL: <test_read_aircr>:
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #12]

// Test reading SCR register
extern "C" [[gnu::naked]] void test_read_scr() {
    auto scr = Cortex::M0Plus::Scb::SCR(Cortex::M0Plus::SCB->SCR);
    (void)scr;
}

// CHECK-LABEL: <test_read_scr>:
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #16]

// Test writing SCR register
extern "C" [[gnu::naked]] void test_write_scr() {
    Cortex::M0Plus::Scb::SCR scr;
    scr.bits.SLEEPDEEP = 1;
    Cortex::M0Plus::SCB->SCR = scr.value;
}

// CHECK-LABEL: <test_write_scr>:
// CHECK: movs r{{[0-9]+}}, #4
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: str r{{[0-9]+}}, [r{{[0-9]+}}, #16]

// Test reading CCR register
extern "C" [[gnu::naked]] void test_read_ccr() {
    auto ccr = Cortex::M0Plus::Scb::CCR(Cortex::M0Plus::SCB->CCR);
    (void)ccr;
}

// CHECK-LABEL: <test_read_ccr>:
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #20]

// Test reading SHPR2 register
extern "C" [[gnu::naked]] void test_read_shpr2() {
    auto shpr2 = Cortex::M0Plus::Scb::SHPR2(Cortex::M0Plus::SCB->SHPR2);
    (void)shpr2;
}

// CHECK-LABEL: <test_read_shpr2>:
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #28]

// Test writing SHPR2 register
extern "C" [[gnu::naked]] void test_write_shpr2() {
    Cortex::M0Plus::Scb::SHPR2 shpr2;
    shpr2.bits.PRI_11 = 0x80;
    Cortex::M0Plus::SCB->SHPR2 = shpr2.value;
}

// CHECK-LABEL: <test_write_shpr2>:
// CHECK: movs r{{[0-9]+}}, #{{128|0x80}}
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: lsls r{{[0-9]+}}, r{{[0-9]+}}, #24
// CHECK: str r{{[0-9]+}}, [r{{[0-9]+}}, #28]

// Test reading SHPR3 register
extern "C" [[gnu::naked]] void test_read_shpr3() {
    auto shpr3 = Cortex::M0Plus::Scb::SHPR3(Cortex::M0Plus::SCB->SHPR3);
    (void)shpr3;
}

// CHECK-LABEL: <test_read_shpr3>:
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #32]

// Test writing SHPR3 register
extern "C" [[gnu::naked]] void test_write_shpr3() {
    Cortex::M0Plus::Scb::SHPR3 shpr3;
    shpr3.bits.PRI_14 = 0xC0;
    shpr3.bits.PRI_15 = 0x40;
    Cortex::M0Plus::SCB->SHPR3 = shpr3.value;
}

// CHECK-LABEL: <test_write_shpr3>:
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: str r{{[0-9]+}}, [r{{[0-9]+}}, #32]

// Test reading SHCSR register
extern "C" [[gnu::naked]] void test_read_shcsr() {
    auto shcsr = Cortex::M0Plus::Scb::SHCSR(Cortex::M0Plus::SCB->SHCSR);
    (void)shcsr;
}

// CHECK-LABEL: <test_read_shcsr>:
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #{{36|0x24}}]

// Note: systemReset() is [[gnu::noreturn]] so we can't test it with naked functions
// as it would never return. The function itself contains the necessary barriers and
// register writes, which would be tested in integration tests.

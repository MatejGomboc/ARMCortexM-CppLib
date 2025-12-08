#include "armcortex/m1/scb.hpp"

// Test reading CPUID register
extern "C" [[gnu::naked]] auto test_read_cpuid() {
    return ArmCortex::Scb::CPUID(ArmCortex::SCB->CPUID);
}

// CHECK-LABEL: <test_read_cpuid>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r0, [r3, #0]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading ICSR register
extern "C" [[gnu::naked]] auto test_read_icsr() {
    return ArmCortex::Scb::ICSR(ArmCortex::SCB->ICSR);
}

// CHECK-LABEL: <test_read_icsr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r0, [r3, #4]
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

// MINSIZE-CHECK-NEXT: movs r2, #128
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: lsls r2, r2, #19
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #128
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: lsls r2, r2, #19
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Note: M1 does not have VTOR register (unlike M0Plus)

// Test reading AIRCR register
extern "C" [[gnu::naked]] auto test_read_aircr() {
    return ArmCortex::Scb::AIRCR(ArmCortex::SCB->AIRCR);
}

// CHECK-LABEL: <test_read_aircr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r0, [r3, #12]
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
extern "C" [[gnu::naked]] auto test_read_scr() {
    return ArmCortex::Scb::SCR(ArmCortex::SCB->SCR);
}

// CHECK-LABEL: <test_read_scr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r0, [r3, #16]
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

// MINSIZE-CHECK-NEXT: movs r2, #4
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str r2, [r3, #16]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #4
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #16]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test reading CCR register
extern "C" [[gnu::naked]] auto test_read_ccr() {
    return ArmCortex::Scb::CCR(ArmCortex::SCB->CCR);
}

// CHECK-LABEL: <test_read_ccr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r0, [r3, #20]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading SHPR2 register
extern "C" [[gnu::naked]] auto test_read_shpr2() {
    return ArmCortex::Scb::SHPR2(ArmCortex::SCB->SHPR2);
}

// CHECK-LABEL: <test_read_shpr2>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r0, [r3, #28]
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

// MINSIZE-CHECK-NEXT: movs r2, #128
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: lsls r2, r2, #24
// MINSIZE-CHECK-NEXT: str r2, [r3, #28]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #128
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: lsls r2, r2, #24
// MAXSPEED-CHECK-NEXT: str r2, [r3, #28]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test reading SHPR3 register
extern "C" [[gnu::naked]] auto test_read_shpr3() {
    return ArmCortex::Scb::SHPR3(ArmCortex::SCB->SHPR3);
}

// CHECK-LABEL: <test_read_shpr3>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r0, [r3, #32]
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
extern "C" [[gnu::naked]] auto test_read_shcsr() {
    return ArmCortex::Scb::SHCSR(ArmCortex::SCB->SHCSR);
}

// CHECK-LABEL: <test_read_shcsr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r0, [r3, #36]
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

// MINSIZE-CHECK-NEXT: movs r2, #128
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: lsls r2, r2, #8
// MINSIZE-CHECK-NEXT: str r2, [r3, #36]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #128
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: lsls r2, r2, #8
// MAXSPEED-CHECK-NEXT: str r2, [r3, #36]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

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

// CHECK-EMPTY:

// =============================================================================
// ICSR W1S/W1C Helper Function Tests
// =============================================================================

// Test isSysTickPending() - reads ICSR and checks bit 26
extern "C" [[gnu::naked]] bool test_is_systick_pending() {
    return ArmCortex::Scb::isSysTickPending();
}

// CHECK-LABEL: <test_is_systick_pending>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #8]
// DEBUG-CHECK-NEXT: ldr r0, [r3, #4]
// DEBUG-CHECK-NEXT: lsrs r0, r0, #24
// DEBUG-CHECK-NEXT: lsls r0, r0, #29
// DEBUG-CHECK-NEXT: lsrs r0, r0, #31
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: ldr r0, [r3, #4]
// MINSIZE-CHECK-NEXT: lsls r0, r0, #5
// MINSIZE-CHECK-NEXT: lsrs r0, r0, #31
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: ldr r0, [r3, #4]
// MAXSPEED-CHECK-NEXT: lsls r0, r0, #5
// MAXSPEED-CHECK-NEXT: lsrs r0, r0, #31
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test setSysTickPending() - writes 1 to bit 26 (W1S)
extern "C" [[gnu::naked]] void test_set_systick_pending() {
    ArmCortex::Scb::setSysTickPending();
}

// CHECK-LABEL: <test_set_systick_pending>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #128
// DEBUG-CHECK-NEXT: lsls r2, r2, #19
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: movs r2, #128
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: lsls r2, r2, #19
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #128
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: lsls r2, r2, #19
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test clearSysTickPending() - writes 1 to bit 25 (W1C)
extern "C" [[gnu::naked]] void test_clear_systick_pending() {
    ArmCortex::Scb::clearSysTickPending();
}

// CHECK-LABEL: <test_clear_systick_pending>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #128
// DEBUG-CHECK-NEXT: lsls r2, r2, #18
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: movs r2, #128
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: lsls r2, r2, #18
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #128
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: lsls r2, r2, #18
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test isPendSVPending() - reads ICSR and checks bit 28
extern "C" [[gnu::naked]] bool test_is_pendsv_pending() {
    return ArmCortex::Scb::isPendSVPending();
}

// CHECK-LABEL: <test_is_pendsv_pending>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #8]
// DEBUG-CHECK-NEXT: ldr r0, [r3, #4]
// DEBUG-CHECK-NEXT: lsrs r0, r0, #24
// DEBUG-CHECK-NEXT: lsls r0, r0, #27
// DEBUG-CHECK-NEXT: lsrs r0, r0, #31
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: ldr r0, [r3, #4]
// MINSIZE-CHECK-NEXT: lsls r0, r0, #3
// MINSIZE-CHECK-NEXT: lsrs r0, r0, #31
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: ldr r0, [r3, #4]
// MAXSPEED-CHECK-NEXT: lsls r0, r0, #3
// MAXSPEED-CHECK-NEXT: lsrs r0, r0, #31
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test setPendSV() - writes 1 to bit 28 (W1S)
extern "C" [[gnu::naked]] void test_set_pendsv() {
    ArmCortex::Scb::setPendSV();
}

// CHECK-LABEL: <test_set_pendsv>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #128
// DEBUG-CHECK-NEXT: lsls r2, r2, #21
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: movs r2, #128
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: lsls r2, r2, #21
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #128
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: lsls r2, r2, #21
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test clearPendSV() - writes 1 to bit 27 (W1C)
extern "C" [[gnu::naked]] void test_clear_pendsv() {
    ArmCortex::Scb::clearPendSV();
}

// CHECK-LABEL: <test_clear_pendsv>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #128
// DEBUG-CHECK-NEXT: lsls r2, r2, #20
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: movs r2, #128
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: lsls r2, r2, #20
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #128
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: lsls r2, r2, #20
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test isNMIPending() - reads ICSR and checks bit 31
extern "C" [[gnu::naked]] bool test_is_nmi_pending() {
    return ArmCortex::Scb::isNMIPending();
}

// CHECK-LABEL: <test_is_nmi_pending>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr r0, [r3, #4]
// CHECK-NEXT: lsrs r0, r0, #31
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test triggerNMI() - writes 1 to bit 31 (W1S)
extern "C" [[gnu::naked]] void test_trigger_nmi() {
    ArmCortex::Scb::triggerNMI();
}

// CHECK-LABEL: <test_trigger_nmi>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #128
// DEBUG-CHECK-NEXT: lsls r2, r2, #24
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: movs r2, #128
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: lsls r2, r2, #24
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #128
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: lsls r2, r2, #24
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

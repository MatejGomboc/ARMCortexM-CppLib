#include "armcortex/m3/scb.hpp"

// =============================================================================
// Core SCB registers
// =============================================================================

// Test reading CPUID register (offset 0x00)
extern "C" [[gnu::naked]] auto test_read_cpuid() {
    return ArmCortex::Scb::CPUID(ArmCortex::SCB->CPUID);
}

// CHECK-LABEL: <test_read_cpuid>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #0]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading ICSR register (offset 0x04)
extern "C" [[gnu::naked]] auto test_read_icsr() {
    return ArmCortex::Scb::ICSR(ArmCortex::SCB->ICSR);
}

// CHECK-LABEL: <test_read_icsr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #4]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing ICSR register - set SysTick pending
extern "C" [[gnu::naked]] void test_write_icsr() {
    ArmCortex::Scb::ICSR icsr;
    icsr.bits.PENDSTSET = 1;
    ArmCortex::SCB->ICSR = icsr.value;
}

// CHECK-LABEL: <test_write_icsr>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: mov.w r2, #67108864
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: mov.w r2, #67108864
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: mov.w r2, #67108864
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test reading VTOR register (offset 0x08)
extern "C" [[gnu::naked]] uint32_t test_read_vtor() {
    return ArmCortex::SCB->VTOR;
}

// CHECK-LABEL: <test_read_vtor>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #8]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing VTOR register
extern "C" [[gnu::naked]] void test_write_vtor() {
    ArmCortex::SCB->VTOR = 0x20000000;
}

// CHECK-LABEL: <test_write_vtor>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: mov.w r2, #536870912
// DEBUG-CHECK-NEXT: str r2, [r3, #8]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: mov.w r2, #536870912
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #8]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: mov.w r2, #536870912
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #8]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test reading AIRCR register (offset 0x0C)
extern "C" [[gnu::naked]] auto test_read_aircr() {
    return ArmCortex::Scb::AIRCR(ArmCortex::SCB->AIRCR);
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

// Test reading SCR register (offset 0x10)
extern "C" [[gnu::naked]] auto test_read_scr() {
    return ArmCortex::Scb::SCR(ArmCortex::SCB->SCR);
}

// CHECK-LABEL: <test_read_scr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #16]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing SCR register - enable deep sleep
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

// Test reading CCR register (offset 0x14)
extern "C" [[gnu::naked]] auto test_read_ccr() {
    return ArmCortex::Scb::CCR(ArmCortex::SCB->CCR);
}

// CHECK-LABEL: <test_read_ccr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #20]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing CCR register - enable div-by-zero trap and stack alignment
extern "C" [[gnu::naked]] void test_write_ccr() {
    ArmCortex::Scb::CCR ccr;
    ccr.bits.DIV_0_TRP = 1;
    ccr.bits.STKALIGN = 1;
    ArmCortex::SCB->CCR = ccr.value;
}

// CHECK-LABEL: <test_write_ccr>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: mov.w r2, #528
// DEBUG-CHECK-NEXT: str r2, [r3, #20]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: mov.w r2, #528
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #20]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: mov.w r2, #528
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #20]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// =============================================================================
// System Handler Priority Registers (SHPR) - byte array
// =============================================================================

// Test reading SHPR[0] (offset 0x18) - MemManage priority
extern "C" [[gnu::naked]] uint8_t test_read_shpr0() {
    return ArmCortex::SCB->SHPR[0];
}

// CHECK-LABEL: <test_read_shpr0>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldrb r3, [r3, #24]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing SHPR[0] - set MemManage priority
extern "C" [[gnu::naked]] void test_write_shpr0() {
    ArmCortex::SCB->SHPR[0] = 0x40;
}

// CHECK-LABEL: <test_write_shpr0>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #64
// DEBUG-CHECK-NEXT: strb r2, [r3, #24]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: movs r2, #64
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: strb r2, [r3, #24]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #64
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: strb r2, [r3, #24]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test reading SHPR[7] (offset 0x1F) - SVCall priority
extern "C" [[gnu::naked]] uint8_t test_read_shpr7() {
    return ArmCortex::SCB->SHPR[7];
}

// CHECK-LABEL: <test_read_shpr7>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldrb r3, [r3, #31]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading SHPR[10] (offset 0x22) - PendSV priority
extern "C" [[gnu::naked]] uint8_t test_read_shpr10() {
    return ArmCortex::SCB->SHPR[10];
}

// CHECK-LABEL: <test_read_shpr10>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldrb.w r3, [r3, #34]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading SHPR[11] (offset 0x23) - SysTick priority
extern "C" [[gnu::naked]] uint8_t test_read_shpr11() {
    return ArmCortex::SCB->SHPR[11];
}

// CHECK-LABEL: <test_read_shpr11>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldrb.w r3, [r3, #35]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing SHPR[11] - set SysTick priority
extern "C" [[gnu::naked]] void test_write_shpr11() {
    ArmCortex::SCB->SHPR[11] = 0xC0;
}

// CHECK-LABEL: <test_write_shpr11>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #192
// DEBUG-CHECK-NEXT: strb.w r2, [r3, #35]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: movs r2, #192
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: strb.w r2, [r3, #35]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #192
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: strb.w r2, [r3, #35]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// =============================================================================
// System Handler Control and State Register
// =============================================================================

// Test reading SHCSR register (offset 0x24)
extern "C" [[gnu::naked]] auto test_read_shcsr() {
    return ArmCortex::Scb::SHCSR(ArmCortex::SCB->SHCSR);
}

// CHECK-LABEL: <test_read_shcsr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #36]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing SHCSR register - enable fault handlers
extern "C" [[gnu::naked]] void test_write_shcsr() {
    ArmCortex::Scb::SHCSR shcsr;
    shcsr.bits.MEMFAULTENA = 1;
    shcsr.bits.BUSFAULTENA = 1;
    shcsr.bits.USGFAULTENA = 1;
    ArmCortex::SCB->SHCSR = shcsr.value;
}

// CHECK-LABEL: <test_write_shcsr>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: mov.w r2, #458752
// DEBUG-CHECK-NEXT: str r2, [r3, #36]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: mov.w r2, #458752
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #36]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: mov.w r2, #458752
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #36]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// =============================================================================
// Fault Status Registers (M3-specific)
// =============================================================================

// Test reading CFSR register (offset 0x28)
extern "C" [[gnu::naked]] auto test_read_cfsr() {
    return ArmCortex::Scb::CFSR(ArmCortex::SCB->CFSR);
}

// CHECK-LABEL: <test_read_cfsr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #40]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing CFSR register (write-1-to-clear)
extern "C" [[gnu::naked]] void test_write_cfsr() {
    ArmCortex::Scb::CFSR cfsr;
    cfsr.bits.DIVBYZERO = 1;  // Clear divide-by-zero flag
    ArmCortex::SCB->CFSR = cfsr.value;
}

// CHECK-LABEL: <test_write_cfsr>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: mov.w r2, #33554432
// DEBUG-CHECK-NEXT: str r2, [r3, #40]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: mov.w r2, #33554432
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #40]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: mov.w r2, #33554432
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #40]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test reading HFSR register (offset 0x2C)
extern "C" [[gnu::naked]] auto test_read_hfsr() {
    return ArmCortex::Scb::HFSR(ArmCortex::SCB->HFSR);
}

// CHECK-LABEL: <test_read_hfsr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #44]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test writing HFSR register (write-1-to-clear)
extern "C" [[gnu::naked]] void test_write_hfsr() {
    ArmCortex::Scb::HFSR hfsr;
    hfsr.bits.FORCED = 1;  // Clear forced flag
    ArmCortex::SCB->HFSR = hfsr.value;
}

// CHECK-LABEL: <test_write_hfsr>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: mov.w r2, #1073741824
// DEBUG-CHECK-NEXT: str r2, [r3, #44]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: mov.w r2, #1073741824
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #44]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: mov.w r2, #1073741824
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #44]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test reading DFSR register (offset 0x30)
extern "C" [[gnu::naked]] auto test_read_dfsr() {
    return ArmCortex::Scb::DFSR(ArmCortex::SCB->DFSR);
}

// CHECK-LABEL: <test_read_dfsr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #48]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// =============================================================================
// Fault Address Registers (M3-specific)
// =============================================================================

// Test reading MMFAR register (offset 0x34)
extern "C" [[gnu::naked]] uint32_t test_read_mmfar() {
    return ArmCortex::SCB->MMFAR;
}

// CHECK-LABEL: <test_read_mmfar>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #52]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading BFAR register (offset 0x38)
extern "C" [[gnu::naked]] uint32_t test_read_bfar() {
    return ArmCortex::SCB->BFAR;
}

// CHECK-LABEL: <test_read_bfar>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #56]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading AFSR register (offset 0x3C)
extern "C" [[gnu::naked]] uint32_t test_read_afsr() {
    return ArmCortex::SCB->AFSR;
}

// CHECK-LABEL: <test_read_afsr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #60]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// =============================================================================
// Helper functions (always inlined with [[gnu::always_inline]])
// =============================================================================

// Test getPriorityGrouping function (always inlined)
// Returns PRIGROUP field (bits 10:8) from AIRCR - must return value to prevent optimization
extern "C" [[gnu::naked]] uint32_t test_get_priority_grouping() {
    return ArmCortex::Scb::getPriorityGrouping();
}

// CHECK-LABEL: <test_get_priority_grouping>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr r0, [r3, #12]
// CHECK-NEXT: ubfx r0, r0, #8, #3
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test setPriorityGrouping function (always inlined)
extern "C" [[gnu::naked]] void test_set_priority_grouping() {
    ArmCortex::Scb::setPriorityGrouping(3);
}

// CHECK-LABEL: <test_set_priority_grouping>:
// CHECK-NEXT: dsb sy

// DEBUG-CHECK-NEXT: ldr r2, [pc, #20]
// DEBUG-CHECK-NEXT: ldr r3, [r2, #12]
// DEBUG-CHECK-NEXT: movs r1, #3
// DEBUG-CHECK-NEXT: bfi r3, r1, #8, #3
// DEBUG-CHECK-NEXT: movt r3, #1530
// DEBUG-CHECK-NEXT: str r3, [r2, #12]
// DEBUG-CHECK-NEXT: dsb sy
// DEBUG-CHECK-NEXT: isb sy
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: ldr r1, [pc, #24]
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #28]
// MINSIZE-CHECK-NEXT: ldr r2, [r1, #12]
// MINSIZE-CHECK-NEXT: bic.w r2, r2, #1792
// MINSIZE-CHECK-NEXT: lsls r2, r2, #16
// MINSIZE-CHECK-NEXT: lsrs r2, r2, #16
// MINSIZE-CHECK-NEXT: orrs r3, r2
// MINSIZE-CHECK-NEXT: str r3, [r1, #12]
// MINSIZE-CHECK-NEXT: dsb sy
// MINSIZE-CHECK-NEXT: isb sy
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-NEXT: .word 0x05fa0300

// MAXSPEED-CHECK-NEXT: movw r0, #63743
// MAXSPEED-CHECK-NEXT: ldr r1, [pc, #16]
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #20]
// MAXSPEED-CHECK-NEXT: ldr r2, [r1, #12]
// MAXSPEED-CHECK-NEXT: ands r2, r0
// MAXSPEED-CHECK-NEXT: orrs r3, r2
// MAXSPEED-CHECK-NEXT: str r3, [r1, #12]
// MAXSPEED-CHECK-NEXT: dsb sy
// MAXSPEED-CHECK-NEXT: isb sy
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-NEXT: .word 0x05fa0300

// CHECK-EMPTY:

// Test systemReset function (always inlined)
extern "C" [[gnu::naked]] void test_system_reset() {
    ArmCortex::Scb::systemReset();
}

// CHECK-LABEL: <test_system_reset>:
// CHECK-NEXT: dsb sy

// DEBUG-CHECK-NEXT: ldr r2, [pc, #28]
// DEBUG-CHECK-NEXT: ldr r3, [r2, #12]
// DEBUG-CHECK-NEXT: bic.w r3, r3, #1
// DEBUG-CHECK-NEXT: bic.w r3, r3, #2
// DEBUG-CHECK-NEXT: orr.w r3, r3, #4
// DEBUG-CHECK-NEXT: movt r3, #1530
// DEBUG-CHECK-NEXT: str r3, [r2, #12]
// DEBUG-CHECK-NEXT: dsb sy
// DEBUG-CHECK-NEXT: isb sy
// DEBUG-CHECK-NEXT: b.n
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: ldr r1, [pc, #24]
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #28]
// MINSIZE-CHECK-NEXT: ldr r2, [r1, #12]
// MINSIZE-CHECK-NEXT: bic.w r2, r2, #7
// MINSIZE-CHECK-NEXT: lsls r2, r2, #16
// MINSIZE-CHECK-NEXT: lsrs r2, r2, #16
// MINSIZE-CHECK-NEXT: orrs r3, r2
// MINSIZE-CHECK-NEXT: str r3, [r1, #12]
// MINSIZE-CHECK-NEXT: dsb sy
// MINSIZE-CHECK-NEXT: isb sy
// MINSIZE-CHECK-NEXT: b.n
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-NEXT: .word 0x05fa0004

// MAXSPEED-CHECK-NEXT: movw r0, #65528
// MAXSPEED-CHECK-NEXT: ldr r1, [pc, #20]
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #24]
// MAXSPEED-CHECK-NEXT: ldr r2, [r1, #12]
// MAXSPEED-CHECK-NEXT: ands r2, r0
// MAXSPEED-CHECK-NEXT: orrs r3, r2
// MAXSPEED-CHECK-NEXT: str r3, [r1, #12]
// MAXSPEED-CHECK-NEXT: dsb sy
// MAXSPEED-CHECK-NEXT: isb sy
// MAXSPEED-CHECK-NEXT: b.n
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
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
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr r0, [r3, #4]
// CHECK-NEXT: ubfx r0, r0, #26, #1
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test setSysTickPending() - writes 1 to bit 26 (W1S)
extern "C" [[gnu::naked]] void test_set_systick_pending() {
    ArmCortex::Scb::setSysTickPending();
}

// CHECK-LABEL: <test_set_systick_pending>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: mov.w r2, #67108864
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: mov.w r2, #67108864
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: mov.w r2, #67108864
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test clearSysTickPending() - writes 1 to bit 25 (W1C)
extern "C" [[gnu::naked]] void test_clear_systick_pending() {
    ArmCortex::Scb::clearSysTickPending();
}

// CHECK-LABEL: <test_clear_systick_pending>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: mov.w r2, #33554432
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: mov.w r2, #33554432
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: mov.w r2, #33554432
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test isPendSVPending() - reads ICSR and checks bit 28
extern "C" [[gnu::naked]] bool test_is_pendsv_pending() {
    return ArmCortex::Scb::isPendSVPending();
}

// CHECK-LABEL: <test_is_pendsv_pending>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr r0, [r3, #4]
// CHECK-NEXT: ubfx r0, r0, #28, #1
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test setPendSV() - writes 1 to bit 28 (W1S)
extern "C" [[gnu::naked]] void test_set_pendsv() {
    ArmCortex::Scb::setPendSV();
}

// CHECK-LABEL: <test_set_pendsv>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: mov.w r2, #268435456
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: mov.w r2, #268435456
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: mov.w r2, #268435456
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test clearPendSV() - writes 1 to bit 27 (W1C)
extern "C" [[gnu::naked]] void test_clear_pendsv() {
    ArmCortex::Scb::clearPendSV();
}

// CHECK-LABEL: <test_clear_pendsv>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: mov.w r2, #134217728
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: mov.w r2, #134217728
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: mov.w r2, #134217728
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
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
// DEBUG-CHECK-NEXT: mov.w r2, #2147483648
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: mov.w r2, #2147483648
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: mov.w r2, #2147483648
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// =============================================================================
// CFSR W1C Helper Function Tests (Configurable Fault Status)
// =============================================================================

// Test getFaultStatus() - reads CFSR
extern "C" [[gnu::naked]] ArmCortex::Scb::CFSR test_get_fault_status() {
    return ArmCortex::Scb::getFaultStatus();
}

// CHECK-LABEL: <test_get_fault_status>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r0, [r3, #40]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test clearMemManageFaults() - writes 0x9B to CFSR (W1C mask)
extern "C" [[gnu::naked]] void test_clear_memmanage_faults() {
    ArmCortex::Scb::clearMemManageFaults();
}

// CHECK-LABEL: <test_clear_memmanage_faults>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #155
// DEBUG-CHECK-NEXT: str r2, [r3, #40]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: movs r2, #155
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str r2, [r3, #40]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #155
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #40]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test clearBusFaults() - writes 0x9F00 to CFSR (W1C mask)
extern "C" [[gnu::naked]] void test_clear_bus_faults() {
    ArmCortex::Scb::clearBusFaults();
}

// CHECK-LABEL: <test_clear_bus_faults>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: mov.w r2, #40704
// DEBUG-CHECK-NEXT: str r2, [r3, #40]
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: mov.w r2, #40704
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #40]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: mov.w r2, #40704
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #40]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

// Test clearUsageFaults() - writes 0x030F0000 to CFSR (W1C mask)
extern "C" [[gnu::naked]] void test_clear_usage_faults() {
    ArmCortex::Scb::clearUsageFaults();
}

// CHECK-LABEL: <test_clear_usage_faults>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr r2, [pc, #8]
// CHECK-NEXT: str r2, [r3, #40]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
// CHECK-NEXT: .word 0x030f0000
// CHECK-EMPTY:

// Test clearAllConfigurableFaults() - writes 0x030F9F9B to CFSR (W1C mask)
extern "C" [[gnu::naked]] void test_clear_all_configurable_faults() {
    ArmCortex::Scb::clearAllConfigurableFaults();
}

// CHECK-LABEL: <test_clear_all_configurable_faults>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr r2, [pc, #8]
// CHECK-NEXT: str r2, [r3, #40]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
// CHECK-NEXT: .word 0x030f9f9b
// CHECK-EMPTY:

// =============================================================================
// HFSR W1C Helper Function Tests (HardFault Status)
// =============================================================================

// Test getHardFaultStatus() - reads HFSR
extern "C" [[gnu::naked]] ArmCortex::Scb::HFSR test_get_hardfault_status() {
    return ArmCortex::Scb::getHardFaultStatus();
}

// CHECK-LABEL: <test_get_hardfault_status>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r0, [r3, #44]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test clearHardFaultStatus() - writes 0xC0000002 to HFSR (W1C mask)
extern "C" [[gnu::naked]] void test_clear_hardfault_status() {
    ArmCortex::Scb::clearHardFaultStatus();
}

// CHECK-LABEL: <test_clear_hardfault_status>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr r2, [pc, #8]
// CHECK-NEXT: str r2, [r3, #44]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
// CHECK-NEXT: .word 0xc0000002
// CHECK-EMPTY:

// =============================================================================
// DFSR W1C Helper Function Tests (Debug Fault Status)
// =============================================================================

// Test getDebugFaultStatus() - reads DFSR
extern "C" [[gnu::naked]] ArmCortex::Scb::DFSR test_get_debugfault_status() {
    return ArmCortex::Scb::getDebugFaultStatus();
}

// CHECK-LABEL: <test_get_debugfault_status>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r0, [r3, #48]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test clearDebugFaultStatus() - writes 0x1F to DFSR (W1C mask)
extern "C" [[gnu::naked]] void test_clear_debugfault_status() {
    ArmCortex::Scb::clearDebugFaultStatus();
}

// CHECK-LABEL: <test_clear_debugfault_status>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #31
// DEBUG-CHECK-NEXT: str r2, [r3, #48]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000ed00

// MINSIZE-CHECK-NEXT: movs r2, #31
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str r2, [r3, #48]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000ed00

// MAXSPEED-CHECK-NEXT: movs r2, #31
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #48]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00

// CHECK-EMPTY:

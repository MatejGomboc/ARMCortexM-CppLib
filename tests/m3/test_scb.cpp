#include "armcortex/m3/scb.hpp"

// =============================================================================
// Core SCB registers
// =============================================================================

// Test reading CPUID register (offset 0x00)
extern "C" [[gnu::naked]] void test_read_cpuid() {
    auto cpuid = ArmCortex::Scb::CPUID(ArmCortex::SCB->CPUID);
    (void)cpuid;
}

// CHECK-LABEL: <test_read_cpuid>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #0]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading ICSR register (offset 0x04)
extern "C" [[gnu::naked]] void test_read_icsr() {
    auto icsr = ArmCortex::Scb::ICSR(ArmCortex::SCB->ICSR);
    (void)icsr;
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
// DEBUG-CHECK-EMPTY:

// MINSIZE-CHECK-NEXT: mov.w r2, #67108864
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-EMPTY:

// MAXSPEED-CHECK-NEXT: mov.w r2, #67108864
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-EMPTY:

// Test reading VTOR register (offset 0x08)
extern "C" [[gnu::naked]] void test_read_vtor() {
    uint32_t vtor = ArmCortex::SCB->VTOR;
    (void)vtor;
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
// DEBUG-CHECK-EMPTY:

// MINSIZE-CHECK-NEXT: mov.w r2, #536870912
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #8]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-EMPTY:

// MAXSPEED-CHECK-NEXT: mov.w r2, #536870912
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #8]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-EMPTY:

// Test reading AIRCR register (offset 0x0C)
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

// Test reading SCR register (offset 0x10)
extern "C" [[gnu::naked]] void test_read_scr() {
    auto scr = ArmCortex::Scb::SCR(ArmCortex::SCB->SCR);
    (void)scr;
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

// Test reading CCR register (offset 0x14)
extern "C" [[gnu::naked]] void test_read_ccr() {
    auto ccr = ArmCortex::Scb::CCR(ArmCortex::SCB->CCR);
    (void)ccr;
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
// DEBUG-CHECK-EMPTY:

// MINSIZE-CHECK-NEXT: mov.w r2, #528
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #20]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-EMPTY:

// MAXSPEED-CHECK-NEXT: mov.w r2, #528
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #20]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-EMPTY:

// =============================================================================
// System Handler Priority Registers (SHPR) - byte array
// =============================================================================

// Test reading SHPR[0] (offset 0x18) - MemManage priority
extern "C" [[gnu::naked]] void test_read_shpr0() {
    uint8_t pri = ArmCortex::SCB->SHPR[0];
    (void)pri;
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
// DEBUG-CHECK-EMPTY:

// MINSIZE-CHECK-NEXT: movs r2, #64
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: strb r2, [r3, #24]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-EMPTY:

// MAXSPEED-CHECK-NEXT: movs r2, #64
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: strb r2, [r3, #24]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-EMPTY:

// Test reading SHPR[7] (offset 0x1F) - SVCall priority
extern "C" [[gnu::naked]] void test_read_shpr7() {
    uint8_t pri = ArmCortex::SCB->SHPR[7];
    (void)pri;
}

// CHECK-LABEL: <test_read_shpr7>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldrb r3, [r3, #31]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading SHPR[10] (offset 0x22) - PendSV priority
extern "C" [[gnu::naked]] void test_read_shpr10() {
    uint8_t pri = ArmCortex::SCB->SHPR[10];
    (void)pri;
}

// CHECK-LABEL: <test_read_shpr10>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldrb.w r3, [r3, #34]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading SHPR[11] (offset 0x23) - SysTick priority
extern "C" [[gnu::naked]] void test_read_shpr11() {
    uint8_t pri = ArmCortex::SCB->SHPR[11];
    (void)pri;
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
// DEBUG-CHECK-EMPTY:

// MINSIZE-CHECK-NEXT: movs r2, #192
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: strb.w r2, [r3, #35]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-EMPTY:

// MAXSPEED-CHECK-NEXT: movs r2, #192
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: strb.w r2, [r3, #35]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-EMPTY:

// =============================================================================
// System Handler Control and State Register
// =============================================================================

// Test reading SHCSR register (offset 0x24)
extern "C" [[gnu::naked]] void test_read_shcsr() {
    auto shcsr = ArmCortex::Scb::SHCSR(ArmCortex::SCB->SHCSR);
    (void)shcsr;
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
// DEBUG-CHECK-EMPTY:

// MINSIZE-CHECK-NEXT: mov.w r2, #458752
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #36]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-EMPTY:

// MAXSPEED-CHECK-NEXT: mov.w r2, #458752
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #36]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-EMPTY:

// =============================================================================
// Fault Status Registers (M3-specific)
// =============================================================================

// Test reading CFSR register (offset 0x28)
extern "C" [[gnu::naked]] void test_read_cfsr() {
    auto cfsr = ArmCortex::Scb::CFSR(ArmCortex::SCB->CFSR);
    (void)cfsr;
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
// DEBUG-CHECK-EMPTY:

// MINSIZE-CHECK-NEXT: mov.w r2, #33554432
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #40]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-EMPTY:

// MAXSPEED-CHECK-NEXT: mov.w r2, #33554432
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #40]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-EMPTY:

// Test reading HFSR register (offset 0x2C)
extern "C" [[gnu::naked]] void test_read_hfsr() {
    auto hfsr = ArmCortex::Scb::HFSR(ArmCortex::SCB->HFSR);
    (void)hfsr;
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
// DEBUG-CHECK-EMPTY:

// MINSIZE-CHECK-NEXT: mov.w r2, #1073741824
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #44]
// MINSIZE-CHECK-NEXT: .word 0xe000ed00
// MINSIZE-CHECK-EMPTY:

// MAXSPEED-CHECK-NEXT: mov.w r2, #1073741824
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #44]
// MAXSPEED-CHECK-NEXT: .word 0xe000ed00
// MAXSPEED-CHECK-EMPTY:

// Test reading DFSR register (offset 0x30)
extern "C" [[gnu::naked]] void test_read_dfsr() {
    auto dfsr = ArmCortex::Scb::DFSR(ArmCortex::SCB->DFSR);
    (void)dfsr;
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
extern "C" [[gnu::naked]] void test_read_mmfar() {
    uint32_t mmfar = ArmCortex::SCB->MMFAR;
    (void)mmfar;
}

// CHECK-LABEL: <test_read_mmfar>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #52]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading BFAR register (offset 0x38)
extern "C" [[gnu::naked]] void test_read_bfar() {
    uint32_t bfar = ArmCortex::SCB->BFAR;
    (void)bfar;
}

// CHECK-LABEL: <test_read_bfar>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #56]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// Test reading AFSR register (offset 0x3C)
extern "C" [[gnu::naked]] void test_read_afsr() {
    uint32_t afsr = ArmCortex::SCB->AFSR;
    (void)afsr;
}

// CHECK-LABEL: <test_read_afsr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #60]
// CHECK-NEXT: .word 0xe000ed00
// CHECK-EMPTY:

// =============================================================================
// Helper functions (always inlined with [[gnu::always_inline]])
// =============================================================================

// Test getPriorityGrouping function
extern "C" [[gnu::naked]] void test_get_priority_grouping() {
    uint32_t prigroup = ArmCortex::Scb::getPriorityGrouping();
    (void)prigroup;
}

// CHECK-LABEL: <test_get_priority_grouping>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #12]
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
// DEBUG-CHECK-EMPTY:

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
// MINSIZE-CHECK-EMPTY:

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
// MAXSPEED-CHECK-EMPTY:

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
// DEBUG-CHECK-EMPTY:

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
// MINSIZE-CHECK-EMPTY:

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
// MAXSPEED-CHECK-EMPTY:

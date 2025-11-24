#include "m1/scnscb.hpp"

// Test reading ACTLR register
extern "C" [[gnu::naked]] void test_read_actlr() {
    auto actlr = Cortex::M1::ScnScb::ACTLR(Cortex::M1::SCN_SCB->ACTLR);
    (void)actlr;
}

// CHECK-LABEL: <test_read_actlr>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #8]
// CHECK-NEXT: .word 0xe000e000
// CHECK-EMPTY:

// Test writing ACTLR register with ITCMLAEN enabled
extern "C" [[gnu::naked]] void test_write_actlr_itcmlaen() {
    Cortex::M1::ScnScb::ACTLR actlr;
    actlr.bits.ITCMLAEN = 1;
    Cortex::M1::SCN_SCB->ACTLR = actlr.value;
}

// CHECK-LABEL: <test_write_actlr_itcmlaen>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #8
// DEBUG-CHECK-NEXT: str r2, [r3, #8]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000e000

// MINSIZE-CHECK-NEXT: movs r2, #8
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str r2, [r3, #8]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000e000

// MAXSPEED-CHECK-NEXT: movs r2, #8
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #8]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000e000

// CHECK-EMPTY:

// Test writing ACTLR register with ITCMUAEN enabled
extern "C" [[gnu::naked]] void test_write_actlr_itcmuaen() {
    Cortex::M1::ScnScb::ACTLR actlr;
    actlr.bits.ITCMUAEN = 1;
    Cortex::M1::SCN_SCB->ACTLR = actlr.value;
}

// CHECK-LABEL: <test_write_actlr_itcmuaen>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #16
// DEBUG-CHECK-NEXT: str r2, [r3, #8]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000e000

// MINSIZE-CHECK-NEXT: movs r2, #16
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str r2, [r3, #8]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000e000

// MAXSPEED-CHECK-NEXT: movs r2, #16
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #8]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000e000

// CHECK-EMPTY:

// Test writing ACTLR register with both ITCMLAEN and ITCMUAEN enabled
extern "C" [[gnu::naked]] void test_write_actlr_both() {
    Cortex::M1::ScnScb::ACTLR actlr;
    actlr.bits.ITCMLAEN = 1;
    actlr.bits.ITCMUAEN = 1;
    Cortex::M1::SCN_SCB->ACTLR = actlr.value;
}

// CHECK-LABEL: <test_write_actlr_both>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #24
// DEBUG-CHECK-NEXT: str r2, [r3, #8]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000e000

// MINSIZE-CHECK-NEXT: movs r2, #24
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str r2, [r3, #8]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000e000

// MAXSPEED-CHECK-NEXT: movs r2, #24
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #8]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000e000

// CHECK-EMPTY:

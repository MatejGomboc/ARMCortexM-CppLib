#include "armcortex/m0/nvic.hpp"

// Test isIrqEnabled()
extern "C" [[gnu::naked]] void test_is_irq_enabled() {
    bool enabled = ArmCortex::Nvic::isIrqEnabled(5);
    (void)enabled;
}

// CHECK-LABEL: <test_is_irq_enabled>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #0]
// CHECK-NEXT: .word 0xe000e100
// CHECK-EMPTY:

// Test enableIrq()
extern "C" [[gnu::naked]] void test_enable_irq() {
    ArmCortex::Nvic::enableIrq(10);
}

// CHECK-LABEL: <test_enable_irq>:

// DEBUG-CHECK-NEXT: ldr r2, [pc, #8]
// DEBUG-CHECK-NEXT: ldr r1, [r2, #0]
// DEBUG-CHECK-NEXT: movs r3, #128
// DEBUG-CHECK-NEXT: lsls r3, r3, #3
// DEBUG-CHECK-NEXT: orrs r3, r1
// DEBUG-CHECK-NEXT: str r3, [r2, #0]
// DEBUG-CHECK-NEXT: .word 0xe000e100

// MINSIZE-CHECK-NEXT: movs r3, #128
// MINSIZE-CHECK-NEXT: ldr r2, [pc, #8]
// MINSIZE-CHECK-NEXT: lsls r3, r3, #3
// MINSIZE-CHECK-NEXT: ldr r1, [r2, #0]
// MINSIZE-CHECK-NEXT: orrs r3, r1
// MINSIZE-CHECK-NEXT: str r3, [r2, #0]
// MINSIZE-CHECK-NEXT: .word 0xe000e100

// MAXSPEED-CHECK-NEXT: movs r3, #128
// MAXSPEED-CHECK-NEXT: ldr r2, [pc, #8]
// MAXSPEED-CHECK-NEXT: lsls r3, r3, #3
// MAXSPEED-CHECK-NEXT: ldr r1, [r2, #0]
// MAXSPEED-CHECK-NEXT: orrs r3, r1
// MAXSPEED-CHECK-NEXT: str r3, [r2, #0]
// MAXSPEED-CHECK-NEXT: .word 0xe000e100

// CHECK-EMPTY:

// Test disableIrq()
extern "C" [[gnu::naked]] void test_disable_irq() {
    ArmCortex::Nvic::disableIrq(7);
}

// CHECK-LABEL: <test_disable_irq>:

// DEBUG-CHECK-NEXT: ldr r2, [pc, #8]
// DEBUG-CHECK-NEXT: ldr r3, [r2, #0]
// DEBUG-CHECK-NEXT: movs r1, #128
// DEBUG-CHECK-NEXT: orrs r3, r1
// DEBUG-CHECK-NEXT: str r3, [r2, #0]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000e180

// MINSIZE-CHECK-NEXT: movs r3, #128
// MINSIZE-CHECK-NEXT: ldr r2, [pc, #8]
// MINSIZE-CHECK-NEXT: ldr r1, [r2, #0]
// MINSIZE-CHECK-NEXT: orrs r3, r1
// MINSIZE-CHECK-NEXT: str r3, [r2, #0]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000e180

// MAXSPEED-CHECK-NEXT: movs r1, #128
// MAXSPEED-CHECK-NEXT: ldr r2, [pc, #8]
// MAXSPEED-CHECK-NEXT: ldr r3, [r2, #0]
// MAXSPEED-CHECK-NEXT: orrs r3, r1
// MAXSPEED-CHECK-NEXT: str r3, [r2, #0]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000e180

// CHECK-EMPTY:

// Test isIrqPending()
extern "C" [[gnu::naked]] void test_is_irq_pending() {
    bool pending = ArmCortex::Nvic::isIrqPending(3);
    (void)pending;
}

// CHECK-LABEL: <test_is_irq_pending>:

// DEBUG-CHECK-NEXT: ldr r2, [pc, #4]
// DEBUG-CHECK-NEXT: movs r3, #128
// DEBUG-CHECK-NEXT: lsls r3, r3, #1
// DEBUG-CHECK-NEXT: ldr r3, [r2, r3]
// DEBUG-CHECK-NEXT: .word 0xe000e100

// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: ldr r3, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000e1fc

// MAXSPEED-CHECK-NEXT: movs r3, #128
// MAXSPEED-CHECK-NEXT: ldr r2, [pc, #4]
// MAXSPEED-CHECK-NEXT: lsls r3, r3, #1
// MAXSPEED-CHECK-NEXT: ldr r3, [r2, r3]
// MAXSPEED-CHECK-NEXT: .word 0xe000e100

// CHECK-EMPTY:

// Test setPendingIrq()
extern "C" [[gnu::naked]] void test_set_pending_irq() {
    ArmCortex::Nvic::setPendingIrq(12);
}

// CHECK-LABEL: <test_set_pending_irq>:

// DEBUG-CHECK-NEXT: ldr r2, [pc, #8]
// DEBUG-CHECK-NEXT: ldr r1, [r2, #0]
// DEBUG-CHECK-NEXT: movs r3, #128
// DEBUG-CHECK-NEXT: lsls r3, r3, #5
// DEBUG-CHECK-NEXT: orrs r3, r1
// DEBUG-CHECK-NEXT: str r3, [r2, #0]
// DEBUG-CHECK-NEXT: .word 0xe000e200

// MINSIZE-CHECK-NEXT: movs r3, #128
// MINSIZE-CHECK-NEXT: ldr r2, [pc, #8]
// MINSIZE-CHECK-NEXT: lsls r3, r3, #5
// MINSIZE-CHECK-NEXT: ldr r1, [r2, #0]
// MINSIZE-CHECK-NEXT: orrs r3, r1
// MINSIZE-CHECK-NEXT: str r3, [r2, #0]
// MINSIZE-CHECK-NEXT: .word 0xe000e200

// MAXSPEED-CHECK-NEXT: movs r3, #128
// MAXSPEED-CHECK-NEXT: ldr r2, [pc, #8]
// MAXSPEED-CHECK-NEXT: lsls r3, r3, #5
// MAXSPEED-CHECK-NEXT: ldr r1, [r2, #0]
// MAXSPEED-CHECK-NEXT: orrs r3, r1
// MAXSPEED-CHECK-NEXT: str r3, [r2, #0]
// MAXSPEED-CHECK-NEXT: .word 0xe000e200

// CHECK-EMPTY:

// Test clearPendingIrq()
extern "C" [[gnu::naked]] void test_clear_pending_irq() {
    ArmCortex::Nvic::clearPendingIrq(15);
}

// CHECK-LABEL: <test_clear_pending_irq>:

// DEBUG-CHECK-NEXT: ldr r2, [pc, #8]
// DEBUG-CHECK-NEXT: ldr r1, [r2, #0]
// DEBUG-CHECK-NEXT: movs r3, #128
// DEBUG-CHECK-NEXT: lsls r3, r3, #8
// DEBUG-CHECK-NEXT: orrs r3, r1
// DEBUG-CHECK-NEXT: str r3, [r2, #0]
// DEBUG-CHECK-NEXT: .word 0xe000e280

// MINSIZE-CHECK-NEXT: movs r3, #128
// MINSIZE-CHECK-NEXT: ldr r2, [pc, #8]
// MINSIZE-CHECK-NEXT: lsls r3, r3, #8
// MINSIZE-CHECK-NEXT: ldr r1, [r2, #0]
// MINSIZE-CHECK-NEXT: orrs r3, r1
// MINSIZE-CHECK-NEXT: str r3, [r2, #0]
// MINSIZE-CHECK-NEXT: .word 0xe000e280

// MAXSPEED-CHECK-NEXT: movs r3, #128
// MAXSPEED-CHECK-NEXT: ldr r2, [pc, #8]
// MAXSPEED-CHECK-NEXT: lsls r3, r3, #8
// MAXSPEED-CHECK-NEXT: ldr r1, [r2, #0]
// MAXSPEED-CHECK-NEXT: orrs r3, r1
// MAXSPEED-CHECK-NEXT: str r3, [r2, #0]
// MAXSPEED-CHECK-NEXT: .word 0xe000e280

// CHECK-EMPTY:

// Test reading IPR (interrupt priority)
extern "C" [[gnu::naked]] void test_read_ipr() {
    uint8_t priority = ArmCortex::NVIC->IPR[5];
    (void)priority;
}

// CHECK-LABEL: <test_read_ipr>:
// CHECK-NEXT: ldr r2, [pc, #4]
// CHECK-NEXT: ldr r3, [pc, #8]
// CHECK-NEXT: ldrb r3, [r2, r3]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000e100
// CHECK-NEXT: .word 0x00000305
// CHECK-EMPTY:

// Test writing IPR (interrupt priority)
extern "C" [[gnu::naked]] void test_write_ipr() {
    ArmCortex::NVIC->IPR[5] = 0x80;
}

// CHECK-LABEL: <test_write_ipr>:

// DEBUG-CHECK-NEXT: ldr r2, [pc, #4]
// DEBUG-CHECK-NEXT: ldr r3, [pc, #8]
// DEBUG-CHECK-NEXT: movs r1, #128
// DEBUG-CHECK-NEXT: strb r1, [r2, r3]
// DEBUG-CHECK-NEXT: .word 0xe000e100
// DEBUG-CHECK-NEXT: .word 0x00000305

// MINSIZE-CHECK-NEXT: movs r1, #128
// MINSIZE-CHECK-NEXT: ldr r2, [pc, #4]
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: strb r1, [r2, r3]
// MINSIZE-CHECK-NEXT: .word 0xe000e100
// MINSIZE-CHECK-NEXT: .word 0x00000305

// MAXSPEED-CHECK-NEXT: movs r1, #128
// MAXSPEED-CHECK-NEXT: ldr r2, [pc, #4]
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: strb r1, [r2, r3]
// MAXSPEED-CHECK-NEXT: .word 0xe000e100
// MAXSPEED-CHECK-NEXT: .word 0x00000305

// CHECK-EMPTY:

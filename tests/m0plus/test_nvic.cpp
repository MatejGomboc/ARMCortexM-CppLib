#include "m0plus/nvic.hpp"

// Test isIrqEnabled()
extern "C" [[gnu::naked]] void test_is_irq_enabled() {
    bool enabled = Cortex::M0Plus::Nvic::isIrqEnabled(5);
    (void)enabled;
}

// CHECK-LABEL: <test_is_irq_enabled>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #0]
// CHECK-NEXT: .word 0xe000e100
// CHECK-EMPTY:

// Test enableIrq()
extern "C" [[gnu::naked]] void test_enable_irq() {
    Cortex::M0Plus::Nvic::enableIrq(10);
}

// CHECK-LABEL: <test_enable_irq>:
// CHECK-NEXT: movs r3, #128
// CHECK-NEXT: ldr r2, [pc, #8]
// CHECK-NEXT: lsls r3, r3, #3
// CHECK-NEXT: ldr r1, [r2, #0]
// CHECK-NEXT: orrs r3, r1
// CHECK-NEXT: str r3, [r2, #0]
// CHECK-NEXT: .word 0xe000e100
// CHECK-EMPTY:

// Test disableIrq()
extern "C" [[gnu::naked]] void test_disable_irq() {
    Cortex::M0Plus::Nvic::disableIrq(7);
}

// CHECK-LABEL: <test_disable_irq>:
// CHECK-NEXT: movs r3, #128
// CHECK-NEXT: ldr r2, [pc, #8]
// CHECK-NEXT: ldr r1, [r2, #0]
// CHECK-NEXT: orrs r3, r1
// CHECK-NEXT: str r3, [r2, #0]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000e180
// CHECK-EMPTY:

// Test isIrqPending()
extern "C" [[gnu::naked]] void test_is_irq_pending() {
    bool pending = Cortex::M0Plus::Nvic::isIrqPending(3);
    (void)pending;
}

// CHECK-LABEL: <test_is_irq_pending>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #4]
// CHECK-NEXT: .word 0xe000e1fc
// CHECK-EMPTY:

// Test setPendingIrq()
extern "C" [[gnu::naked]] void test_set_pending_irq() {
    Cortex::M0Plus::Nvic::setPendingIrq(12);
}

// CHECK-LABEL: <test_set_pending_irq>:
// CHECK-NEXT: movs r3, #128
// CHECK-NEXT: ldr r2, [pc, #8]
// CHECK-NEXT: lsls r3, r3, #5
// CHECK-NEXT: ldr r1, [r2, #0]
// CHECK-NEXT: orrs r3, r1
// CHECK-NEXT: str r3, [r2, #0]
// CHECK-NEXT: .word 0xe000e200
// CHECK-EMPTY:

// Test clearPendingIrq()
extern "C" [[gnu::naked]] void test_clear_pending_irq() {
    Cortex::M0Plus::Nvic::clearPendingIrq(15);
}

// CHECK-LABEL: <test_clear_pending_irq>:
// CHECK-NEXT: movs r3, #128
// CHECK-NEXT: ldr r2, [pc, #8]
// CHECK-NEXT: lsls r3, r3, #8
// CHECK-NEXT: ldr r1, [r2, #0]
// CHECK-NEXT: orrs r3, r1
// CHECK-NEXT: str r3, [r2, #0]
// CHECK-NEXT: .word 0xe000e280
// CHECK-EMPTY:

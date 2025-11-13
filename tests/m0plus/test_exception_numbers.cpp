#include "m0plus/exceptions.hpp"

// Test isIrqNumber() with IRQ number
extern "C" [[gnu::naked]] void test_is_irq_number_true() {
    bool result = Cortex::M0Plus::isIrqNumber(16);
    (void)result;
}

// CHECK-LABEL: <test_is_irq_number_true>:
// CHECK: mov{{.*}} r0, #1
// CHECK-NEXT: bx lr

// Test isIrqNumber() with non-IRQ number
extern "C" [[gnu::naked]] void test_is_irq_number_false() {
    bool result = Cortex::M0Plus::isIrqNumber(3);
    (void)result;
}

// CHECK-LABEL: <test_is_irq_number_false>:
// CHECK: mov{{.*}} r0, #0
// CHECK-NEXT: bx lr

// Test isIrqNumber() with last valid IRQ
extern "C" [[gnu::naked]] void test_is_irq_number_last() {
    bool result = Cortex::M0Plus::isIrqNumber(47); // FIRST_IRQ (16) + NUM_OF_IRQS (32) - 1
    (void)result;
}

// CHECK-LABEL: <test_is_irq_number_last>:
// CHECK: mov{{.*}} r0, #1
// CHECK-NEXT: bx lr

// Test isIrqNumber() with boundary condition (first IRQ)
extern "C" [[gnu::naked]] void test_is_irq_number_first() {
    bool result = Cortex::M0Plus::isIrqNumber(static_cast<uint8_t>(Cortex::M0Plus::ExceptionNumber::FIRST_IRQ));
    (void)result;
}

// CHECK-LABEL: <test_is_irq_number_first>:
// CHECK: mov{{.*}} r0, #1
// CHECK-NEXT: bx lr

// Test isIrqNumber() with value above range
extern "C" [[gnu::naked]] void test_is_irq_number_above() {
    bool result = Cortex::M0Plus::isIrqNumber(48);
    (void)result;
}

// CHECK-LABEL: <test_is_irq_number_above>:
// CHECK: mov{{.*}} r0, #0
// CHECK-NEXT: bx lr

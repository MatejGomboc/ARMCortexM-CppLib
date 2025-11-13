#include "m0plus/exceptions.hpp"

// Test isIrqNumber() with IRQ number - use volatile to prevent optimization
extern "C" [[gnu::naked]] void test_is_irq_number_true() {
    volatile uint8_t num = 16;
    volatile bool result = Cortex::M0Plus::isIrqNumber(num);
    (void)result;
}

// CHECK-LABEL: <test_is_irq_number_true>:
// CHECK: movs r{{[0-9]+}}, #16
// CHECK: cmp r{{[0-9]+}}, #15
// CHECK: bls

// Test isIrqNumber() with non-IRQ number
extern "C" [[gnu::naked]] void test_is_irq_number_false() {
    volatile uint8_t num = 3;
    volatile bool result = Cortex::M0Plus::isIrqNumber(num);
    (void)result;
}

// CHECK-LABEL: <test_is_irq_number_false>:
// CHECK: movs r{{[0-9]+}}, #3
// CHECK: cmp r{{[0-9]+}}, #15
// CHECK: bls

// Test isIrqNumber() with last valid IRQ
extern "C" [[gnu::naked]] void test_is_irq_number_last() {
    volatile uint8_t num = 47; // FIRST_IRQ (16) + NUM_OF_IRQS (32) - 1
    volatile bool result = Cortex::M0Plus::isIrqNumber(num);
    (void)result;
}

// CHECK-LABEL: <test_is_irq_number_last>:
// CHECK: movs r{{[0-9]+}}, #47
// CHECK: cmp r{{[0-9]+}}, #15
// CHECK: bls

// Test isIrqNumber() with boundary condition (first IRQ)
extern "C" [[gnu::naked]] void test_is_irq_number_first() {
    volatile uint8_t num = static_cast<uint8_t>(Cortex::M0Plus::ExceptionNumber::FIRST_IRQ);
    volatile bool result = Cortex::M0Plus::isIrqNumber(num);
    (void)result;
}

// CHECK-LABEL: <test_is_irq_number_first>:
// CHECK: movs r{{[0-9]+}}, #16
// CHECK: cmp r{{[0-9]+}}, #15
// CHECK: bls

// Test isIrqNumber() with value above range
extern "C" [[gnu::naked]] void test_is_irq_number_above() {
    volatile uint8_t num = 48;
    volatile bool result = Cortex::M0Plus::isIrqNumber(num);
    (void)result;
}

// CHECK-LABEL: <test_is_irq_number_above>:
// CHECK: movs r{{[0-9]+}}, #48
// CHECK: cmp r{{[0-9]+}}, #15
// CHECK: bls

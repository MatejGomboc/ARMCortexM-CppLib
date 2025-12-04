#include "armcortex/m3/nvic.hpp"

// Test isIrqEnabled() - IRQ in first register
extern "C" [[gnu::naked]] void test_is_irq_enabled() {
    bool enabled = ArmCortex::Nvic::isIrqEnabled(5);
    (void)enabled;
}

// CHECK-LABEL: <test_is_irq_enabled>:
// TODO: Add CHECK patterns after seeing actual assembly
// CHECK: .word 0xe000e100
// CHECK-EMPTY:

// Test isIrqEnabled() - IRQ in second register (tests array indexing)
extern "C" [[gnu::naked]] void test_is_irq_enabled_high() {
    bool enabled = ArmCortex::Nvic::isIrqEnabled(45);
    (void)enabled;
}

// CHECK-LABEL: <test_is_irq_enabled_high>:
// TODO: Add CHECK patterns after seeing actual assembly
// CHECK: .word 0xe000e100
// CHECK-EMPTY:

// Test enableIrq() - IRQ in first register
extern "C" [[gnu::naked]] void test_enable_irq() {
    ArmCortex::Nvic::enableIrq(10);
}

// CHECK-LABEL: <test_enable_irq>:
// TODO: Add CHECK patterns after seeing actual assembly
// CHECK: .word 0xe000e100
// CHECK-EMPTY:

// Test enableIrq() - IRQ in second register
extern "C" [[gnu::naked]] void test_enable_irq_high() {
    ArmCortex::Nvic::enableIrq(45);
}

// CHECK-LABEL: <test_enable_irq_high>:
// TODO: Add CHECK patterns after seeing actual assembly
// CHECK: .word 0xe000e100
// CHECK-EMPTY:

// Test disableIrq()
extern "C" [[gnu::naked]] void test_disable_irq() {
    ArmCortex::Nvic::disableIrq(7);
}

// CHECK-LABEL: <test_disable_irq>:
// TODO: Add CHECK patterns after seeing actual assembly
// CHECK: .word 0xe000e
// CHECK-EMPTY:

// Test disableIrq() - IRQ in second register
extern "C" [[gnu::naked]] void test_disable_irq_high() {
    ArmCortex::Nvic::disableIrq(45);
}

// CHECK-LABEL: <test_disable_irq_high>:
// TODO: Add CHECK patterns after seeing actual assembly
// CHECK: .word 0xe000e
// CHECK-EMPTY:

// Test isIrqPending()
extern "C" [[gnu::naked]] void test_is_irq_pending() {
    bool pending = ArmCortex::Nvic::isIrqPending(3);
    (void)pending;
}

// CHECK-LABEL: <test_is_irq_pending>:
// TODO: Add CHECK patterns after seeing actual assembly
// CHECK: .word 0xe000e
// CHECK-EMPTY:

// Test setPendingIrq()
extern "C" [[gnu::naked]] void test_set_pending_irq() {
    ArmCortex::Nvic::setPendingIrq(12);
}

// CHECK-LABEL: <test_set_pending_irq>:
// TODO: Add CHECK patterns after seeing actual assembly
// CHECK: .word 0xe000e
// CHECK-EMPTY:

// Test clearPendingIrq()
extern "C" [[gnu::naked]] void test_clear_pending_irq() {
    ArmCortex::Nvic::clearPendingIrq(15);
}

// CHECK-LABEL: <test_clear_pending_irq>:
// TODO: Add CHECK patterns after seeing actual assembly
// CHECK: .word 0xe000e
// CHECK-EMPTY:

// Test isIrqActive() - M3-specific
extern "C" [[gnu::naked]] void test_is_irq_active() {
    bool active = ArmCortex::Nvic::isIrqActive(8);
    (void)active;
}

// CHECK-LABEL: <test_is_irq_active>:
// TODO: Add CHECK patterns after seeing actual assembly
// CHECK: .word 0xe000e
// CHECK-EMPTY:

// Test reading IPR (interrupt priority)
extern "C" [[gnu::naked]] void test_read_ipr() {
    uint8_t priority = ArmCortex::NVIC->IPR[5];
    (void)priority;
}

// CHECK-LABEL: <test_read_ipr>:
// TODO: Add CHECK patterns after seeing actual assembly
// CHECK: .word 0xe000e
// CHECK-EMPTY:

// Test writing IPR (interrupt priority)
extern "C" [[gnu::naked]] void test_write_ipr() {
    ArmCortex::NVIC->IPR[5] = 0x80;
}

// CHECK-LABEL: <test_write_ipr>:
// TODO: Add CHECK patterns after seeing actual assembly
// CHECK: .word 0xe000e
// CHECK-EMPTY:

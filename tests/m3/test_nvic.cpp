#include "armcortex/m3/nvic.hpp"

// Test isIrqEnabled() - IRQ in first register
extern "C" [[gnu::naked]] bool test_is_irq_enabled() {
    return ArmCortex::Nvic::isIrqEnabled(5);
}

// CHECK-LABEL: <test_is_irq_enabled>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #0]
// CHECK-NEXT: .word 0xe000e100
// CHECK-EMPTY:

// Test isIrqEnabled() - IRQ in second register (tests array indexing)
extern "C" [[gnu::naked]] bool test_is_irq_enabled_high() {
    return ArmCortex::Nvic::isIrqEnabled(45);
}

// CHECK-LABEL: <test_is_irq_enabled_high>:
// CHECK-NEXT: ldr r3, [pc, #0]
// CHECK-NEXT: ldr r3, [r3, #4]
// CHECK-NEXT: .word 0xe000e100
// CHECK-EMPTY:

// Test enableIrq() - IRQ in first register
extern "C" [[gnu::naked]] void test_enable_irq() {
    ArmCortex::Nvic::enableIrq(10);
}

// CHECK-LABEL: <test_enable_irq>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: mov.w r2, #1024
// DEBUG-CHECK-NEXT: str r2, [r3, #0]
// DEBUG-CHECK-NEXT: .word 0xe000e100

// MINSIZE-CHECK-NEXT: mov.w r2, #1024
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #0]
// MINSIZE-CHECK-NEXT: .word 0xe000e100

// MAXSPEED-CHECK-NEXT: mov.w r2, #1024
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #0]
// MAXSPEED-CHECK-NEXT: .word 0xe000e100

// CHECK-EMPTY:

// Test enableIrq() - IRQ in second register
extern "C" [[gnu::naked]] void test_enable_irq_high() {
    ArmCortex::Nvic::enableIrq(45);
}

// CHECK-LABEL: <test_enable_irq_high>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: mov.w r2, #8192
// DEBUG-CHECK-NEXT: str r2, [r3, #4]
// DEBUG-CHECK-NEXT: .word 0xe000e100

// MINSIZE-CHECK-NEXT: mov.w r2, #8192
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #0]
// MINSIZE-CHECK-NEXT: str r2, [r3, #4]
// MINSIZE-CHECK-NEXT: .word 0xe000e100

// MAXSPEED-CHECK-NEXT: mov.w r2, #8192
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #0]
// MAXSPEED-CHECK-NEXT: str r2, [r3, #4]
// MAXSPEED-CHECK-NEXT: .word 0xe000e100

// CHECK-EMPTY:

// Test disableIrq()
extern "C" [[gnu::naked]] void test_disable_irq() {
    ArmCortex::Nvic::disableIrq(7);
}

// CHECK-LABEL: <test_disable_irq>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #128
// DEBUG-CHECK-NEXT: str.w r2, [r3, #128]
// DEBUG-CHECK-NEXT: .word 0xe000e100

// MINSIZE-CHECK-NEXT: movs r2, #128
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str.w r2, [r3, #128]
// MINSIZE-CHECK-NEXT: .word 0xe000e100

// MAXSPEED-CHECK-NEXT: movs r2, #128
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str.w r2, [r3, #128]
// MAXSPEED-CHECK-NEXT: .word 0xe000e100

// CHECK-EMPTY:

// Test disableIrq() - IRQ in second register
extern "C" [[gnu::naked]] void test_disable_irq_high() {
    ArmCortex::Nvic::disableIrq(45);
}

// CHECK-LABEL: <test_disable_irq_high>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #8]
// DEBUG-CHECK-NEXT: mov.w r2, #8192
// DEBUG-CHECK-NEXT: str.w r2, [r3, #132]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000e100

// MINSIZE-CHECK-NEXT: mov.w r2, #8192
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str.w r2, [r3, #132]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000e100

// MAXSPEED-CHECK-NEXT: mov.w r2, #8192
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str.w r2, [r3, #132]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000e100

// CHECK-EMPTY:

// Test isIrqPending()
extern "C" [[gnu::naked]] bool test_is_irq_pending() {
    return ArmCortex::Nvic::isIrqPending(3);
}

// CHECK-LABEL: <test_is_irq_pending>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr.w r3, [r3, #256]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000e100
// CHECK-EMPTY:

// Test setPendingIrq()
extern "C" [[gnu::naked]] void test_set_pending_irq() {
    ArmCortex::Nvic::setPendingIrq(12);
}

// CHECK-LABEL: <test_set_pending_irq>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #8]
// DEBUG-CHECK-NEXT: mov.w r2, #4096
// DEBUG-CHECK-NEXT: str.w r2, [r3, #256]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000e100

// MINSIZE-CHECK-NEXT: mov.w r2, #4096
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str.w r2, [r3, #256]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000e100

// MAXSPEED-CHECK-NEXT: mov.w r2, #4096
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str.w r2, [r3, #256]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000e100

// CHECK-EMPTY:

// Test clearPendingIrq()
extern "C" [[gnu::naked]] void test_clear_pending_irq() {
    ArmCortex::Nvic::clearPendingIrq(15);
}

// CHECK-LABEL: <test_clear_pending_irq>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #8]
// DEBUG-CHECK-NEXT: mov.w r2, #32768
// DEBUG-CHECK-NEXT: str.w r2, [r3, #384]
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0xe000e100

// MINSIZE-CHECK-NEXT: mov.w r2, #32768
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: str.w r2, [r3, #384]
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0xe000e100

// MAXSPEED-CHECK-NEXT: mov.w r2, #32768
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: str.w r2, [r3, #384]
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0xe000e100

// CHECK-EMPTY:

// Test isIrqActive() - M3-specific
extern "C" [[gnu::naked]] bool test_is_irq_active() {
    return ArmCortex::Nvic::isIrqActive(8);
}

// CHECK-LABEL: <test_is_irq_active>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldr.w r3, [r3, #512]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000e100
// CHECK-EMPTY:

// Test reading IPR (interrupt priority)
extern "C" [[gnu::naked]] uint8_t test_read_ipr() {
    return ArmCortex::NVIC->IPR[5];
}

// CHECK-LABEL: <test_read_ipr>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: ldrb.w r3, [r3, #773]
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0xe000e100
// CHECK-EMPTY:

// Test writing IPR (interrupt priority)
extern "C" [[gnu::naked]] void test_write_ipr() {
    ArmCortex::NVIC->IPR[5] = 0x80;
}

// CHECK-LABEL: <test_write_ipr>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: movs r2, #128
// DEBUG-CHECK-NEXT: strb.w r2, [r3, #773]
// DEBUG-CHECK-NEXT: .word 0xe000e100

// MINSIZE-CHECK-NEXT: movs r2, #128
// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: strb.w r2, [r3, #773]
// MINSIZE-CHECK-NEXT: .word 0xe000e100

// MAXSPEED-CHECK-NEXT: movs r2, #128
// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: strb.w r2, [r3, #773]
// MAXSPEED-CHECK-NEXT: .word 0xe000e100

// CHECK-EMPTY:

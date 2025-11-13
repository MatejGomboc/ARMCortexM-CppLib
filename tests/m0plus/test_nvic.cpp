#include "m0plus/nvic.hpp"

// Test isIrqEnabled()
extern "C" [[gnu::naked]] void test_is_irq_enabled() {
    bool enabled = Cortex::M0Plus::Nvic::isIrqEnabled(5);
    (void)enabled;
}

// CHECK-LABEL: <test_is_irq_enabled>:
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #0]

// Test enableIrq()
extern "C" [[gnu::naked]] void test_enable_irq() {
    Cortex::M0Plus::Nvic::enableIrq(10);
}

// CHECK-LABEL: <test_enable_irq>:
// CHECK: movs r{{[0-9]+}}, #{{128|0x80}}
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: lsls r{{[0-9]+}}, r{{[0-9]+}}, #3
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #0]
// CHECK: orrs r{{[0-9]+}}, r{{[0-9]+}}
// CHECK: str r{{[0-9]+}}, [r{{[0-9]+}}, #0]

// Test disableIrq()
extern "C" [[gnu::naked]] void test_disable_irq() {
    Cortex::M0Plus::Nvic::disableIrq(7);
}

// CHECK-LABEL: <test_disable_irq>:
// CHECK: movs r{{[0-9]+}}, #{{128|0x80}}
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #0]
// CHECK: orrs r{{[0-9]+}}, r{{[0-9]+}}
// CHECK: str r{{[0-9]+}}, [r{{[0-9]+}}, #0]

// Test isIrqPending()
extern "C" [[gnu::naked]] void test_is_irq_pending() {
    bool pending = Cortex::M0Plus::Nvic::isIrqPending(3);
    (void)pending;
}

// CHECK-LABEL: <test_is_irq_pending>:
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #4]

// Test setPendingIrq()
extern "C" [[gnu::naked]] void test_set_pending_irq() {
    Cortex::M0Plus::Nvic::setPendingIrq(12);
}

// CHECK-LABEL: <test_set_pending_irq>:
// CHECK: movs r{{[0-9]+}}, #{{128|0x80}}
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: lsls r{{[0-9]+}}, r{{[0-9]+}}, #5
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #0]
// CHECK: orrs r{{[0-9]+}}, r{{[0-9]+}}
// CHECK: str r{{[0-9]+}}, [r{{[0-9]+}}, #0]

// Test clearPendingIrq()
extern "C" [[gnu::naked]] void test_clear_pending_irq() {
    Cortex::M0Plus::Nvic::clearPendingIrq(15);
}

// CHECK-LABEL: <test_clear_pending_irq>:
// CHECK: movs r{{[0-9]+}}, #{{128|0x80}}
// CHECK: ldr r{{[0-9]+}}, [pc
// CHECK: lsls r{{[0-9]+}}, r{{[0-9]+}}, #8
// CHECK: ldr r{{[0-9]+}}, [r{{[0-9]+}}, #0]
// CHECK: orrs r{{[0-9]+}}, r{{[0-9]+}}
// CHECK: str r{{[0-9]+}}, [r{{[0-9]+}}, #0]

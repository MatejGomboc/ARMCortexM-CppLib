#include "cortexm0plus/nvic.hpp"

extern "C" {
    void assert_true(bool condition, const char* test_name);
    void assert_equals(uint32_t expected, uint32_t actual, const char* test_name);
}

void test_nvic() {
    using namespace CortexM0Plus::Nvic;
    
    // Test IRQ 0 enable/disable
    disableIrq(0);
    assert_true(!isIrqEnabled(0), "IRQ 0 should be disabled");
    
    enableIrq(0);
    assert_true(isIrqEnabled(0), "IRQ 0 should be enabled");
    
    disableIrq(0);
    assert_true(!isIrqEnabled(0), "IRQ 0 should be disabled again");
    
    // Test IRQ 15 enable/disable
    disableIrq(15);
    assert_true(!isIrqEnabled(15), "IRQ 15 should be disabled");
    
    enableIrq(15);
    assert_true(isIrqEnabled(15), "IRQ 15 should be enabled");
    
    // Test pending IRQ
    clearPendingIrq(5);
    assert_true(!isIrqPending(5), "IRQ 5 should not be pending");
    
    setPendingIrq(5);
    assert_true(isIrqPending(5), "IRQ 5 should be pending");
    
    clearPendingIrq(5);
    assert_true(!isIrqPending(5), "IRQ 5 should not be pending after clear");
    
    // Test IRQ priority
    setIrqPriority(10, 0xC0);
    assert_equals(0xC0, getIrqPriority(10), "IRQ 10 priority should be 0xC0");
    
    setIrqPriority(10, 0x40);
    assert_equals(0x40, getIrqPriority(10), "IRQ 10 priority should be 0x40");
    
    // Test multiple IRQs in same priority register
    setIrqPriority(0, 0x00);
    setIrqPriority(1, 0x40);
    setIrqPriority(2, 0x80);
    setIrqPriority(3, 0xC0);
    
    assert_equals(0x00, getIrqPriority(0), "IRQ 0 priority check");
    assert_equals(0x40, getIrqPriority(1), "IRQ 1 priority check");
    assert_equals(0x80, getIrqPriority(2), "IRQ 2 priority check");
    assert_equals(0xC0, getIrqPriority(3), "IRQ 3 priority check");
    
    // Clean up - disable all tested IRQs
    disableIrq(0);
    disableIrq(1);
    disableIrq(2);
    disableIrq(3);
    disableIrq(5);
    disableIrq(10);
    disableIrq(15);
}

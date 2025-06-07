#include "cortexm0plus/systick.hpp"

extern "C" {
    void assert_true(bool condition, const char* test_name);
    void assert_equals(uint32_t expected, uint32_t actual, const char* test_name);
    void test_print(const char* str);
}

// SysTick interrupt counter
volatile uint32_t g_systick_count = 0;

extern "C" void SysTick_Handler() {
    g_systick_count++;
}

void test_systick() {
    using namespace CortexM0Plus::SysTick;
    
    // Initially SysTick should be disabled
    assert_true(!isEnabled(), "SysTick should be initially disabled");
    
    // Test reload value
    setReloadValue(1000);
    assert_equals(1000, getReloadValue(), "SysTick reload value should be 1000");
    
    // Test current value
    setCurrentValue(500);
    // Note: Current value resets to 0 when written, then counts from reload value
    // So we can't directly verify the written value
    
    // Test clock source
    useProcessorClock();
    assert_true(isUsingProcessorClock(), "SysTick should use processor clock");
    
    useReferenceClock();
    assert_true(!isUsingProcessorClock(), "SysTick should use reference clock");
    
    // Switch back to processor clock for testing
    useProcessorClock();
    
    // Test interrupt enable/disable
    disableInterrupt();
    assert_true(!isInterruptEnabled(), "SysTick interrupt should be disabled");
    
    enableInterrupt();
    assert_true(isInterruptEnabled(), "SysTick interrupt should be enabled");
    
    // Test count flag
    // The count flag is set when SysTick counts to 0
    // Reading the flag clears it
    clearCountFlag(); // Clear any previous flag
    assert_true(!hasCountFlagSet(), "Count flag should be clear");
    
    // Test enable/disable with small count
    disableInterrupt(); // Disable interrupt for this test
    setReloadValue(10);
    setCurrentValue(0);
    
    enable();
    assert_true(isEnabled(), "SysTick should be enabled");
    
    // Wait for count flag (polling)
    uint32_t timeout = 1000;
    while (!hasCountFlagSet() && timeout > 0) {
        timeout--;
    }
    assert_true(timeout > 0, "SysTick count flag should be set");
    
    disable();
    assert_true(!isEnabled(), "SysTick should be disabled");
    
    // Test with interrupt
    g_systick_count = 0;
    setReloadValue(1000);
    enableInterrupt();
    enable();
    
    // Wait a bit for interrupts
    for (volatile uint32_t i = 0; i < 10000; i++) {
        __asm("nop");
    }
    
    disable();
    disableInterrupt();
    
    // We should have gotten at least one interrupt
    assert_true(g_systick_count > 0, "SysTick should have generated interrupts");
    
    test_print("  SysTick interrupts received: ");
    test_print_hex(g_systick_count);
    test_print("\n");
    
    // Test calibration value (read-only)
    uint32_t calib = getCalibrationValue();
    test_print("  SysTick calibration value: ");
    test_print_hex(calib);
    test_print("\n");
    
    uint32_t tenms = calib & 0xFFFFFF;
    bool skew = (calib & (1 << 30)) != 0;
    bool noref = (calib & (1 << 31)) != 0;
    
    if (tenms != 0) {
        test_print("  10ms reload value: ");
        test_print_hex(tenms);
        test_print("\n");
    }
    
    if (skew) {
        test_print("  [INFO] 10ms calibration value is inexact\n");
    }
    
    if (noref) {
        test_print("  [INFO] Reference clock not available\n");
    }
}

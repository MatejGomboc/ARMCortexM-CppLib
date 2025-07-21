#include "cortexm0plus/special_regs.hpp"

extern "C" {
    void assert_true(bool condition, const char* test_name);
    void assert_equals(uint32_t expected, uint32_t actual, const char* test_name);
    void test_print(const char* str);
    void test_print_hex(uint32_t value);
}

void test_special_regs() {
    using namespace CortexM0Plus::SpecialRegs;
    
    // Test PRIMASK
    uint32_t original_primask = getPrimask();
    
    // Disable interrupts
    disableIrq();
    assert_equals(1, getPrimask(), "PRIMASK should be 1 (interrupts disabled)");
    
    // Enable interrupts
    enableIrq();
    assert_equals(0, getPrimask(), "PRIMASK should be 0 (interrupts enabled)");
    
    // Test setPrimask
    setPrimask(1);
    assert_equals(1, getPrimask(), "PRIMASK should be 1 after setPrimask(1)");
    
    setPrimask(0);
    assert_equals(0, getPrimask(), "PRIMASK should be 0 after setPrimask(0)");
    
    // Restore original PRIMASK
    setPrimask(original_primask);
    
    // Test CONTROL register
    uint32_t control = getControl();
    test_print("  CONTROL register: ");
    test_print_hex(control);
    test_print("\n");
    
    // In handler mode (which we're likely in during reset), nPRIV bit has no effect
    // SPSEL bit selects stack pointer
    bool using_psp = (control & 0x2) != 0;
    test_print("  Stack pointer: ");
    test_print(using_psp ? "PSP" : "MSP");
    test_print("\n");
    
    // Test MSP/PSP
    uint32_t msp = getMsp();
    test_print("  MSP: ");
    test_print_hex(msp);
    test_print("\n");
    
    uint32_t psp = getPsp();
    test_print("  PSP: ");
    test_print_hex(psp);
    test_print("\n");
    
    // Test setting PSP (won't affect current operation since we're using MSP)
    uint32_t test_psp_value = 0x20008000;
    setPsp(test_psp_value);
    assert_equals(test_psp_value, getPsp(), "PSP should be set to test value");
    
    // Test APSR (Application Program Status Register)
    uint32_t apsr = getApsr();
    test_print("  APSR: ");
    test_print_hex(apsr);
    test_print("\n");
    
    // Extract and display condition flags
    bool n_flag = (apsr & (1 << 31)) != 0;
    bool z_flag = (apsr & (1 << 30)) != 0;
    bool c_flag = (apsr & (1 << 29)) != 0;
    bool v_flag = (apsr & (1 << 28)) != 0;
    
    test_print("  Flags: ");
    test_print(n_flag ? "N" : "n");
    test_print(z_flag ? "Z" : "z");
    test_print(c_flag ? "C" : "c");
    test_print(v_flag ? "V" : "v");
    test_print("\n");
    
    // Test IPSR (Interrupt Program Status Register)
    uint32_t ipsr = getIpsr();
    uint8_t exception_number = ipsr & 0x3F;
    test_print("  IPSR (Exception number): ");
    test_print_hex(exception_number);
    test_print("\n");
    
    // In thread mode, exception number should be 0
    // In handler mode, it will show the current exception number
    if (exception_number == 0) {
        test_print("  Currently in Thread mode\n");
    } else {
        test_print("  Currently in Handler mode\n");
    }
    
    // Test xPSR (combined PSR)
    uint32_t xpsr = getXpsr();
    test_print("  xPSR: ");
    test_print_hex(xpsr);
    test_print("\n");
    
    // xPSR combines APSR, IPSR, and EPSR
    // Verify that xPSR contains both APSR and IPSR information
    assert_equals(exception_number, xpsr & 0x3F, "xPSR should contain IPSR exception number");
    assert_equals(apsr & 0xF0000000, xpsr & 0xF0000000, "xPSR should contain APSR flags");
    
    // Test wait for interrupt/event
    test_print("  Testing WFI/WFE/SEV/NOP instructions...\n");
    
    // These should execute without issues
    nop();
    nop();
    sev(); // Send event
    wfe(); // Wait for event (should return immediately due to previous SEV)
    
    test_print("  Instruction tests completed\n");
}

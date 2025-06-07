#include <cstdint>
#include <cstring>

// Test result tracking
struct TestResult {
    uint32_t total_tests;
    uint32_t passed_tests;
    uint32_t failed_tests;
    char current_test[64];
};

// Global test result accessible by Renode
volatile TestResult g_test_result __attribute__((section(".bss")));

// Test functions declarations
extern void test_nvic();
extern void test_scb();
extern void test_systick();
extern void test_mpu();
extern void test_special_regs();

// Simple UART-like output for Renode (memory-mapped)
// Using AnalyzableUART compatible register layout
struct TestUART {
    volatile uint32_t data;     // 0x00 - Data register
    volatile uint32_t status;   // 0x04 - Status register (unused)
    volatile uint32_t control;  // 0x08 - Control register (unused)
};

volatile TestUART* const TEST_OUTPUT = reinterpret_cast<volatile TestUART*>(0x40000000);

void test_print(const char* str) {
    while (*str) {
        // Write to data register
        TEST_OUTPUT->data = static_cast<uint32_t>(*str);
        str++;
    }
}

void test_print_hex(uint32_t value) {
    const char hex_chars[] = "0123456789ABCDEF";
    char buffer[11] = "0x00000000";
    
    for (int i = 9; i >= 2; i--) {
        buffer[i] = hex_chars[value & 0xF];
        value >>= 4;
    }
    
    test_print(buffer);
}

int main() {
    // Initialize test results
    g_test_result.total_tests = 0;
    g_test_result.passed_tests = 0;
    g_test_result.failed_tests = 0;
    std::strcpy(const_cast<char*>(g_test_result.current_test), "INIT");
    
    test_print("\n=== ARM Cortex-M0+ Library Tests ===\n");
    
    // Run NVIC tests
    test_print("\n[TEST] NVIC Functions\n");
    std::strcpy(const_cast<char*>(g_test_result.current_test), "NVIC");
    test_nvic();
    
    // Run SCB tests
    test_print("\n[TEST] SCB Functions\n");
    std::strcpy(const_cast<char*>(g_test_result.current_test), "SCB");
    test_scb();
    
    // Run SysTick tests
    test_print("\n[TEST] SysTick Functions\n");
    std::strcpy(const_cast<char*>(g_test_result.current_test), "SYSTICK");
    test_systick();
    
    // Run MPU tests
    test_print("\n[TEST] MPU Functions\n");
    std::strcpy(const_cast<char*>(g_test_result.current_test), "MPU");
    test_mpu();
    
    // Run Special Registers tests
    test_print("\n[TEST] Special Registers\n");
    std::strcpy(const_cast<char*>(g_test_result.current_test), "SPECIAL_REGS");
    test_special_regs();
    
    // Print summary
    test_print("\n=== Test Summary ===\n");
    test_print("Total tests: ");
    test_print_hex(g_test_result.total_tests);
    test_print("\nPassed: ");
    test_print_hex(g_test_result.passed_tests);
    test_print("\nFailed: ");
    test_print_hex(g_test_result.failed_tests);
    test_print("\n\n");
    
    std::strcpy(const_cast<char*>(g_test_result.current_test), "COMPLETE");
    
    // Signal completion to Renode
    volatile uint32_t* const TEST_COMPLETE = reinterpret_cast<volatile uint32_t*>(0x40001000);
    *TEST_COMPLETE = 0xDEADBEEF;
    
    // Infinite loop
    while (1) {
        __asm("wfi");
    }
    
    return 0;
}

// Test helper functions
extern "C" {
    void assert_true(bool condition, const char* test_name) {
        g_test_result.total_tests++;
        if (condition) {
            g_test_result.passed_tests++;
            test_print("  [PASS] ");
        } else {
            g_test_result.failed_tests++;
            test_print("  [FAIL] ");
        }
        test_print(test_name);
        test_print("\n");
    }
    
    void assert_equals(uint32_t expected, uint32_t actual, const char* test_name) {
        g_test_result.total_tests++;
        if (expected == actual) {
            g_test_result.passed_tests++;
            test_print("  [PASS] ");
            test_print(test_name);
        } else {
            g_test_result.failed_tests++;
            test_print("  [FAIL] ");
            test_print(test_name);
            test_print(" - Expected: ");
            test_print_hex(expected);
            test_print(", Got: ");
            test_print_hex(actual);
        }
        test_print("\n");
    }
}

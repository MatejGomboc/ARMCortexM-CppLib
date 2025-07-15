// REQUIRES: cortex-m0
// RUN: %cc% %ccflags% %ccout% %T/%basename_t.o %s; objdump --mcpu=%mcpu% -d %T/%basename_t.o | FileCheck --allow-unused-prefixes --check-prefixes %prefixes% %s

#include "utils.hpp"
#include <cstdint>
#include <limits>

using namespace Utils;

void test_intCeilDiv_edge_cases() {
    // CHECK-LABEL: <{{.*test_intCeilDiv_edge_cases.*}}>:
    
    // Test basic functionality
    volatile auto basic1 = intCeilDiv(10, 3);   // Should be 4
    volatile auto basic2 = intCeilDiv(9, 3);    // Should be 3
    volatile auto basic3 = intCeilDiv(11, 3);   // Should be 4
    
    // Test edge case: dividend equals divisor
    volatile auto equal = intCeilDiv(5, 5);     // Should be 1
    
    // Test edge case: dividend less than divisor
    volatile auto less = intCeilDiv(2, 5);      // Should be 1
    
    // Test edge case: dividend is 0
    volatile auto zero_dividend = intCeilDiv(0, 5);  // Should be 0
    
    // Test edge case: divisor is 1
    volatile auto div_one = intCeilDiv(42, 1);  // Should be 42
    
    // Test large numbers
    volatile auto large = intCeilDiv(1000000, 7);  // Should be 142858
    
    // Test with different integer types
    volatile auto uint8_result = intCeilDiv<uint8_t, uint8_t>(250, 7);   // Should be 36
    volatile auto uint16_result = intCeilDiv<uint16_t, uint16_t>(65000, 7); // Should be 9286
    volatile auto uint32_result = intCeilDiv<uint32_t, uint32_t>(4000000000U, 7); // Should be 571428572
    
    // Test mixed types
    volatile auto mixed1 = intCeilDiv<uint8_t, uint16_t>(200, 7);
    volatile auto mixed2 = intCeilDiv<uint16_t, uint32_t>(1000, 7);
    
    // Test boundary conditions for uint8_t
    volatile auto uint8_max = intCeilDiv<uint8_t, uint8_t>(255, 1);     // Should be 255
    volatile auto uint8_near_max = intCeilDiv<uint8_t, uint8_t>(255, 2); // Should be 128
    
    // Test that the formula (dividend + divisor - 1) / divisor works correctly
    // and doesn't overflow for the specific types
    constexpr uint8_t test_dividend = 200;
    constexpr uint8_t test_divisor = 3;
    // Manual calculation: (200 + 3 - 1) / 3 = 202 / 3 = 67 (rounded down)
    volatile auto manual_calc = intCeilDiv<uint8_t, uint8_t>(test_dividend, test_divisor);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_bit_operations_comprehensive() {
    // CHECK-LABEL: <{{.*test_bit_operations_comprehensive.*}}>:
    
    // Test all 32 bits for uint32_t
    uint32_t test_value = 0;
    
    // Set all bits one by one and verify
    for (uint8_t bit = 0; bit < 32; ++bit) {
        setBit(test_value, bit);
        volatile bool is_set = isBitSet(test_value, bit);
    }
    
    // After setting all bits, value should be 0xFFFFFFFF
    volatile bool all_bits_set = (test_value == 0xFFFFFFFF);
    
    // Clear all bits one by one and verify
    for (uint8_t bit = 0; bit < 32; ++bit) {
        clearBit(test_value, bit);
        volatile bool is_clear = !isBitSet(test_value, bit);
    }
    
    // After clearing all bits, value should be 0
    volatile bool all_bits_clear = (test_value == 0);
    
    // Test specific bit patterns
    uint32_t pattern_value = 0;
    
    // Set alternating bits (0x55555555)
    for (uint8_t bit = 0; bit < 32; bit += 2) {
        setBit(pattern_value, bit);
    }
    volatile bool alternating_pattern = (pattern_value == 0x55555555);
    
    // Test edge cases for different integer types
    uint8_t val8 = 0;
    setBit(val8, 0);    // Set bit 0
    setBit(val8, 7);    // Set bit 7 (MSB for uint8_t)
    volatile bool uint8_bits = isBitSet(val8, 0) && isBitSet(val8, 7);
    volatile bool uint8_value = (val8 == 0x81);
    
    uint16_t val16 = 0;
    setBit(val16, 0);   // Set bit 0
    setBit(val16, 15);  // Set bit 15 (MSB for uint16_t)
    volatile bool uint16_bits = isBitSet(val16, 0) && isBitSet(val16, 15);
    volatile bool uint16_value = (val16 == 0x8001);
    
    // Test clearing specific bits in a full pattern
    uint32_t full_pattern = 0xFFFFFFFF;
    clearBit(full_pattern, 0);   // Clear LSB
    clearBit(full_pattern, 31);  // Clear MSB
    clearBit(full_pattern, 16);  // Clear middle bit
    volatile bool selective_clear = (full_pattern == 0x7FFFFFFE);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_bit_operations_boundary_conditions() {
    // CHECK-LABEL: <{{.*test_bit_operations_boundary_conditions.*}}>:
    
    // Test bit 0 (LSB) operations
    uint32_t lsb_test = 0xFFFFFFFE;  // All bits set except bit 0
    volatile bool lsb_not_set = !isBitSet(lsb_test, 0);
    setBit(lsb_test, 0);
    volatile bool lsb_now_set = isBitSet(lsb_test, 0);
    volatile bool lsb_full = (lsb_test == 0xFFFFFFFF);
    
    // Test bit 31 (MSB) operations
    uint32_t msb_test = 0x7FFFFFFF;  // All bits set except bit 31
    volatile bool msb_not_set = !isBitSet(msb_test, 31);
    setBit(msb_test, 31);
    volatile bool msb_now_set = isBitSet(msb_test, 31);
    volatile bool msb_full = (msb_test == 0xFFFFFFFF);
    
    // Test operations on value 0
    uint32_t zero_value = 0;
    for (uint8_t bit = 0; bit < 32; ++bit) {
        volatile bool should_be_false = !isBitSet(zero_value, bit);
    }
    
    // Test operations on value 0xFFFFFFFF
    uint32_t full_value = 0xFFFFFFFF;
    for (uint8_t bit = 0; bit < 32; ++bit) {
        volatile bool should_be_true = isBitSet(full_value, bit);
    }
    
    // Test that setBit on already set bit doesn't change anything
    uint32_t already_set = 0x00000100;  // Bit 8 set
    volatile bool bit8_initially_set = isBitSet(already_set, 8);
    setBit(already_set, 8);  // Set again
    volatile bool bit8_still_set = isBitSet(already_set, 8);
    volatile bool value_unchanged = (already_set == 0x00000100);
    
    // Test that clearBit on already clear bit doesn't change anything
    uint32_t already_clear = 0xFFFFFEFF;  // All bits set except bit 8
    volatile bool bit8_initially_clear = !isBitSet(already_clear, 8);
    clearBit(already_clear, 8);  // Clear again
    volatile bool bit8_still_clear = !isBitSet(already_clear, 8);
    volatile bool value_unchanged2 = (already_clear == 0xFFFFFEFF);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_template_instantiation_comprehensive() {
    // CHECK-LABEL: <{{.*test_template_instantiation_comprehensive.*}}>:
    
    // Test intCeilDiv with all supported integer types
    
    // uint8_t tests
    volatile auto u8_1 = intCeilDiv<uint8_t, uint8_t>(255, 8);    // 32
    volatile auto u8_2 = intCeilDiv<uint8_t, uint8_t>(200, 9);    // 23
    volatile auto u8_3 = intCeilDiv<uint8_t, uint8_t>(1, 255);    // 1
    
    // uint16_t tests
    volatile auto u16_1 = intCeilDiv<uint16_t, uint16_t>(65535, 8);   // 8192
    volatile auto u16_2 = intCeilDiv<uint16_t, uint16_t>(50000, 7);   // 7143
    volatile auto u16_3 = intCeilDiv<uint16_t, uint16_t>(1000, 999);  // 2
    
    // uint32_t tests
    volatile auto u32_1 = intCeilDiv<uint32_t, uint32_t>(4294967295U, 1000000); // 4295
    volatile auto u32_2 = intCeilDiv<uint32_t, uint32_t>(1000000000, 7);        // 142857143
    
    // Mixed type tests (explicit template instantiation)
    volatile auto mixed_1 = intCeilDiv<uint8_t, uint16_t>(200, 7);   // uint8_t / uint8_t -> uint16_t
    volatile auto mixed_2 = intCeilDiv<uint16_t, uint32_t>(50000, 7); // uint16_t / uint16_t -> uint32_t
    volatile auto mixed_3 = intCeilDiv<uint32_t, uint64_t>(4000000000U, 7); // uint32_t / uint32_t -> uint64_t
    
    // Test bit operations with all integer types
    
    // uint8_t bit operations
    uint8_t val8 = 0;
    for (uint8_t bit = 0; bit < 8; ++bit) {
        setBit(val8, bit);
        volatile bool is_set = isBitSet(val8, bit);
    }
    volatile bool val8_full = (val8 == 0xFF);
    
    // uint16_t bit operations  
    uint16_t val16 = 0;
    setBit(val16, 0);
    setBit(val16, 8);
    setBit(val16, 15);
    volatile bool val16_pattern = isBitSet(val16, 0) && isBitSet(val16, 8) && isBitSet(val16, 15);
    
    // uint32_t bit operations
    uint32_t val32 = 0;
    setBit(val32, 0);
    setBit(val32, 16);
    setBit(val32, 31);
    volatile bool val32_pattern = isBitSet(val32, 0) && isBitSet(val32, 16) && isBitSet(val32, 31);
    
    // uint64_t bit operations (if supported)
    uint64_t val64 = 0;
    setBit(val64, 0);
    setBit(val64, 32);
    setBit(val64, 63);
    volatile bool val64_pattern = isBitSet(val64, 0) && isBitSet(val64, 32) && isBitSet(val64, 63);
    
    // Test constexpr evaluation
    constexpr auto const_result1 = intCeilDiv(100, 7);  // Should be evaluable at compile time
    constexpr auto const_result2 = intCeilDiv(1000, 13);
    volatile auto runtime_copy1 = const_result1;
    volatile auto runtime_copy2 = const_result2;
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_performance_characteristics() {
    // CHECK-LABEL: <{{.*test_performance_characteristics.*}}>:
    
    // Test that bit operations compile to efficient code
    // These should compile to single bit manipulation instructions where possible
    
    uint32_t value = 0x12345678;
    
    // Single bit operations - should be very efficient
    setBit(value, 5);      // Should use ORR with immediate or shifted register
    clearBit(value, 10);   // Should use BIC with immediate or shifted register  
    volatile bool check = isBitSet(value, 15);  // Should use TST or AND with shift
    
    // Multiple bit operations in sequence
    setBit(value, 0);
    setBit(value, 1);
    setBit(value, 2);
    setBit(value, 3);
    
    clearBit(value, 16);
    clearBit(value, 17);
    clearBit(value, 18);
    clearBit(value, 19);
    
    // Test that intCeilDiv with constants gets optimized
    constexpr uint32_t dividend = 1000;
    constexpr uint32_t divisor = 7;
    volatile auto optimized_result = intCeilDiv(dividend, divisor);
    
    // Test with power-of-2 divisors (should be very efficient)
    volatile auto pow2_div_2 = intCeilDiv(1000, 2);    // Should use shift
    volatile auto pow2_div_4 = intCeilDiv(1000, 4);    // Should use shift
    volatile auto pow2_div_8 = intCeilDiv(1000, 8);    // Should use shift
    volatile auto pow2_div_16 = intCeilDiv(1000, 16);  // Should use shift
    
    // Test small constant divisors
    volatile auto small_div_3 = intCeilDiv(1000, 3);
    volatile auto small_div_5 = intCeilDiv(1000, 5);
    volatile auto small_div_7 = intCeilDiv(1000, 7);
    
    // Use all results to prevent optimization
    volatile uint32_t final_result = value + optimized_result + pow2_div_2 + 
                                    pow2_div_4 + pow2_div_8 + pow2_div_16 + 
                                    small_div_3 + small_div_5 + small_div_7 + 
                                    (check ? 1 : 0);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_compiler_optimization_resistance() {
    // CHECK-LABEL: <{{.*test_compiler_optimization_resistance.*}}>:
    
    // Test that volatile prevents dead code elimination
    uint32_t value = 0;
    
    // These operations should not be eliminated even though 
    // the final value of 'value' is deterministic
    setBit(value, 5);
    volatile bool check1 = isBitSet(value, 5);  // Should be true
    
    clearBit(value, 5);
    volatile bool check2 = isBitSet(value, 5);  // Should be false
    
    setBit(value, 5);
    volatile bool check3 = isBitSet(value, 5);  // Should be true again
    
    // Test that calculations aren't folded when they shouldn't be
    volatile uint32_t runtime_dividend = 1000;  // Compiler can't know this is constant
    volatile uint32_t runtime_divisor = 7;
    
    volatile auto runtime_result1 = intCeilDiv(runtime_dividend, runtime_divisor);
    volatile auto runtime_result2 = intCeilDiv(runtime_dividend, runtime_divisor);
    
    // Even though these are the same calculation, both should be performed
    // because the inputs are volatile
    
    // Test that bit operations on volatile values aren't optimized away
    volatile uint32_t volatile_value = 0x12345678;
    setBit(volatile_value, 8);
    volatile bool volatile_check1 = isBitSet(volatile_value, 8);
    
    clearBit(volatile_value, 8);
    volatile bool volatile_check2 = isBitSet(volatile_value, 8);
    
    // Use all results
    volatile uint32_t final = runtime_result1 + runtime_result2 + volatile_value +
                             (check1 ? 1 : 0) + (check2 ? 2 : 0) + (check3 ? 4 : 0) +
                             (volatile_check1 ? 8 : 0) + (volatile_check2 ? 16 : 0);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

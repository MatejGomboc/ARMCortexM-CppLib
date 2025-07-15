// REQUIRES: cortex-m0
// RUN: %cc% %ccflags% %ccout% %T/%basename_t.o %s; objdump --mcpu=%mcpu% -d %T/%basename_t.o | FileCheck --allow-unused-prefixes --check-prefixes %prefixes% %s

#include "utils.hpp"
#include <cstdint>

using namespace Utils;

void test_intCeilDiv() {
    // CHECK-LABEL: <{{.*test_intCeilDiv.*}}>:
    volatile auto result1 = intCeilDiv(10, 3);  // Should be 4
    volatile auto result2 = intCeilDiv(9, 3);   // Should be 3  
    volatile auto result3 = intCeilDiv(8, 3);   // Should be 3
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_bitOperations() {
    // CHECK-LABEL: <{{.*test_bitOperations.*}}>:
    volatile uint32_t value = 0x12345678;
    
    // Test bit checking
    volatile bool bit0 = isBitSet(value, 0);  // Should be false (bit 0 of 0x78 is 0)
    volatile bool bit3 = isBitSet(value, 3);  // Should be true (bit 3 of 0x78 is 1)
    
    // Test bit setting
    uint32_t setValue = 0;
    setBit(setValue, 5);
    volatile bool checkSet = isBitSet(setValue, 5);  // Should be true
    
    // Test bit clearing  
    uint32_t clearValue = 0xFFFFFFFF;
    clearBit(clearValue, 7);
    volatile bool checkClear = isBitSet(clearValue, 7);  // Should be false
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_templateInstantiation() {
    // CHECK-LABEL: <{{.*test_templateInstantiation.*}}>:
    // Test that templates work with different types
    volatile auto result8 = intCeilDiv<uint8_t, uint8_t>(200, 7);
    volatile auto result16 = intCeilDiv<uint16_t, uint16_t>(1000, 7); 
    volatile auto result32 = intCeilDiv<uint32_t, uint32_t>(100000, 7);
    
    uint8_t val8 = 0x55;
    uint16_t val16 = 0x5555;
    uint32_t val32 = 0x55555555;
    
    volatile bool check8 = isBitSet(val8, 2);
    volatile bool check16 = isBitSet(val16, 6);
    volatile bool check32 = isBitSet(val32, 10);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

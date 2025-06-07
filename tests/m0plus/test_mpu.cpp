#include "cortexm0plus/mpu.hpp"

extern "C" {
    void assert_true(bool condition, const char* test_name);
    void assert_equals(uint32_t expected, uint32_t actual, const char* test_name);
    void test_print(const char* str);
    void test_print_hex(uint32_t value);
}

void test_mpu() {
    using namespace CortexM0Plus::Mpu;
    
    // Check if MPU is present
    uint8_t num_regions = getNumberOfRegions();
    test_print("  MPU regions available: ");
    test_print_hex(num_regions);
    test_print("\n");
    
    if (num_regions == 0) {
        test_print("  [INFO] MPU not present in this M0+ implementation\n");
        return;
    }
    
    // Test MPU enable/disable
    disable();
    assert_true(!isEnabled(), "MPU should be disabled");
    
    // Test default memory map enable/disable during NMI
    enableDefaultMemoryMapDuringNmi();
    assert_true(isDefaultMemoryMapEnabledDuringNmi(), "Default memory map should be enabled during NMI");
    
    disableDefaultMemoryMapDuringNmi();
    assert_true(!isDefaultMemoryMapEnabledDuringNmi(), "Default memory map should be disabled during NMI");
    
    // Test region configuration
    if (num_regions >= 1) {
        // Configure region 0
        uint8_t region = 0;
        uint32_t base_addr = 0x20000000; // RAM base
        uint32_t size_bits = 14; // 16KB (2^14)
        
        setRegionNumber(region);
        assert_equals(region, getRegionNumber(), "Region number should be 0");
        
        setRegionBaseAddress(base_addr);
        assert_equals(base_addr, getRegionBaseAddress(), "Region base address should match");
        
        // Configure region attributes
        uint8_t ap = 0b011; // Full access
        uint8_t tex = 0b000;
        bool cacheable = false;
        bool bufferable = false;
        bool shareable = false;
        uint8_t subregions_disabled = 0x00;
        
        setRegionAttributes(
            true,  // execute never
            ap,
            tex,
            shareable,
            cacheable,
            bufferable,
            subregions_disabled,
            size_bits
        );
        
        // Verify attributes
        uint32_t rasr = getRegionAttributesAndSize();
        assert_true((rasr & 0x1) != 0, "Region should be enabled");
        assert_equals(size_bits, (rasr >> 1) & 0x1F, "Region size should match");
        assert_equals(ap, (rasr >> 24) & 0x7, "Access permissions should match");
        assert_true((rasr & (1 << 28)) != 0, "Execute never should be set");
        
        // Test region disable
        disableRegion();
        rasr = getRegionAttributesAndSize();
        assert_true((rasr & 0x1) == 0, "Region should be disabled");
        
        // Re-enable for further testing
        enableRegion();
        assert_true(isRegionEnabled(), "Region should be enabled");
    }
    
    // Test additional regions if available
    if (num_regions >= 2) {
        // Configure region 1 with different settings
        setRegionNumber(1);
        setRegionBaseAddress(0x00000000); // Flash base
        
        setRegionAttributes(
            false, // execute allowed
            0b110, // Read-only
            0b000,
            false,
            true,  // cacheable
            false,
            0x00,
            15     // 32KB
        );
        
        assert_true(isRegionEnabled(), "Region 1 should be enabled");
    }
    
    // Test MPU enable with default memory map
    enableWithDefaultMemoryMap();
    assert_true(isEnabled(), "MPU should be enabled");
    assert_true(isDefaultMemoryMapEnabledDuringNmi(), "Default memory map should be enabled");
    
    // Clean up - disable MPU
    disable();
    
    // Disable all configured regions
    for (uint8_t i = 0; i < num_regions && i < 2; i++) {
        setRegionNumber(i);
        disableRegion();
    }
}

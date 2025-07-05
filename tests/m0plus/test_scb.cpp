#include "cortexm0plus/scb.hpp"

extern "C" {
    void assert_true(bool condition, const char* test_name);
    void assert_equals(uint32_t expected, uint32_t actual, const char* test_name);
    void test_print(const char* str);
    void test_print_hex(uint32_t value);
}

void test_scb() {
    using namespace CortexM0Plus::Scb;
    
    // Test CPUID register (read-only)
    uint32_t cpuid = getCpuId();
    test_print("  CPUID: ");
    test_print_hex(cpuid);
    test_print("\n");
    
    // Cortex-M0+ CPUID should have:
    // - Implementer = 0x41 (ARM)
    // - Variant = 0x0
    // - Architecture = 0xC (ARMv6-M)
    // - PartNo = 0xC60 (Cortex-M0+)
    // - Revision varies
    
    uint8_t implementer = (cpuid >> 24) & 0xFF;
    uint8_t variant = (cpuid >> 20) & 0x0F;
    uint8_t architecture = (cpuid >> 16) & 0x0F;
    uint16_t partno = (cpuid >> 4) & 0xFFF;
    
    assert_equals(0x41, implementer, "CPUID Implementer should be ARM (0x41)");
    assert_equals(0xC, architecture, "CPUID Architecture should be ARMv6-M (0xC)");
    assert_equals(0xC60, partno, "CPUID PartNo should be Cortex-M0+ (0xC60)");
    
    // Test AIRCR register - read key value
    uint32_t aircr = getAircr();
    uint16_t vectkey = (aircr >> 16) & 0xFFFF;
    assert_equals(0xFA05, vectkey, "AIRCR VECTKEY readback should be 0xFA05");
    
    // Test VTOR (Vector Table Offset Register)
    // Note: VTOR might not be implemented in all M0+ implementations
    uint32_t original_vtor = getVtor();
    
    // Try to set VTOR to a valid aligned address
    uint32_t test_vtor = 0x00001000; // 4KB offset
    setVtor(test_vtor);
    uint32_t new_vtor = getVtor();
    
    // Check if VTOR is implemented (if not, it will read as 0)
    if (new_vtor != 0) {
        assert_equals(test_vtor & 0xFFFFFF00, new_vtor, "VTOR should be set to aligned address");
        // Restore original VTOR
        setVtor(original_vtor);
    } else {
        test_print("  [INFO] VTOR not implemented in this M0+ variant\n");
    }
    
    // Test priority grouping (Note: M0+ doesn't support priority grouping)
    // getPriorityGrouping() should always return 0 for M0+
    uint8_t prigroup = getPriorityGrouping();
    assert_equals(0, prigroup, "Priority grouping should be 0 for Cortex-M0+");
    
    // Test exception priorities
    // SVC priority
    setSvcPriority(0x80);
    assert_equals(0x80, getSvcPriority(), "SVC priority should be 0x80");
    
    setSvcPriority(0x00);
    assert_equals(0x00, getSvcPriority(), "SVC priority should be 0x00");
    
    // PendSV priority
    setPendSvPriority(0xC0);
    assert_equals(0xC0, getPendSvPriority(), "PendSV priority should be 0xC0");
    
    // SysTick priority
    setSysTickPriority(0x40);
    assert_equals(0x40, getSysTickPriority(), "SysTick priority should be 0x40");
    
    // Test PendSV pending bit
    clearPendSvPending();
    assert_true(!isPendSvPending(), "PendSV should not be pending");
    
    setPendSvPending();
    assert_true(isPendSvPending(), "PendSV should be pending");
    
    clearPendSvPending();
    assert_true(!isPendSvPending(), "PendSV should not be pending after clear");
    
    // Test SysTick pending bit
    clearSysTickPending();
    assert_true(!isSysTickPending(), "SysTick should not be pending");
    
    setSysTickPending();
    assert_true(isSysTickPending(), "SysTick should be pending");
    
    clearSysTickPending();
    assert_true(!isSysTickPending(), "SysTick should not be pending after clear");
}

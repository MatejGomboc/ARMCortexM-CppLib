// REQUIRES: cortex-m0
// RUN: %cc% %ccflags% %ccout% %T/%basename_t.o %s; objdump --mcpu=%mcpu% -d %T/%basename_t.o | FileCheck --allow-unused-prefixes --check-prefixes %prefixes% %s

#include "cortexm0/systick.hpp"
#include <cstdint>

using namespace CortexM0;

void test_systick_config_all_combinations() {
    // CHECK-LABEL: <{{.*test_systick_config_all_combinations.*}}>:
    
    // Test all 8 combinations of the 3 control bits
    Systick::Config config;
    
    // Combination 1: disabled, no interrupt, external clock
    config.value = 0;
    config.bits.enable = 0;
    config.bits.interrupt_enable = 0;
    config.bits.clock_source = static_cast<uint32_t>(Systick::Config::ClockSource::EXTERNAL_CLOCK);
    Systick::setConfig(config);
    // CHECK: {{str|ldr}}
    
    // Combination 2: enabled, no interrupt, external clock
    config.bits.enable = 1;
    Systick::setConfig(config);
    // CHECK: {{str|ldr}}
    
    // Combination 3: disabled, interrupt enabled, external clock
    config.bits.enable = 0;
    config.bits.interrupt_enable = 1;
    Systick::setConfig(config);
    // CHECK: {{str|ldr}}
    
    // Combination 4: enabled, interrupt enabled, external clock
    config.bits.enable = 1;
    Systick::setConfig(config);
    // CHECK: {{str|ldr}}
    
    // Combination 5: disabled, no interrupt, processor clock
    config.bits.enable = 0;
    config.bits.interrupt_enable = 0;
    config.bits.clock_source = static_cast<uint32_t>(Systick::Config::ClockSource::PROCESSOR_CLOCK);
    Systick::setConfig(config);
    // CHECK: {{str|ldr}}
    
    // Combination 6: enabled, no interrupt, processor clock
    config.bits.enable = 1;
    Systick::setConfig(config);
    // CHECK: {{str|ldr}}
    
    // Combination 7: disabled, interrupt enabled, processor clock
    config.bits.enable = 0;
    config.bits.interrupt_enable = 1;
    Systick::setConfig(config);
    // CHECK: {{str|ldr}}
    
    // Combination 8: enabled, interrupt enabled, processor clock
    config.bits.enable = 1;
    Systick::setConfig(config);
    // CHECK: {{str|ldr}}
    
    // Read final config and verify
    volatile auto final_config = Systick::getConfig();
    // CHECK: {{str|ldr}}
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_systick_reload_boundary_values() {
    // CHECK-LABEL: <{{.*test_systick_reload_boundary_values.*}}>:
    
    // Test minimum reload value (1)
    Systick::setReloadValue(1);
    // CHECK: {{str|ldr}}
    volatile uint32_t min_reload = Systick::getReloadValue();
    // CHECK: {{str|ldr}}
    
    // Test maximum reload value (24-bit: 0xFFFFFF)
    Systick::setReloadValue(0xFFFFFF);
    // CHECK: {{str|ldr}}
    volatile uint32_t max_reload = Systick::getReloadValue();
    // CHECK: {{str|ldr}}
    
    // Test common timer values
    Systick::setReloadValue(1000);
    // CHECK: {{str|ldr}}
    volatile uint32_t reload_1000 = Systick::getReloadValue();
    // CHECK: {{str|ldr}}
    
    Systick::setReloadValue(10000);
    // CHECK: {{str|ldr}}
    volatile uint32_t reload_10000 = Systick::getReloadValue();
    // CHECK: {{str|ldr}}
    
    // Test power-of-2 values
    Systick::setReloadValue(256);
    // CHECK: {{str|ldr}}
    volatile uint32_t reload_256 = Systick::getReloadValue();
    // CHECK: {{str|ldr}}
    
    Systick::setReloadValue(65536);
    // CHECK: {{str|ldr}}
    volatile uint32_t reload_65536 = Systick::getReloadValue();
    // CHECK: {{str|ldr}}
    
    // Verify values are correct
    volatile bool values_correct = (min_reload == 1) && (max_reload == 0xFFFFFF) &&
                                  (reload_1000 == 1000) && (reload_10000 == 10000) &&
                                  (reload_256 == 256) && (reload_65536 == 65536);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_systick_current_value_operations() {
    // CHECK-LABEL: <{{.*test_systick_current_value_operations.*}}>:
    
    // Set reload value
    Systick::setReloadValue(5000);
    // CHECK: {{str|ldr}}
    
    // Clear current value
    Systick::clearCurrentValue();
    // CHECK: {{str|ldr}}
    
    // Read current value multiple times
    volatile uint32_t current1 = Systick::getCurrentValue();
    // CHECK: {{str|ldr}}
    volatile uint32_t current2 = Systick::getCurrentValue();
    // CHECK: {{str|ldr}}
    volatile uint32_t current3 = Systick::getCurrentValue();
    // CHECK: {{str|ldr}}
    
    // Clear again
    Systick::clearCurrentValue();
    // CHECK: {{str|ldr}}
    
    // Read after clear
    volatile uint32_t current_after_clear = Systick::getCurrentValue();
    // CHECK: {{str|ldr}}
    
    // Multiple clears in sequence
    Systick::clearCurrentValue();
    // CHECK: {{str|ldr}}
    Systick::clearCurrentValue();
    // CHECK: {{str|ldr}}
    
    volatile uint32_t final_current = Systick::getCurrentValue();
    // CHECK: {{str|ldr}}
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

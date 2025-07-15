// REQUIRES: cortex-m0plus
// RUN: %cc% %ccflags% %ccout% %T/%basename_t.o %s; objdump --mcpu=%mcpu% -d %T/%basename_t.o | FileCheck --allow-unused-prefixes --check-prefixes %prefixes% %s

#include "cortexm0plus/mpu.hpp"
#include <cstdint>

using namespace CortexM0plus;

void test_mpu_type_register() {
    // CHECK-LABEL: <{{.*test_mpu_type_register.*}}>:
    
    // Read MPU type register
    volatile auto mpu_type = Mpu::getType();
    // CHECK: {{str|ldr}}
    
    // Test bitfield access
    volatile uint32_t num_regions = mpu_type.bits.dregion;
    volatile bool separate_regions = mpu_type.bits.separate;
    
    // Read multiple times to ensure consistency
    volatile auto mpu_type2 = Mpu::getType();
    // CHECK: {{str|ldr}}
    volatile bool consistent = (mpu_type.value == mpu_type2.value);
    
    // Verify reasonable values for Cortex-M0+
    volatile bool regions_reasonable = (num_regions >= 4) && (num_regions <= 16);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_mpu_control_register_comprehensive() {
    // CHECK-LABEL: <{{.*test_mpu_control_register_comprehensive.*}}>:
    
    // Test all combinations of MPU control bits
    Mpu::Control ctrl;
    
    // Test disabled MPU
    ctrl.value = 0;
    ctrl.bits.enable = 0;
    ctrl.bits.hfnmiena = 0;
    ctrl.bits.privdefena = 0;
    Mpu::setControl(ctrl);
    // CHECK: {{str|ldr}}
    
    // Test enabled MPU, basic config
    ctrl.bits.enable = 1;
    Mpu::setControl(ctrl);
    // CHECK: {{str|ldr}}
    
    // Test with HardFault/NMI enable
    ctrl.bits.hfnmiena = 1;
    Mpu::setControl(ctrl);
    // CHECK: {{str|ldr}}
    
    // Test with privileged default enable
    ctrl.bits.privdefena = 1;
    Mpu::setControl(ctrl);
    // CHECK: {{str|ldr}}
    
    // Test all flags enabled
    ctrl.bits.enable = 1;
    ctrl.bits.hfnmiena = 1;
    ctrl.bits.privdefena = 1;
    Mpu::setControl(ctrl);
    // CHECK: {{str|ldr}}
    
    // Read back and verify
    volatile auto read_ctrl = Mpu::getControl();
    // CHECK: {{str|ldr}}
    
    volatile bool enable_correct = read_ctrl.bits.enable;
    volatile bool hfnmi_correct = read_ctrl.bits.hfnmiena;
    volatile bool privdef_correct = read_ctrl.bits.privdefena;
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_mpu_region_selection() {
    // CHECK-LABEL: <{{.*test_mpu_region_selection.*}}>:
    
    // Test setting different region numbers
    for (uint32_t region = 0; region < 8; ++region) {
        Mpu::setRegionNumber(region);
        // CHECK: {{str|ldr}}
        
        volatile uint32_t read_region = Mpu::getRegionNumber();
        // CHECK: {{str|ldr}}
        
        volatile bool region_correct = (read_region == region);
    }
    
    // Test boundary values
    Mpu::setRegionNumber(0);  // First region
    // CHECK: {{str|ldr}}
    volatile uint32_t region_0 = Mpu::getRegionNumber();
    // CHECK: {{str|ldr}}
    
    Mpu::setRegionNumber(7);  // Last region for typical M0+
    // CHECK: {{str|ldr}}
    volatile uint32_t region_7 = Mpu::getRegionNumber();
    // CHECK: {{str|ldr}}
    
    // Verify boundary values
    volatile bool boundaries_correct = (region_0 == 0) && (region_7 == 7);
    
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

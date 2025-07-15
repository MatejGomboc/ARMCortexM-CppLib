// REQUIRES: cortex-m0
// RUN: %cc% %ccflags% %ccout% %T/%basename_t.o %s; objdump --mcpu=%mcpu% -d %T/%basename_t.o | FileCheck --allow-unused-prefixes --check-prefixes %prefixes% %s

#include "cortexm0/special_regs.hpp"
#include <cstdint>

using namespace CortexM0;

void test_getLr() {
    // CHECK-LABEL: <{{.*test_getLr.*}}>:
    // CHECK: mov {{r[0-9]+}}, lr
    volatile uint32_t lr_value = getLr();
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_getApsrReg() {
    // CHECK-LABEL: <{{.*test_getApsrReg.*}}>:
    // CHECK: mrs {{r[0-9]+}}, apsr
    volatile Psr apsr = getApsrReg();
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_getIpsrReg() {
    // CHECK-LABEL: <{{.*test_getIpsrReg.*}}>:
    // CHECK: mrs {{r[0-9]+}}, ipsr
    volatile Psr ipsr = getIpsrReg();
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_getMspReg() {
    // CHECK-LABEL: <{{.*test_getMspReg.*}}>:
    // CHECK: mrs {{r[0-9]+}}, msp
    volatile uint32_t msp = getMspReg();
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_setMspReg() {
    // CHECK-LABEL: <{{.*test_setMspReg.*}}>:
    // CHECK: msr msp, {{r[0-9]+}}
    // CHECK: isb
    setMspReg(0x20008000);
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_getPspReg() {
    // CHECK-LABEL: <{{.*test_getPspReg.*}}>:
    // CHECK: mrs {{r[0-9]+}}, psp
    volatile uint32_t psp = getPspReg();
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_setPspReg() {
    // CHECK-LABEL: <{{.*test_setPspReg.*}}>:
    // CHECK: msr psp, {{r[0-9]+}}
    // CHECK: isb
    setPspReg(0x20004000);
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_getPrimaskReg() {
    // CHECK-LABEL: <{{.*test_getPrimaskReg.*}}>:
    // CHECK: mrs {{r[0-9]+}}, primask
    volatile Primask primask = getPrimaskReg();
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_getControlReg() {
    // CHECK-LABEL: <{{.*test_getControlReg.*}}>:
    // CHECK: mrs {{r[0-9]+}}, control
    volatile Control control = getControlReg();
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

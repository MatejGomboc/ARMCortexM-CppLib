#include "m0plus/special_regs.hpp"

// Test getLr()
extern "C" [[gnu::naked]] void test_get_lr() {
    auto lr = Cortex::M0Plus::getLr();
    (void)lr;
}

// CHECK-LABEL: <test_get_lr>:
// CHECK-NEXT: mov{{.*}} r0, lr
// CHECK-NEXT: bx lr

// Test getApsrReg()
extern "C" [[gnu::naked]] void test_get_apsr() {
    auto apsr = Cortex::M0Plus::getApsrReg();
    (void)apsr;
}

// CHECK-LABEL: <test_get_apsr>:
// CHECK-NEXT: mrs r0, apsr
// CHECK-NEXT: bx lr

// Test getIpsrReg()
extern "C" [[gnu::naked]] void test_get_ipsr() {
    auto ipsr = Cortex::M0Plus::getIpsrReg();
    (void)ipsr;
}

// CHECK-LABEL: <test_get_ipsr>:
// CHECK-NEXT: mrs r0, ipsr
// CHECK-NEXT: bx lr

// Test getEpsrReg()
extern "C" [[gnu::naked]] void test_get_epsr() {
    auto epsr = Cortex::M0Plus::getEpsrReg();
    (void)epsr;
}

// CHECK-LABEL: <test_get_epsr>:
// CHECK-NEXT: mrs r0, epsr
// CHECK-NEXT: bx lr

// Test getIepsrReg()
extern "C" [[gnu::naked]] void test_get_iepsr() {
    auto iepsr = Cortex::M0Plus::getIepsrReg();
    (void)iepsr;
}

// CHECK-LABEL: <test_get_iepsr>:
// CHECK-NEXT: mrs r0, iepsr
// CHECK-NEXT: bx lr

// Test getIapsrReg()
extern "C" [[gnu::naked]] void test_get_iapsr() {
    auto iapsr = Cortex::M0Plus::getIapsrReg();
    (void)iapsr;
}

// CHECK-LABEL: <test_get_iapsr>:
// CHECK-NEXT: mrs r0, iapsr
// CHECK-NEXT: bx lr

// Test getEapsrReg()
extern "C" [[gnu::naked]] void test_get_eapsr() {
    auto eapsr = Cortex::M0Plus::getEapsrReg();
    (void)eapsr;
}

// CHECK-LABEL: <test_get_eapsr>:
// CHECK-NEXT: mrs r0, eapsr
// CHECK-NEXT: bx lr

// Test getPsrReg()
extern "C" [[gnu::naked]] void test_get_psr() {
    auto psr = Cortex::M0Plus::getPsrReg();
    (void)psr;
}

// CHECK-LABEL: <test_get_psr>:
// CHECK-NEXT: mrs r0, psr
// CHECK-NEXT: bx lr

// Test getMspReg()
extern "C" [[gnu::naked]] void test_get_msp() {
    auto msp = Cortex::M0Plus::getMspReg();
    (void)msp;
}

// CHECK-LABEL: <test_get_msp>:
// CHECK-NEXT: mrs r0, msp
// CHECK-NEXT: bx lr

// Test setMspReg()
extern "C" [[gnu::naked]] void test_set_msp() {
    Cortex::M0Plus::setMspReg(0x20001000);
}

// CHECK-LABEL: <test_set_msp>:
// CHECK: msr msp, {{r[0-9]+}}
// CHECK-NEXT: bx lr

// Test getPspReg()
extern "C" [[gnu::naked]] void test_get_psp() {
    auto psp = Cortex::M0Plus::getPspReg();
    (void)psp;
}

// CHECK-LABEL: <test_get_psp>:
// CHECK-NEXT: mrs r0, psp
// CHECK-NEXT: bx lr

// Test setPspReg()
extern "C" [[gnu::naked]] void test_set_psp() {
    Cortex::M0Plus::setPspReg(0x20002000);
}

// CHECK-LABEL: <test_set_psp>:
// CHECK: msr psp, {{r[0-9]+}}
// CHECK-NEXT: bx lr

// Test getPrimaskReg()
extern "C" [[gnu::naked]] void test_get_primask() {
    auto primask = Cortex::M0Plus::getPrimaskReg();
    (void)primask;
}

// CHECK-LABEL: <test_get_primask>:
// CHECK-NEXT: mrs r0, primask
// CHECK-NEXT: bx lr

// Test setPrimaskReg()
extern "C" [[gnu::naked]] void test_set_primask() {
    Cortex::M0Plus::PRIMASK primask;
    primask.bits.PRIMASK = 1;
    Cortex::M0Plus::setPrimaskReg(primask);
}

// CHECK-LABEL: <test_set_primask>:
// CHECK: msr primask, {{r[0-9]+}}
// CHECK-NEXT: bx lr

// Test getControlReg()
extern "C" [[gnu::naked]] void test_get_control() {
    auto control = Cortex::M0Plus::getControlReg();
    (void)control;
}

// CHECK-LABEL: <test_get_control>:
// CHECK-NEXT: mrs r0, control
// CHECK-NEXT: bx lr

// Test setControlReg()
extern "C" [[gnu::naked]] void test_set_control() {
    Cortex::M0Plus::CONTROL control;
    control.bits.SPSEL = 1;
    Cortex::M0Plus::setControlReg(control);
}

// CHECK-LABEL: <test_set_control>:
// CHECK: msr control, {{r[0-9]+}}
// CHECK-NEXT: bx lr

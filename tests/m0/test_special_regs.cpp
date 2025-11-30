#include "m0/special_regs.hpp"

// Test getLr()
extern "C" [[gnu::naked]] void test_get_lr() {
    uint32_t lr = ArmCortex::M0::getLr();
    (void)lr;
}

// CHECK-LABEL: <test_get_lr>:
// CHECK-NEXT: mov r3, lr
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// Test getApsrReg()
extern "C" [[gnu::naked]] void test_get_apsr() {
    ArmCortex::M0::PSR apsr = ArmCortex::M0::getApsrReg();
    (void)apsr;
}

// CHECK-LABEL: <test_get_apsr>:
// CHECK-NEXT: mrs r3, CPSR
// CHECK-EMPTY:

// Test getIpsrReg()
extern "C" [[gnu::naked]] void test_get_ipsr() {
    ArmCortex::M0::PSR ipsr = ArmCortex::M0::getIpsrReg();
    (void)ipsr;
}

// CHECK-LABEL: <test_get_ipsr>:
// CHECK-NEXT: mrs r3, IPSR
// CHECK-EMPTY:

// Test getEpsrReg()
extern "C" [[gnu::naked]] void test_get_epsr() {
    ArmCortex::M0::PSR epsr = ArmCortex::M0::getEpsrReg();
    (void)epsr;
}

// CHECK-LABEL: <test_get_epsr>:
// CHECK-NEXT: mrs r3, EPSR
// CHECK-EMPTY:

// Test getIepsrReg()
extern "C" [[gnu::naked]] void test_get_iepsr() {
    ArmCortex::M0::PSR iepsr = ArmCortex::M0::getIepsrReg();
    (void)iepsr;
}

// CHECK-LABEL: <test_get_iepsr>:
// CHECK-NEXT: mrs r3, IEPSR
// CHECK-EMPTY:

// Test getIapsrReg()
extern "C" [[gnu::naked]] void test_get_iapsr() {
    ArmCortex::M0::PSR iapsr = ArmCortex::M0::getIapsrReg();
    (void)iapsr;
}

// CHECK-LABEL: <test_get_iapsr>:
// CHECK-NEXT: mrs r3, IAPSR
// CHECK-EMPTY:

// Test getEapsrReg()
extern "C" [[gnu::naked]] void test_get_eapsr() {
    ArmCortex::M0::PSR eapsr = ArmCortex::M0::getEapsrReg();
    (void)eapsr;
}

// CHECK-LABEL: <test_get_eapsr>:
// CHECK-NEXT: mrs r3, EAPSR
// CHECK-EMPTY:

// Test getPsrReg()
extern "C" [[gnu::naked]] void test_get_psr() {
    ArmCortex::M0::PSR psr = ArmCortex::M0::getPsrReg();
    (void)psr;
}

// CHECK-LABEL: <test_get_psr>:
// CHECK-NEXT: mrs r3, PSR
// CHECK-EMPTY:

// Test getMspReg()
extern "C" [[gnu::naked]] void test_get_msp() {
    uint32_t msp = ArmCortex::M0::getMspReg();
    (void)msp;
}

// CHECK-LABEL: <test_get_msp>:
// CHECK-NEXT: mrs r3, MSP
// CHECK-EMPTY:

// Test setMspReg()
extern "C" [[gnu::naked]] void test_set_msp() {
    ArmCortex::M0::setMspReg(0x20001000);
}

// CHECK-LABEL: <test_set_msp>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: msr MSP, r3
// MAXSPEED-CHECK-NEXT: nop
// CHECK-NEXT: .word 0x20001000
// CHECK-EMPTY:

// Test getPspReg()
extern "C" [[gnu::naked]] void test_get_psp() {
    uint32_t psp = ArmCortex::M0::getPspReg();
    (void)psp;
}

// CHECK-LABEL: <test_get_psp>:
// CHECK-NEXT: mrs r3, PSP
// CHECK-EMPTY:

// Test setPspReg()
extern "C" [[gnu::naked]] void test_set_psp() {
    ArmCortex::M0::setPspReg(0x20002000);
}

// CHECK-LABEL: <test_set_psp>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: msr PSP, r3
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0x20002000
// CHECK-EMPTY:

// Test getPrimaskReg()
extern "C" [[gnu::naked]] void test_get_primask() {
    ArmCortex::M0::PRIMASK primask = ArmCortex::M0::getPrimaskReg();
    (void)primask;
}

// CHECK-LABEL: <test_get_primask>:
// CHECK-NEXT: mrs r3, PRIMASK
// CHECK-EMPTY:

// Test setPrimaskReg()
extern "C" [[gnu::naked]] void test_set_primask() {
    ArmCortex::M0::PRIMASK primask;
    primask.bits.PRIMASK = 1;
    ArmCortex::M0::setPrimaskReg(primask);
}

// CHECK-LABEL: <test_set_primask>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: msr PRIMASK, r3
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// Test getControlReg()
extern "C" [[gnu::naked]] void test_get_control() {
    ArmCortex::M0::CONTROL control = ArmCortex::M0::getControlReg();
    (void)control;
}

// CHECK-LABEL: <test_get_control>:
// CHECK-NEXT: mrs r3, CONTROL
// CHECK-EMPTY:

// Test setControlReg()
extern "C" [[gnu::naked]] void test_set_control() {
    ArmCortex::M0::CONTROL control;
    control.bits.SPSEL = 1;
    ArmCortex::M0::setControlReg(control);
}

// CHECK-LABEL: <test_set_control>:
// CHECK-NEXT: movs r3, #2
// CHECK-NEXT: msr CONTROL, r3
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

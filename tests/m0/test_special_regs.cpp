#include "armcortex/m0/special_regs.hpp"

// Test getLr()
extern "C" [[gnu::naked]] void test_get_lr() {
    uint32_t lr = ArmCortex::getLr();
    (void)lr;
}

// CHECK-LABEL: <test_get_lr>:
// CHECK-NEXT: mov r3, lr
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// Test getApsrReg()
extern "C" [[gnu::naked]] void test_get_apsr() {
    ArmCortex::PSR apsr = ArmCortex::getApsrReg();
    (void)apsr;
}

// CHECK-LABEL: <test_get_apsr>:
// CHECK-NEXT: mrs r3, CPSR
// CHECK-EMPTY:

// Test getIpsrReg()
extern "C" [[gnu::naked]] void test_get_ipsr() {
    ArmCortex::PSR ipsr = ArmCortex::getIpsrReg();
    (void)ipsr;
}

// CHECK-LABEL: <test_get_ipsr>:
// CHECK-NEXT: mrs r3, IPSR
// CHECK-EMPTY:

// Test getEpsrReg()
extern "C" [[gnu::naked]] void test_get_epsr() {
    ArmCortex::PSR epsr = ArmCortex::getEpsrReg();
    (void)epsr;
}

// CHECK-LABEL: <test_get_epsr>:
// CHECK-NEXT: mrs r3, EPSR
// CHECK-EMPTY:

// Test getIepsrReg()
extern "C" [[gnu::naked]] void test_get_iepsr() {
    ArmCortex::PSR iepsr = ArmCortex::getIepsrReg();
    (void)iepsr;
}

// CHECK-LABEL: <test_get_iepsr>:
// CHECK-NEXT: mrs r3, IEPSR
// CHECK-EMPTY:

// Test getIapsrReg()
extern "C" [[gnu::naked]] void test_get_iapsr() {
    ArmCortex::PSR iapsr = ArmCortex::getIapsrReg();
    (void)iapsr;
}

// CHECK-LABEL: <test_get_iapsr>:
// CHECK-NEXT: mrs r3, IAPSR
// CHECK-EMPTY:

// Test getEapsrReg()
extern "C" [[gnu::naked]] void test_get_eapsr() {
    ArmCortex::PSR eapsr = ArmCortex::getEapsrReg();
    (void)eapsr;
}

// CHECK-LABEL: <test_get_eapsr>:
// CHECK-NEXT: mrs r3, EAPSR
// CHECK-EMPTY:

// Test getPsrReg()
extern "C" [[gnu::naked]] void test_get_psr() {
    ArmCortex::PSR psr = ArmCortex::getPsrReg();
    (void)psr;
}

// CHECK-LABEL: <test_get_psr>:
// CHECK-NEXT: mrs r3, PSR
// CHECK-EMPTY:

// Test getMspReg()
extern "C" [[gnu::naked]] void test_get_msp() {
    uint32_t msp = ArmCortex::getMspReg();
    (void)msp;
}

// CHECK-LABEL: <test_get_msp>:
// CHECK-NEXT: mrs r3, MSP
// CHECK-EMPTY:

// Test setMspReg()
extern "C" [[gnu::naked]] void test_set_msp() {
    ArmCortex::setMspReg(0x20001000);
}

// CHECK-LABEL: <test_set_msp>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: msr MSP, r3
// MAXSPEED-CHECK-NEXT: nop
// CHECK-NEXT: .word 0x20001000
// CHECK-EMPTY:

// Test getPspReg()
extern "C" [[gnu::naked]] void test_get_psp() {
    uint32_t psp = ArmCortex::getPspReg();
    (void)psp;
}

// CHECK-LABEL: <test_get_psp>:
// CHECK-NEXT: mrs r3, PSP
// CHECK-EMPTY:

// Test setPspReg()
extern "C" [[gnu::naked]] void test_set_psp() {
    ArmCortex::setPspReg(0x20002000);
}

// CHECK-LABEL: <test_set_psp>:
// CHECK-NEXT: ldr r3, [pc, #4]
// CHECK-NEXT: msr PSP, r3
// CHECK-NEXT: nop
// CHECK-NEXT: .word 0x20002000
// CHECK-EMPTY:

// Test getPrimaskReg()
extern "C" [[gnu::naked]] void test_get_primask() {
    ArmCortex::PRIMASK primask = ArmCortex::getPrimaskReg();
    (void)primask;
}

// CHECK-LABEL: <test_get_primask>:
// CHECK-NEXT: mrs r3, PRIMASK
// CHECK-EMPTY:

// Test setPrimaskReg()
extern "C" [[gnu::naked]] void test_set_primask() {
    ArmCortex::PRIMASK primask;
    primask.bits.PRIMASK = 1;
    ArmCortex::setPrimaskReg(primask);
}

// CHECK-LABEL: <test_set_primask>:
// CHECK-NEXT: movs r3, #1
// CHECK-NEXT: msr PRIMASK, r3
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

// Test getControlReg()
extern "C" [[gnu::naked]] void test_get_control() {
    ArmCortex::CONTROL control = ArmCortex::getControlReg();
    (void)control;
}

// CHECK-LABEL: <test_get_control>:
// CHECK-NEXT: mrs r3, CONTROL
// CHECK-EMPTY:

// Test setControlReg()
extern "C" [[gnu::naked]] void test_set_control() {
    ArmCortex::CONTROL control;
    control.bits.SPSEL = 1;
    ArmCortex::setControlReg(control);
}

// CHECK-LABEL: <test_set_control>:
// CHECK-NEXT: movs r3, #2
// CHECK-NEXT: msr CONTROL, r3
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

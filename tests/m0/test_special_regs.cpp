#include "armcortex/m0/special_regs.hpp"

// Test getLr()
extern "C" [[gnu::naked]] uint32_t test_get_lr() {
    return ArmCortex::getLr();
}

// CHECK-LABEL: <test_get_lr>:

// DEBUG-CHECK-NEXT: mov r0, lr

// MINSIZE-CHECK-NEXT: mov r0, lr

// MAXSPEED-CHECK-NEXT: mov r0, lr
// MAXSPEED-CHECK-NEXT: nop

// CHECK-EMPTY:

// Test getApsrReg()
extern "C" [[gnu::naked]] ArmCortex::PSR test_get_apsr() {
    return ArmCortex::getApsrReg();
}

// CHECK-LABEL: <test_get_apsr>:
// CHECK-NEXT: mrs r0, CPSR
// CHECK-EMPTY:

// Test getIpsrReg()
extern "C" [[gnu::naked]] ArmCortex::PSR test_get_ipsr() {
    return ArmCortex::getIpsrReg();
}

// CHECK-LABEL: <test_get_ipsr>:
// CHECK-NEXT: mrs r0, IPSR
// CHECK-EMPTY:

// Test getEpsrReg()
extern "C" [[gnu::naked]] ArmCortex::PSR test_get_epsr() {
    return ArmCortex::getEpsrReg();
}

// CHECK-LABEL: <test_get_epsr>:
// CHECK-NEXT: mrs r0, EPSR
// CHECK-EMPTY:

// Test getIepsrReg()
extern "C" [[gnu::naked]] ArmCortex::PSR test_get_iepsr() {
    return ArmCortex::getIepsrReg();
}

// CHECK-LABEL: <test_get_iepsr>:
// CHECK-NEXT: mrs r0, IEPSR
// CHECK-EMPTY:

// Test getIapsrReg()
extern "C" [[gnu::naked]] ArmCortex::PSR test_get_iapsr() {
    return ArmCortex::getIapsrReg();
}

// CHECK-LABEL: <test_get_iapsr>:
// CHECK-NEXT: mrs r0, IAPSR
// CHECK-EMPTY:

// Test getEapsrReg()
extern "C" [[gnu::naked]] ArmCortex::PSR test_get_eapsr() {
    return ArmCortex::getEapsrReg();
}

// CHECK-LABEL: <test_get_eapsr>:
// CHECK-NEXT: mrs r0, EAPSR
// CHECK-EMPTY:

// Test getPsrReg()
extern "C" [[gnu::naked]] ArmCortex::PSR test_get_psr() {
    return ArmCortex::getPsrReg();
}

// CHECK-LABEL: <test_get_psr>:
// CHECK-NEXT: mrs r0, PSR
// CHECK-EMPTY:

// Test getMspReg()
extern "C" [[gnu::naked]] uint32_t test_get_msp() {
    return ArmCortex::getMspReg();
}

// CHECK-LABEL: <test_get_msp>:
// CHECK-NEXT: mrs r0, MSP
// CHECK-EMPTY:

// Test setMspReg()
extern "C" [[gnu::naked]] void test_set_msp() {
    ArmCortex::setMspReg(0x20001000);
}

// CHECK-LABEL: <test_set_msp>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: msr MSP, r3
// DEBUG-CHECK-NEXT: .word 0x20001000

// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: msr MSP, r3
// MINSIZE-CHECK-NEXT: .word 0x20001000

// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: msr MSP, r3
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0x20001000

// CHECK-EMPTY:

// Test getPspReg()
extern "C" [[gnu::naked]] uint32_t test_get_psp() {
    return ArmCortex::getPspReg();
}

// CHECK-LABEL: <test_get_psp>:
// CHECK-NEXT: mrs r0, PSP
// CHECK-EMPTY:

// Test setPspReg()
extern "C" [[gnu::naked]] void test_set_psp() {
    ArmCortex::setPspReg(0x20002000);
}

// CHECK-LABEL: <test_set_psp>:

// DEBUG-CHECK-NEXT: ldr r3, [pc, #4]
// DEBUG-CHECK-NEXT: msr PSP, r3
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: .word 0x20002000

// MINSIZE-CHECK-NEXT: ldr r3, [pc, #4]
// MINSIZE-CHECK-NEXT: msr PSP, r3
// MINSIZE-CHECK-NEXT: nop
// MINSIZE-CHECK-NEXT: .word 0x20002000

// MAXSPEED-CHECK-NEXT: ldr r3, [pc, #4]
// MAXSPEED-CHECK-NEXT: msr PSP, r3
// MAXSPEED-CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: .word 0x20002000

// CHECK-EMPTY:

// Test getPrimaskReg()
extern "C" [[gnu::naked]] ArmCortex::PRIMASK test_get_primask() {
    return ArmCortex::getPrimaskReg();
}

// CHECK-LABEL: <test_get_primask>:
// CHECK-NEXT: mrs r0, PRIMASK
// CHECK-EMPTY:

// Test setPrimaskReg()
extern "C" [[gnu::naked]] void test_set_primask() {
    ArmCortex::PRIMASK primask;
    primask.bits.PRIMASK = 1;
    ArmCortex::setPrimaskReg(primask);
}

// CHECK-LABEL: <test_set_primask>:

// DEBUG-CHECK-NEXT: movs r3, #1
// DEBUG-CHECK-NEXT: msr PRIMASK, r3

// MINSIZE-CHECK-NEXT: movs r3, #1
// MINSIZE-CHECK-NEXT: msr PRIMASK, r3

// MAXSPEED-CHECK-NEXT: movs r3, #1
// MAXSPEED-CHECK-NEXT: msr PRIMASK, r3
// MAXSPEED-CHECK-NEXT: nop

// CHECK-EMPTY:

// Test getControlReg()
extern "C" [[gnu::naked]] ArmCortex::CONTROL test_get_control() {
    return ArmCortex::getControlReg();
}

// CHECK-LABEL: <test_get_control>:
// CHECK-NEXT: mrs r0, CONTROL
// CHECK-EMPTY:

// Test setControlReg()
extern "C" [[gnu::naked]] void test_set_control() {
    ArmCortex::CONTROL control;
    control.bits.SPSEL = 1;
    ArmCortex::setControlReg(control);
}

// CHECK-LABEL: <test_set_control>:

// DEBUG-CHECK-NEXT: movs r3, #2
// DEBUG-CHECK-NEXT: msr CONTROL, r3

// MINSIZE-CHECK-NEXT: movs r3, #2
// MINSIZE-CHECK-NEXT: msr CONTROL, r3

// MAXSPEED-CHECK-NEXT: movs r3, #2
// MAXSPEED-CHECK-NEXT: msr CONTROL, r3
// MAXSPEED-CHECK-NEXT: nop

// CHECK-EMPTY:

#include "m0/special_regs.hpp"

extern "C" [[gnu::naked]] uint32_t test_get_lr() {
    return Cortex::M0::getLr();
}

// CHECK-LABEL: <test_get_lr>:
// CHECK-NEXT: mov r0, lr
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M0::PSR test_get_apsr_reg() {
    return Cortex::M0::getApsrReg();
}

// CHECK-LABEL: <test_get_apsr_reg>:
// CHECK-NEXT: mrs r0, APSR
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M0::PSR test_get_ipsr_reg() {
    return Cortex::M0::getIpsrReg();
}

// CHECK-LABEL: <test_get_ipsr_reg>:
// CHECK-NEXT: mrs r0, IPSR
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M0::PSR test_get_epsr_reg() {
    return Cortex::M0::getEpsrReg();
}

// CHECK-LABEL: <test_get_epsr_reg>:
// CHECK-NEXT: mrs r0, EPSR
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M0::PSR test_get_iepsr_reg() {
    return Cortex::M0::getIepsrReg();
}

// CHECK-LABEL: <test_get_iepsr_reg>:
// CHECK-NEXT: mrs r0, IEPSR
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M0::PSR test_get_iapsr_reg() {
    return Cortex::M0::getIapsrReg();
}

// CHECK-LABEL: <test_get_iapsr_reg>:
// CHECK-NEXT: mrs r0, IAPSR
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M0::PSR test_get_eapsr_reg() {
    return Cortex::M0::getEapsrReg();
}

// CHECK-LABEL: <test_get_eapsr_reg>:
// CHECK-NEXT: mrs r0, EAPSR
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M0::PSR test_get_psr_reg() {
    return Cortex::M0::getPsrReg();
}

// CHECK-LABEL: <test_get_psr_reg>:
// CHECK-NEXT: mrs r0, PSR
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_get_msp_reg() {
    return Cortex::M0::getMspReg();
}

// CHECK-LABEL: <test_get_msp_reg>:
// CHECK-NEXT: mrs r0, MSP
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_set_msp_reg(uint32_t value) {
    Cortex::M0::setMspReg(value);
}

// CHECK-LABEL: <test_set_msp_reg>:
// CHECK-NEXT: msr MSP, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_get_psp_reg() {
    return Cortex::M0::getPspReg();
}

// CHECK-LABEL: <test_get_psp_reg>:
// CHECK-NEXT: mrs r0, PSP
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_set_psp_reg(uint32_t value) {
    Cortex::M0::setPspReg(value);
}

// CHECK-LABEL: <test_set_psp_reg>:
// CHECK-NEXT: msr PSP, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M0::PRIMASK test_get_primask_reg() {
    return Cortex::M0::getPrimaskReg();
}

// CHECK-LABEL: <test_get_primask_reg>:
// CHECK-NEXT: mrs r0, PRIMASK
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_set_primask_reg(Cortex::M0::PRIMASK primask) {
    Cortex::M0::setPrimaskReg(primask);
}

// CHECK-LABEL: <test_set_primask_reg>:
// CHECK-NEXT: msr PRIMASK, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M0::CONTROL test_get_control_reg() {
    return Cortex::M0::getControlReg();
}

// CHECK-LABEL: <test_get_control_reg>:
// CHECK-NEXT: mrs r0, CONTROL
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_set_control_reg(Cortex::M0::CONTROL control) {
    Cortex::M0::setControlReg(control);
}

// CHECK-LABEL: <test_set_control_reg>:
// CHECK-NEXT: msr CONTROL, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

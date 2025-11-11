#include "m3/special_regs.hpp"

extern "C" [[gnu::naked]] uint32_t test_get_lr_m3() {
    return Cortex::M3::getLr();
}

// CHECK-LABEL: <test_get_lr_m3>:
// CHECK-NEXT: mov r0, lr
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M3::PSR test_get_apsr_reg_m3() {
    return Cortex::M3::getApsrReg();
}

// CHECK-LABEL: <test_get_apsr_reg_m3>:
// CHECK-NEXT: mrs r0, APSR
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M3::PSR test_get_ipsr_reg_m3() {
    return Cortex::M3::getIpsrReg();
}

// CHECK-LABEL: <test_get_ipsr_reg_m3>:
// CHECK-NEXT: mrs r0, IPSR
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M3::PSR test_get_epsr_reg_m3() {
    return Cortex::M3::getEpsrReg();
}

// CHECK-LABEL: <test_get_epsr_reg_m3>:
// CHECK-NEXT: mrs r0, EPSR
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M3::PSR test_get_iepsr_reg_m3() {
    return Cortex::M3::getIepsrReg();
}

// CHECK-LABEL: <test_get_iepsr_reg_m3>:
// CHECK-NEXT: mrs r0, IEPSR
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M3::PSR test_get_iapsr_reg_m3() {
    return Cortex::M3::getIapsrReg();
}

// CHECK-LABEL: <test_get_iapsr_reg_m3>:
// CHECK-NEXT: mrs r0, IAPSR
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M3::PSR test_get_eapsr_reg_m3() {
    return Cortex::M3::getEapsrReg();
}

// CHECK-LABEL: <test_get_eapsr_reg_m3>:
// CHECK-NEXT: mrs r0, EAPSR
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M3::PSR test_get_psr_reg_m3() {
    return Cortex::M3::getPsrReg();
}

// CHECK-LABEL: <test_get_psr_reg_m3>:
// CHECK-NEXT: mrs r0, PSR
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_get_msp_reg_m3() {
    return Cortex::M3::getMspReg();
}

// CHECK-LABEL: <test_get_msp_reg_m3>:
// CHECK-NEXT: mrs r0, MSP
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_set_msp_reg_m3(uint32_t value) {
    Cortex::M3::setMspReg(value);
}

// CHECK-LABEL: <test_set_msp_reg_m3>:
// CHECK-NEXT: msr MSP, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_get_psp_reg_m3() {
    return Cortex::M3::getPspReg();
}

// CHECK-LABEL: <test_get_psp_reg_m3>:
// CHECK-NEXT: mrs r0, PSP
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_set_psp_reg_m3(uint32_t value) {
    Cortex::M3::setPspReg(value);
}

// CHECK-LABEL: <test_set_psp_reg_m3>:
// CHECK-NEXT: msr PSP, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M3::PRIMASK test_get_primask_reg_m3() {
    return Cortex::M3::getPrimaskReg();
}

// CHECK-LABEL: <test_get_primask_reg_m3>:
// CHECK-NEXT: mrs r0, PRIMASK
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_set_primask_reg_m3(Cortex::M3::PRIMASK primask) {
    Cortex::M3::setPrimaskReg(primask);
}

// CHECK-LABEL: <test_set_primask_reg_m3>:
// CHECK-NEXT: msr PRIMASK, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M3::FAULTMASK test_get_faultmask_reg() {
    return Cortex::M3::getFaultmaskReg();
}

// CHECK-LABEL: <test_get_faultmask_reg>:
// CHECK-NEXT: mrs r0, FAULTMASK
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_set_faultmask_reg(Cortex::M3::FAULTMASK faultmask) {
    Cortex::M3::setFaultmaskReg(faultmask);
}

// CHECK-LABEL: <test_set_faultmask_reg>:
// CHECK-NEXT: msr FAULTMASK, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M3::BASEPRI test_get_basepri_reg() {
    return Cortex::M3::getBasepriReg();
}

// CHECK-LABEL: <test_get_basepri_reg>:
// CHECK-NEXT: mrs r0, BASEPRI
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_set_basepri_reg(Cortex::M3::BASEPRI basepri) {
    Cortex::M3::setBasepriReg(basepri);
}

// CHECK-LABEL: <test_set_basepri_reg>:
// CHECK-NEXT: msr BASEPRI, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_set_basepri_max_reg(Cortex::M3::BASEPRI basepri) {
    Cortex::M3::setBasepriMaxReg(basepri);
}

// CHECK-LABEL: <test_set_basepri_max_reg>:
// CHECK-NEXT: msr BASEPRI_MAX, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] Cortex::M3::CONTROL test_get_control_reg_m3() {
    return Cortex::M3::getControlReg();
}

// CHECK-LABEL: <test_get_control_reg_m3>:
// CHECK-NEXT: mrs r0, CONTROL
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_set_control_reg_m3(Cortex::M3::CONTROL control) {
    Cortex::M3::setControlReg(control);
}

// CHECK-LABEL: <test_set_control_reg_m3>:
// CHECK-NEXT: msr CONTROL, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

#include "power_management.hpp"

extern "C" [[gnu::naked]] void test_sev() {
    Cortex::asmSev();
}

// CHECK-LABEL: <test_sev>:
// CHECK-NEXT: sev
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_wfe() {
    Cortex::asmWfe();
}

// CHECK-LABEL: <test_wfe>:
// CHECK-NEXT: wfe
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_wfi() {
    Cortex::asmWfi();
}

// CHECK-LABEL: <test_wfi>:
// CHECK-NEXT: wfi
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

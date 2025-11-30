#include "power_management.hpp"

extern "C" [[gnu::naked]] void test_sev() {
    ArmCortex::asmSev();
}

// CHECK-LABEL: <test_sev>:
// CHECK-NEXT: sev
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_wfe() {
    ArmCortex::asmWfe();
}

// CHECK-LABEL: <test_wfe>:
// CHECK-NEXT: wfe
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_wfi() {
    ArmCortex::asmWfi();
}

// CHECK-LABEL: <test_wfi>:
// CHECK-NEXT: wfi
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

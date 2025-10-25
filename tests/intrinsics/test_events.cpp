#include "intrinsics/events.hpp"

extern "C" [[gnu::naked]] void test_sev() {
    Cortex::asmSev();
}

// CHECK-LABEL: <test_sev>:
// CHECK-NEXT: sev
// RELEASE-CHECK-NEXT: nop
// RELWITHDEBINFO-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_wfe() {
    Cortex::asmWfe();
}

// CHECK-LABEL: <test_wfe>:
// CHECK-NEXT: wfe
// RELEASE-CHECK-NEXT: nop
// RELWITHDEBINFO-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_wfi() {
    Cortex::asmWfi();
}

// CHECK-LABEL: <test_wfi>:
// CHECK-NEXT: wfi
// RELEASE-CHECK-NEXT: nop
// RELWITHDEBINFO-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// CHECK-EMPTY:

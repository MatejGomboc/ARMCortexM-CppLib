#include "intrinsics/exceptions.hpp"

extern "C" [[gnu::naked]] void test_cpsie() {
    Cortex::asmCpsie();
}

// CHECK-LABEL: <test_cpsie>:
// CHECK-NEXT: cpsie
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_cpsid() {
    Cortex::asmCpsid();
}

// CHECK-LABEL: <test_cpsid>:
// CHECK-NEXT: cpsid
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// CHECK-EMPTY:

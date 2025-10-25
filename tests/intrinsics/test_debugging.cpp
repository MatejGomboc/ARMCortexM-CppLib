#include "intrinsics/debugging.hpp"

extern "C" [[gnu::naked]] void test_bkpt() {
    Cortex::asmBkpt(0);
}

// CHECK-LABEL: <test_bkpt>:
// CHECK-NEXT: bkpt
// RELEASE-CHECK-NEXT: bx lr
// MINSIZEREL-CHECK-NEXT: bx lr
// RELWITHDEBINFO-CHECK-NEXT: bx lr
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: bx lr
// CHECK-EMPTY:

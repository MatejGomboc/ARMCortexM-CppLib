#include "intrinsics/debugging.hpp"

extern "C" [[gnu::naked]] void test_bkpt() {
    Cortex::asmBkpt(0);
}

// CHECK-LABEL: <test_bkpt>:
// CHECK-NEXT: bkpt
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// CHECK-EMPTY:

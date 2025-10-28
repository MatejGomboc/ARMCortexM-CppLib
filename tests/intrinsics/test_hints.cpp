#include "intrinsics/hints.hpp"

extern "C" [[gnu::naked]] void test_nop() {
    Cortex::asmNop();
}

// CHECK-LABEL: <test_nop>:
// CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// CHECK-EMPTY:

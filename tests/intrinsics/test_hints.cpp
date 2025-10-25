#include "intrinsics/hints.hpp"

extern "C" void test_nop() {
    Cortex::asmNop();
}

// CHECK-LABEL: <test_nop>:
// CHECK-NEXT: nop
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

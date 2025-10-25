#include "intrinsics/hints.hpp"

extern "C" void test_hints() {
    Cortex::asmNop();
}

// CHECK-LABEL: <test_hints>:
// CHECK-NEXT: nop
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

#include "execution_hints.hpp"

extern "C" [[gnu::naked]] void test_nop() {
    Cortex::asmNop();
}

// CHECK-LABEL: <test_nop>:
// CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_yield() {
    Cortex::asmYield();
}

// CHECK-LABEL: <test_yield>:
// CHECK-NEXT: yield
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

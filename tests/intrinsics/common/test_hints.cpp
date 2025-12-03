#include "armcortex/intrinsics/hints.hpp"

extern "C" [[gnu::naked]] void test_nop() {
    ArmCortex::asmNop();
}

// CHECK-LABEL: <test_nop>:
// CHECK-NEXT: nop
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_yield() {
    ArmCortex::asmYield();
}

// CHECK-LABEL: <test_yield>:
// CHECK-NEXT: yield
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

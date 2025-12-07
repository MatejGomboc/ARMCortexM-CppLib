#include "armcortex/intrinsics/exceptions.hpp"

extern "C" [[gnu::naked]] void test_cpsie_f() {
    ArmCortex::asmCpsieF();
}

// CHECK-LABEL: <test_cpsie_f>:
// CHECK-NEXT: cpsie f
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_cpsid_f() {
    ArmCortex::asmCpsidF();
}

// CHECK-LABEL: <test_cpsid_f>:
// CHECK-NEXT: cpsid f
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

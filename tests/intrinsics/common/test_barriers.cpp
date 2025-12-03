#include "armcortex/intrinsics/barriers.hpp"

extern "C" [[gnu::naked]] void test_dsb() {
    ArmCortex::asmDsb();
}

// CHECK-LABEL: <test_dsb>:
// CHECK-NEXT: dsb sy
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_isb() {
    ArmCortex::asmIsb();
}

// CHECK-LABEL: <test_isb>:
// CHECK-NEXT: isb sy
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_dmb() {
    ArmCortex::asmDmb();
}

// CHECK-LABEL: <test_dmb>:
// CHECK-NEXT: dmb sy
// CHECK-EMPTY:

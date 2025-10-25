#include "intrinsics/byte_reversing.hpp"

extern "C" [[gnu::naked]] void test_rev() {
    Cortex::asmRev(0);
}

// CHECK-LABEL: <test_rev>:
// CHECK-NEXT: rev
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_rev16() {
    Cortex::asmRev16(0);
}

// CHECK-LABEL: <test_rev16>:
// CHECK-NEXT: rev16
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_revsh() {
    Cortex::asmRevsh(0);
}

// CHECK-LABEL: <test_revsh>:
// CHECK-NEXT: revsh
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// CHECK-EMPTY:

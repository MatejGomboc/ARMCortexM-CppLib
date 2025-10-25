#include "intrinsics/byte_reversing.hpp"

extern "C" [[gnu::naked]] void test_rev() {
    Cortex::asmRev(0);
}

// CHECK-LABEL: <test_rev>:
// CHECK-NEXT: rev
// RELEASE-CHECK-NEXT: bx lr
// MINSIZEREL-CHECK-NEXT: bx lr
// RELWITHDEBINFO-CHECK-NEXT: bx lr
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_rev16() {
    Cortex::asmRev16(0);
}

// CHECK-LABEL: <test_rev16>:
// CHECK-NEXT: rev16
// RELEASE-CHECK-NEXT: bx lr
// MINSIZEREL-CHECK-NEXT: bx lr
// RELWITHDEBINFO-CHECK-NEXT: bx lr
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_revsh() {
    Cortex::asmRevsh(0);
}

// CHECK-LABEL: <test_revsh>:
// CHECK-NEXT: revsh
// RELEASE-CHECK-NEXT: bx lr
// MINSIZEREL-CHECK-NEXT: bx lr
// RELWITHDEBINFO-CHECK-NEXT: bx lr
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: bx lr
// CHECK-EMPTY:

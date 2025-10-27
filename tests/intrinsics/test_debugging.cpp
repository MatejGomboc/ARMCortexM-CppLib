#include "intrinsics/debugging.hpp"

extern "C" [[gnu::naked]] void test_bkpt_0() {
    Cortex::asmBkpt<0>();
}

// CHECK-LABEL: <test_bkpt_0>:

// CHECK-NEXT: bkpt 0x0000

// RELEASE-CHECK-NEXT: nop
// RELWITHDEBINFO-CHECK-NEXT: nop

// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop

// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_bkpt_1() {
    Cortex::asmBkpt<1>();
}

// CHECK-LABEL: <test_bkpt_1>:

// CHECK-NEXT: bkpt 0x0001

// RELEASE-CHECK-NEXT: nop
// RELWITHDEBINFO-CHECK-NEXT: nop

// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop

// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_bkpt_8() {
    Cortex::asmBkpt<8>();
}

// CHECK-LABEL: <test_bkpt_8>:

// CHECK-NEXT: bkpt 0x0008

// RELEASE-CHECK-NEXT: nop
// RELWITHDEBINFO-CHECK-NEXT: nop

// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop

// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_bkpt_128() {
    Cortex::asmBkpt<128>();
}

// CHECK-LABEL: <test_bkpt_128>:

// CHECK-NEXT: bkpt 0x0080

// RELEASE-CHECK-NEXT: nop
// RELWITHDEBINFO-CHECK-NEXT: nop

// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop

// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_bkpt_255() {
    Cortex::asmBkpt<255>();
}

// CHECK-LABEL: <test_bkpt_255>:

// CHECK-NEXT: bkpt 0x00ff

// RELEASE-CHECK-NEXT: nop
// RELWITHDEBINFO-CHECK-NEXT: nop

// DEBUG-CHECK-NEXT: nop
// DEBUG-CHECK-NEXT: nop

// CHECK-EMPTY:

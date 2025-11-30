#include "debugging.hpp"

extern "C" [[gnu::naked]] void test_bkpt_0() {
    ArmCortex::asmBkpt<0>();
}

// CHECK-LABEL: <test_bkpt_0>:
// CHECK-NEXT: bkpt 0x0000
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_bkpt_1() {
    ArmCortex::asmBkpt<1>();
}

// CHECK-LABEL: <test_bkpt_1>:
// CHECK-NEXT: bkpt 0x0001
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_bkpt_8() {
    ArmCortex::asmBkpt<8>();
}

// CHECK-LABEL: <test_bkpt_8>:
// CHECK-NEXT: bkpt 0x0008
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_bkpt_128() {
    ArmCortex::asmBkpt<128>();
}

// CHECK-LABEL: <test_bkpt_128>:
// CHECK-NEXT: bkpt 0x0080
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_bkpt_255() {
    ArmCortex::asmBkpt<255>();
}

// CHECK-LABEL: <test_bkpt_255>:
// CHECK-NEXT: bkpt 0x00ff
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

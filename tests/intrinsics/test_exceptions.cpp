#include "intrinsics/exceptions.hpp"

extern "C" [[gnu::naked]] void test_cpsie() {
    Cortex::asmCpsie();
}

// CHECK-LABEL: <test_cpsie>:
// CHECK-NEXT: cpsie i
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_cpsid() {
    Cortex::asmCpsid();
}

// CHECK-LABEL: <test_cpsid>:
// CHECK-NEXT: cpsid i
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_svc_0() {
    Cortex::asmSvc<0>();
}

// CHECK-LABEL: <test_svc_0>:
// CHECK-NEXT: svc 0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_svc_1() {
    Cortex::asmSvc<1>();
}

// CHECK-LABEL: <test_svc_1>:
// CHECK-NEXT: svc 1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_svc_8() {
    Cortex::asmSvc<8>();
}

// CHECK-LABEL: <test_svc_8>:
// CHECK-NEXT: svc 8
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_svc_128() {
    Cortex::asmSvc<128>();
}

// CHECK-LABEL: <test_svc_128>:
// CHECK-NEXT: svc 128
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_svc_255() {
    Cortex::asmSvc<255>();
}

// CHECK-LABEL: <test_svc_255>:
// CHECK-NEXT: svc 255
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

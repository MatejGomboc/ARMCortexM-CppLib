#include "intrinsics/common/exceptions.hpp"

extern "C" [[gnu::naked]] void test_cpsie() {
    ArmCortex::asmCpsie();
}

// CHECK-LABEL: <test_cpsie>:
// CHECK-NEXT: cpsie i
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_cpsid() {
    ArmCortex::asmCpsid();
}

// CHECK-LABEL: <test_cpsid>:
// CHECK-NEXT: cpsid i
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_svc_0() {
    ArmCortex::asmSvc<0>();
}

// CHECK-LABEL: <test_svc_0>:
// CHECK-NEXT: svc 0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_svc_1() {
    ArmCortex::asmSvc<1>();
}

// CHECK-LABEL: <test_svc_1>:
// CHECK-NEXT: svc 1
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_svc_8() {
    ArmCortex::asmSvc<8>();
}

// CHECK-LABEL: <test_svc_8>:
// CHECK-NEXT: svc 8
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_svc_128() {
    ArmCortex::asmSvc<128>();
}

// CHECK-LABEL: <test_svc_128>:
// CHECK-NEXT: svc 128
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_svc_255() {
    ArmCortex::asmSvc<255>();
}

// CHECK-LABEL: <test_svc_255>:
// CHECK-NEXT: svc 255
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

#include "intrinsics/barriers.hpp"

extern "C" void test_dsb() {
    Cortex::asmDsb();
}

// CHECK-LABEL: <test_dsb>:
// CHECK-NEXT: dsb
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" void test_isb() {
    Cortex::asmIsb();
}

// CHECK-LABEL: <test_isb>:
// CHECK-NEXT: isb
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" void test_dmb() {
    Cortex::asmDmb();
}

// CHECK-LABEL: <test_dmb>:
// CHECK-NEXT: dmb
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

extern "C" void test_compiler_barrier() {
    Cortex::compilerBarrier();
}

// CHECK-LABEL: <test_compiler_barrier>:
// CHECK-NEXT: bx lr
// CHECK-EMPTY:

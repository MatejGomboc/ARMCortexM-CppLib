#include "utils.hpp"

extern "C" uint32_t test_runtime_int_ceil_div_1(uint32_t a, uint32_t b) {
    return Utils::intCeilDiv(a, b);
}

// CHECK-LABEL: <test_runtime_int_ceil_div_1>:
// CHECK-NEXT: push {r4, lr}
// CHECK-NEXT: cmp r0, #0
// CHECK-NEXT: beq.n e
// CHECK-NEXT: subs r0, #1
// CHECK-NEXT: bl 0 <__aeabi_uidiv>
// CHECK-NEXT: adds r0, #1
// CHECK-NEXT: pop {r4, pc}
// CHECK-EMPTY:

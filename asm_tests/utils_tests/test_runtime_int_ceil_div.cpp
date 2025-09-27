#include "utils.hpp"

extern "C" uint8_t test_runtime_int_ceil_div_1(uint8_t a, uint8_t b) {
    return Utils::intCeilDiv(a, b);
}

// CHECK-LABEL: <test_runtime_int_ceil_div_1>:
// CHECK-NEXT: push {r4, lr}
// CHECK-NEXT: cmp r0, #0

// DEBUG-CHECK-NEXT: beq.n 12 <test_runtime_int_ceil_div_1+0x12>
// MINSIZEREL-CHECK-NEXT: beq.n 10 <test_runtime_int_ceil_div_1+0x10>
// RELEASE-CHECK-NEXT: beq.n 10 <test_runtime_int_ceil_div_1+0x10>
// RELWITHDEBINFO-CHECK-NEXT: beq.n 10 <test_runtime_int_ceil_div_1+0x10>

// CHECK-NEXT: subs r0, #1
// CHECK-NEXT: bl 0 <__aeabi_uidiv>

// DEBUG-CHECK-NEXT: uxtb r0, r0

// CHECK-NEXT: adds r0, #1
// CHECK-NEXT: uxtb r0, r0
// CHECK-NEXT: pop {r4, pc}

// RELEASE-CHECK-NEXT: nop
// RELWITHDEBINFO-CHECK-NEXT: nop

// CHECK-EMPTY:

extern "C" uint16_t test_runtime_int_ceil_div_2(uint16_t a, uint16_t b) {
    return Utils::intCeilDiv(a, b);
}

// CHECK-LABEL: <test_runtime_int_ceil_div_2>:
// CHECK-NEXT: push {r4, lr}
// CHECK-NEXT: cmp r0, #0

// DEBUG-CHECK-NEXT: beq.n 26 <test_runtime_int_ceil_div_2+0x12>
// MINSIZEREL-CHECK-NEXT: beq.n 22 <test_runtime_int_ceil_div_2+0x10>
// RELEASE-CHECK-NEXT: beq.n 24 <test_runtime_int_ceil_div_2+0x10>
// RELWITHDEBINFO-CHECK-NEXT: beq.n 24 <test_runtime_int_ceil_div_2+0x10>

// CHECK-NEXT: subs r0, #1
// CHECK-NEXT: bl 0 <__aeabi_uidiv>

// DEBUG-CHECK-NEXT: uxth r0, r0

// CHECK-NEXT: adds r0, #1
// CHECK-NEXT: uxth r0, r0
// CHECK-NEXT: pop {r4, pc}

// RELEASE-CHECK-NEXT: nop
// RELWITHDEBINFO-CHECK-NEXT: nop

// CHECK-EMPTY:

extern "C" uint32_t test_runtime_int_ceil_div_3(uint32_t a, uint32_t b) {
    return Utils::intCeilDiv(a, b);
}

// CHECK-LABEL: <test_runtime_int_ceil_div_3>:
// CHECK-NEXT: push {r4, lr}
// CHECK-NEXT: cmp r0, #0

// DEBUG-CHECK-NEXT: beq.n 36 <test_runtime_int_ceil_div_3+0xe>
// MINSIZEREL-CHECK-NEXT: beq.n 32 <test_runtime_int_ceil_div_3+0xe>
// RELEASE-CHECK-NEXT: beq.n 36 <test_runtime_int_ceil_div_3+0xe>
// RELWITHDEBINFO-CHECK-NEXT: beq.n 36 <test_runtime_int_ceil_div_3+0xe>

// CHECK-NEXT: subs r0, #1
// CHECK-NEXT: bl 0 <__aeabi_uidiv>
// CHECK-NEXT: adds r0, #1
// CHECK-NEXT: pop {r4, pc}
// CHECK-EMPTY:

extern "C" uint64_t test_runtime_int_ceil_div_4(uint64_t a, uint64_t b) {
    return Utils::intCeilDiv(a, b);
}

// CHECK-LABEL: <test_runtime_int_ceil_div_4>:
// CHECK-NEXT: push {r4, r5, r6, lr}

// DEBUG-CHECK-NEXT: movs r4, r0
// DEBUG-CHECK-NEXT: movs r5, r1
// DEBUG-CHECK-NEXT: movs r1, r0
// DEBUG-CHECK-NEXT: orrs r1, r5
// DEBUG-CHECK-NEXT: beq.n 5a <test_runtime_int_ceil_div_4+0x22>

// MINSIZEREL-CHECK-NEXT: movs r5, r1
// MINSIZEREL-CHECK-NEXT: movs r1, r0
// MINSIZEREL-CHECK-NEXT: movs r4, r0
// MINSIZEREL-CHECK-NEXT: orrs r1, r5
// MINSIZEREL-CHECK-NEXT: beq.n 56 <test_runtime_int_ceil_div_4+0x22>

// RELEASE-CHECK-NEXT: movs r5, r1
// RELEASE-CHECK-NEXT: movs r1, r0
// RELEASE-CHECK-NEXT: movs r4, r0
// RELEASE-CHECK-NEXT: orrs r1, r5
// RELEASE-CHECK-NEXT: beq.n 5a <test_runtime_int_ceil_div_4+0x22>

// RELWITHDEBINFO-CHECK-NEXT: movs r5, r1
// RELWITHDEBINFO-CHECK-NEXT: movs r1, r0
// RELWITHDEBINFO-CHECK-NEXT: movs r4, r0
// RELWITHDEBINFO-CHECK-NEXT: orrs r1, r5
// RELWITHDEBINFO-CHECK-NEXT: beq.n 5a <test_runtime_int_ceil_div_4+0x22>

// CHECK-NEXT: movs r0, #1
// CHECK-NEXT: negs r0, r0
// CHECK-NEXT: asrs r1, r0, #31
// CHECK-NEXT: adds r0, r0, r4
// CHECK-NEXT: adcs r1, r5
// CHECK-NEXT: bl 0 <__aeabi_uldivmod>
// CHECK-NEXT: movs r4, #1
// CHECK-NEXT: movs r5, #0
// CHECK-NEXT: adds r4, r4, r0
// CHECK-NEXT: adcs r5, r1

// DEBUG-CHECK-NEXT: movs r0, r4
// DEBUG-CHECK-NEXT: movs r1, r5

// MINSIZEREL-CHECK-NEXT: movs r1, r5
// MINSIZEREL-CHECK-NEXT: movs r0, r4

// RELEASE-CHECK-NEXT: movs r1, r5
// RELEASE-CHECK-NEXT: movs r0, r4

// RELWITHDEBINFO-CHECK-NEXT: movs r1, r5
// RELWITHDEBINFO-CHECK-NEXT: movs r0, r4

// CHECK-NEXT: pop {r4, r5, r6, pc}
// CHECK-EMPTY:

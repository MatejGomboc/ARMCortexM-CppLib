#include "utils.hpp"

extern "C" unsigned long long test_const_int_ceil_div1() {
    static constexpr unsigned long long result = Utils::intCeilDiv(10ull, 3ull);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div1>:
// CHECK: movs r0, #4
// CHECK: movs r1, #0
// CHECK-NEXT: bx lr

extern "C" unsigned long test_const_int_ceil_div2() {
    static constexpr unsigned long result = Utils::intCeilDiv(10ul, 3ul);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div2>:
// CHECK: movs r0, #4
// CHECK-NEXT: bx lr

extern "C" unsigned test_const_int_ceil_div3() {
    static constexpr unsigned result = Utils::intCeilDiv(10u, 3u);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div3>:
// CHECK: movs r0, #4
// CHECK-NEXT: bx lr

////////////////////////////////////////////////////////////////////

extern "C" long long test_const_int_ceil_div4() {
    static constexpr long long result = Utils::intCeilDiv(10ll, 3ll);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div4>:
// CHECK: movs r0, #4
// CHECK: movs r1, #0
// CHECK-NEXT: bx lr

extern "C" long test_const_int_ceil_div5() {
    static constexpr long result = Utils::intCeilDiv(10l, 3l);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div5>:
// CHECK: movs r0, #4
// CHECK-NEXT: bx lr

extern "C" int test_const_int_ceil_div6() {
    static constexpr int result = Utils::intCeilDiv(10, 3);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div6>:
// CHECK: movs r0, #4
// CHECK-NEXT: bx lr

////////////////////////////////////////////////////////////////////

extern "C" long long test_const_int_ceil_div7() {
    static constexpr long long result = Utils::intCeilDiv(-10ll, -3ll);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div7>:
// CHECK: movs r0, #4
// CHECK: movs r1, #0
// CHECK-NEXT: bx lr

extern "C" long test_const_int_ceil_div8() {
    static constexpr long result = Utils::intCeilDiv(-10l, -3l);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div8>:
// CHECK: movs r0, #4
// CHECK-NEXT: bx lr

extern "C" int test_const_int_ceil_div9() {
    static constexpr int result = Utils::intCeilDiv(-10, -3);
    return result;
}

// CHECK-LABEL: <test_const_int_ceil_div9>:
// CHECK: movs r0, #4
// CHECK-NEXT: bx lr

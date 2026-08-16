#include "utils.hpp"

extern "C" uint32_t test_runtime_ceil_div1(uint32_t a, uint32_t b) {
    return Utils::intCeilDiv(a, b);
}

// CHECK-LABEL: test_runtime_ceil_div1:

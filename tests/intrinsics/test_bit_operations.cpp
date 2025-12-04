#include "armcortex/intrinsics/bit_operations.hpp"

extern "C" [[gnu::naked]] uint32_t test_clz(uint32_t value) {
    return ArmCortex::asmClz(value);
}

// CHECK-LABEL: <test_clz>:
// CHECK-NEXT: clz r0, r0
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_rbit(uint32_t value) {
    return ArmCortex::asmRbit(value);
}

// CHECK-LABEL: <test_rbit>:
// CHECK-NEXT: rbit r0, r0
// CHECK-EMPTY:

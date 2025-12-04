#include "armcortex/intrinsics/exclusive_access.hpp"

extern "C" [[gnu::naked]] uint32_t test_ldrex(volatile uint32_t* addr) {
    return ArmCortex::asmLdrex(addr);
}

// CHECK-LABEL: <test_ldrex>:
// CHECK-NEXT: ldrex r0, [r0]
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint16_t test_ldrexh(volatile uint16_t* addr) {
    return ArmCortex::asmLdrexh(addr);
}

// CHECK-LABEL: <test_ldrexh>:
// CHECK-NEXT: ldrexh r0, [r0]
// CHECK-NEXT: uxth r0, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_ldrexb(volatile uint8_t* addr) {
    return ArmCortex::asmLdrexb(addr);
}

// CHECK-LABEL: <test_ldrexb>:
// CHECK-NEXT: ldrexb r0, [r0]
// CHECK-NEXT: uxtb r0, r0
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_strex(uint32_t value, volatile uint32_t* addr) {
    return ArmCortex::asmStrex(value, addr);
}

// CHECK-LABEL: <test_strex>:
// CHECK-NEXT: strex r3, r0, [r1]
// CHECK-NEXT: mov r0, r3
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_strexh(uint16_t value, volatile uint16_t* addr) {
    return ArmCortex::asmStrexh(value, addr);
}

// CHECK-LABEL: <test_strexh>:
// CHECK-NEXT: strexh r3, r0, [r1]
// CHECK-NEXT: mov r0, r3
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_strexb(uint8_t value, volatile uint8_t* addr) {
    return ArmCortex::asmStrexb(value, addr);
}

// CHECK-LABEL: <test_strexb>:
// CHECK-NEXT: strexb r3, r0, [r1]
// CHECK-NEXT: mov r0, r3
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_clrex() {
    ArmCortex::asmClrex();
}

// CHECK-LABEL: <test_clrex>:
// CHECK-NEXT: clrex
// CHECK-EMPTY:

#include "exclusive_access.hpp"

extern "C" [[gnu::naked]] uint32_t test_ldrex(volatile uint32_t* addr) {
    return Cortex::asmLdrex(addr);
}

// CHECK-LABEL: <test_ldrex>:
// CHECK-NEXT: ldrex r0, [r0]
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint16_t test_ldrexh(volatile uint16_t* addr) {
    return Cortex::asmLdrexh(addr);
}

// CHECK-LABEL: <test_ldrexh>:
// CHECK-NEXT: ldrexh r0, [r0]
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint8_t test_ldrexb(volatile uint8_t* addr) {
    return Cortex::asmLdrexb(addr);
}

// CHECK-LABEL: <test_ldrexb>:
// CHECK-NEXT: ldrexb r0, [r0]
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_strex(uint32_t value, volatile uint32_t* addr) {
    return Cortex::asmStrex(value, addr);
}

// CHECK-LABEL: <test_strex>:
// CHECK-NEXT: strex r0, r0, [r1]
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_strexh(uint16_t value, volatile uint16_t* addr) {
    return Cortex::asmStrexh(value, addr);
}

// CHECK-LABEL: <test_strexh>:
// CHECK-NEXT: strexh r0, r0, [r1]
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] uint32_t test_strexb(uint8_t value, volatile uint8_t* addr) {
    return Cortex::asmStrexb(value, addr);
}

// CHECK-LABEL: <test_strexb>:
// CHECK-NEXT: strexb r0, r0, [r1]
// MAXSPEED-CHECK-NEXT: nop
// CHECK-EMPTY:

extern "C" [[gnu::naked]] void test_clrex() {
    Cortex::asmClrex();
}

// CHECK-LABEL: <test_clrex>:
// CHECK-NEXT: clrex
// CHECK-EMPTY:

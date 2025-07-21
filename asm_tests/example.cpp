extern "C" void example() {
    asm volatile("nop");
}

// CHECK-LABEL: <example>:
// CHECK: nop
// CHECK: bx lr

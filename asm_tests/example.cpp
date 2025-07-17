// RUN: arm-none-eabi-g++ -S %s -o - | FileCheck %s

void example() {
    // CHECK: nop
    asm volatile("nop");
}

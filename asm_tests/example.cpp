// RUN: arm-none-eabi-g++ -S %s -o %t.asm
// RUN: FileCheck %s < %t.asm

void example() {
    // CHECK: nop
    asm volatile("nop");
}

// RUN: arm-none-eabi-g++ -mcpu=cortex-m0plus -mthumb -std=c++17 -S %s -o %t.asm
// RUN: FileCheck %s < %t.asm

__attribute__((naked)) void example() {
    // CHECK: nop
    asm volatile("nop");
}

// RUN: arm-none-eabi-g++ %arch_flag% -mthumb -mfloat-abi=soft -masm-syntax-unified -std=gnu++17 %default_flags% -S %s -o %t.asm
// RUN: FileCheck %s < %t.asm

void example() {
    // CHECK: nop
    asm volatile("nop");
}

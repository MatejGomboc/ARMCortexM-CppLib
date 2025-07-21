// RUN: arm-none-eabi-g++ %arch_flag% -mthumb -mfloat-abi=soft -masm-syntax-unified -std=c++17 %default_flags% -c %s -o %t.o
// RUN: arm-none-eabi-objdump -d --no-show-raw-insn %t.o > %t.asm
// RUN: FileCheck %s --input-file %t.asm

extern "C" void example() {
    asm volatile("nop");
}

// CHECK-LABEL: <example>:
// CHECK: nop
// CHECK: bx lr

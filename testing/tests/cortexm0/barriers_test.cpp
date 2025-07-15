// REQUIRES: cortex-m0
// RUN: %cc% %ccflags% %ccout% %T/%basename_t.o %s; objdump --mcpu=%mcpu% -d %T/%basename_t.o | FileCheck --allow-unused-prefixes --check-prefixes %prefixes% %s

#include "cortexm0/barriers.hpp"

void test_InstrSyncBarrier() {
    // CHECK-LABEL: <{{.*test_InstrSyncBarrier.*}}>:
    // CHECK: isb
    InstrSyncBarrier();
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_DataSyncBarrier() {
    // CHECK-LABEL: <{{.*test_DataSyncBarrier.*}}>:
    // CHECK: dsb
    DataSyncBarrier();
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_DataMemBarrier() {
    // CHECK-LABEL: <{{.*test_DataMemBarrier.*}}>:
    // CHECK: dmb
    DataMemBarrier();
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_Nop() {
    // CHECK-LABEL: <{{.*test_Nop.*}}>:
    // CHECK: nop
    Nop();
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

void test_barrier_sequence() {
    // CHECK-LABEL: <{{.*test_barrier_sequence.*}}>:
    // Test a typical barrier sequence
    DataMemBarrier();   // DMB
    // CHECK: dmb
    DataSyncBarrier();  // DSB  
    // CHECK: dsb
    InstrSyncBarrier(); // ISB
    // CHECK: isb
    // CHECK: {{(bx lr)|(pop {.*pc})}}
}

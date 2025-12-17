add_asm_test(test_exceptions)

if(ARM_CORTEX_M_ARCH STREQUAL "M3")
    add_asm_test(test_exceptions_v7m)
endif()

*** Settings ***
Library           Process
Library           OperatingSystem
Library           String
Suite Setup       Setup
Suite Teardown    Teardown

*** Variables ***
${RENODE}         renode
${TEST_DIR}       ${CURDIR}/..
${BUILD_DIR}      ${TEST_DIR}/build
${RENODE_DIR}     ${TEST_DIR}/renode
${TIMEOUT}        30s

*** Keywords ***
Setup
    [Documentation]    Build the test application
    ${result}=    Run Process    cmake    -B    ${BUILD_DIR}    -S    ${TEST_DIR}    
    ...    -DCMAKE_TOOLCHAIN_FILE\=${TEST_DIR}/../../arm_none_eabi_gcc.cmake
    ...    cwd=${TEST_DIR}
    Should Be Equal As Integers    ${result.rc}    0    CMake configuration failed
    
    ${result}=    Run Process    cmake    --build    ${BUILD_DIR}
    ...    cwd=${TEST_DIR}
    Should Be Equal As Integers    ${result.rc}    0    Build failed
    
    File Should Exist    ${BUILD_DIR}/m0plus_tests

Teardown
    [Documentation]    Clean up test artifacts
    Remove File    ${RENODE_DIR}/test_output.txt
    Remove File    ${RENODE_DIR}/renode.log

Run Renode Test
    [Arguments]    ${test_script}
    [Documentation]    Run a Renode test script
    ${result}=    Run Process    ${RENODE}    --disable-xwt    --console    --execute\=${RENODE_DIR}/${test_script}
    ...    cwd=${RENODE_DIR}    timeout=${TIMEOUT}
    RETURN    ${result}

*** Test Cases ***
Cortex-M0+ Library Tests
    [Documentation]    Run all Cortex-M0+ library tests in Renode
    ${result}=    Run Renode Test    test_runner.resc
    
    # Check that tests ran successfully
    Should Be Equal As Integers    ${result.rc}    0    Tests failed or timed out
    
    # Verify test output
    ${output}=    Get File    ${RENODE_DIR}/test_output.txt
    Should Contain    ${output}    === ARM Cortex-M0+ Library Tests ===
    Should Contain    ${output}    [TEST] NVIC Functions
    Should Contain    ${output}    [TEST] SCB Functions
    Should Contain    ${output}    [TEST] SysTick Functions
    Should Contain    ${output}    [TEST] MPU Functions
    Should Contain    ${output}    [TEST] Special Registers
    Should Contain    ${output}    === Test Summary ===
    
    # Check for any failures
    Should Not Contain    ${output}    [FAIL]
    
    Log    Test output:\n${output}

NVIC Interrupt Controller Tests
    [Documentation]    Verify NVIC functionality
    ${result}=    Run Renode Test    test_runner.resc
    ${output}=    Get File    ${RENODE_DIR}/test_output.txt
    
    # Check NVIC specific tests
    Should Contain    ${output}    [PASS] IRQ 0 should be disabled
    Should Contain    ${output}    [PASS] IRQ 0 should be enabled
    Should Contain    ${output}    [PASS] IRQ 5 should be pending
    Should Contain    ${output}    [PASS] IRQ 10 priority should be

SCB System Control Tests
    [Documentation]    Verify SCB functionality
    ${result}=    Run Renode Test    test_runner.resc
    ${output}=    Get File    ${RENODE_DIR}/test_output.txt
    
    # Check SCB specific tests
    Should Contain    ${output}    CPUID: 0x
    Should Contain    ${output}    [PASS] CPUID Implementer should be ARM
    Should Contain    ${output}    [PASS] CPUID Architecture should be ARMv6-M
    Should Contain    ${output}    [PASS] CPUID PartNo should be Cortex-M0+

SysTick Timer Tests
    [Documentation]    Verify SysTick functionality
    ${result}=    Run Renode Test    test_runner.resc
    ${output}=    Get File    ${RENODE_DIR}/test_output.txt
    
    # Check SysTick specific tests
    Should Contain    ${output}    [PASS] SysTick should be initially disabled
    Should Contain    ${output}    [PASS] SysTick reload value should be
    Should Contain    ${output}    [PASS] SysTick should have generated interrupts
    Should Contain    ${output}    SysTick interrupts received:

MPU Memory Protection Tests
    [Documentation]    Verify MPU functionality if present
    ${result}=    Run Renode Test    test_runner.resc
    ${output}=    Get File    ${RENODE_DIR}/test_output.txt
    
    # Check MPU tests - might not be present in all implementations
    Should Contain    ${output}    MPU regions available:
    ${mpu_present}=    Run Keyword And Return Status    Should Not Contain    ${output}    MPU not present
    
    Run Keyword If    ${mpu_present}
    ...    Should Contain    ${output}    [PASS] MPU should be disabled

Special Registers Tests
    [Documentation]    Verify special register access
    ${result}=    Run Renode Test    test_runner.resc
    ${output}=    Get File    ${RENODE_DIR}/test_output.txt
    
    # Check special register tests
    Should Contain    ${output}    [PASS] PRIMASK should be
    Should Contain    ${output}    CONTROL register:
    Should Contain    ${output}    MSP:
    Should Contain    ${output}    PSP:
    Should Contain    ${output}    APSR:
    Should Contain    ${output}    Instruction tests completed

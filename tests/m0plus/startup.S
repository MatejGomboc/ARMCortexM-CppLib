/* Startup code for Cortex-M0+ */

.syntax unified
.cpu cortex-m0plus
.thumb

.global g_pfnVectors
.global Default_Handler

/* Start address for initialization values */
.word _sidata
.word _sdata
.word _edata
.word _sbss
.word _ebss
.word _estack

/**
 * @brief  Reset handler
 */
.section .text.Reset_Handler
.weak Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    /* Set stack pointer */
    ldr r0, =_estack
    mov sp, r0

    /* Copy data segment from flash to RAM */
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata
    movs r3, #0
    b LoopCopyDataInit

CopyDataInit:
    ldr r4, [r2, r3]
    str r4, [r0, r3]
    adds r3, r3, #4

LoopCopyDataInit:
    adds r4, r0, r3
    cmp r4, r1
    bcc CopyDataInit

    /* Zero fill the bss segment */
    ldr r2, =_sbss
    ldr r4, =_ebss
    movs r3, #0
    b LoopFillZerobss

FillZerobss:
    str r3, [r2]
    adds r2, r2, #4

LoopFillZerobss:
    cmp r2, r4
    bcc FillZerobss

    /* Call main() */
    bl main
    
    /* Infinite loop if main returns */
    b .

.size Reset_Handler, .-Reset_Handler

/**
 * @brief Default interrupt handler
 */
.section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
    b Infinite_Loop
.size Default_Handler, .-Default_Handler

/**
 * @brief Vector table
 */
.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object
.size g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
    .word _estack
    .word Reset_Handler
    .word NMI_Handler
    .word HardFault_Handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word SVC_Handler
    .word 0
    .word 0
    .word PendSV_Handler
    .word SysTick_Handler
    
    /* External interrupts */
    .rept 32
    .word Default_Handler
    .endr

/* Weak aliases for interrupt handlers */
.weak NMI_Handler
.thumb_set NMI_Handler,Default_Handler

.weak HardFault_Handler
.thumb_set HardFault_Handler,Default_Handler

.weak SVC_Handler
.thumb_set SVC_Handler,Default_Handler

.weak PendSV_Handler
.thumb_set PendSV_Handler,Default_Handler

.weak SysTick_Handler
.thumb_set SysTick_Handler,Default_Handler

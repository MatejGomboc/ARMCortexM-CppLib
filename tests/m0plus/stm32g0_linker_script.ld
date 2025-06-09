/* Linker script for STM32G0 (Cortex-M0+) */
/* Based on STM32G071 with 128KB Flash and 36KB RAM */

MEMORY
{
  /* STM32G0 Flash starts at 0x08000000 */
  /* Note: Flash is also aliased at 0x00000000 for boot */
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
  
  /* SRAM */
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 36K
}

/* Stack at end of RAM */
_estack = ORIGIN(RAM) + LENGTH(RAM);
_Min_Stack_Size = 0x400;  /* 1KB stack */

SECTIONS
{
  /* Interrupt vector table - must be at start of Flash */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } > FLASH

  /* Program code */
  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)

    KEEP(*(.init))
    KEEP(*(.fini))

    . = ALIGN(4);
    _etext = .;
  } > FLASH

  /* Read-only data */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
  } > FLASH

  /* ARM exception handling */
  .ARM.extab : 
  { 
    *(.ARM.extab* .gnu.linkonce.armextab.*) 
  } > FLASH
  
  .ARM : 
  {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } > FLASH

  /* Used by startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } > RAM AT> FLASH

  /* Uninitialized data */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
  } > RAM

  /* User heap */
  ._user_heap :
  {
    . = ALIGN(8);
    PROVIDE(end = .);
    PROVIDE(_end = .);
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } > RAM
}

/* STM32G0 specific: define memory regions for peripherals */
PROVIDE(NVIC_BASE = 0xE000E000);
PROVIDE(SCB_BASE = 0xE000ED00);
PROVIDE(SYSTICK_BASE = 0xE000E010);

/* */

/* Custom Linker Script for Cortex-M4 processor - Specifiaclly tailored for STM32 Nucleo-F411RE */

/* ENTRY => This linker script command sets the Entry point address information in final elf/hex */

/* MEMORY => This linker script command allows to describe different memory regions present in the target. Linker uses this information to assign addresses to merged sections. Information provided here helps linker to keep track of code and data memory consumed and if necessary throw errors if something does not fit the available size */

/* SECTIONS => This linker script command creates different output sections in the final ELF/HEX. Instructs linker to merge input sections to form output sections. Also, the order of generated output sections in the output file is managed by this command. Also, places sections in desired memory region. */

/* Location counter => The location counter is denoted by "." The linker automatically updates this symbol with location/address information. This can be used to track and define boundaries of various sections. This is also settable/definable with specific values. This appears only inside the SECTIONS command. It is also incremented by the size of output section. */

/* Location counter always tracks the VMA in which it is used and never the LMA */

/* ALIGN => Aligns the location counter for word(4)/half-word(2)/byte(1) alignment. Used mainly during end of sections where linker does not automatically make padding to maintatin alignment. */

/* LOADADDR(section) Return the absolute load address of the named section. This is normally the same as ADDR, but it may be different if the AT keyword is used in the section definition */

/* (.init) and (.fini) sections are observed to have same VMA and LMA at the objdump -h Binary.elf and hence could be cateogarized as code sections. Thereby, including them under the .text section */

/* _etext symbol declaration can not be placed at the end of .text section as the *(.eh_frame) and *(.ARM.exidx) sections are also placed before data location in the FLASH/.text */

/* Other comments - .data : AT(ADDR(.text) + SIZEOF(.text)) is also acceptable */

ENTRY(Reset_Handler)

MEMORY
{

    FLASH(rx): ORIGIN =0x08000000,LENGTH =512K

    RAM(rwx): ORIGIN =0x20000000,LENGTH =128K

}

__max_heap_size = 0x400;    /* Symbol declaration, will be exported to be used in Reset_Handler */

__max_stack_size = 0x200;   /* Symbol declaration, will be exported to be used in Reset_Handler */

/*

* Sections definitions:

* .text         - Machine instructions.

* .data         - Initialized data defined in the program.

* .bss          - Block Start by Symbol - un-initialized global and static variables (to be initialized to 0 before starting main).

* .stack        - Contains the pointer to the stack end at the right place.

*/

SECTIONS
{

/* This section includes .text section of all input files */

.text :
{

 *(.InterruptVectors)   /* Merge all Interrupt Vector section from all input files */

 *(.text)   /* Merge all .text section from all input files */
 
 *(.text.*) /* Merge .text section from all newlib nano library files*/

 *(.init)   /* newlib nano introduces these sections*/
 
 *(.fini)   /* newlib nano introduces these sections*/
 
 *(.rodata) /* Merge all .rodata section from all input files */

 *(.rodata.*) /* Merge .rodata section from all newlib nano library files*/
 
 . = ALIGN(4); /* Previous location counter address incrmented to next word/half-word/byte aligned address */
 
 /* _etext = .; *//* Not acceptable ( See comments above) */

}>FLASH /* >(vma) AT> (lma) */ /* The Virtual Memory Address and Load Memory Address are the same for .text section */

/* _etext = (ADDR(.text) + SIZEOF(.text) + SIZEOF(.eh_frame) +SIZEOF(.ARM.exidx) ); */ /* Symbol declaration, will be exported to be used in Reset_Handler */ /* _etext is now updated with the load address of data section */ /* Acceptable */

/* _etext = LOADADDR(.data);    */ /* Symbol declaration, will be exported to be used in Reset_Handler */ /* _etext is now updated with the load address of data section */ /* Acceptable */

.data :
{

 _etext = LOADADDR(.data);  /* Symbol declaration, will be exported to be used in Reset_Handler */ /* _etext is now updated with the load address of data section */ /* Acceptable */

 _sdata = .;    /* Symbol declaration, will be exported to be used in Reset_Handler */

 *(.data)   /* Merge all data section from all input files */

 *(.data.*) /* Merge .data section from all newlib nano library files*/

 . = ALIGN(4); /* Previous location counter address incrmented to next word/half-word/byte aligned address */

 _edata = .;    /* Symbol declaration, will be exported to be used in Reset_Handler */

}>RAM AT> FLASH /* >(vma) AT> (lma) */ /* The Virtual Memory Address and Load Memory Address are different for .data section */

.bss :
{

 _sbss = .; /* Symbol declaration, will be exported to be used in Reset_Handler */

 __bss_start__ = _sbss; /* Symbol declaration, will be exported to be used in Syscalls file */

 *(.bss)    /* Merge all .bss section from all input files */

 *(.bss.*) /* Merge .bss section from all newlib nano library files*/

 . = ALIGN(4); /* Previous location counter address incrmented to next word/half-word/byte aligned address */

 *(COMMON)  /* Merge all COMMON section from all input files */
 
 _ebss = .; /* Symbol declaration, will be exported to be used in Reset_Handler */

 __bss_end__ = _ebss;   /* Symbol declaration, will be exported to be used in Syscalls file*/
 
  . = ALIGN(4); /* Previous location counter address incrmented to next word/half-word/byte aligned address */

 end = .; /* Symbol declaration, will be exported to be used in Syscalls file, specifically to _sbrk function. This indicates start of heap */

 __end__ = end; /* Symbol declaration, will be exported to be used in rdimon library to use semihosting*/

}>RAM /* >(vma) AT> (lma) */ /* The Virtual Memory Address and Load Memory Address are same for .bss section */

}
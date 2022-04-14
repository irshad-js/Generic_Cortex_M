#include <stdio.h>

#include <stdint.h>

const int TempVariable = 0xAABBCCDD;    // Dummy data for rodata section

int TempVariable2 = 0xFFAABBCC; // Dummy data for data section

int TempVariable3 = 0; // Dummy data for bss section

void HardFault_Handler_C(uint32_t * Frame);

void SVC_Handler_C(uint32_t * Frame);

void MemManage_Handler_C( uint32_t* Frame);

void BusFault_Handler_C( uint32_t* Frame);

void UsageFault_Handler_C( uint32_t* Frame);

extern void initialise_monitor_handles(void);

int main(void)
{
    
    initialise_monitor_handles();

    printf("SWV trace started\n");

    // Enable BusFault, MemFault and Usage Fault exception triggers from
    // System Handler Control and State Register located at 0xE000ED24

    uint32_t * SHCSR = (uint32_t*)0xE000ED24;

    // ( 1 << 16)  //mem manage // ( 1 << 17) //bus fault //( 1 << 18) //usage fault

    *SHCSR |= ( (1<<16) | (1<<17) | (1<<18));

    // Trap divide by zero by configuring the Configuration and Control Register

    uint32_t * CCR = (uint32_t*)0xE000ED14;

    *CCR |= (1<<4);

    // trigger divide by zero fault

    //volatile char temp = 15/0;

    // Trigger SVC instruction

    __asm volatile ("SVC #25");

    for(;;);

}

void HardFault_Handler_C(uint32_t * Frame)
{

    printf("in HardFault handler\n");

    volatile uint32_t* StackFrame = Frame;

    // Reason for the Fault handler exception raise is extraced from BusFault Status Register

    volatile uint32_t * HFSR  = (uint32_t*)0xE000ED2C;

    volatile uint32_t Reason = *HFSR;

    switch(Reason){

    case 2: break; // Indicates a BusFault on a vector table read during exception processing

    case 0x40000000: break; // Indicates a forced hard fault

    }

    printf("Value of R0 = %lx\n", StackFrame[0]);

    printf("Value of R1 = %lx\n", StackFrame[1]);

    printf("Value of R2 = %lx\n", StackFrame[2]);

    printf("Value of R3 = %lx\n", StackFrame[3]);

    printf("Value of R12 = %lx\n", StackFrame[4]);

    printf("Value of LR = %lx\n", StackFrame[5]);

    printf("Value of PC = %lx\n", StackFrame[6]);

    printf("Value of XPSR = %lx\n", StackFrame[7]);

    while(1);

}


__attribute__ ((naked)) void HardFault_Handler(void)
{
    //1 . get the value of the MSP

    __asm("MRS R0,MSP");

    __asm("B HardFault_Handler_C");

}

void SVC_Handler_C(uint32_t * Frame)
{

    printf("in SVC handler\n");

    uint32_t * StackFrame = Frame;

    uint8_t *ReturnAddress = (uint8_t*)StackFrame[6];

    //2. decrement the return address by 2 to point to
    //opcode of the SVC instruction in the program memory

    ReturnAddress -= 2;

    //3. extract the SVC number (LSByte of the opcode)

    uint8_t svc_number = *ReturnAddress;

    printf("Svc number is : %d\n",svc_number);

    while(1);

}


__attribute__ ((naked)) void SVC_Handler(void)
{
    //1 . get the value of the MSP

    __asm("MRS R0,MSP");

    __asm("B SVC_Handler_C");

}

void MemManage_Handler_C( uint32_t* Frame){

    volatile uint32_t* StackFrame = Frame;

    printf("MemManage Handler triggered");

    // Reason for the Fault handler exception raise is extraced from BusFault Status Register

    volatile uint16_t * MMFSR  = (uint16_t*)0xE000ED28;

    volatile uint16_t Reason = *MMFSR;

    switch(Reason){

    case 1: break; // Instruction access violation flag:

    case 2: break; // Data access violation flag:

    case 8: break; // MemManage fault on unstacking for a return from exception:

    case 16:break; // MemManage fault on stacking for exception entry:

    case 128: break; // MemManage Fault Address Register (MMFAR) valid flag:

    }

    printf("Value of R0 = %lx\n", StackFrame[0]);

    printf("Value of R1 = %lx\n", StackFrame[1]);

    printf("Value of R2 = %lx\n", StackFrame[2]);

    printf("Value of R3 = %lx\n", StackFrame[3]);

    printf("Value of R12 = %lx\n", StackFrame[4]);

    printf("Value of LR = %lx\n", StackFrame[5]);

    printf("Value of PC = %lx\n", StackFrame[6]);

    printf("Value of XPSR = %lx\n", StackFrame[7]);

    while(1);

}

__attribute((naked)) void MemManage_Handler (){

    // attribute naked used to prevent compiler from utilizing prologue and epilogue sequences
    // that alter stack frame

    __asm("MRS R0,MSP");

    __asm("B MemManage_Handler_C");

}


void BusFault_Handler_C( uint32_t* Frame){

    volatile uint32_t* StackFrame = Frame;

    printf("BusFault Handler triggered");

    // Reason for the Fault handler exception raise is extraced from BusFault Status Register

    volatile uint16_t * BFSR = (uint16_t*)0xE000ED29;

    volatile uint16_t Reason = *BFSR;

    switch(Reason){

    case 1: break; // Instruction bus error

    case 2: break; // Precise data bus error

    case 4: break; // Imprecise data bus error

    case 8: break; // BusFault on unstacking for a return from exception

    case 16:break; // BusFault on stacking for exception entry

    case 128: break; // BusFault Address Register (BFAR) valid flag

    }

    printf("Value of R0 = %lx\n", StackFrame[0]);

    printf("Value of R1 = %lx\n", StackFrame[1]);

    printf("Value of R2 = %lx\n", StackFrame[2]);

    printf("Value of R3 = %lx\n", StackFrame[3]);

    printf("Value of R12 = %lx\n", StackFrame[4]);

    printf("Value of LR = %lx\n", StackFrame[5]);

    printf("Value of PC = %lx\n", StackFrame[6]);

    printf("Value of XPSR = %lx\n", StackFrame[7]);

    while(1);

}

__attribute((naked)) void BusFault_Handler (){

    // attribute naked used to prevent compiler from utilizing prologue and epilogue sequences
    // that alter stack frame

    __asm("MRS R0,MSP");

    __asm("B BusFault_Handler_C");

}

void UsageFault_Handler_C( uint32_t* Frame){

    volatile uint32_t* StackFrame = Frame;

    printf("Usage Fault handler triggered");

    // Reason for the Fault handler exception raise is extraced from UsageFault Status Register

    volatile uint16_t * UFSR = (uint16_t*)0xE000ED2A;

    volatile uint16_t Reason = *UFSR;

    switch(Reason){

    case 1: break; // processor has attempted to execute an undefined instruction.

    case 2: break; // processor has attempted to execute an instruction that makes illegal use of the EPSR.

    case 4: break; // Invalid PC load UsageFault, caused by an invalid PC load by EXC_RETURN:

    case 8: break; // No coprocessor UsageFault. The processor does not support coprocessor instructions:

    case 256: break; // Unaligned access detected // Try remedial measures

    case 512: break; // Divide by zero trapped

    }

    printf("Value of R0 = %lx\n", StackFrame[0]);

    printf("Value of R1 = %lx\n", StackFrame[1]);

    printf("Value of R2 = %lx\n", StackFrame[2]);

    printf("Value of R3 = %lx\n", StackFrame[3]);

    printf("Value of R12 = %lx\n", StackFrame[4]);

    printf("Value of LR = %lx\n", StackFrame[5]);

    printf("Value of PC = %lx\n", StackFrame[6]);

    printf("Value of XPSR = %lx\n", StackFrame[7]);

    while(1);

}

__attribute((naked)) void UsageFault_Handler (){

    // attribute naked used to prevent compiler from utilizing prologue and epilogue sequences
    // that alter stack frame

    __asm("MRS R0,MSP");

    __asm("B UsageFault_Handler_C");

}
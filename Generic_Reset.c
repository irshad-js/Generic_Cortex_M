/* # Experimenatl startup file written in C for Cortex M4 processors - Specifically tailored for STM32 Nucleo F411RE board */

/* # Non traditional methods of Stack placement at Begining of RAM could be explored later as well, In that case STACK_START should become SRAM_START+Desired_STACK_SIZE */

/* # Implement Reset handler in C as well as Assembly for reference */

/* # Step 1 => Create function prototypes for available and declared intrrupts.*/

/* # Step 2 => Create a vector table as a struct that holds the necessary addresses. Also use compiler attribute to instruct the struct to be placed in a user defined section instead of .data or .text section */

/* # Attribute Alias replaces the address of the function with the address of the alias. */  

/* # Attribute weak allows the user to override the function declaration/definition outside the scope. */

#include <stdint.h>

#define SRAM_Actual_Size_KB 128

#define SRAM_START 0x20000000U

#define SRAM_SIZE (SRAM_Actual_Size_KB * 1024)

#define SRAM_END SRAM_START+SRAM_SIZE

#define STACK_START SRAM_END

extern uint32_t _etext; /* End of text region. Exported by linker script */

extern uint32_t _sdata; /* Start of data region. Exported by linker script */

extern uint32_t _edata; /* End of data region. Exported by linker script */

extern uint32_t _sbss;  /* Start of bss region. Exported by linker script */

extern uint32_t _ebss;  /* End of bss region. Exported by linker script */

int main(void); /* Main function prototype declaration */

void __libc_init_array(void);   /* Newlib nano initialization prototype declaration */

void Reset_Handler(void);

void Default_Handler(void);

void NMI_Handler(void) __attribute__((weak,alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak,alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak,alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak,alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak,alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak,alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak,alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak,alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak,alias("Default_Handler")));
void WWDG_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void PVD_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void TAMP_STAMP_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void RTC_WKUP_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void FLASH_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void RCC_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void EXTI0_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void EXTI1_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void EXTI2_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void EXTI3_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void EXTI4_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA1_Stream0_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA1_Stream1_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA1_Stream2_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA1_Stream3_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA1_Stream4_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA1_Stream5_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA1_Stream6_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void ADC_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void EXTI9_5_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void TIM1_CC_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void TIM2_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void TIM3_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void TIM4_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void I2C1_EV_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void I2C1_ER_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void I2C2_EV_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void I2C2_ER_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void SPI2_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void USART1_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void USART2_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void EXTI15_10_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void RTC_Alarm_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void OTG_FS_WKUP_IRQHandler (void) __attribute__((weak,alias("Default_Handler")));
void DMA1_Stream7_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void SDIO_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void TIM5_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void SPI3_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA2_Stream0_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA2_Stream1_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA2_Stream2_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA2_Stream3_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA2_Stream4_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void OTG_FS_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA2_Stream5_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA2_Stream6_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void DMA2_Stream7_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void USART6_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void I2C3_EV_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void I2C3_ER_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void FPU_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void SPI4_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));
void SPI5_IRQHandler(void) __attribute__((weak,alias("Default_Handler")));

void Default_Handler(void){

}

void Reset_Handler(void){

    /* Objective 1 => Copy .data section to RAM */

    /* Extract the addresses of the symbols and work on them instead of treating them like C variables */

    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;  /* End of data - Start of data reveals data section size */

    uint8_t * Destination = (uint8_t*)&_sdata;  /* RAM */

    uint8_t * Source = (uint8_t*)&_etext;   /* FLASH */

    for(uint32_t TempValue=0; TempValue<size;TempValue++){

    *Destination++ = *Source++;

    }

    /* Objective 2 => Initialize the .bss section to zero in RAM */

    size = (uint32_t)&_ebss -(uint32_t) &_sbss; /* End of bss - Start of bss reveals bss section size */

    Destination = (uint8_t*)&_sbss; /* RAM */

    for(uint32_t TempValue=0; TempValue<size;TempValue++){

    *Destination++ = 0;

    }
    
    __libc_init_array();    /* Newlib nano initialization routine - Necessary when the library is utilized */ /* Run constructors / initializers */

    main(); /* Main function called after startup routine */


}

uint32_t VectorTable[] __attribute__((section(".InterruptVectors"))) ={

  STACK_START,
  (uint32_t)&Reset_Handler,
  (uint32_t)&NMI_Handler,
  (uint32_t)&HardFault_Handler,
  (uint32_t)&MemManage_Handler,
  (uint32_t)&BusFault_Handler,
  (uint32_t)&UsageFault_Handler,
  0,
  0,
  0,
  0,
  (uint32_t)&SVC_Handler,
  (uint32_t)&DebugMon_Handler,
  0,
  (uint32_t)&PendSV_Handler,
  (uint32_t)&SysTick_Handler,
  (uint32_t)&WWDG_IRQHandler,                       
  (uint32_t)&PVD_IRQHandler,                        
  (uint32_t)&TAMP_STAMP_IRQHandler,                 
  (uint32_t)&RTC_WKUP_IRQHandler,                   
  (uint32_t)&FLASH_IRQHandler,                      
  (uint32_t)&RCC_IRQHandler,                        
  (uint32_t)&EXTI0_IRQHandler,                      
  (uint32_t)&EXTI1_IRQHandler,                      
  (uint32_t)&EXTI2_IRQHandler,                      
  (uint32_t)&EXTI3_IRQHandler,                      
  (uint32_t)&EXTI4_IRQHandler,                      
  (uint32_t)&DMA1_Stream0_IRQHandler,               
  (uint32_t)&DMA1_Stream1_IRQHandler,               
  (uint32_t)&DMA1_Stream2_IRQHandler,               
  (uint32_t)&DMA1_Stream3_IRQHandler,               
  (uint32_t)&DMA1_Stream4_IRQHandler,               
  (uint32_t)&DMA1_Stream5_IRQHandler,               
  (uint32_t)&DMA1_Stream6_IRQHandler,               
  (uint32_t)&ADC_IRQHandler,                        
  0,                                        
  0,                                        
  0,                                        
  0,                                        
  (uint32_t)&EXTI9_5_IRQHandler,                    
  (uint32_t)&TIM1_BRK_TIM9_IRQHandler,              
  (uint32_t)&TIM1_UP_TIM10_IRQHandler,              
  (uint32_t)&TIM1_TRG_COM_TIM11_IRQHandler,         
  (uint32_t)&TIM1_CC_IRQHandler,                    
  (uint32_t)&TIM2_IRQHandler,                       
  (uint32_t)&TIM3_IRQHandler,                       
  (uint32_t)&TIM4_IRQHandler,                       
  (uint32_t)&I2C1_EV_IRQHandler,                    
  (uint32_t)&I2C1_ER_IRQHandler,                    
  (uint32_t)&I2C2_EV_IRQHandler,                    
  (uint32_t)&I2C2_ER_IRQHandler,                    
  (uint32_t)&SPI1_IRQHandler,                       
  (uint32_t)&SPI2_IRQHandler,                       
  (uint32_t)&USART1_IRQHandler,                     
  (uint32_t)&USART2_IRQHandler,                     
  0,                                        
  (uint32_t)&EXTI15_10_IRQHandler,                  
  (uint32_t)&RTC_Alarm_IRQHandler,                  
  (uint32_t)&OTG_FS_WKUP_IRQHandler,                
  0,                                        
  0,                                        
  0,                                        
  0,                                        
  (uint32_t)&DMA1_Stream7_IRQHandler,               
  0,                                        
  (uint32_t)&SDIO_IRQHandler,                       
  (uint32_t)&TIM5_IRQHandler,                       
  (uint32_t)&SPI3_IRQHandler,                       
  0,                                        
  0,                                        
  0,                                        
  0,                                        
  (uint32_t)&DMA2_Stream0_IRQHandler,               
  (uint32_t)&DMA2_Stream1_IRQHandler,               
  (uint32_t)&DMA2_Stream2_IRQHandler,               
  (uint32_t)&DMA2_Stream3_IRQHandler,               
  (uint32_t)&DMA2_Stream4_IRQHandler,               
  0,                                        
  0,                                        
  0,                                        
  0,                                        
  0,                                        
  0,                                        
  (uint32_t)&OTG_FS_IRQHandler,                     
  (uint32_t)&DMA2_Stream5_IRQHandler,               
  (uint32_t)&DMA2_Stream6_IRQHandler,               
  (uint32_t)&DMA2_Stream7_IRQHandler,               
  (uint32_t)&USART6_IRQHandler,                     
  (uint32_t)&I2C3_EV_IRQHandler,                    
  (uint32_t)&I2C3_ER_IRQHandler,                    
  0,                                        
  0,                                        
  0,                                        
  0,                                        
  0,                                        
  0,                                        
  0,                                        
  (uint32_t)&FPU_IRQHandler,                        
  0,                                        
  0,                                        
  (uint32_t)&SPI4_IRQHandler,                       
  (uint32_t)&SPI5_IRQHandler,                       
};
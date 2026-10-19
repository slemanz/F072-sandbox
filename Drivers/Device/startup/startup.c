#include <stdint.h>

#define SRAM_START      0x20000000U
#define SRAM_SIZE       (16 * 1024) // 16K bytes
#define SRAM_END        ((SRAM_START) + (SRAM_SIZE))

#define STACK_START     (SRAM_END)

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;

extern uint32_t _sbss;
extern uint32_t _ebss;


/* Prototype of main*/
int main(void);

void __libc_init_array(void);



/* Functions prototypes of STM32F072 system exceptions and IRQ handlers */
void Reset_Handler(void);


void NMI_Handler                     (void) __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler               (void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler                     (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler                  (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void WWDG_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_VDDIO2_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void RTC_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void RCC_CRS_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_1_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_3_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_15_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void TSC_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler        (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel2_3_IRQHandler      (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Channel4_5_6_7_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void ADC1_COMP_IRQHandler            (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler  (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM3_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM7_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM14_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM15_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM16_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM17_IRQHandler                (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C1_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void I2C2_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler                 (void) __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler               (void) __attribute__ ((weak, alias("Default_Handler")));
void USART3_4_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void CEC_CAN_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void USB_IRQHandler                  (void) __attribute__ ((weak, alias("Default_Handler")));


__attribute__((section(".isr_vector")))
uint32_t vectors[]  = {
    STACK_START,
    (uint32_t)Reset_Handler,
    (uint32_t)NMI_Handler,
    (uint32_t)HardFault_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)SVC_Handler,
    0,
    0,
    (uint32_t)PendSV_Handler,
    (uint32_t)SysTick_Handler,
    (uint32_t)WWDG_IRQHandler,
    (uint32_t)PVD_VDDIO2_IRQHandler,
    (uint32_t)RTC_IRQHandler,
    (uint32_t)FLASH_IRQHandler,
    (uint32_t)RCC_CRS_IRQHandler,
    (uint32_t)EXTI0_1_IRQHandler,
    (uint32_t)EXTI2_3_IRQHandler,
    (uint32_t)EXTI4_15_IRQHandler,
    (uint32_t)TSC_IRQHandler,
    (uint32_t)DMA1_Channel1_IRQHandler,
    (uint32_t)DMA1_Channel2_3_IRQHandler,
    (uint32_t)DMA1_Channel4_5_6_7_IRQHandler,
    (uint32_t)ADC1_COMP_IRQHandler,
    (uint32_t)TIM1_BRK_UP_TRG_COM_IRQHandler,
    (uint32_t)TIM1_CC_IRQHandler,
    (uint32_t)TIM2_IRQHandler,
    (uint32_t)TIM3_IRQHandler,
    (uint32_t)TIM6_DAC_IRQHandler,
    (uint32_t)TIM7_IRQHandler,
    (uint32_t)TIM14_IRQHandler,
    (uint32_t)TIM15_IRQHandler,
    (uint32_t)TIM16_IRQHandler,
    (uint32_t)TIM17_IRQHandler,
    (uint32_t)I2C1_IRQHandler,
    (uint32_t)I2C2_IRQHandler,
    (uint32_t)SPI1_IRQHandler,
    (uint32_t)SPI2_IRQHandler,
    (uint32_t)USART1_IRQHandler,
    (uint32_t)USART2_IRQHandler,
    (uint32_t)USART3_4_IRQHandler,
    (uint32_t)CEC_CAN_IRQHandler,
    (uint32_t)USB_IRQHandler
};

void Default_Handler(void)
{
    while(1);
}

void Reset_Handler(void)
{
    // copy .data section to SRAM
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;

    uint8_t *pDst = (uint8_t*)&_sdata; //sram
    uint8_t *pSrc = (uint8_t*)&_la_data; //flash

    for(uint32_t i = 0; i < size; i++)
    {
        *pDst++ = *pSrc++;
    }

    // Init the .bss section to zero in SRAM
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t*)&_sbss;

    for(uint32_t i = 0; i < size; i++)
    {
        *pDst++ = 0;
    }


    // call init function of std. library
    __libc_init_array();

    // call main()
    __asm volatile("MSR MSP, %0": : "r" (STACK_START): ); // stack reset
    main();
}
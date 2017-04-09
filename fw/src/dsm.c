#include "stm32f0xx.h"
#include "dsm.h"

volatile uint8_t DSMFrameIsSending = 0;


void DSMInit (void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	GPIOA->MODER &= ~(GPIO_MODER_MODER2);
	GPIOA->MODER |= GPIO_MODER_MODER2_1; 	// PA2 - TX - AF,
	GPIOA->AFR[0] = (1U << 2*4);			// PA2 - UART1 - AF1.
	
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	USART1->BRR = SystemCoreClock / DSM_BAUDRATE;
	USART1->CR3 = USART_CR3_DMAT;
	USART1->CR1 = USART_CR1_TE | USART_CR1_UE; 
	
	while ((USART1->ISR & USART_ISR_TC) != USART_ISR_TC){}						// Polling idle frame Transmission
	USART1->ICR |= USART_ICR_TCCF; 												// Clear TC flag
	DSMFrameIsSending = 0;
	
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->CFGR1 |= SYSCFG_CFGR1_USART1TX_DMA_RMP;								// USART1 TX DMA remap on channel 4
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
		
	NVIC_SetPriority(DMA1_Channel4_5_IRQn, 0);
	NVIC_EnableIRQ(DMA1_Channel4_5_IRQn);
}



void DSMSend (uint8_t *data, uint8_t num)
{
	while (DSMFrameIsSending){}
	DSMFrameIsSending = 1;
	DMA1_Channel4->CNDTR = num;
	DMA1_Channel4->CMAR = (uint32_t)data;
	DMA1_Channel4->CPAR = (uint32_t)&USART1->TDR;
	DMA1_Channel4->CCR = DMA_CCR_PL_0 | DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE | DMA_CCR_EN;
}
	


void DMA1_Channel4_5_IRQHandler (void)
{
	if (DMA1->ISR & DMA_ISR_TCIF4)
	{
		DMA1->IFCR = DMA_IFCR_CTCIF4;
		DMA1_Channel4->CCR = 0;
		DSMFrameIsSending = 0;
	}
}










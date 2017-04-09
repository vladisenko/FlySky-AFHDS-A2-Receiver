#include "bsp.h"



void HardWareInit (void)
{
	SystemCoreClockUpdate();
	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER0; 			// PA0 - Analog mode
		
	RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
	RCC->CR2 |= RCC_CR2_HSI14ON;				// Start HSI14 RC oscillator
	while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0);
	ADC1->CR &= (uint32_t)(~ADC_CR_ADEN);
	ADC1->CR |= ADC_CR_ADCAL;					// Launch the calibration by setting ADCAL
	while ((ADC1->CR & ADC_CR_ADCAL) != 0);
	ADC1->CR |= ADC_CR_ADEN;
	while ((ADC1->ISR & ADC_ISR_ADRDY) == 0);
	ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE;
	ADC1->CFGR1 |= ADC_CFGR1_AUTOFF;			
	ADC1->CHSELR = ADC_CHSELR_CHSEL0;
	ADC1->SMPR = 0;
	ADC->CCR = 0;
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = SystemCoreClock/(1000000UL) - 1; // run at 1 MHz
	TIM2->ARR = 0xFFFFFFFF;
	TIM2->CNT = 0;
	TIM2->EGR = TIM_EGR_UG;
	while ( (TIM2->SR & TIM_SR_UIF) == 0);
	TIM2->SR = 0;
	TIM2->CR1 = TIM_CR1_CEN;
}


uint32_t micros (void)
{
	return TIM2->CNT;
}


void delayMicroseconds (uint32_t us)
{
	uint32_t start = micros();
	while ( micros() - start < us);
}

void delayMilliseconds (uint32_t ms)
{
	while (ms--) delayMicroseconds(1000);
}


void LED (uint8_t state)
{
	GPIOA->BSRR = state ? GPIO_BSRR_BR_1 : GPIO_BSRR_BS_1; 
}


uint8_t CheckJumper (void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER = 0x10000000 | (GPIOA->MODER & ~0x3C000000);	// PA13 - GP in,
	uint8_t res = ((GPIOA->IDR & (1<<13)) == 0) ? 1 : 0;
	GPIOA->MODER = 0x28000000 | (GPIOA->MODER & ~0x3C000000);	// PA13 - SDWIO - AF,
	return res;
}


uint32_t GetCPUID (void)
{
	return UID->UID0 ^ UID->UID1 ^ UID->UID2;
}


static inline uint16_t GetADC (void)
{
	ADC1->CR |= ADC_CR_ADSTART; 			// start the ADC conversion
    while ((ADC1->ISR & ADC_ISR_EOC) == 0); // wait end of conversion
	return ADC1->DR;
}


uint16_t GetVoltage (void)
{
	uint32_t tmp = GetADC();
	tmp *= ((R_HIGH + R_LOW)  * VREF) / R_LOW;
	tmp /= 4095 * 10;
	return tmp;
}


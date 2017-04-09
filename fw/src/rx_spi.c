#include "rx_spi.h"


void rxSpiDeviceInit (rx_spi_type_e spiType)
{
	(void)spiType;
	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;
	GPIOA->MODER &= ~(GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
	GPIOA->MODER |= GPIO_MODER_MODER5_1 |	// PA5 - SCK A7105 - AF,
					GPIO_MODER_MODER6_1 |	// PA6 - DIO A7105 - AF,
					GPIO_MODER_MODER7_1;	// PA7 - DIO A7105 - AF,
	
	GPIOA->PUPDR |=	GPIO_PUPDR_PUPDR4_1;	// PA4 - Pull-up.				
	
	GPIOB->MODER &= ~(GPIO_MODER_MODER1);
	GPIOB->MODER |=	GPIO_MODER_MODER1_0;	// PB1 - CS A7105 - GPout
	DISABLE_RX();
	
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	SPI1->CR1 = 0;
	SPI1->CR2 = SPI_CR2_FRXTH |				// RXNE event is generated if the FIFO level is greater than or equal to 1/4 (8-bit)
				SPI_CR2_DS_0 |				// Data Size: 0b0111 - 8 bit
				SPI_CR2_DS_1 |
				SPI_CR2_DS_2;
	SPI1->CR1 = SPI_CR1_MSTR |
				SPI_CR1_SPE |				// Peripheral enabled
				SPI_CR1_SSI |				// Internal slave select
				SPI_CR1_SSM ;				// Software slave management
}


uint8_t rxSpiTransferByte (uint8_t data)
{
	while ((SPI1->SR & SPI_SR_TXE) == 0);
	*(uint8_t *)&(SPI1->DR) = (uint8_t) data;
	while ((SPI1->SR & SPI_SR_RXNE) == 0);
	const uint8_t tmp = (uint8_t) SPI1->DR;
	//while ((SPI1->SR & SPI_SR_BSY) != 0);
	return tmp;
}


uint8_t rxSpiWriteByte(uint8_t data)
{
    ENABLE_RX();
    const uint8_t ret = rxSpiTransferByte(data);
    DISABLE_RX();
    return ret;
}


uint8_t rxSpiWriteCommand(uint8_t command, uint8_t data)
{
    ENABLE_RX();
    const uint8_t ret = rxSpiTransferByte(command);
    rxSpiTransferByte(data);
    DISABLE_RX();
    return ret;
}


uint8_t rxSpiWriteCommandMulti(uint8_t command, const uint8_t *data, uint8_t length)
{
    ENABLE_RX();
    const uint8_t ret = rxSpiTransferByte(command);
    for (uint8_t i = 0; i < length; i++) {
        rxSpiTransferByte(data[i]);
    }
    DISABLE_RX();
    return ret;
}


uint8_t rxSpiReadCommand(uint8_t command, uint8_t data)
{
    ENABLE_RX();
    rxSpiTransferByte(command);
    const uint8_t ret = rxSpiTransferByte(data);
    DISABLE_RX();
    return ret;
}


uint8_t rxSpiReadCommandMulti(uint8_t command, uint8_t commandData, uint8_t *retData, uint8_t length)
{
    ENABLE_RX();
    const uint8_t ret = rxSpiTransferByte(command);
    for (uint8_t i = 0; i < length; i++) {
        retData[i] = rxSpiTransferByte(commandData);
    }
    DISABLE_RX();
    return ret;
}

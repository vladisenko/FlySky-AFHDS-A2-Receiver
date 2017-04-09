#ifndef _RX_SPI_H_
#define _RX_SPI_H_

#include <stdint.h>
#include "stm32f0xx.h"

#define ENABLE_RX()		do { GPIOB->BSRR = GPIO_BSRR_BR_1; } while(0)
#define DISABLE_RX()	do { GPIOB->BSRR = GPIO_BSRR_BS_1; } while(0)
#define GIO_GET()		(GPIOA->IDR & GPIO_IDR_4)

typedef enum {
    RX_SPI_SOFTSPI,
    RX_SPI_HARDSPI
} rx_spi_type_e;


void rxSpiDeviceInit (rx_spi_type_e spiType);
uint8_t rxSpiTransferByte (uint8_t data);
uint8_t rxSpiWriteByte (uint8_t data);
uint8_t rxSpiWriteCommand (uint8_t command, uint8_t data);
uint8_t rxSpiWriteCommandMulti (uint8_t command, const uint8_t *data, uint8_t length);
uint8_t rxSpiReadCommand (uint8_t command, uint8_t commandData);
uint8_t rxSpiReadCommandMulti (uint8_t command, uint8_t commandData, uint8_t *retData, uint8_t length);

#endif // _RX_SPI_H_

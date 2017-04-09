#include "A7105.h"
#include "rx_spi.h"


void A7105_Init (void)
{
    rxSpiDeviceInit(RX_SPI_HARDSPI);
}


void A7105_SoftReset (void)
{
	rxSpiWriteCommand ((uint8_t)A7105_00_MODE, 0x00);
}


uint8_t A7105_ReadReg (a7105_reg_t reg)
{
	return rxSpiReadCommand( (uint8_t)reg | 0x40, 0xFF);
}


void A7105_WriteReg (a7105_reg_t reg, uint8_t data)
{
	rxSpiWriteCommand ((uint8_t)reg, data);
}


void A7105_Strobe (a7105_state_t st)
{
	rxSpiWriteByte ((uint8_t)st);
}


void A7105_WriteID(uint32_t id)
{
	uint8_t data[4];
	data[0] = (id >> 24) & 0xFF;
	data[1] = (id >> 16) & 0xFF;
	data[2] = (id >> 8) & 0xFF;
	data[3] = (id >> 0) & 0xFF;
	rxSpiWriteCommandMulti ((uint8_t)A7105_06_ID_DATA, &data[0], sizeof(data));
}


uint32_t A7105_ReadID (void)
{
	uint32_t id;
	uint8_t data[4];
	rxSpiReadCommandMulti ( (uint8_t)A7105_06_ID_DATA | 0x40, 0xFF, &data[0], sizeof(data));
	id  = data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3] << 0;
	return id;
}


void A7105_ReadFIFO (uint8_t *data, uint8_t num)
{
	if(num > 64) num = 64;
	A7105_Strobe(A7105_RST_RDPTR);	// reset read pointer
	rxSpiReadCommandMulti ( (uint8_t)A7105_05_FIFO_DATA | 0x40, 0xFF, data, num);
}


void A7105_WriteFIFO (uint8_t *data, uint8_t num)
{
	if(num > 64) num = 64;
	A7105_Strobe(A7105_RST_WRPTR);	// reset write pointer
	rxSpiWriteCommandMulti( (uint8_t)A7105_05_FIFO_DATA, data, num);
}


uint8_t A7105_RX_TX_Finished (void)
{
	return (GIO_GET() == 0) ? 0xFF : 0x00;
}

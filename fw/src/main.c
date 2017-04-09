/*
FlySky compatible receiver with DSM-like output. Tested with LibrePilot CC3D,
Cleanflight and Betaflight.
After the first turn on the receiver automatically switches to bind mode.
For manual binding pin PA13 and PA14 must be closed before power up. 

Sources:
	https://www.deviationtx.com/forum/protocol-development/5251-flysky-afhds-2a-protocol-as-used-i10-i6-it4
	https://github.com/goebish/deviation/blob/master/src/protocol/flysky_afhds2a_a7105.c
*/
#include "bsp.h"
#include "dsm.h"
#include "flash.h"
#include "flysky_A2.h"

rxRuntimeConfig_t rxRuntimeConfig;
rxConfig_t	rxConfig;

uint8_t payload[PACKET_SIZE];
uint16_t rcData[FLYSKY_CHANNEL_COUNT];
uint8_t DSMFrame[DSM_FRAME_LENGTH];

void makeDSMFrame (uint8_t *frame, const uint16_t *rc, const uint8_t nchan);


int main (void)
{
	HardWareInit();
	DSMInit();
	delayMilliseconds(100);
	DSMSend((uint8_t*)"Start\n", 6);
	
	LoadEEPROM ((uint8_t*)&rxConfig, sizeof(rxConfig_t)); 
	FlySkyA2Init (&rxConfig, &rxRuntimeConfig);
	
	uint8_t HaveNewData = 0;
	uint32_t TimeDSMSend = 0;
	
	while (1)
	{
		rx_spi_received_e result = FlySkyA2DataReceived (payload);
		
		if (result == RX_SPI_RECEIVED_DATA)
		{
			FlySkyA2SetRcDataFromPayload (rcData, payload);
			HaveNewData = 0xFF;
		}
		else if (result == RX_SPI_RECEIVED_BIND)
		{
			SaveEEPROM ((uint8_t*)&rxConfig, sizeof(rxConfig_t)); 
		}
		
		if ( (micros() - TimeDSMSend > 11000) && HaveNewData)
		{
			makeDSMFrame (DSMFrame, rcData, rxRuntimeConfig.channelCount);
			DSMSend (DSMFrame, sizeof(DSMFrame));
			HaveNewData = 0;
			TimeDSMSend = micros();
		}
	} // while (1)
} // main()


void makeDSMFrame (uint8_t *frame, const uint16_t *rc, const uint8_t nchan)
{
	frame[0] = 0;
#if DSM_11BIT
	frame[1] = 0x12;
#else
	frame[1] = 0x01;				
#endif		
	for (uint8_t ch = 0; ch < DSM_CHANNELS_PER_FRAME && ch < nchan; ch++)
	{
		uint32_t tmp = rc[ch];
		if (tmp > 1000) tmp -= 1000; else tmp = 0;									// todo: check value
#if DSM_11BIT
		tmp = (tmp * 2047 + 500)/1000;				
		tmp = (tmp & 0x07FF) | (ch << 11);
#else
		tmp = (tmp * 1023 + 500)/1000;				
		tmp = (tmp & 0x03FF) | (ch << 10);				
#endif
		frame[2*ch + 2]  = (tmp >> 8) & 0x00FF;
		frame[2*ch + 3]  = tmp & 0x00FF;
	}
}











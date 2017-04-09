#ifndef _FLYSKY_A2_H_
#define _FLYSKY_A2_H_

#include <stdint.h>


#define FLYSKY_CHANNEL_COUNT 		8 // max is 14
#define PACKET_SIZE 				37
#define NUMFREQ       				16
#define TXID_SIZE     				4
#define RXID_SIZE     				4


enum Sensors
{
	IntV 	= 0x00,
	Temp 	= 0x01,
	MotRPM 	= 0x02,
	ExtV 	= 0x03,
	ErrRate	= 0xFE
};


typedef enum {
    RX_SPI_RECEIVED_NONE = 0,
    RX_SPI_RECEIVED_BIND,
    RX_SPI_RECEIVED_DATA
} rx_spi_received_e;


typedef struct rxConfig_s {
  uint32_t rx_spi_id;
	uint8_t rx_spi_rf_channel_map[NUMFREQ];
} rxConfig_t;


struct rxRuntimeConfig_s;
typedef uint16_t (*rcReadRawDataFnPtr)(const struct rxRuntimeConfig_s *rxRuntimeConfig, uint8_t chan); // used by receiver driver to return channel data
typedef uint8_t (*rcFrameStatusFnPtr)(void);


typedef struct rxRuntimeConfig_s {
    uint8_t          channelCount; // number of RC channels as reported by current input driver
    uint16_t         rxRefreshRate;
    rcReadRawDataFnPtr rcReadRawFn;
    rcFrameStatusFnPtr rcFrameStatusFn;
} rxRuntimeConfig_t;



void FlySkyA2Init(const struct rxConfig_s *rxConfig, struct rxRuntimeConfig_s *rxRuntimeConfig);
void FlySkyA2SetRcDataFromPayload(uint16_t *rcData, const uint8_t *payload);
rx_spi_received_e  FlySkyA2DataReceived(uint8_t *payload);


extern rxConfig_t rxConfig;
#define rxConfig() (&rxConfig)


#endif // _FLYSKY_A2_H_

#ifndef _BSP_H_
#define _BSP_H_

#include <stdint.h>
#include "stm32f0xx.h"

#define VREF 		2500 // mV
#define R_HIGH		2000 // Ohm
#define R_LOW		1200 // Ohm

typedef struct 
{
	uint32_t UID0;
	uint32_t UID1;
	uint32_t UID2;
} UID_TypeDef;

#define UID ((UID_TypeDef *)0x1FFFF7AC)


void HardWareInit (void);

uint32_t micros (void);
void delayMicroseconds (uint32_t us);
void delayMilliseconds (uint32_t ms);

void LED (uint8_t state);

uint8_t CheckJumper (void);

uint32_t GetCPUID (void);

uint16_t GetVoltage (void);


#endif // _BSP_H_

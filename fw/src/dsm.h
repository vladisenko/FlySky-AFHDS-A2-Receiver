#ifndef __dsm_h_
#define __dsm_h_

#include <stdint.h>

#define DSM_CHANNELS_PER_FRAME 	7
#define DSM_FRAME_LENGTH       (1 + 1 + DSM_CHANNELS_PER_FRAME * 2)
#define DSM_BAUDRATE 			115200UL
#define DSM_11BIT				0


void DSMInit (void);
void DSMSend (uint8_t *data, uint8_t num);



#endif

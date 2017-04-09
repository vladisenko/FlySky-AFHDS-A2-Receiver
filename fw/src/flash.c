#include "stm32f0xx.h"
#include "flash.h"


static inline void UnlockFlash (void)
{
	while ((FLASH->SR & FLASH_SR_BSY) != 0) {}
	if ((FLASH->CR & FLASH_CR_LOCK) != 0)
	{
		FLASH->KEYR = FLASH_FKEY1;
		FLASH->KEYR = FLASH_FKEY2;
	}
}


static inline void LockFlash (void)
{
	FLASH->CR |= FLASH_CR_LOCK;
}


static inline void ErasePage (uint32_t addr)
{
	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR = addr;
	FLASH->CR |= FLASH_CR_STRT;
	while ((FLASH->SR & FLASH_SR_BSY) != 0)	{}
	if ((FLASH->SR & FLASH_SR_EOP) != 0)
	{
		FLASH->SR |= FLASH_SR_EOP;
	}
	FLASH->CR &= ~FLASH_CR_PER;
}


uint8_t SaveEEPROM (uint8_t *data, uint16_t num)
{
	uint8_t res = 1;
	
	if (num <= FLASH_PAGE_SIZE)
	{
		UnlockFlash();
		ErasePage(FLASH_LAST_PAGE);
		
		__IO uint16_t *pflash = (__IO uint16_t*)FLASH_LAST_PAGE;
		uint16_t num_to_write = (num + 1) >> 1;
		while(num_to_write--)
		{
			uint16_t tmp = *data++;
			num--;
			if (num)
			{
				tmp |= (*data++) << 8;
				num--;
			}
			
			FLASH->CR |= FLASH_CR_PG;
			*pflash++ = tmp; 
			while ((FLASH->SR & FLASH_SR_BSY) != 0);
			if ((FLASH->SR & FLASH_SR_EOP) != 0) 
			{
				FLASH->SR |= FLASH_SR_EOP;
			}
			FLASH->CR &= ~FLASH_CR_PG;
		}
		
		LockFlash();
		
		res = 0;
	}
	return res;
}


uint8_t LoadEEPROM (uint8_t *data, uint16_t num)
{
	uint8_t res = 1;
	
	if (num <= FLASH_PAGE_SIZE)
	{
		uint16_t num_to_read;
		uint16_t tmp;
		__IO uint16_t *pflash = (__IO uint16_t*)FLASH_LAST_PAGE;
		
		num_to_read = (num + 1) >> 1;

		while (num_to_read--)
		{
			tmp = *pflash++;
			*data++ = tmp & 0x00FF;
			num--;
			if (num)
			{
				*data++ = (tmp >>8) & 0x00FF;
				num--;
			}
		}
		res = 0;
	}
	return res;
} 

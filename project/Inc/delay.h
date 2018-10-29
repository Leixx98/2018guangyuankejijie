#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define SYSTEM_SUPPORT_OS 1	
	
void Delay_Init(uint8_t SYSCLK);
void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);
#ifdef __cplusplus
}
#endif

#endif


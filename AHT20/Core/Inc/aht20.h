#ifndef __AHT20_H
#define __AHT20_H

#include "stm32f1xx_hal.h"

uint8_t AHT20_Init(void);
uint8_t AHT20_Read(float *temperature, float *humidity);

#endif

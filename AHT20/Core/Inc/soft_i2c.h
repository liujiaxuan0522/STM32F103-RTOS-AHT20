#ifndef __SOFT_I2C_H
#define __SOFT_I2C_H

#include "stm32f1xx_hal.h"

/*
 * 软件 I2C，使用 PB6=SCL，PB7=SDA。
 * 两个引脚都配置为开漏输出，外部各接 4.7 kΩ 上拉电阻到 3.3 V。
 * SDA 读取时直接读 IDR，因此不需要频繁切换输入/输出模式。
 */
#define SOFT_I2C_SCL_PORT   GPIOB
#define SOFT_I2C_SCL_PIN    GPIO_PIN_6
#define SOFT_I2C_SDA_PORT   GPIOB
#define SOFT_I2C_SDA_PIN    GPIO_PIN_7

void SoftI2C_Init(void);
void SoftI2C_Start(void);
void SoftI2C_Stop(void);
uint8_t SoftI2C_WriteByte(uint8_t byte);
uint8_t SoftI2C_ReadByte(uint8_t ack);
void SoftI2C_DelayUs(uint32_t us);

#endif

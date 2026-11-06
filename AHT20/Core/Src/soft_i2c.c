#include "soft_i2c.h"

#define SCL_H()  HAL_GPIO_WritePin(SOFT_I2C_SCL_PORT, SOFT_I2C_SCL_PIN, GPIO_PIN_SET)
#define SCL_L()  HAL_GPIO_WritePin(SOFT_I2C_SCL_PORT, SOFT_I2C_SCL_PIN, GPIO_PIN_RESET)
#define SDA_H()  HAL_GPIO_WritePin(SOFT_I2C_SDA_PORT, SOFT_I2C_SDA_PIN, GPIO_PIN_SET)
#define SDA_L()  HAL_GPIO_WritePin(SOFT_I2C_SDA_PORT, SOFT_I2C_SDA_PIN, GPIO_PIN_RESET)
#define SDA_READ() HAL_GPIO_ReadPin(SOFT_I2C_SDA_PORT, SOFT_I2C_SDA_PIN)

void SoftI2C_DelayUs(uint32_t us)
{
    /* 72 MHz 下约 1 us 的粗延时；I2C 时序要求不严时可使用 */
    while (us--) {
        for (volatile uint32_t i = 0; i < 18; i++) {
            __NOP();
        }
    }
}

void SoftI2C_Init(void)
{
    GPIO_InitTypeDef gpio = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();

    gpio.Pin = SOFT_I2C_SCL_PIN | SOFT_I2C_SDA_PIN;
    gpio.Mode = GPIO_MODE_OUTPUT_OD;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio);

    SCL_H();
    SDA_H();
    SoftI2C_DelayUs(10);
}

void SoftI2C_Start(void)
{
    SDA_H();
    SCL_H();
    SoftI2C_DelayUs(5);
    SDA_L();
    SoftI2C_DelayUs(5);
    SCL_L();
    SoftI2C_DelayUs(5);
}

void SoftI2C_Stop(void)
{
    SDA_L();
    SCL_H();
    SoftI2C_DelayUs(5);
    SDA_H();
    SoftI2C_DelayUs(5);
}

uint8_t SoftI2C_WriteByte(uint8_t byte)
{
    uint8_t i, ack;

    for (i = 0; i < 8; i++) {
        SCL_L();
        SoftI2C_DelayUs(2);
        if (byte & 0x80) {
            SDA_H();
        } else {
            SDA_L();
        }
        byte <<= 1;
        SoftI2C_DelayUs(2);
        SCL_H();
        SoftI2C_DelayUs(5);
    }

    SCL_L();
    SDA_H();                 /* 释放 SDA，等待从机 ACK */
    SoftI2C_DelayUs(2);
    SCL_H();
    SoftI2C_DelayUs(2);
    ack = (SDA_READ() == GPIO_PIN_RESET) ? 0 : 1;
    SCL_L();
    SoftI2C_DelayUs(2);
    return ack;              /* 0=ACK，1=NACK */
}

uint8_t SoftI2C_ReadByte(uint8_t ack)
{
    uint8_t i, byte = 0;

    SDA_H();                 /* 释放 SDA，由从机驱动 */
    for (i = 0; i < 8; i++) {
        SCL_L();
        SoftI2C_DelayUs(2);
        SCL_H();
        SoftI2C_DelayUs(2);
        byte = (byte << 1) | (SDA_READ() == GPIO_PIN_SET ? 1 : 0);
        SoftI2C_DelayUs(2);
    }

    SCL_L();
    SoftI2C_DelayUs(2);
    if (ack) {
        SDA_L();             /* 主机发送 ACK */
    } else {
        SDA_H();             /* 主机发送 NACK */
    }
    SoftI2C_DelayUs(2);
    SCL_H();
    SoftI2C_DelayUs(5);
    SCL_L();
    SDA_H();
    SoftI2C_DelayUs(2);
    return byte;
}

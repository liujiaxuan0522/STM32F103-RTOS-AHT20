#include "aht20.h"
#include "soft_i2c.h"

#define AHT20_WRITE_ADDR   0x70u
#define AHT20_READ_ADDR    0x71u

static uint8_t AHT20_WriteBytes(const uint8_t *buf, uint8_t len)
{
    uint8_t i;
    SoftI2C_Start();
    if (SoftI2C_WriteByte(AHT20_WRITE_ADDR) != 0) {
        SoftI2C_Stop();
        return 1;
    }
    for (i = 0; i < len; i++) {
        if (SoftI2C_WriteByte(buf[i]) != 0) {
            SoftI2C_Stop();
            return 1;
        }
    }
    SoftI2C_Stop();
    return 0;
}

static uint8_t AHT20_ReadStatus(void)
{
    uint8_t status;
    SoftI2C_Start();
    if (SoftI2C_WriteByte(AHT20_READ_ADDR) != 0) {
        SoftI2C_Stop();
        return 0xFF;
    }
    status = SoftI2C_ReadByte(0);
    SoftI2C_Stop();
    return status;
}

static uint8_t AHT20_CalcCRC8(const uint8_t *data, uint8_t len)
{
    uint8_t i, crc = 0xFF;
    while (len--) {
        crc ^= *data++;
        for (i = 0; i < 8; i++) {
            crc = (crc & 0x80) ? (uint8_t)((crc << 1) ^ 0x31) : (uint8_t)(crc << 1);
        }
    }
    return crc;
}

uint8_t AHT20_Init(void)
{
    uint8_t cmd[3];
    uint8_t status;

    SoftI2C_Init();
    HAL_Delay(40);                 /* 上电后等待传感器内部初始化 */

    status = AHT20_ReadStatus();
    if ((status & 0x18) != 0x18) {
        cmd[0] = 0xBE;             /* 初始化命令 */
        cmd[1] = 0x08;             /* 使能校准 */
        cmd[2] = 0x00;
        if (AHT20_WriteBytes(cmd, 3) != 0) {
            return 1;
        }
        HAL_Delay(10);
    }
    return 0;
}

uint8_t AHT20_Read(float *temperature, float *humidity)
{
    uint8_t cmd[3] = {0xAC, 0x33, 0x00};
    uint8_t buf[7];
    uint32_t rawHum, rawTemp;
    uint8_t i, retry = 0;

    if (AHT20_WriteBytes(cmd, 3) != 0) {
        return 1;
    }
    HAL_Delay(80);                 /* 测量时间 */

    while ((AHT20_ReadStatus() & 0x80) != 0) {
        HAL_Delay(2);
        if (++retry > 20) {
            return 2;
        }
    }

    SoftI2C_Start();
    if (SoftI2C_WriteByte(AHT20_READ_ADDR) != 0) {
        SoftI2C_Stop();
        return 3;
    }
    for (i = 0; i < 6; i++) {
        buf[i] = SoftI2C_ReadByte(1);   /* ACK */
    }
    buf[6] = SoftI2C_ReadByte(0);       /* NACK */
    SoftI2C_Stop();

    if (AHT20_CalcCRC8(buf, 6) != buf[6]) {
        return 4;
    }

    rawHum  = ((uint32_t)buf[1] << 16) | ((uint32_t)buf[2] << 8) | buf[3];
    rawHum >>= 4;
    rawTemp = (((uint32_t)buf[3] & 0x0F) << 16) | ((uint32_t)buf[4] << 8) | buf[5];

    *humidity    = (float)rawHum  * 100.0f / 1048576.0f;
    *temperature = (float)rawTemp * 200.0f / 1048576.0f - 50.0f;
    return 0;
}

#include "BMP180.h"
#include <SensorHubTemplates.h>

BMP180::BMP180() : sensorHub(BMP180_I2C_ADDR) {}

bool BMP180::begin()
{
    if (isConnected && readCalibParams())
        return true;
    return false;
}

bool BMP180::isConnected()
{
    return sensorHub.is_sensor_connected();
}

bool BMP180::readCalibParams()
{
    return sensorHub.i2c_read_Xbit(BMP180_AC1_CAL_REG, &AC1, 16) &&
           sensorHub.i2c_read_Xbit(BMP180_AC2_CAL_REG, &AC2, 16) &&
           sensorHub.i2c_read_Xbit(BMP180_AC3_CAL_REG, &AC3, 16) &&
           sensorHub.i2c_read_Xbit(BMP180_AC4_CAL_REG, &AC4, 16) &&
           sensorHub.i2c_read_Xbit(BMP180_AC5_CAL_REG, &AC5, 16) &&
           sensorHub.i2c_read_Xbit(BMP180_AC6_CAL_REG, &AC6, 16) &&
           sensorHub.i2c_read_Xbit(BMP180_B1_CAL_REG, &B1, 16) &&
           sensorHub.i2c_read_Xbit(BMP180_B2_CAL_REG, &B2, 16) &&
           sensorHub.i2c_read_Xbit(BMP180_MB_CAL_REG, &MB, 16) &&
           sensorHub.i2c_read_Xbit(BMP180_MC_CAL_REG, &MC, 16) &&
           sensorHub.i2c_read_Xbit(BMP180_MD_CAL_REG, &MD, 16);
}

void BMP180::readUT()
{
    sensorHub.i2c_write(BMP180_CTRL_TEMP_MEAS_REG, BMP180_TEMP_START_MEAS);
    delay(5);
    sensorHub.i2c_read_Xbit(BMP180_TEMP_MEAS_REG, &UT, 16);
}

void BMP180::readUP()
{
    sensorHub.i2c_write(BMP180_CTRL_PRESS_MEAS_REG, BMP180_PRESS_START_MEAS | (pres_oss << 6));
    delay(70);
    sensorHub.i2c_read_Xbit(BMP180_PRESS_MEAS_REG, &UP, 24);
    UP >>= (8 - pres_oss);
}

float BMP180::readTemperature()
{
    readUT();
    int32_t X1 = (UT - AC6) * AC5 >> 15;
    int32_t X2 = (MC << 11) / (X1 + MD);
    int32_t B5 = X1 + X2;
    return (B5 + 8) >> 4;
}

float BMP180::readPressure()
{
    readUP();
    int32_t B6 = B5 - 4000;
    X1 = (B2 * (B6 * B6 >> 12)) >> 11;
    X2 = AC2 * B6 >> 11;
    int32_t X3 = X1 + X2;
    int32_t B3 = (((AC1 * 4 + X3) << pres_oss) + 2) >> 2;
    X1 = AC3 * B6 >> 13;
    X2 = (B1 * (B6 * B6 >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    uint32_t B4 = AC4 * (uint32_t)(X3 + 32768) >> 15;
    uint32_t B7 = ((uint32_t)UP - B3) * (50000 >> pres_oss);
    int32_t p;
    if (B7 < 0x80000000)
        p = (B7 * 2) / B4;
    else
        p = (B7 / B4) * 2;
    X1 = (p >> 8) * (p >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7357 * p) >> 16;
    return p + ((X1 + X2 + 3791) >> 4);
}

void BMP180::setPressureOverSampling(uint8_t os)
{
    pres_oss = os;
}

float BMP180::readAltitude()
{
    float pressure = readPressure();
    return 44330 * (1 - pow(pressure / 101325, 0.1903));
}
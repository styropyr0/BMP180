#ifndef BMP180_H
#define BMP180_H

#include <Arduino.h>
#include <SensorHub.h>
#include "BMP180DEFS.h"

#ifdef __cplusplus

class BMP180
{
public:
    BMP180();
    bool begin();
    float readTemperature();
    float readPressure();
    void setPressureOverSampling(uint8_t os);
    float readAltitude();
    bool isConnected();

private:
    SensorHub sensorHub;
    uint8_t pres_oss = 0;
    float UT = 0, UP = 0;
    int16_t AC1, AC2, AC3, B1, B2, MB, MC, MD;
    uint16_t AC4, AC5, AC6;

    bool readCalibParams();
    void readUT();
    void readUP();
}

#endif // __cplusplus
#endif // BMP180_H
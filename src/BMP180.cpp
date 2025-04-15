#include "BMP180.h"
#include <SensorHubTemplates.h>

BMP180::BMP180() : sensorHub(BMP180_I2C_ADDR) {}

bool BMP180::begin()
{
    if (isConnected() && readCalibParams())
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
           sensorHub.i2c_read_Xbit(BMP180_B1_CAL_REG, &_B1, 16) &&
           sensorHub.i2c_read_Xbit(BMP180_B2_CAL_REG, &_B2, 16) &&
           sensorHub.i2c_read_Xbit(BMP180_MB_CAL_REG, &MB, 16) &&
           sensorHub.i2c_read_Xbit(BMP180_MC_CAL_REG, &MC, 16) &&
           sensorHub.i2c_read_Xbit(BMP180_MD_CAL_REG, &MD, 16);
}

void BMP180::readUT()
{
    sensorHub.i2c_execute(BMP180_CTRL_TEMP_MEAS_REG, BMP180_TEMP_START_MEAS);
    delay(5);
    sensorHub.i2c_read_Xbit(BMP180_TEMP_MEAS_REG, &UT, 16);
}

void BMP180::readUP()
{
    sensorHub.i2c_execute(BMP180_CTRL_PRESS_MEAS_REG, BMP180_PRESS_START_MEAS | (pres_oss << 6));
    delay(70);
    sensorHub.i2c_read_Xbit(BMP180_PRESS_MEAS_REG, &UP, 24);
    UP >>= (8 - pres_oss);
}

float BMP180::readTemperature()
{
    readUT();
    int32_t X1 = (UT - AC6) * (AC5 / pow(2, 15));
    int32_t X2 = (MC * pow(2, 11)) / (X1 + MD);
    B5 = X1 + X2;

    if (!metricSystem)
        return (B5 + 8) / pow(2, 4) / 10.0;
    else
        return metricSystem->convertTemperature((B5 + 8) / pow(2, 4) / 10.0);
}

float BMP180::readPressure()
{
    readUP();
    int32_t B6 = B5 - 4000;
    int32_t X1 = (_B2 * (B6 * B6 >> 12)) >> 11;
    int32_t X2 = AC2 * B6 >> 11;
    int32_t X3 = X1 + X2;
    int32_t B3 = (((AC1 * 4 + X3) << pres_oss) + 2) >> 2;
    X1 = AC3 * B6 >> 13;
    X2 = (_B1 * (B6 * B6 >> 12)) >> 16;
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
    pressure = p + ((X1 + X2 + 3791) >> 4);

    if (!metricSystem)
        return pressure;
    else
        return metricSystem->convertPressure(pressure);
}

void BMP180::setPressureOverSampling(uint8_t os)
{
    pres_oss = os;
}

float BMP180::readAltitude()
{
    readPressure();

    if (!metricSystem)
        return 44330 * (1 - pow(pressure / 101325, 0.1903));
    else
        return metricSystem->convertAltitude(44330 * (1 - pow(pressure / 101325, 0.1903)));
}

void BMP180::setMetricSystem(const MetricSystem &metricSystem)
{
    if (this->metricSystem)
    {
        if (this->metricSystem->getType() == metricSystem.getType())
            return;

        delete this->metricSystem;
        this->metricSystem = nullptr;
    }
    if (metricSystem.getType() == INTERNATIONAL_SYSTEM)
        this->metricSystem = new InternationalSystem();
    else if (metricSystem.getType() == IMPERIAL_SYSTEM)
        this->metricSystem = new ImperialSystem();
    else
        this->metricSystem = new MetricSystem(metricSystem.temperature, metricSystem.pressure, metricSystem.altitude);
}

String BMP180::getTemperatureUnit()
{
    if (metricSystem)
        return metricSystem->temperatureUnit;
    else
        return METRIC_UNIT_CELSIUS;
}

String BMP180::getPressureUnit()
{
    if (metricSystem)
        return metricSystem->pressureUnit;
    else
        return METRIC_UNIT_PASCAL;
}

String BMP180::getAltitudeUnit()
{
    if (metricSystem)
        return metricSystem->altitudeUnit;
    else
        return METRIC_UNIT_METRE;
}
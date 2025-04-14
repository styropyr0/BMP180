#if defined(BMP180_H) && defined(__cplusplus)

#ifndef METRIC_SYSTEM_PRIVATE_H
#define METRIC_SYSTEM_PRIVATE_H

#include <Arduino.h>
#include "BMP180DEFS.h"

/**
 * @brief Metric System class for defining the measurement system.
 * @details This class provides methods to convert pressure, temperature, and altitude values between different units.
 * @author Saurav Sajeev
 */
class MetricSystem
{
public:
    uint8_t pressure = BMP180_PRESSURE_PASCAL;
    uint8_t temperature = BMP180_TEMP_CELSIUS;
    uint8_t altitude = BMP180_UNIT_METRE;

    virtual uint8_t getType() { return 0; }

    float convertPressure(float pressure)
    {
        switch (this->pressure)
        {
        case BMP180_PRESSURE_PSI:
            return pressure * 0.00014503773773;
        case BMP180_PRESSURE_BAR:
            return pressure * 0.00001;
        case BMP180_PRESSURE_INCH_HG:
            return pressure * 0.000295299830714;
        case BMP180_PRESSURE_ATM:
            return pressure * 0.00000986923;
        default:
            return pressure;
        }
        return pressure;
    }

    float convertAltitude(float altitude)
    {
        switch (this->altitude)
        {
        case BMP180_UNIT_FEET:
            return altitude * 3.28084;
        default:
            return altitude;
        }
        return altitude;
    }

    float convertTemperature(float temperature)
    {
        switch (this->temperature)
        {
        case BMP180_TEMP_FAHRENHEIT:
            return (temperature * 9.0 / 5.0) + 32.0;
        case BMP180_TEMP_KELVIN:
            return temperature + 273.15;
        default:
            return temperature;
        }
        return temperature;
    }
};

/**
 * @brief ImperialSystem class for defining the imperial measurement system.
 * @details This class inherits from the MetricSystem class and sets the pressure, temperature, and altitude units to imperial values.
 * @author Saurav Sajeev
 */
class ImperialSystem : public MetricSystem
{
public:
    ImperialSystem(uint8_t pressureUnit, uint8_t temperatureUnit, uint8_t altitudeUnit)
    {
        this->pressure = pressureUnit;
        this->temperature = temperatureUnit;
        this->altitude = altitudeUnit;
    }

    ImperialSystem()
    {
        this->pressure = BMP180_PRESSURE_PSI;
        this->temperature = BMP180_TEMP_FAHRENHEIT;
        this->altitude = BMP180_UNIT_FEET;
    }

    uint8_t getType() override { return IMPERIAL_SYSTEM; }
};

/**
 * @brief InternationalSystem class for defining the international measurement system.
 * @details This class inherits from the MetricSystem class and sets the pressure, temperature, and altitude units to international values.
 * @author Saurav Sajeev
 */
class InternationalSystem : public MetricSystem
{
public:
    InternationalSystem(uint8_t pressureUnit, uint8_t temperatureUnit, uint8_t altitudeUnit)
    {
        this->pressure = pressureUnit;
        this->temperature = temperatureUnit;
        this->altitude = altitudeUnit;
    }

    InternationalSystem()
    {
        this->pressure = BMP180_PRESSURE_PASCAL;
        this->temperature = BMP180_TEMP_CELSIUS;
        this->altitude = BMP180_UNIT_METRE;
    }

    uint8_t getType() override { return INTERNATIONAL_SYSTEM; }
};

#endif // METRIC_SYSTEM_PRIVATE_H
#endif // BMP180_H && __cplusplus
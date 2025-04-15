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
    uint8_t pressure, temperature, altitude;
    String pressureUnit, temperatureUnit, altitudeUnit;

    /**
     * @brief Constructor for the MetricSystem class.
     * @param pressure The pressure unit to be used.
     * @param temperature The temperature unit to be used.
     * @param altitude The altitude unit to be used.
     */
    MetricSystem(uint8_t temperature, uint8_t pressure, uint8_t altitude)
    {
        this->pressure = pressure;
        this->temperature = temperature;
        this->altitude = altitude;
    }

    /**
     * @brief Default constructor for the MetricSystem class.
     * @details Initializes the pressure, temperature, and altitude units to default values.
     */
    MetricSystem()
    {
        this->pressure = BMP180_PRESSURE_PASCAL;
        this->temperature = BMP180_TEMP_CELSIUS;
        this->altitude = BMP180_UNIT_METRE;
    }

    virtual uint8_t getType() const { return 0; }

    float convertPressure(float pressure)
    {
        switch (this->pressure)
        {
        case BMP180_PRESSURE_PSI:
            pressureUnit = METRIC_UNIT_PSI;
            return pressure * 0.00014503773773;
        case BMP180_PRESSURE_BAR:
            pressureUnit = METRIC_UNIT_BAR;
            return pressure * 0.00001;
        case BMP180_PRESSURE_INCH_HG:
            pressureUnit = METRIC_UNIT_INCH_HG;
            return pressure * 0.000295299830714;
        case BMP180_PRESSURE_ATM:
            pressureUnit = METRIC_UNIT_ATM;
            return pressure * 0.00000986923;
        default:
            pressureUnit = METRIC_UNIT_PASCAL;
            return pressure;
        }
        return pressure;
    }

    float convertAltitude(float altitude)
    {
        switch (this->altitude)
        {
        case BMP180_UNIT_FEET:
            altitudeUnit = METRIC_UNIT_FEET;
            return altitude * 3.28084;
        default:
            altitudeUnit = METRIC_UNIT_METRE;
            return altitude;
        }
        return altitude;
    }

    float convertTemperature(float temperature)
    {
        switch (this->temperature)
        {
        case BMP180_TEMP_FAHRENHEIT:
            temperatureUnit = METRIC_UNIT_FAHRENHEIT;
            return (temperature * 9.0 / 5.0) + 32.0;
        case BMP180_TEMP_KELVIN:
            temperatureUnit = METRIC_UNIT_KELVIN;
            return temperature + 273.15;
        default:
            temperatureUnit = METRIC_UNIT_CELSIUS;
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
    /**
     * @brief Constructor for the ImperialSystem class.
     * @details Initializes the pressure, temperature, and altitude units to imperial values.
     */
    ImperialSystem()
    {
        this->pressure = BMP180_PRESSURE_PSI;
        this->temperature = BMP180_TEMP_FAHRENHEIT;
        this->altitude = BMP180_UNIT_FEET;
    }

    uint8_t getType() const override { return IMPERIAL_SYSTEM; }
};

/**
 * @brief InternationalSystem class for defining the international measurement system.
 * @details This class inherits from the MetricSystem class and sets the pressure, temperature, and altitude units to international values.
 * @author Saurav Sajeev
 */
class InternationalSystem : public MetricSystem
{
public:
    /**
     * @brief Constructor for the InternationalSystem class.
     * @details Initializes the pressure, temperature, and altitude units to international values.
     */
    InternationalSystem()
    {
        this->pressure = BMP180_PRESSURE_PASCAL;
        this->temperature = BMP180_TEMP_CELSIUS;
        this->altitude = BMP180_UNIT_METRE;
    }

    uint8_t getType() const override { return INTERNATIONAL_SYSTEM; }
};

#endif // METRIC_SYSTEM_PRIVATE_H
#endif // BMP180_H && __cplusplus
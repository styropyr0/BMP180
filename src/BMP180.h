#ifndef BMP180_H
#define BMP180_H

#include <Arduino.h>
#include <SensorHub.h>
#include "BMP180DEFS.h"
#include "MetricSystem.h"

#ifdef __cplusplus

/**
 * @brief BMP180 class for interfacing with the BMP180 sensor.
 * @details This class provides methods to initialize the sensor, read temperature, pressure, and altitude values.
 * @author Saurav Sajeev
 */
class BMP180
{
public:
    /**
     * @brief Constructor for the BMP180 class.
     * @details Initializes the sensor with the default I2C address.
     */
    BMP180();

    /**
     * @brief Initializes the BMP180 sensor.
     */
    bool begin();

    /**
     * @brief Reads the temperature from the BMP180 sensor.
     * @return The temperature in degrees Celsius.
     * @details This method reads the temperature value from the sensor and returns it in degrees Celsius.
     */
    float readTemperature();

    /**
     * @brief Reads the pressure from the BMP180 sensor.
     * @return The pressure in Pascals.
     * @details This method reads the pressure value from the sensor and returns it in Pascals.
     */
    float readPressure();

    /**
     * @brief Sets the oversampling setting for pressure measurement.
     * @param os The oversampling setting (0-3).
     * @details This method allows you to configure the oversampling setting for pressure measurement.
     */
    void setPressureOverSampling(uint8_t os);

    /**
     * @brief Reads the altitude from the BMP180 sensor.
     * @return The altitude in meters.
     * @details This method calculates the altitude based on the current pressure and a reference pressure.
     */
    float readAltitude();

    /**
     * @brief Returns the connection status of the sensor.
     * @return True if the sensor is connected, false otherwise.
     * @details This method checks if the sensor is connected to the I2C bus.
     * It is useful for verifying the sensor's presence before attempting to read data.
     */
    bool isConnected();

    /**
     * @brief Sets the metric system for the sensor.
     * @param metricSystem A custom metric system to be used. You may use the InternationalSystem or ImperialSystem objects.
     * @details This method allows you to set a custom metric system for the sensor.
     */
    void setMetricSystem(MetricSystem &metricSystem);

private:
    SensorHub sensorHub;
    uint8_t pres_oss = 0;
    int32_t UT = 0, UP = 0, B5;
    int16_t AC1, AC2, AC3, _B1, _B2, MB, MC, MD;
    uint16_t AC4, AC5, AC6;
    float pressure = 0.0;
    
    MetricSystem *metricSystem;

    bool readCalibParams();
    void readUT();
    void readUP();
};

#endif // __cplusplus
#endif // BMP180_H
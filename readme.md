# **BMP180 Arduino Library**

### **Overview**

The **BMP180 Arduino Library** provides an easy-to-use interface for the **BMP180 Barometric Pressure and Temperature Sensor**. With support for multiple metric systems, including **Imperial** and **International** units, this library offers temperature, pressure, and altitude data with customizable unit conversions.

### **Author**  
**Saurav Sajeev**

---

## **Table of Contents**
1. [Features](#1-features)  
2. [Hardware Requirements](#2-hardware-requirements)  
3. [Installation](#3-installation)  
4. [Library Structure](#4-library-structure)  
5. [Getting Started](#5-getting-started)  
6. [Detailed API Reference](#6-detailed-api-reference)  
7. [Constants Reference](#7-constants-reference)  
8. [Examples](#8-examples)  
9. [Troubleshooting](#9-troubleshooting)  
10. [Contributing](#10-contributing)  
11. [License](#11-license)

---

## **1. Features**
- **Temperature, Pressure, and Altitude Measurement**
- **Custom Metric System Support**:
  - Use **Imperial** or **International** systems
- **Pressure Oversampling Configuration**
- **Unit Conversion Utilities**:
  - Convert between °C/°F/K, Pa/psi/bar/inHg/atm, meters/feet
- **Sensor Connectivity Check**

---

## **2. Hardware Requirements**
- **Sensor**: BMP180 Digital Pressure Sensor
- **Microcontroller**: Arduino-compatible board (UNO, Mega, Nano)
- **Communication Protocol**: I2C
- **Connections**:
  - **VCC** → 3.3V or 5V
  - **GND** → GND
  - **SDA** → A4 (on UNO)
  - **SCL** → A5 (on UNO)

---

## **3. Installation**

### Using Arduino Library Manager
1. Open **Arduino IDE**
2. Go to **Sketch → Include Library → Manage Libraries**
3. Search for `BMP180` and click **Install**

### Manual Installation
1. Download the library from [GitHub](https://github.com/styropyr0/BMP180)
2. Open **Arduino IDE**
3. Go to **Sketch → Include Library → Add .ZIP Library**
4. Select the downloaded ZIP file

---

## **4. Library Structure**

### File Overview
- `BMP180.h / .cpp`: Main class for reading sensor data
- `MetricSystem.h`: Handles unit conversion logic
- `BMP180DEFS.h`: Constants for unit types and values

---

## **5. Getting Started**

### Basic Setup
```cpp
#include <BMP180.h>

BMP180 bmp;

void setup() {
    Serial.begin(9600);
    if (bmp.begin()) {
        Serial.println("BMP180 initialized!");
    } else {
        Serial.println("Sensor not found!");
    }
    bmp.setMetricSystem(ImperialSystem()); // You don't need to create a long lasting variable. RValues are also supported.
}

void loop() {
    Serial.print("Temperature: ");
    Serial.println(bmp.readTemperature());
    Serial.print("Pressure: ");
    Serial.println(bmp.readPressure());
    Serial.print("Altitude: ");
    Serial.println(bmp.readAltitude());
    delay(1000);
}
```

---

## **6. Detailed API Reference**

### Constructors
- **`BMP180()`**  
  Default constructor with I2C communication.

### Initialization
- **`bool begin()`**  
  Initializes the sensor and reads calibration data.

### Sensor Data
- **`float readTemperature()`**  
  Returns the temperature in °C (or converted unit).

- **`float readPressure()`**  
  Returns pressure in Pascals (or converted unit).

- **`float readAltitude()`**  
  Returns altitude in meters (or converted unit).

### Configuration
- **`void setPressureOverSampling(uint8_t os)`**  
  Set oversampling (0 to 3) for more accurate pressure readings.

- **`void setMetricSystem(MetricSystem &metricSystem)`**  
  Set a custom unit system. Use `InternationalSystem` or `ImperialSystem`.  
  You may also directly pass a dynamically declared object:
  ```cpp
  bmp.setMetricSystem(ImperialSystem());
  ```

### Utility
- **`bool isConnected()`**  
  Returns `true` if sensor is detected on the I2C bus.

### Unit Accessors
- **`String getTemperatureUnit()`**  
  Returns current temperature unit (`"°C"`, `"°F"`, `"K"`)

- **`String getPressureUnit()`**  
  Returns current pressure unit (`"Pa"`, `"psi"`, `"bar"`, `"inHg"`, `"atm"`)

- **`String getAltitudeUnit()`**  
  Returns current altitude unit (`"m"`, `"ft"`)

---

## **7. Constants Reference**

### Temperature Units
| Constant                | Unit         |
|-------------------------|--------------|
| `BMP180_UNIT_CELSIUS`   | °C           |
| `BMP180_UNIT_FAHRENHEIT`| °F           |
| `BMP180_UNIT_KELVIN`    | K            |

### Pressure Units
| Constant               | Unit  |
|------------------------|-------|
| `BMP180_UNIT_PASCAL`| Pa   |
| `BMP180_UNIT_PSI`   | psi  |
| `BMP180_UNIT_BAR`   | bar  |
| `BMP180_UNIT_INCH_HG`| inHg|
| `BMP180_UNIT_ATM`   | atm  |

### Altitude Units
| Constant             | Unit   |
|----------------------|--------|
| `BMP180_UNIT_METRE`  | meter  |
| `BMP180_UNIT_FEET`   | feet   |

---

## **8. Examples**

### Example 1: Use Imperial Units
```cpp
#include <BMP180.h>

BMP180 bmp;
ImperialSystem imperial;

void setup() {
    Serial.begin(9600);
    bmp.setMetricSystem(imperial);
    bmp.begin();
}

void loop() {
    Serial.print("Temp: ");
    Serial.print(bmp.readTemperature());
    Serial.println(" " + imperial.temperatureUnit);

    Serial.print("Pressure: ");
    Serial.print(bmp.readPressure());
    Serial.println(" " + imperial.pressureUnit);

    Serial.print("Altitude: ");
    Serial.print(bmp.readAltitude());
    Serial.println(" " + imperial.altitudeUnit);

    delay(1000);
}
```

### Example 2: Set Oversampling
```cpp
#include <BMP180.h>

BMP180 bmp;

void setup() {
    Serial.begin(9600);
    bmp.begin();
    bmp.setPressureOverSampling(3); // Highest oversampling
}

void loop() {
    Serial.println("Pressure: " + String(bmp.readPressure()) + " Pa");
    delay(1000);
}
```

---

## **9. Troubleshooting**

| Issue                        | Solution |
|-----------------------------|----------|
| No sensor detected          | Check I2C wiring and address |
| Constant 0 readings         | Ensure `begin()` is called and returns `true` |
| Wrong values for units      | Ensure correct `MetricSystem` is used |
| Compilation errors          | Check if all dependencies are installed |

---

## **10. Contributing**

Want to contribute? Here's how:

1. **Fork the repo**  
   ```bash
   git clone https://github.com/<your-repo>/BMP180.git
   ```
2. **Create a feature branch**  
   ```bash
   git checkout -b your-feature
   ```
3. **Push and create a Pull Request**

---

## **11. License**

This library is licensed under the **MIT License**.  
See the [LICENSE](LICENSE) file for full terms.

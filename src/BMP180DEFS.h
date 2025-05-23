#ifndef BMP180DEFS
#define BMP180DEFS

#ifdef __cplusplus

// BMP180 I2C Address
#define BMP180_I2C_ADDR 0x77

// BMP180 Registers
#define BMP180_AC1_CAL_REG 0xAA
#define BMP180_AC2_CAL_REG 0xAC
#define BMP180_AC3_CAL_REG 0xAE
#define BMP180_AC4_CAL_REG 0xB0
#define BMP180_AC5_CAL_REG 0xB2
#define BMP180_AC6_CAL_REG 0xB4
#define BMP180_B1_CAL_REG 0xB6
#define BMP180_B2_CAL_REG 0xB8
#define BMP180_MB_CAL_REG 0xBA
#define BMP180_MC_CAL_REG 0xBC
#define BMP180_MD_CAL_REG 0xBE

// Control Registers
#define BMP180_CTRL_TEMP_MEAS_REG 0xF4
#define BMP180_CTRL_PRESS_MEAS_REG 0xF4
#define BMP180_TEMP_MEAS_REG 0xF6
#define BMP180_PRESS_MEAS_REG 0xF6
#define BMP180_TEMP_START_MEAS 0x2E
#define BMP180_PRESS_START_MEAS 0x34

// Measurement Systems
#define INTERNATIONAL_SYSTEM 0
#define IMPERIAL_SYSTEM 1
#define CUSTOM_SYSTEM 2

// Altitude
#define BMP180_UNIT_METRE 90
#define BMP180_UNIT_FEET 91

// Temperature
#define BMP180_UNIT_CELSIUS 110
#define BMP180_UNIT_FAHRENHEIT 111
#define BMP180_UNIT_KELVIN 112

// Pressure
#define BMP180_UNIT_PASCAL 120
#define BMP180_UNIT_PSI 121
#define BMP180_UNIT_BAR 122
#define BMP180_UNIT_INCH_HG 123
#define BMP180_UNIT_ATM 124

// Units
#define METRIC_UNIT_METRE "m"
#define METRIC_UNIT_FEET "ft"
#define METRIC_UNIT_CELSIUS "°C"
#define METRIC_UNIT_FAHRENHEIT "°F"
#define METRIC_UNIT_KELVIN "K"
#define METRIC_UNIT_PASCAL "Pa"
#define METRIC_UNIT_PSI "psi"
#define METRIC_UNIT_BAR "bar"
#define METRIC_UNIT_INCH_HG "inHg"
#define METRIC_UNIT_ATM "atm"

#endif // __cplusplus
#endif // BMP180DEFS
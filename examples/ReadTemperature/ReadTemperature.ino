#include <BMP180.h>

BMP180 bmp180;

void setup()
{
    Serial.begin(9600);
    if (!bmp180.begin())
    {
        Serial.println("BMP180 not found!");
        while (1);
    }
}

void loop()
{
    Serial.print("Temperature: ");
    Serial.print(bmp180.readTemperature());
    Serial.println(" °C");

    delay(2000);
}
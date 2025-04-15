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
    Serial.print("Pressure: ");
    Serial.print(bmp180.readPressure());
    Serial.println(" Pa");

    delay(2000);
}
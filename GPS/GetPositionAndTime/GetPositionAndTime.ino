
#include <Wire.h> //Needed for I2C to GPS

#include "SparkFun_Ublox_Arduino_Library_Series_6_7.h"
SFE_UBLOX_GPS myGPS;

long lastTime = 0; //Simple local timer. Limits amount if I2C traffic to Ublox module.

void setup()
{
  Serial.begin(115200);
  while (!Serial); //Wait for user to open terminal
  Serial.println("SparkFun Ublox Example");

  Wire.begin();

  //myGPS.enableDebugging(); // Uncomment this line to enable debug messages

  if (myGPS.begin() == false) //Connect to the Ublox module using Wire port
  {
    Serial.println(F("Ublox GPS not detected at default I2C address. Please check wiring. Freezing."));
    while (1);
  }

  myGPS.setI2COutput(COM_TYPE_UBX); //Set the I2C port to output UBX only (turn off NMEA noise)
  myGPS.saveConfiguration(); //Save the current settings to flash and BBR
}

void loop()
{
  //Query module only every second. Doing it more often will just cause I2C traffic.
  //The module only responds when a new position is available
  if (millis() - lastTime > 1000)
  {
    lastTime = millis(); //Update the timer
    
    long latitude = myGPS.getLatitude();
    Serial.print(F("Lat: "));
    Serial.print(latitude);

    long longitude = myGPS.getLongitude();
    Serial.print(F(" Long: "));
    Serial.print(longitude);
    Serial.print(F(" (degrees * 10^-7)"));

    long altitude = myGPS.getAltitude();
    Serial.print(F(" Alt: "));
    Serial.print(altitude);
    Serial.print(F(" (mm)"));

    Serial.print(F(" Time: "));

    byte Hour = myGPS.getHour();
    if (Hour < 10)
    {
      Serial.print(F("0"));
    }
    Serial.print(Hour);
    Serial.print(F(":"));

    byte Minute = myGPS.getMinute();
    if (Minute < 10)
    {
      Serial.print(F("0"));
    }
    Serial.print(Minute);
    Serial.print(F(":"));

    byte Second = myGPS.getSecond();
    if (Second < 10)
    {
      Serial.print(F("0"));
    }
    Serial.print(Second);

    Serial.println();
  }
}

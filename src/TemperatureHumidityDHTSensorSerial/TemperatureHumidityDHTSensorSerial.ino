#include <Arduino.h>
#include <EEPROM.h>

#include <duinocom.h>

#include "Common.h"
#include "TemperatureHumidityDHTSensor.h"

#define SERIAL_MODE_CSV 1
#define SERIAL_MODE_QUERYSTRING 2

#define VERSION "1-0-0-0"
#define BOARD_TYPE "uno"

int serialMode = SERIAL_MODE_CSV;

void setup()
{
  Serial.begin(9600);

  Serial.println("Starting temperature humidity monitor");

  serialPrintDeviceInfo();
  
  setupTemperatureHumidityDHTSensor();

  serialOutputIntervalInSeconds = temperatureHumidityDHTSensorReadingIntervalInSeconds;
}

void loop()
{
  loopNumber++;

  serialPrintLoopHeader();

  checkCommand();

  takeTemperatureHumidityDHTSensorReading();

  serialPrintData();

  serialPrintLoopFooter();

  delay(1);
}

/* Commands */
void checkCommand()
{
  if (isDebugMode)
  {
    Serial.println("Checking incoming serial commands");
  }

  if (checkMsgReady())
  {
    char* msg = getMsg();
        
    char letter = msg[0];

    int length = strlen(msg);

    Serial.print("Received message: ");
    Serial.println(msg);

    switch (letter)
    {
      case '#':
        serialPrintDeviceInfo();
        break;
      case 'I':
        setTemperatureHumidityDHTSensorReadingInterval(msg);
        break;
      case 'X':
        restoreDefaultSettings();
        break;
      case 'Z':
        Serial.println("Toggling isDebugMode");
        isDebugMode = !isDebugMode;
        break;
    }

    forceSerialOutput();
  }
  delay(1);
}

void serialPrintDeviceInfo()
{
  Serial.println("");
  Serial.println("-- Start Device Info");
  Serial.println("Family: GreenSense");
  Serial.println("Group: monitor");
  Serial.println("Project: TemperatureHumidityDHTSensorSerial");
  Serial.print("Board: ");
  Serial.println(BOARD_TYPE);
  Serial.print("Version: ");
  Serial.println(VERSION);
  Serial.println("ScriptCode: temperature-humidity-monitor");
  Serial.println("-- End Device Info");
  Serial.println("");
}

/* Settings */
void restoreDefaultSettings()
{
  Serial.println("Restoring default settings");

  restoreDefaultTemperatureHumidityDHTSensorSettings();
}

/* Serial Output */
void serialPrintData()
{
  bool isTimeToPrintData = lastSerialOutputTime + secondsToMilliseconds(serialOutputIntervalInSeconds) < millis()
      || lastSerialOutputTime == 0;

  bool isReadyToPrintData = isTimeToPrintData && temperatureHumidityDHTSensorReadingHasBeenTaken;

  if (isReadyToPrintData)
  {
    if (isDebugMode)
      Serial.println("Ready to serial print data");
  
    long numberOfSecondsOnline = millis()/1000;

    if (serialMode == SERIAL_MODE_CSV)
    {
      Serial.print("D;"); // This prefix indicates that the line contains data.
      //Serial.print("T:");
      //Serial.print(numberOfSecondsOnline);
      //Serial.print(";");
      Serial.print("T:");
      Serial.print(temperatureValue);
      Serial.print(";");
      Serial.print("H:");
      Serial.print(humidityValue);
      Serial.print(";");
      Serial.print("I:");
      Serial.print(temperatureHumidityDHTSensorReadingIntervalInSeconds);
      Serial.print(";");
      Serial.print("V:");
      Serial.print(VERSION);
      Serial.print(";;");
      Serial.println();
    }
    else if (serialMode == SERIAL_MODE_QUERYSTRING)
    {
      //Serial.print("time=");
      //Serial.print(numberOfSecondsOnline);
      //Serial.print("&");
      Serial.print("temperature=");
      Serial.print(temperatureValue);
      Serial.print("&");
      Serial.print("humidity=");
      Serial.print(humidityValue);
      Serial.print("&");
      Serial.print("readInterval=");
      Serial.print(temperatureHumidityDHTSensorReadingIntervalInSeconds);
      Serial.println();
    }

    lastSerialOutputTime = millis();
  }
  else
  {
    if (isDebugMode)
    {    
      Serial.println("Not ready to serial print data");

      Serial.print("  Is time to serial print data: ");
      Serial.println(isTimeToPrintData);
      if (!isTimeToPrintData)
      {
        Serial.print("    Time remaining before printing data: ");
        Serial.print(millisecondsToSecondsWithDecimal(lastSerialOutputTime + secondsToMilliseconds(serialOutputIntervalInSeconds) - millis()));
        Serial.println(" seconds");
      }
      Serial.print("  Soil moisture sensor reading has been taken: ");
      Serial.println(temperatureHumidityDHTSensorReadingHasBeenTaken);
      Serial.print("  Is ready to print data: ");
      Serial.println(isReadyToPrintData);

    }
  }
}

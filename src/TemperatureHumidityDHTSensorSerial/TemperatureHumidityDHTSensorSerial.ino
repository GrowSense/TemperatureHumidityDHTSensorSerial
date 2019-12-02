#include <Arduino.h>
#include <EEPROM.h>

#include <duinocom2.h>

#include "Common.h"
#include "SerialOutput.h"
#include "Commands.h"
#include "DeviceName.h"
#include "TemperatureHumidityDHTSensor.h"

void setup()
{
  Serial.begin(9600);

  Serial.println("Starting temperature humidity monitor");
  
  loadDeviceNameFromEEPROM();

  serialPrintDeviceInfo();
  
  setupTemperatureHumidityDHTSensor();

  serialOutputIntervalInSeconds = temperatureHumidityDHTSensorReadingIntervalInSeconds;
  
  Serial.println("Online");
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

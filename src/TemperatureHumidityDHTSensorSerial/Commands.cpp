#include <Arduino.h>
#include <EEPROM.h>

#include "Commands.h"
#include "DeviceName.h"
#include "SerialOutput.h"

void checkCommand()
{
  /*if (isDebugMode)
  {
    Serial.println("Checking incoming serial commands");
  }*/

  if (checkMsgReady())
  {
    char* msg = getMsg();
       
    handleCommand(msg);
  }
}

void handleCommand(char* msg)
{
  if (isDebugMode)
  {
    Serial.println("");
    Serial.println("Handling command...");  
  }

  Serial.print("Received message: ");
  Serial.println(msg);
        
  char letter = msg[0];

  Serial.print("Received message: ");
  Serial.println(msg);

  if (isKeyValue(msg))
  {
    Serial.println("  Is key value");
  
    char* key = getKey(msg);
  
    Serial.print("  Key: \"");
    Serial.print(key);
    Serial.println("\"");
  
    char* value = getValue(msg);
  
    Serial.print("  Value: \"");
    Serial.print(value);
    Serial.println("\"");

    if (strcmp(key, "Name") == 0)
    {
      if (isDebugMode)
        Serial.println("  Set device name");
      setDeviceName(value);
    }
  }
  else
  {
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
  }
  
  forceSerialOutput();
  
  if (isDebugMode)
  {
    Serial.println("");
  }
}

void restoreDefaultSettings()
{
  Serial.println("Restoring default settings");

  restoreDefaultTemperatureHumidityDHTSensorSettings();
  
  EEPROMReset();
}

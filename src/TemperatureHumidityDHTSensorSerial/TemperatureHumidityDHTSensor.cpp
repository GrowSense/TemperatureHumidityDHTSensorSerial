#include <Arduino.h>
#include <EEPROM.h>
#include <DHT.h>

#include <duinocom2.h>

#include "Common.h"
#include "EEPROMHelper.h"
#include "SerialOutput.h"
#include "TemperatureHumidityDHTSensor.h"

DHT dht;

#define DHT11_PIN 7

#define temperatureHumidityDHTSensorPin A0
#define temperatureHumidityDHTSensorPowerPin 12

bool temperatureHumidityDHTSensorIsEnabled = true;
unsigned long lastSensorOnTime = 0;

bool temperatureHumidityDHTSensorReadingHasBeenTaken = false;
long temperatureHumidityDHTSensorReadingIntervalInSeconds = 5;
unsigned long lastTemperatureHumidityDHTSensorReadingTime = 0; // Milliseconds
int minimumTemperatureHumidityDHTSensorReadingIntervalInSeconds = 3;

int temperatureValue = 0;
int humidityValue = 0;

#define temperatureHumidityDHTSensorReadIntervalIsSetFlagAddress 10
#define temperatureHumidityDHTSensorReadingIntervalAddress 13

/* Setup */
void setupTemperatureHumidityDHTSensor()
{
  if (isDebugMode)
    Serial.println("Setting up temperature humidity DHT sensor...");

  dht.setup(DHT11_PIN);

  delay(dht.getMinimumSamplingPeriod());

  setupTemperatureHumidityDHTSensorReadingInterval();

  pinMode(temperatureHumidityDHTSensorPowerPin, OUTPUT);
}

/* Sensor Readings */
void takeTemperatureHumidityDHTSensorReading()
{
  bool sensorReadingIsDue = millis() - lastTemperatureHumidityDHTSensorReadingTime >= secondsToMilliseconds(temperatureHumidityDHTSensorReadingIntervalInSeconds)
    || lastTemperatureHumidityDHTSensorReadingTime == 0;

  /*Serial.print("Sensor reading due: ");
  Serial.println(sensorReadingIsDue);
  Serial.print("Last reading time: ");
  Serial.println(lastTemperatureHumidityDHTSensorReadingTime);
  Serial.print("Interval: ");
  Serial.println(temperatureHumidityDHTSensorReadingIntervalInSeconds * 1000);
  Serial.print("Millis: ");
  Serial.println(millis());*/

  if (sensorReadingIsDue && temperatureHumidityDHTSensorIsEnabled)
  {
    if (isDebugMode)
      Serial.println("Sensor reading is due");


    //if (isDebugMode)
    //  Serial.println("Preparing to take reading");


    //delay(dht.getMinimumSamplingPeriod());

    humidityValue = dht.getHumidity();

    if (isnan(humidityValue))
      humidityValue = 0;

    temperatureValue = dht.getTemperature();

    if (isnan(temperatureValue))
      temperatureValue = 0;

    /*if (isDebugMode)
    {
      Serial.println("Humidity:");
      Serial.println(humidityValue);
      Serial.println("Temperature:");
      Serial.println(temperatureValue);
    }*/

    temperatureHumidityDHTSensorReadingHasBeenTaken = true;
    lastTemperatureHumidityDHTSensorReadingTime = millis();
  }
}

/* Temperature/Humidity */
void setTemperature(char* msg)
{
    int value = readInt(msg, 1, strlen(msg)-1);

    setTemperature(value);
}

void setTemperature(long newValue)
{
  /*if (isDebugMode)
  {
    Serial.print("Set temperature: ");
    Serial.println(newValue);
  }*/

  temperatureValue = newValue;
}

void setHumidity(char* msg)
{
  int value = readInt(msg, 1, strlen(msg)-1);

  setHumidity(value);
}

void setHumidity(long newValue)
{
  /*if (isDebugMode)
  {
    Serial.print("Set humidity: ");
    Serial.println(newValue);
  }*/

  humidityValue = newValue;
}

/* Reading interval */
void setupTemperatureHumidityDHTSensorReadingInterval()
{
  if (EEPROMFlagIsSet(temperatureHumidityDHTSensorReadIntervalIsSetFlagAddress))
  {
    if (isDebugMode)
    	Serial.println("EEPROM read interval value has been set. Loading.");

    temperatureHumidityDHTSensorReadingIntervalInSeconds = getTemperatureHumidityDHTSensorReadingInterval();
  }
  /*else
  {
    if (isDebugMode)
      Serial.println("EEPROM read interval value has not been set. Using defaults.");
  }*/
}

void setTemperatureHumidityDHTSensorReadingInterval(char* msg)
{
    int value = readInt(msg, 1, strlen(msg)-1);

    setTemperatureHumidityDHTSensorReadingInterval(value);
}

void setTemperatureHumidityDHTSensorReadingInterval(long newValue)
{
  /*if (isDebugMode)
  {
    Serial.print("Set sensor reading interval: ");
    Serial.println(newValue);
  }*/

  // Set minimum interval to avoid issues with reading from the sensor too quickly
  if (newValue < minimumTemperatureHumidityDHTSensorReadingIntervalInSeconds)
  {
    Serial.print("Setting interval to ");
    Serial.print(minimumTemperatureHumidityDHTSensorReadingIntervalInSeconds);
    Serial.println(" seconds. The DHT sensor cannot support faster readings.");
    newValue = minimumTemperatureHumidityDHTSensorReadingIntervalInSeconds;
  }

  EEPROMWriteLong(temperatureHumidityDHTSensorReadingIntervalAddress, newValue);

  EEPROMSetFlag(temperatureHumidityDHTSensorReadIntervalIsSetFlagAddress);

  temperatureHumidityDHTSensorReadingIntervalInSeconds = newValue;

  serialOutputIntervalInSeconds = newValue;
}

long getTemperatureHumidityDHTSensorReadingInterval()
{
  long value = EEPROMReadLong(temperatureHumidityDHTSensorReadingIntervalAddress);

  if (value == 0
      || value == 255)
    return temperatureHumidityDHTSensorReadingIntervalInSeconds;
  else
  {
    /*if (isDebugMode)
    {
      Serial.print("Read interval found in EEPROM: ");
      Serial.println(value);
    }*/

    return value;
  }
}

void restoreDefaultTemperatureHumidityDHTSensorSettings()
{
  restoreDefaultTemperatureHumidityDHTSensorReadingIntervalSettings();
}

void restoreDefaultTemperatureHumidityDHTSensorReadingIntervalSettings()
{
  EEPROMRemoveFlag(temperatureHumidityDHTSensorReadIntervalIsSetFlagAddress);

  temperatureHumidityDHTSensorReadingIntervalInSeconds = 5;
  serialOutputIntervalInSeconds = 5;

  setTemperatureHumidityDHTSensorReadingInterval(temperatureHumidityDHTSensorReadingIntervalInSeconds);
}


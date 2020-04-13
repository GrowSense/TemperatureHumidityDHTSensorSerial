#ifndef TEMPERATUREHUMIDITYDHTSENSOR_H_
#define TEMPERATUREHUMIDITYDHTSENSOR_H_

extern int temperatureValue;
extern int humidityValue;

extern unsigned long lastTemperatureHumidityDHTSensorReadingTime;
extern long temperatureHumidityDHTSensorReadingIntervalInSeconds;
extern int temperatureHumidityDHTSensorReadIntervalIsSetFlagAddress;
extern int minimumTemperatureHumidityDHTSensorReadingIntervalInSeconds;

extern int drySoilMoistureCalibrationValue;
extern int wetSoilMoistureCalibrationValue;

extern bool temperatureHumidityDHTSensorIsEnabled;
extern unsigned long lastSensorOnTime;
extern bool temperatureHumidityDHTSensorReadingHasBeenTaken;

void setupTemperatureHumidityDHTSensor();

void setupTemperatureHumidityDHTSensorReadingInterval();

void turnTemperatureHumidityDHTSensorOn();

void turnTemperatureHumidityDHTSensorOff();

void takeTemperatureHumidityDHTSensorReading();

void setTemperature(char* msg);
void setTemperature(long temperature);

void setHumidity(char* msg);
void setHumidity(long humidity);

void setTemperatureHumidityDHTSensorReadingInterval(char* msg);
void setTemperatureHumidityDHTSensorReadingInterval(long readInterval);

long getTemperatureHumidityDHTSensorReadingInterval();

void restoreDefaultTemperatureHumidityDHTSensorSettings();
void restoreDefaultTemperatureHumidityDHTSensorReadingIntervalSettings();
#endif
/* TEMPERATUREHUMIDITYDHTSENSOR_H_ */

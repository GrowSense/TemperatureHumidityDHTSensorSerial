#ifndef SOILMOISTURESENSOR_H_
#define SOILMOISTURESENSOR_H_

extern float temperatureValue;
extern float humidityValue;

extern unsigned long lastTemperatureHumidityDHTSensorReadingTime;
extern long temperatureHumidityDHTSensorReadingIntervalInSeconds;
extern int temperatureHumidityDHTSensorReadIntervalIsSetFlagAddress;

extern int drySoilMoistureCalibrationValue;
extern int wetSoilMoistureCalibrationValue;

extern bool temperatureHumidityDHTSensorIsOn;
extern unsigned long lastSensorOnTime;
extern int delayAfterTurningSensorOn;
extern bool temperatureHumidityDHTSensorReadingHasBeenTaken;

void setupTemperatureHumidityDHTSensor();

void setupCalibrationValues();

void setupTemperatureHumidityDHTSensorReadingInterval();

void turnTemperatureHumidityDHTSensorOn();

void turnTemperatureHumidityDHTSensorOff();

void takeTemperatureHumidityDHTSensorReading();

double getAverageTemperatureHumidityDHTSensorReading();

double calculateSoilMoistureLevel(int temperatureHumidityDHTSensorReading);

void setEEPROMIsCalibratedFlag();

void setTemperatureHumidityDHTSensorReadingInterval(char* msg);
void setTemperatureHumidityDHTSensorReadingInterval(long readInterval);

long getTemperatureHumidityDHTSensorReadingInterval();

void setEEPROMTemperatureHumidityDHTSensorReadingIntervalIsSetFlag();
void removeEEPROMTemperatureHumidityDHTSensorReadingIntervalIsSetFlag();

void setDrySoilMoistureCalibrationValue(char* msg);

void setDrySoilMoistureCalibrationValueToCurrent();

void setDrySoilMoistureCalibrationValue(int drySoilMoistureCalibrationValue);

void setWetSoilMoistureCalibrationValue(char* msg);

void setWetSoilMoistureCalibrationValueToCurrent();

void setWetSoilMoistureCalibrationValue(int wetSoilMoistureCalibrationValue);

void reverseSoilMoistureCalibrationValues();

int getDrySoilMoistureCalibrationValue();

int getWetSoilMoistureCalibrationValue();

void setEEPROMIsCalibratedFlag();

void removeEEPROMIsCalibratedFlag();

void restoreDefaultTemperatureHumidityDHTSensorSettings();
void restoreDefaultTemperatureHumidityDHTSensorReadingIntervalSettings();
void restoreDefaultCalibrationSettings();
#endif
/* SOILMOISTURESENSOR_H_ */

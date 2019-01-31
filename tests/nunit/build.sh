echo "Starting build for project"
echo "Dir: $PWD"

DIR=$PWD

xbuild src/TemperatureHumidityDHTSensorSerial.sln /p:Configuration=Release

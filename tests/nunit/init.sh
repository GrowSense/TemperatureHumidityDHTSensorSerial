echo "Initializing nunit tests for TemperatureHumidityDHTSensorSerial project"

DIR=$PWD

cd lib && \
sh get-libs.sh && \
cd $DIR

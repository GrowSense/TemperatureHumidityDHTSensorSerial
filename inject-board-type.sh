BOARD_TYPE=$1

if [ ! $BOARD_TYPE ]; then
  echo "Provide a board type as an argument. For example 'nano' or 'uno'."
  exit 1
fi

echo "Injecting board type into sketch..."
echo "  Board type: $BOARD_TYPE"

SOURCE_FILE="src/TemperatureHumidityDHTSensorSerial/Common.h"

echo "  Source file:"
echo "    $SOURCE_FILE"

sed -i "s/#define BOARD_TYPE .*/#define BOARD_TYPE \"$BOARD_TYPE\"/" $SOURCE_FILE || exit 1

echo "Finished injecting board type into sketch."

PORT_NAME=$1

if [ ! $PORT_NAME ]; then
  PORT_NAME="/dev/ttyUSB0"
fi

echo "Port: $PORT_NAME"

bash inject-board-type.sh uno || exit 1

pio run --target upload --environment=uno --upload-port=$PORT_NAME || exit 1

using System;
namespace TemperatureHumidityDHTSensorSerial.Tests.Integration
{
	public class ReadIntervalCommandTestHelper : GrowSenseHardwareTestHelper
	{
		public int ReadInterval = 1;

		public ReadIntervalCommandTestHelper()
		{
		}

		public void TestSetReadIntervalCommand()
		{
			WriteTitleText("Starting read interval command test");

			Console.WriteLine("Read interval: " + ReadInterval);

			ConnectDevices(false);

			SetDeviceReadInterval(ReadInterval);

			var dataEntry = WaitForDataEntry();

			AssertDataValueEquals(dataEntry, "I", ReadInterval);
		}
	}
}

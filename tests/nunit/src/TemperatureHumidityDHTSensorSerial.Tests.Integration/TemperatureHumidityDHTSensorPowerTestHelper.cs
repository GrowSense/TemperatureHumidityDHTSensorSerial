using System;
using System.Threading;
using NUnit.Framework;
namespace TemperatureHumidityDHTSensorSerial.Tests.Integration
{
	public class TemperatureHumidityDHTSensorPowerTestHelper : GreenSenseHardwareTestHelper
	{
		public int ReadInterval = 1;

		public void TestTemperatureHumidityDHTSensorPower()
		{
			WriteTitleText("Starting soil moisture sensor power test");

			ConnectDevices();

			SetDeviceReadInterval(ReadInterval);

			var data = WaitForDataEntry();

			AssertDataValueEquals(data, "I", ReadInterval);

			var sensorDoesTurnOff = ReadInterval > DelayAfterTurningTemperatureHumidityDHTSensorOn;

			if (sensorDoesTurnOff)
			{
				Console.WriteLine("The soil moisture sensor should turn off when not in use.");

				TestTemperatureHumidityDHTSensorPowerTurnsOnAndOff();
			}
			else
			{
				Console.WriteLine("The soil moisture sensor should stay on permanently.");

				TestTemperatureHumidityDHTSensorPowerStaysOn();
			}
		}

		public void TestTemperatureHumidityDHTSensorPowerStaysOn()
		{
			WriteParagraphTitleText("Waiting until the soil moisture sensor is on before starting the test...");

			WaitUntilTemperatureHumidityDHTSensorPowerPinIs(On);

			var durationInSeconds = ReadInterval * 5;

			WriteParagraphTitleText("Checking that soil moisture sensor power pin stays on...");

			AssertTemperatureHumidityDHTSensorPowerPinForDuration(On, durationInSeconds);
		}

		public void TestTemperatureHumidityDHTSensorPowerTurnsOnAndOff()
		{
			WriteParagraphTitleText("Waiting until the soil moisture sensor has turned on then off before starting the test...");

			WaitUntilTemperatureHumidityDHTSensorPowerPinIs(On);
			WaitUntilTemperatureHumidityDHTSensorPowerPinIs(Off);

			CheckTemperatureHumidityDHTSensorOnDuration();
			CheckTemperatureHumidityDHTSensorOffDuration();
		}

		public void CheckTemperatureHumidityDHTSensorOnDuration()
		{
			WriteParagraphTitleText("Getting the total on time...");

			var totalOnTime = WaitWhileTemperatureHumidityDHTSensorPowerPinIs(On);

			WriteParagraphTitleText("Checking the total on time is correct...");

			var expectedOnTime = DelayAfterTurningTemperatureHumidityDHTSensorOn;

			AssertIsWithinRange("total on time", expectedOnTime, totalOnTime, TimeErrorMargin);
		}

		public void CheckTemperatureHumidityDHTSensorOffDuration()
		{
			WriteParagraphTitleText("Getting the total off time...");

			var totalOffTime = WaitWhileTemperatureHumidityDHTSensorPowerPinIs(Off);

			WriteParagraphTitleText("Checking the total off time is correct...");

			var expectedOffTime = ReadInterval - DelayAfterTurningTemperatureHumidityDHTSensorOn;

			AssertIsWithinRange("total off time", expectedOffTime, totalOffTime, TimeErrorMargin);
		}
	}
}

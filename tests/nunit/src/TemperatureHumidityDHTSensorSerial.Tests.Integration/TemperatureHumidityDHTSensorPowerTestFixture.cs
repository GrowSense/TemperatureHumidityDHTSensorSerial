using System;
using NUnit.Framework;

namespace TemperatureHumidityDHTSensorSerial.Tests.Integration
{
	[TestFixture(Category = "Integration")]
	public class TemperatureHumidityDHTSensorPowerTestFixture : BaseTestFixture
	{
		[Test]
		public void Test_TemperatureHumidityDHTSensorPower_AlwaysOn_1SecondReadInterval()
		{
			using (var helper = new TemperatureHumidityDHTSensorPowerTestHelper())
			{
				helper.ReadInterval = 1;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestTemperatureHumidityDHTSensorPower();
			}
		}

		[Test]
		public void Test_TemperatureHumidityDHTSensorPower_AlwaysOn_3SecondReadInterval()
		{
			using (var helper = new TemperatureHumidityDHTSensorPowerTestHelper())
			{
				helper.ReadInterval = 3;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestTemperatureHumidityDHTSensorPower();
			}
		}

		[Test]
		public void Test_TemperatureHumidityDHTSensorPower_OnAndOff_4SecondReadInterval()
		{
			using (var helper = new TemperatureHumidityDHTSensorPowerTestHelper())
			{
				helper.ReadInterval = 4;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestTemperatureHumidityDHTSensorPower();
			}
		}
		[Test]
		public void Test_TemperatureHumidityDHTSensorPower_OnAndOff_6SecondReadInterval()
		{
			using (var helper = new TemperatureHumidityDHTSensorPowerTestHelper())
			{
				helper.ReadInterval = 6;

				helper.DevicePort = GetDevicePort();
				helper.DeviceBaudRate = GetDeviceSerialBaudRate();

				helper.SimulatorPort = GetSimulatorPort();
				helper.SimulatorBaudRate = GetSimulatorSerialBaudRate();

				helper.TestTemperatureHumidityDHTSensorPower();
			}
		}
	}
}

﻿using System;
using System.Threading;
using NUnit.Framework;

namespace TemperatureHumidityDHTSensorSerial.Tests.Integration
{
  public class GrowSenseHardwareTestHelper : HardwareTestHelper
  {
    public int SoilMoistureSimulatorPin = 9;
    public int SoilMoistureSimulatorPowerPin = 3;
    public int DelayAfterTurningTemperatureHumidityDHTSensorOn = 3;
    public int RawValueMarginOfError = 27;
    public int CalibratedValueMarginOfError = 3;
    public double TimeErrorMargin = 0.2;
    public bool CalibrationIsReversedByDefault = true;
    public bool RequiresResetSettings = true;

    public GrowSenseHardwareTestHelper ()
    {
    }
    #region Enable Devices Functions
    public override void ConnectDevices (bool enableSimulator)
    {
      Console.WriteLine ("Connecting devices...");

      base.ConnectDevices (enableSimulator);

      PrepareDeviceForTest ();
    }
    #endregion
    #region Prepare Device Functions
    public virtual void PrepareDeviceForTest ()
    {
      PrepareDeviceForTest (true);
    }

    public virtual void PrepareDeviceForTest (bool consoleWriteDeviceOutput)
    {
      Console.WriteLine ("Preparing device for test...");

      if (RequiresResetSettings) {
        ResetDeviceSettings ();

        SetDeviceReadInterval (3);
      }

      if (consoleWriteDeviceOutput)
        ReadFromDeviceAndOutputToConsole ();
    }
    #endregion
    #region General Device Command Settings
    public void SendDeviceCommand (string command)
    {
      WriteToDevice (command);

      WaitForMessageReceived (command);
    }

    public void WaitForMessageReceived (string message)
    {
      Console.WriteLine ("");
      Console.WriteLine ("Waiting for message: " + message);

      var output = String.Empty;
      var wasMessageReceived = false;

      Timeout.Start ();
                     
      while (!wasMessageReceived) {
        output += ReadLineFromDevice ();

        var expectedText = "Received message: " + message;
        if (output.Contains (expectedText)) {
          wasMessageReceived = true;

          Console.WriteLine ("  Message was received");

          ConsoleWriteSerialOutput (output);
        } else
          Timeout.Check (TimeoutWaitingForResponse, "Timed out waiting for text '" + expectedText + "'.");
      }
    }
    #endregion
    #region Specific Device Command Functions
    public void ResetDeviceSettings ()
    {
      var cmd = "X";

      Console.WriteLine ("");
      Console.WriteLine ("Resetting device default settings...");
      Console.WriteLine ("  Sending '" + cmd + "' command to device");
      Console.WriteLine ("");

      SendDeviceCommand (cmd);
    }

    public void SetDeviceReadInterval (int numberOfSeconds)
    {
      var cmd = "I" + numberOfSeconds;

      Console.WriteLine ("");
      Console.WriteLine ("Setting device read interval to " + numberOfSeconds + " second(s)...");
      Console.WriteLine ("  Sending '" + cmd + "' command to device");
      Console.WriteLine ("");

      SendDeviceCommand (cmd);
    }

    public void ReverseDeviceCalibration ()
    {
      var cmd = "R";

      Console.WriteLine ("");
      Console.WriteLine ("Reversing device calibration settings...");
      Console.WriteLine ("  Sending '" + cmd + "' command to device");
      Console.WriteLine ("");

      SendDeviceCommand (cmd);
    }
    #endregion
  }
}
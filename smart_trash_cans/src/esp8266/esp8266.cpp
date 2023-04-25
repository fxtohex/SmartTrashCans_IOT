#include "SoftwareSerial.h"
#include "Arduino.h"
#include "esp8266.h"

// Use Serial1 for communication with ESP-01
#define ESP_SERIAL Serial1

boolean echoFind(String target)
{
  unsigned long timeout = 10000;
  unsigned long start_time = millis();
  String response = "";

  while (millis() - start_time < timeout)
  {
    while (ESP_SERIAL.available())
    {
      char c = ESP_SERIAL.read();
      response += c;
    }
    if (response.indexOf(target) != -1)
    {
      Serial.print("Received: ");
      Serial.println(response);
      return true;
    }
  }

  Serial.print("Timed out, expected: ");
  Serial.println(target);
  return false;
}

boolean SendCommand(String cmd, String ack)
{
  // Send the AT command to the ESP-01 module
  ESP_SERIAL.println(cmd);

  // Wait for the expected acknowledgement string or time out
  if (echoFind(ack))
  {
    return true; // Acknowledgement found or not expected (ack is empty)
  }
  else
  {
    return false; // Time out, acknowledgement not found
  }
}

// Sets up the esp and connects it to the designated AP
void setup_esp8266(String _ap, String _password)
{
  // Start the Serial Monitor
  Serial.begin(115200);
  // Start the ESP-01 communication
  ESP_SERIAL.begin(115200);

  // Reset the ESP-01 module
  if (SendCommand("AT+RST", "OK"))
  {
    Serial.println("ESP-01 reset successfully");
  }
  else
  {
    Serial.println("ESP-01 reset failed");
  }
  delay(1000);

  // Connect to an access point
  String connectCmd = "AT+CWJAP=\"" + _ap + "\",\"" + _password + "\"";
  if (SendCommand(connectCmd, "OK"))
  {
    Serial.println("ESP-01 connected to AP");
  }
  else
  {
    Serial.println("ESP-01 connection to AP failed");
  }
}

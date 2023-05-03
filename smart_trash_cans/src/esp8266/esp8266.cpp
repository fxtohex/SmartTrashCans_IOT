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
  Serial.print("Received: ");
  Serial.println(response);
  return false;
}

api_response sendGetRequest(String url, String port, String endpoint)
{
  Serial.println("Making GET request to " + url);
  delay(1000);
  if (!sendCommand("AT+CIPSTART=\"TCP\",\"" + url + "\"," + port, "OK"))
  {
    return {false, "failed_to_connect"};
  }

  // make the request
  String cmd = "GET /" + endpoint + " HTTP/1.1\r\nHost: " + url + "\r\n\r\n";

  // String cmd = "GET / HTTP/1.1\r\nHost: " + "http://" + url + ":" + port + "/" + endpoint + "\r\n\r\n";
  if (
      !sendCommand("AT+CIPSEND=2048", ">"))
  {
    return {false, "failed_to_send"};
  }
  delay(1000);
  if (!sendCommand(cmd, "OK"))
  {
    return {false, "failed_to_send"};
  }

  delay(1000);
  // Read response from server

  String response = "";

  unsigned long timeout = 60000;
  unsigned long start_time = millis();

  while (true)
  {
    while (ESP_SERIAL.available())
    {
      char c = ESP_SERIAL.read();
      response += c;
    }
    delay(20000);
    Serial.print("Received: ");
    Serial.println(response);
    return {true, response};
  }
  Serial.print("Request Timed out");
  return {false, response};
}

boolean sendCommand(String cmd, String ack)
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
  Serial.begin(9600);
  // Start the ESP-01 communication
  ESP_SERIAL.begin(115200);

  // Reset the ESP-01 module
  if (sendCommand("AT+RST", "OK"))
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
  if (sendCommand(connectCmd, "OK"))
  {
    Serial.println("ESP-01 connected to AP");
  }
  else
  {
    Serial.println("ESP-01 connection to AP failed");
  }
}

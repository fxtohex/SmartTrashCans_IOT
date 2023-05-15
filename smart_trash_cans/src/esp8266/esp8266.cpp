#include "SoftwareSerial.h"
#include "Arduino.h"
#include "esp8266.h"

// Use Serial1 for communication with ESP-01
#define ESP_SERIAL Serial1

volatile unsigned long httpTimeout = 60000;
volatile unsigned long httpStartTime = 0;
volatile boolean httpInProgress = false;
boolean echoFind(String target)
{
  unsigned long timeout = 30000;
  unsigned long start_time = millis();
  String response = "";

  while (millis() - start_time < timeout)
  {
    delay(50);
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

api_response sendPutRequest(String url, String port, String endpoint, int value, String sensorName)
{
  Serial.println("Making PUT request to " + url);
  delay(100);
  // make the request
  // make the request
  if (!sendCommand("AT+CIPSTART=\"TCP\",\"" + url + "\"," + port, "OK"))
  {
    Serial.println("ESP-01 connection to tcp failed");
    return {false, "failed_to_connect_to_tcp_server"};
  }
  delay(100);
  String contentType = "application/json";
  String requestBody = "{\"value\":" + String(value) + ",\"name\":" + "\"" + String(sensorName) + "\"" + "}";
  // String cmd = "PUT /" + endpoint + " HTTP/1.1\r\nHost: " + url + "\r\n\r\n";
  int contentLength = requestBody.length();
  String cmd = "PUT /" + endpoint + " HTTP/1.1\r\n" +
               "Host: " + url + "\r\n" +
               "Content-Type: " + contentType + "\r\n" +
               "Content-Length: " + String(contentLength) + "\r\n" +
               "\r\n" +
               requestBody;

  int cmdLength = cmd.length();
  if (!sendCommand("AT+CIPSEND=" + String(cmdLength), ">"))
  {
    return {false, "failed_to_send"};
  }
  delay(100);
  if (!sendCommand(cmd, "OK"))
  {

    return {false, "failed_to_send"};
  }

  delay(100);
  // Read response from server

  String response = "";

  unsigned long timeout = 60000;
  unsigned long start_time = millis();
  bool loop = true;
  while (loop)
  {
    while (ESP_SERIAL.available())
    {
      char c = ESP_SERIAL.read();
      response += c;
    }
    delay(100);
    Serial.print("Received: ");
    Serial.println(response);
    loop = false;
  }
  delay(100);
  if (sendCommand("AT+CIPCLOSE", "OK"))
  {
    return {true, response};
  }
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
  int cmdLength = cmd.length();
  if (!sendCommand("AT+CIPSEND=" + String(cmdLength), ">"))
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

  unsigned long timeout = 3000;
  unsigned long start_time = millis();

  while (true)
  {
    while (ESP_SERIAL.available())
    {
      char c = ESP_SERIAL.read();
      response += c;
    }
    delay(10);
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
boolean setup_esp8266(String _ap, String _password, String url, String port)
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
    return false;
  }
  delay(1000);

  // Connect to an access point
  String connectCmd = "AT+CWJAP=\"" + _ap + "\",\"" + _password + "\"";
  if (!sendCommand(connectCmd, "OK"))
  {
    return false;
    Serial.println("ESP-01 connection to AP failed");
  }
  else
  {
    return true;
  }
}

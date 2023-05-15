#ifndef ESP8266_H
#define ESP8266_H

struct api_response
{
  bool success;
  String data;
};

boolean setup_esp8266(String _ap, String _password, String url, String port);
boolean sendCommand(String cmd, String ack);
api_response sendGetRequest(String url, String port, String endpoint);
api_response sendPutRequest(String url, String port, String endpoint, int value, String sensorName);

#endif

#ifndef ESP8266_H
#define ESP8266_H

struct api_response
{
  bool success;
  String data;
};
void setup_esp8266(String _ap, String _password);
boolean sendCommand(String cmd, String ack);
api_response sendGetRequest(String url, String port, String endpoint);
api_response sendPostRequest(String url, String data);

#endif

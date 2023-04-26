#ifndef ESP8266_H
#define ESP8266_H

void setup_esp8266(String _ap, String _password);
boolean sendCommand(String cmd, String ack);

#endif

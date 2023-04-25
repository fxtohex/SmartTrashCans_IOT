#include "Arduino.h"
#include "tilt_sensor.h"
int tiltSensorPin;
int tiltTrashledPin;
void tilt_sensor_setup(int _ledPin, int _tiltSensorPin)
{
  Serial.begin(9600);
  tiltSensorPin = _tiltSensorPin;
  tiltTrashledPin = _ledPin;
  pinMode(tiltTrashledPin, OUTPUT);
  pinMode(tiltSensorPin, INPUT);
  digitalWrite(tiltSensorPin, HIGH);
}

bool is_trash_can_tipped()
{
  int digitalVal = digitalRead(tiltSensorPin);
  if (HIGH == digitalVal)
  {
    digitalWrite(tiltTrashledPin, HIGH); // turn the led off
    return true;
  }
  else
  {
    digitalWrite(tiltTrashledPin, LOW); // turn the led on
    return false;
  }
}

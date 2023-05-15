#include "Arduino.h"
#include "ir_avoidance_sensor.h"
int currentState = 0;
int enablePin;
int outPin;
int irTrashledPin;

void ir_avoidance_sensor_setup(int _enablePin, int _outPin, int _irTrashledPin)
{
  enablePin = _enablePin;
  outPin = _outPin;
  irTrashledPin = _irTrashledPin;

  pinMode(enablePin, OUTPUT);
  pinMode(outPin, INPUT);
  pinMode(irTrashledPin, OUTPUT);
  digitalWrite(enablePin, HIGH); // Enable the sensors
}

bool is_trash_can_full()
{
  int digitalVal = digitalRead(outPin);
  if (HIGH == digitalVal)
  {
    Serial.println("IR sensor is not triggered");
    digitalWrite(irTrashledPin, LOW); // turn the led off
    return false;
  }
  else
  {
    Serial.println("IR sensor is triggered");
    digitalWrite(irTrashledPin, HIGH); // turn the led on
    return true;
  }
}

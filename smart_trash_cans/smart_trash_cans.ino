#include "src/tilt_sensor/tilt_sensor.h"
#include "src/ir_avoidance_sensor/ir_avoidance_sensor.h"
#include "src/ultrasonic_sensor/ultrasonic_sensor.h"
#include "src/esp8266/esp8266.h"

// Pins and leds for tilt sensor
const int tiltTrashLed = 8;
const int tiltTrashSensor = 7;

// Pins and leds for ir avoidance sensor
const int irTrashLed = 11;
const int irTrashSensor = 10;
const int irTrashEnable = 9;

// Pins and leds for ultrasonic sensor
const int trigPin = 2;
const int echoPin = 3;
const int ultRedPin = 5;
const int ultBluePin = 4;
const int ultGreenPin = 6;
bool isEspReady = false;
void setup()
{
  Serial.begin(9600);
  isEspReady = setup_esp8266("Hotspot", "11111111", "192.168.137.1", "3080");
  delay(10);
  tilt_sensor_setup(tiltTrashLed, tiltTrashSensor);
  delay(10);
  ir_avoidance_sensor_setup(irTrashEnable, irTrashSensor, irTrashLed);
  delay(10);
  ultrasonic_sensor_setup(echoPin, trigPin, ultRedPin, ultBluePin, ultGreenPin);
  // put your setup code here, to run once:
  delay(3000);
}
bool prevTiltSensorState = false;
bool prevIrSensorState = false;
void loop()
{

  ultrasonic_sensor_status status = handle_ult_sensor();
  bool i5sFull = status.isFull;
  bool tiltSensorState = is_trash_can_tipped();
  bool irSensorState = is_trash_can_full();
  int percentageFull = status.percentageFull;
  int prevPercentageFull = 0;

  if (isEspReady)
  {
    if (tiltSensorState != prevTiltSensorState)
    {
      prevTiltSensorState = tiltSensorState;
      sendPutRequest("192.168.137.1", "3080", "api/sensors/", tiltSensorState, "tilt_sensor");
    }

    if (percentageFull != prevPercentageFull)
    {
      prevPercentageFull = percentageFull;
      sendPutRequest("192.168.137.1", "3080", "api/sensors/", percentageFull, "us_sensor");
    }

    if (irSensorState != prevIrSensorState)
    {
      prevIrSensorState = irSensorState;
      sendPutRequest("192.168.137.1", "3080", "api/sensors/", irSensorState, "ir_sensor");
    }
  }

  if (Serial.available())
  {
    String command = Serial.readStringUntil('\n');
    sendCommand(command, "OK");
  }
  delay(1000);
  // put your main code here, to run repeatedly:
}

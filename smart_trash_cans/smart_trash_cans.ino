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

void setup()
{
  Serial.begin(9600);
  setup_esp8266("Hotspot", "11111111");
  delay(10);
  tilt_sensor_setup(tiltTrashLed, tiltTrashSensor);
  delay(10);
  ir_avoidance_sensor_setup(irTrashEnable, irTrashSensor, irTrashLed);
  delay(10);
  ultrasonic_sensor_setup(echoPin, trigPin, ultRedPin, ultBluePin, ultGreenPin);
  // put your setup code here, to run once:
  delay(10000);
  Serial.println(sendGetRequest("192.168.137.1", "3080", "api/sensors/424242").data);
}

void loop()
{
  // ultrasonic_sensor_status status = handle_ult_sensor();
  // bool i5sFull = status.isFull;
  // float percentageFull = status.percentageFull;

  // if (is_trash_can_tipped())
  // {
  //   Serial.println("Trash can is tipped");
  // }
  // else
  // {
  //   Serial.println("Trash can is not tipped");
  // }

  // if (is_trash_can_full())
  // {
  //   Serial.println("IR_avoidance sensor trash can is full");
  // }
  // else
  // {
  //   Serial.println("IR_avoidance sensor trash can is not full");
  // }
  if (Serial.available())
  {
    String command = Serial.readStringUntil('\n');
    sendCommand(command, "OK");
  }
  delay(1000);
  // put your main code here, to run repeatedly:
}

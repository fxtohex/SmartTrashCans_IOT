#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

struct ultrasonic_sensor_status
{
  bool isFull;
  float percentageFull;
};
void ultrasonic_sensor_setup(int _echoPin, int _trigPin, int _ultRedPin, int _ultBluePin, int _ultGreenPin);
ultrasonic_sensor_status handle_ult_sensor();
#endif
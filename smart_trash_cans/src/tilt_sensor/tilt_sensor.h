#ifndef TILT_SENSOR_H
#define TILT_SENSOR_H

void tilt_sensor_setup(int _ledPin, int _tiltSensorPin);
bool is_trash_can_tipped();

#endif
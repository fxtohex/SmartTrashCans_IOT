#ifndef IR_AVOIDANCE_SENSOR_H
#define IR_AVOIDANCE_SENSOR_H

void ir_avoidance_sensor_setup(int _enablePin, int _outPin, int _irTrashledPin);
bool is_trash_can_full();

#endif
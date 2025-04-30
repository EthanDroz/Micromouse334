# ifndef attitude_functions.hpp
# define attitude_functions.hpp

#include <BMI160Gen.h>

void HeadingTurn(short& heading, bool turn_direction, class& accelerometer) {
  int turn_angle_raw;
  double turn_angle = 0;
  if (turn_direction == 0) {
    while (turn_angle < 90) {
      turn_angle_raw = accelerometer.readGyro(Z_AXIS);
      turn_angle += accelerometer.convertRawGyro(turn_angle_raw);
    }
    heading -= 1;
  }
  else {
    while (turn_angle > -90) {
      turn_angle_raw = accelerometer.readGyro(Z_AXIS);
      turn_angle += accelerometer.convertRawGyro(turn_angle_raw);
    }
    heading += 1;
  }
  if (heading == 4) {
    heading = 0;
  } else if (heading == -1) {
    heading = 3;
  }
}

void Forward(class& accelerometer, short& heading, short& x, short& y) {
  double distance = 0.0;
  int distance_raw;
  double vel = 0.0;
  while (distance < 0.1016) {
    distance_raw = accelerometer.readAccelerometer(X_AXIS);
    vel += (double)distance_raw * 2*9.81 / 32767.0;
    distance += vel;
  }
  if (heading == 0) {
    y++;
  } else if (heading == 1) {
    x++;
  } else if (heading == 2) {
    y--;
  } else if (heading == 3) {
    x
  }
}


# endif

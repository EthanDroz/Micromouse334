#ifndef sensor.h 
#define sensor.h 


#include <Arduino.h>


int ir_analog(int Pin, int del_t) {
  int reading = analogRead(Pin);

    return reading;
}


float sonar_range(int Pin, int del_t) {
  float range;

  
  return range;
};

#endif
#ifndef sensor.h 
#define sensor.h 


#include <Arduino.h>

double speed_of_sound = 34321.0;


int ir_analog(int Pin, int del_t) {
  int reading = analogRead(Pin);

    return reading;
}

float sonar_range(int trigPin, int echoPin, int del_t) {
  float range;
  
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);

  unsigned short duration = pulseIn(echoPin, HIGH, 11500);

  float range = (speed_of_sound * duration * 1.0e-6) * 0.5;
  
  return range;
};

#endif
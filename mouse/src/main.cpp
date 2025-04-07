#include <Arduino.h>
#include "sensor.h"
#include "attitude.hpp"
#include "Wire.h"

// timer declarations;
unsigned long current_time;
unsigned long prev_time_main;
unsigned long prev_time_att;
unsigned short time1 = 100;
unsigned short delta_att = 20;

// pin declarations;
int irPin[5] = {1,2,3,4,5};
int echoPin = 6;
int trigPin = 7;

// position init;
float position[2] = {0, 0};
float accel[2] = {0, 0};


// function declarations:

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  pinMode(irPin[0], INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  current_time = millis();

  if (current_time - prev_time_att > delta_att) {
    current_position(position, accel, delta_att);
  }

  if (current_time - prev_time_main > time1) {
    prev_time_main = current_time;
    int ir_1 = ir_analog(irPin[0], time1);
  }

}

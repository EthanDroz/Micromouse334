#include <Arduino.h>
#include "sensor.h"
#include "attitude.hpp"
#include "Wire.h"



// timer declarations;
unsigned long current_time;
unsigned long prev_time_main;
unsigned long time1 = 1000;

// pin declarations;
int irPin = 1;

// function declarations:

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  pinMode(irPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  current_time = millis();

  if (current_time - prev_time_main > time1) {
    prev_time_main = current_time;
    int ir_1 = ir_analog(irPin, time1);
  }

}

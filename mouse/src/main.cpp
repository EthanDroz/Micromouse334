#include <Arduino.h>

// timer declarations;
unsigned long current_time;
unsigned long prev_time_main;
unsigned long time1 = 1000;

// pin declarations;
int irPin = 1;

// function declarations:
int ir_analog(int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(irPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  current_time = millis();

  if (current_time - prev_time_main > time1) {
    prev_time_main = current_time;

  }

}

// put function definitions here:
int ir_analog(int Pin) {
  int reading = analogRead(Pin);


}
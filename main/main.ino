
#include "mm-utils.h";

unsigned long current_time;
unsigned long prev_time;
unsigned long trigger1;
int trigPin = 1;
int echoPin = 2;

float range;

void setup()
{
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  pinMode(1, INPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  current_time = millis();

  if (current_time - prev_time > trigger1)
  {
    range = sonar_rangefinder(echoPin, trigPin);
  }
}

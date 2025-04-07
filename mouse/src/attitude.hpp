#ifndef attitude.hpp
#define attitude.hpp

// Includes
#include <Arduino.h>
#include "Wire.h"

void current_position(float *position, float *accel, short dt) {

    while (*position)
    {
        *position = *accel * dt;
        *position++;
        *accel++;
    }
    
}

void attitude_serial_output(float *pos, float *acc, long current_time) {
    Serial.print("Time: ");
    Serial.print(current_time);
    
    Serial.print(", Position: ");
    while (*pos) {
        Serial.print(*pos);
        Serial.print(", ");
        *pos++;
    }
    Serial.print(", Acceleration: ");
    while (*acc) {
        Serial.print(*acc);
        Serial.print(", ");
        *acc++;
    }
    Serial.println(" ");
}

#endif
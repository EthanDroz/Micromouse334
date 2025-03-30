

// Fn to find distance for sonar sensor.

float sonar_rangefinder(echoPin, trigPin)
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    float duration = pulseIn(echoPin, HIGH, 11500);
    return float distance_cm = (34300.0 * duration * 1.0e-6) * 0.5;
}

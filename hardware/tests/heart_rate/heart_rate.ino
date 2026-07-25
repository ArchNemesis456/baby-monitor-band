#include <Arduino.h>

const int HEART_PIN = 34;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    int pulseValue = analogRead(HEART_PIN);

    Serial.print("Pulse: ");
    Serial.println(pulseValue);

    delay(20);
}
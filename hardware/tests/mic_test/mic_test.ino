#include <Arduino.h>

const int MIC_PIN = 35;

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    int micValue = analogRead(MIC_PIN);

    Serial.print("Mic: ");
    Serial.println(micValue);

    delay(100);
}
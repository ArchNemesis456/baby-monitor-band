#include "vibration.h"
#include "config.h"

void initializeVibration()
{
    pinMode(VIBRATION_PIN, OUTPUT);
    digitalWrite(VIBRATION_PIN, LOW);
}

void updateVibration(const String &alertLevel)
{
    if (alertLevel == "Low")
    {
        digitalWrite(VIBRATION_PIN, LOW);
    }
    else if (alertLevel == "Medium")
    {
        digitalWrite(VIBRATION_PIN, HIGH);
        delay(300);
        digitalWrite(VIBRATION_PIN, LOW);
    }
    else if (alertLevel == "High")
    {
        digitalWrite(VIBRATION_PIN, HIGH);
    }
    else
    {
        digitalWrite(VIBRATION_PIN, LOW);
    }
}
#ifndef VIBRATION_H
#define VIBRATION_H

#include <Arduino.h>

void initializeVibration();
void updateVibration(const String &alertLevel);

#endif
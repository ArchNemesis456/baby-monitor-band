#ifndef DATA_MODELS_H
#define DATA_MODELS_H

#include <Arduino.h>

struct PredictionData
{
    String state;
    float confidence;
    String alertLevel;
};

#endif
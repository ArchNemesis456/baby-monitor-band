#ifndef DATA_MODELS_H
#define DATA_MODELS_H

#include <Arduino.h>

struct RawSensorData
{
    // Pulse Sensor
    int pulseADC;
    int bpm;

    // Accelerometer
    float accelX;
    float accelY;
    float accelZ;

    // Gyroscope
    float gyroX;
    float gyroY;
    float gyroZ;

    // Motion magnitude
    float movement;

    // Microphone
    int microphoneADC;
    float soundDB;
    float cryFrequency;
};

struct SensorData
{
    float cryVolume;
    float cryFrequency;

    float motionIntensity;
    float restlessness;

    float heartRate;
    float heartRateTrend;
    float heartRateVariability;
};

struct PredictionResponse
{
    String state;
    float confidence;
    String alertLevel;
};

#endif
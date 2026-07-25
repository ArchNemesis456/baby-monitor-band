#include "feature_extraction.h"

SensorData extractFeatures(const RawSensorData& raw)
{
    SensorData data;

    data.cryVolume = raw.soundDB;

    // Not implemented yet
    data.cryFrequency = 0;

    // Motion intensity
    float movementError = fabs(raw.movement - 9.81f);
    data.motionIntensity = movementError;

    // Not implemented yet
    data.restlessness = 0;

    data.heartRate = raw.bpm;

    // Not implemented yet
    data.heartRateTrend = 0;
    data.heartRateVariability = 0;

    return data;
}
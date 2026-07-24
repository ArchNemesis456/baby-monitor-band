#include "feature_extraction.h"

SensorData extractFeatures(const RawSensorData& raw)
{
    SensorData data;

    // Cry Volume
    data.cryVolume = raw.soundDB;

    // Placeholder until FFT is implemented
    data.cryFrequency = 0;

    // Motion Intensity
    data.motionIntensity = abs(raw.movement - 9.8);

    // Placeholder
    data.restlessness = 0;

    // Heart Rate
    data.heartRate = raw.bpm;

    // Placeholder
    data.heartRateTrend = 0;

    // Placeholder
    data.heartRateVariability = 0;

    return data;
}
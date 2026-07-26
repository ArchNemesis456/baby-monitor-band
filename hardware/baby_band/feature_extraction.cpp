#include "feature_extraction.h"
#include <math.h>

static float previousHeartRate = 0;

const int HISTORY_SIZE = 10;
static float heartHistory[HISTORY_SIZE];
static int historyIndex = 0;
static bool historyFilled = false;

SensorData extractFeatures(const RawSensorData& raw)
{
    SensorData data;

    // ---------------- Cry ----------------

    data.cryVolume = raw.soundDB;

    // TODO: Requires microphone waveform
    data.cryFrequency = raw.cryFrequency;

    // ---------------- Motion ----------------

    static float previousMovement = 0;

    float movementError =
        fabs(raw.movement - previousMovement);

    previousMovement = raw.movement;

    data.motionIntensity = movementError;

    float gyroMagnitude =
        sqrt(raw.gyroX * raw.gyroX +
             raw.gyroY * raw.gyroY +
             raw.gyroZ * raw.gyroZ);

    data.restlessness = gyroMagnitude;

    // ---------------- Heart ----------------

    data.heartRate = raw.bpm;

    if(previousHeartRate == 0)
        data.heartRateTrend = 0;
    else
        data.heartRateTrend = raw.bpm - previousHeartRate;

    previousHeartRate = raw.bpm;

    heartHistory[historyIndex++] = raw.bpm;

    if(historyIndex >= HISTORY_SIZE)
    {
        historyIndex = 0;
        historyFilled = true;
    }

    int count = historyFilled ? HISTORY_SIZE : historyIndex;

    float mean = 0;

    for(int i=0;i<count;i++)
        mean += heartHistory[i];

    if(count>0)
        mean /= count;

    float variance = 0;

    for(int i=0;i<count;i++)
    {
        float diff = heartHistory[i]-mean;
        variance += diff*diff;
    }

    if(count>0)
        variance /= count;

    data.heartRateVariability = sqrt(variance);

    return data;
}
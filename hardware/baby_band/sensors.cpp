#include "sensors.h"
#include "config.h"

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>


const int samples = 150;
const float reference = 1000.0;

Adafruit_MPU6050 mpu;
bool mpu_ok = false;

void initSensors()
{
    Wire.begin(SDA_PIN, SCL_PIN);

    if (mpu.begin())
    {
        mpu_ok = true;
        Serial.println("MPU6050 Connected");
    }
    else
    {
        Serial.println("ERROR: MPU6050 NOT FOUND");
    }

    pinMode(MIC_PIN, INPUT);
    pinMode(HEART_PIN, INPUT);
}

RawSensorData readSensors()
{
    RawSensorData data{};

    // --------------------------
    // Microphone
    // --------------------------

    long sum = 0;
    long long squareSum = 0;

    int prevSample = analogRead(MIC_PIN);
    int zeroCrossings = 0;

    for(int i=0;i<samples;i++)
    {
        int currentSample = analogRead(MIC_PIN);

        sum += currentSample;

        int centered = currentSample - 2048;

        squareSum += (long long)centered * centered;

        if((prevSample < 2048 && currentSample >= 2048) ||
        (prevSample >= 2048 && currentSample < 2048))
        {
            zeroCrossings++;
        }

        prevSample = currentSample;
    }

    float rms = sqrt(squareSum / (float)samples);

    data.microphoneADC = sum / (float)samples;

    // Remove idle microphone noise
    const float MIC_BASELINE = 1650.0f;

    float cryLevel = rms - MIC_BASELINE;

    if (cryLevel < 0)
        cryLevel = 0;

    data.soundDB = cryLevel / 800.0f;

    if (data.soundDB > 1.0f)
        data.soundDB = 1.0f;

    const float sampleRate = 4000.0;

    data.cryFrequency =
        (zeroCrossings * sampleRate) /
        (2.0 * samples);

    // --------------------------
    // Pulse Sensor Calibration
    // --------------------------

    data.pulseADC = analogRead(HEART_PIN);

    Serial.print("Pulse ADC: ");
    Serial.println(data.pulseADC);

    // Temporary for calibration
    data.bpm = 0;

    // --------------------------
    // MPU6050
    // --------------------------

    if(mpu_ok)
    {
        sensors_event_t a,g,temp;

        mpu.getEvent(&a,&g,&temp);

        data.accelX = a.acceleration.x;
        data.accelY = a.acceleration.y;
        data.accelZ = a.acceleration.z;

        data.gyroX = g.gyro.x;
        data.gyroY = g.gyro.y;
        data.gyroZ = g.gyro.z;

        data.movement =
            sqrt(
                data.accelX*data.accelX +
                data.accelY*data.accelY +
                data.accelZ*data.accelZ
            );
    }

    return data;
}
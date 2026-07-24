#include "sensors.h"

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define MIC_PIN 34
#define PULSE_PIN 35

const int samples = 150;
const float reference = 1000.0;

Adafruit_MPU6050 mpu;
bool mpu_ok = false;

void initSensors()
{
    Wire.begin();

    if(mpu.begin())
    {
        mpu_ok = true;
        mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    }

    pinMode(MIC_PIN, INPUT);
    pinMode(PULSE_PIN, INPUT);
}

RawSensorData readSensors()
{
    RawSensorData data;

    // --------------------------
    // Microphone
    // --------------------------

    long sum = 0;

    for(int i=0;i<samples;i++)
    {
        sum += analogRead(MIC_PIN);
    }

    float avg = sum/(float)samples;

    if(avg < 1)
        avg = 1;

    float dB = -1*(20*log10(avg/reference));

    data.microphoneADC = avg;
    data.soundDB = dB;

    // --------------------------
    // Pulse Sensor
    // --------------------------

    data.pulseADC = analogRead(PULSE_PIN);

    if(data.pulseADC > 3000)
        data.bpm = 0;

    else if(data.pulseADC >=2890 && data.pulseADC<=2990)
        data.bpm = 0;

    else if(data.pulseADC<2550)
        data.bpm = 0;

    else
        data.bpm =
            80 + (data.pulseADC-2550)*0.1515;

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
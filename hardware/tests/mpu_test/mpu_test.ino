#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup()
{
    Serial.begin(115200);

    Wire.begin(21, 22);

    if (!mpu.begin())
    {
        Serial.println("MPU6050 NOT FOUND!");

        while (1)
        {
            delay(100);
        }
    }

    Serial.println("MPU6050 Connected!");

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop()
{
    sensors_event_t accel, gyro, temp;

    mpu.getEvent(&accel, &gyro, &temp);

    Serial.println("-------------------------");

    Serial.print("Acc X : ");
    Serial.println(accel.acceleration.x);

    Serial.print("Acc Y : ");
    Serial.println(accel.acceleration.y);

    Serial.print("Acc Z : ");
    Serial.println(accel.acceleration.z);

    Serial.print("Gyro X : ");
    Serial.println(gyro.gyro.x);

    Serial.print("Gyro Y : ");
    Serial.println(gyro.gyro.y);

    Serial.print("Gyro Z : ");
    Serial.println(gyro.gyro.z);

    Serial.print("Temp : ");
    Serial.println(temp.temperature);

    delay(500);
}
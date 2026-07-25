#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

// Pin definitions
const int MIC_PIN = 35;
const int HEART_PIN = 34;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Wire.begin(21, 22);

    if (!mpu.begin())
    {
        Serial.println("ERROR: MPU6050 not found!");
        while (1)
        {
            delay(100);
        }
    }

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    Serial.println();
    Serial.println("====================================");
    Serial.println(" Baby Band Combined Sensor Test");
    Serial.println("====================================");
}

void loop()
{
    // Read microphone
    int micValue = analogRead(MIC_PIN);

    // Read pulse sensor
    int heartValue = analogRead(HEART_PIN);

    // Read MPU6050
    sensors_event_t accel, gyro, temp;
    mpu.getEvent(&accel, &gyro, &temp);

    Serial.println("------------------------------------");

    Serial.print("Microphone : ");
    Serial.println(micValue);

    Serial.print("Heart Raw  : ");
    Serial.println(heartValue);

    Serial.println();

    Serial.println("Accelerometer");
    Serial.print("  X : ");
    Serial.println(accel.acceleration.x, 2);

    Serial.print("  Y : ");
    Serial.println(accel.acceleration.y, 2);

    Serial.print("  Z : ");
    Serial.println(accel.acceleration.z, 2);

    Serial.println();

    Serial.println("Gyroscope");
    Serial.print("  X : ");
    Serial.println(gyro.gyro.x, 2);

    Serial.print("  Y : ");
    Serial.println(gyro.gyro.y, 2);

    Serial.print("  Z : ");
    Serial.println(gyro.gyro.z, 2);

    delay(500);
}
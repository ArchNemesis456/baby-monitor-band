#include "config.h"
#include "data_models.h"

#include "sensors.h"
#include "feature_extraction.h"
#include "wifi_manager.h"
#include "communication.h"

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("Baby Band Starting...");

    initSensors();

    connectWiFi();
}

void loop()
{
    RawSensorData raw = readSensors();

    SensorData features =
        extractFeatures(raw);

    Serial.println("\n========== RAW SENSOR DATA ==========");

    Serial.print("Mic ADC: ");
    Serial.println(raw.microphoneADC);

    Serial.print("Sound dB: ");
    Serial.println(raw.soundDB);

    Serial.print("Cry Frequency: ");
    Serial.println(raw.cryFrequency);

    Serial.print("Pulse ADC: ");
    Serial.println(raw.pulseADC);

    Serial.print("Estimated BPM: ");
    Serial.println(raw.bpm);

    Serial.print("Accel X: ");
    Serial.println(raw.accelX);

    Serial.print("Accel Y: ");
    Serial.println(raw.accelY);

    Serial.print("Accel Z: ");
    Serial.println(raw.accelZ);

    Serial.print("Gyro X: ");
    Serial.println(raw.gyroX);

    Serial.print("Gyro Y: ");
    Serial.println(raw.gyroY);

    Serial.print("Gyro Z: ");
    Serial.println(raw.gyroZ);

    Serial.print("Movement: ");
    Serial.println(raw.movement);

    Serial.println("=====================================");
        
    PredictionResponse prediction =
        sendPrediction(features);

    Serial.println("---------------------------");

    Serial.print("State : ");
    Serial.println(prediction.state);

    Serial.print("Confidence : ");
    Serial.println(prediction.confidence);

    Serial.print("Alert : ");
    Serial.println(prediction.alertLevel);

    Serial.println("---------------------------");

    delay(1000);
}
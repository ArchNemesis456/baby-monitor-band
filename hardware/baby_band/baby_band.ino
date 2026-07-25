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
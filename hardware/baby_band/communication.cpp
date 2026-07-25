#include "communication.h"
#include "config.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

PredictionResponse sendPrediction(const SensorData& data)
{
    PredictionResponse prediction;

    // Default response
    prediction.state = "Unknown";
    prediction.confidence = 0.0;
    prediction.alertLevel = "NONE";

    // Check WiFi
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi not connected!");
        return prediction;
    }

    HTTPClient http;

    http.begin(SERVER_URL);
    http.addHeader("Content-Type", "application/json");

    JsonDocument requestDoc;

    requestDoc["cry_volume"] = data.cryVolume;
    requestDoc["cry_frequency"] = data.cryFrequency;
    requestDoc["motion_intensity"] = data.motionIntensity;
    requestDoc["restlessness"] = data.restlessness;
    requestDoc["heart_rate"] = data.heartRate;
    requestDoc["heart_rate_trend"] = data.heartRateTrend;
    requestDoc["hr_variability"] = data.heartRateVariability;

    String requestBody;
    serializeJson(requestDoc, requestBody);

    Serial.println("\n========== Sending ==========");
    Serial.println(requestBody);

    int httpCode = http.POST(requestBody);

    if (httpCode <= 0)
    {
        Serial.print("HTTP Error Code: ");
        Serial.println(httpCode);

        Serial.print("WiFi Status: ");
        Serial.println(WiFi.status());

        Serial.print("ESP32 IP: ");
        Serial.println(WiFi.localIP());

        http.end();
        return prediction;
    }

    Serial.print("HTTP Code : ");
    Serial.println(httpCode);

    String responseBody = http.getString();

    Serial.println("\n========== Response ==========");
    Serial.println(responseBody);

    JsonDocument responseDoc;

    DeserializationError error =
        deserializeJson(responseDoc, responseBody);

    if (error)
    {
        Serial.println("JSON Parse Error");

        http.end();
        return prediction;
    }

    prediction.state =
        responseDoc["state"].as<String>();

    prediction.confidence =
        responseDoc["confidence"].as<float>();

    prediction.alertLevel =
        responseDoc["alert_level"].as<String>();

    http.end();

    return prediction;
}
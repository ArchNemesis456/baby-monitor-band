#include "communication.h"
#include "config.h"

#include <HTTPClient.h>
#include <ArduinoJson.h>

bool fetchLatestPrediction(PredictionData &prediction)
{
    HTTPClient http;

    http.begin(SERVER_URL);

    int httpCode = http.GET();

    if (httpCode != HTTP_CODE_OK)
    {
        Serial.print("HTTP Error : ");
        Serial.println(httpCode);

        http.end();
        return false;
    }

    String response = http.getString();

    DynamicJsonDocument doc(512);

    if (deserializeJson(doc, response))
    {
        Serial.println("JSON Parse Failed");

        http.end();
        return false;
    }

    prediction.state = doc["state"].as<String>();
    prediction.confidence = doc["confidence"];
    prediction.alertLevel = doc["alert_level"].as<String>();

    http.end();

    return true;
}
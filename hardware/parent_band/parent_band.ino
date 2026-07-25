#include "config.h"
#include "data_models.h"
#include "wifi_manager.h"
#include "communication.h"
#include "display.h"
#include "vibration.h"

PredictionData prediction;

unsigned long lastFetchTime = 0;

void setup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println("=================================");
    Serial.println(" Parent Band Starting...");
    Serial.println("=================================");

    // Initialize OLED
    if (!initializeDisplay())
    {
        Serial.println("Display initialization failed!");
        while (true)
        {
            delay(1000);
        }
    }

    showBootScreen();
    delay(1500);

    // Connect WiFi
    showWiFiConnecting();
    connectWiFi();
    showWiFiConnected();

    // Initialize vibration motor
    initializeVibration();

    Serial.println("Parent Band Ready!");
}

void loop()
{
    maintainWiFi();

    if (millis() - lastFetchTime >= FETCH_INTERVAL_MS)
    {
        lastFetchTime = millis();

        Serial.println();
        Serial.println("========== Fetching Prediction ==========");

        if (fetchLatestPrediction(prediction))
        {
            Serial.println("Prediction Received");

            Serial.print("State : ");
            Serial.println(prediction.state);

            Serial.print("Confidence : ");
            Serial.println(prediction.confidence);

            Serial.print("Alert : ");
            Serial.println(prediction.alertLevel);

            showPrediction(prediction);

            updateVibration(prediction.alertLevel);
        }
        else
        {
            Serial.println("Failed to fetch prediction.");

            showConnectionError();
        }
    }
}
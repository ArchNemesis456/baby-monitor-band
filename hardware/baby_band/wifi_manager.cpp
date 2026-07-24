#include "wifi_manager.h"
#include "config.h"

#include <WiFi.h>

void connectWiFi()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        return;
    }

    Serial.println("\nConnecting to WiFi...");
    Serial.print("SSID: ");
    Serial.println(WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    unsigned long startTime = millis();

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");

        if (millis() - startTime > WIFI_TIMEOUT_MS)
        {
            Serial.println("\nWiFi connection timed out!");
            return;
        }
    }

    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

bool isWiFiConnected()
{
    return WiFi.status() == WL_CONNECTED;
}
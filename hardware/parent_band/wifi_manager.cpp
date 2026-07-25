#include "wifi_manager.h"
#include "config.h"

#include <WiFi.h>

void connectWiFi()
{
    Serial.println();
    Serial.println("==============================");
    Serial.println("Connecting to WiFi...");
    Serial.print("SSID : ");
    Serial.println(WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    unsigned long start = millis();

    while (WiFi.status() != WL_CONNECTED &&
           millis() - start < WIFI_TIMEOUT_MS)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi Connected!");
        Serial.print("IP Address : ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("WiFi Connection Failed!");
    }

    Serial.println("==============================");
}

void maintainWiFi()
{
    if (WiFi.status() == WL_CONNECTED)
        return;

    Serial.println("WiFi Lost! Reconnecting...");
    connectWiFi();
}
#include "display.h"
#include "config.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    OLED_RESET
);

bool initializeDisplay()
{
    Wire.begin(SDA_PIN, SCL_PIN);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("OLED Initialization Failed!");
        return false;
    }

    display.clearDisplay();
    display.display();

    return true;
}

void showBootScreen()
{
    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(10,15);
    display.println("Baby");

    display.setCursor(10,40);
    display.println("Monitor");

    display.display();
}

void showWiFiConnecting()
{
    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0,20);
    display.println("Connecting");

    display.setCursor(0,35);
    display.println("to WiFi...");

    display.display();
}

void showWiFiConnected()
{
    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0,20);
    display.println("WiFi Connected");

    display.display();

    delay(1000);
}

void showPrediction(const PredictionData &prediction)
{
    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0,0);
    display.println("Baby Monitor");

    display.drawLine(0,10,128,10,SSD1306_WHITE);

    display.setCursor(0,18);
    display.print("State:");

    display.setCursor(60,18);
    display.println(prediction.state);

    display.setCursor(0,34);
    display.print("Conf:");

    display.setCursor(60,34);
    display.print(prediction.confidence * 100,0);
    display.println("%");

    display.setCursor(0,50);
    display.print("Alert:");

    display.setCursor(60,50);
    display.println(prediction.alertLevel);

    display.display();
}

void showConnectionError()
{
    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0,20);
    display.println("Server");

    display.setCursor(0,35);
    display.println("Unavailable");

    display.display();
}
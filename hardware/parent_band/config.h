#ifndef CONFIG_H
#define CONFIG_H

/* =========================================
 * WiFi Configuration
 * ========================================= */
constexpr const char* WIFI_SSID = "Ligma";
constexpr const char* WIFI_PASSWORD = "swayam@123";

/* =========================================
 * Backend Configuration
 * ========================================= */
constexpr const char* SERVER_URL =
    "http://10.92.132.75:8000/latest";

/* =========================================
 * OLED Pins
 * ========================================= */
constexpr int SDA_PIN = 21;
constexpr int SCL_PIN = 22;

/* =========================================
 * Vibration Motor
 * ========================================= */
constexpr int VIBRATION_PIN = 26;

/* =========================================
 * OLED Configuration
 * ========================================= */
constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 64;
constexpr int OLED_RESET = -1;

/* =========================================
 * Timing
 * ========================================= */
constexpr unsigned long FETCH_INTERVAL_MS = 1000;
constexpr unsigned long WIFI_TIMEOUT_MS = 15000;

#endif
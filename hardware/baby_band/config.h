#ifndef CONFIG_H
#define CONFIG_H

/* ==============================
 * Wi-Fi Configuration
 * ============================== */
constexpr const char* WIFI_SSID = "Ligma";
constexpr const char* WIFI_PASSWORD = "swayam@123";

/* ==============================
 * Backend Configuration
 * ============================== */
constexpr const char* SERVER_URL = "http://172.20.121.153:8000/predict";

/* ==============================
 * Sensor Pins
 * ============================== */
constexpr int MIC_PIN = 35;
constexpr int HEART_PIN = 34;

constexpr int SDA_PIN = 21;
constexpr int SCL_PIN = 22;

/* ==============================
 * Timing
 * ============================== */
constexpr unsigned long SAMPLE_INTERVAL_MS = 1000;
constexpr unsigned long WIFI_TIMEOUT_MS = 15000;

#endif
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// -------- PINS --------
#define MIC_PIN 34
#define PULSE_PIN 35

// -------- SOUND SETTINGS --------
const int samples = 150;
const float reference = 1000.0;

#define TALK_MIN 22
#define TALK_MAX 35
#define CRY_LEVEL 36
#define CRY_DURATION 6

int cryCounter = 0;

// -------- MPU SETTINGS --------
#define WAKE_THRESHOLD 2.0

Adafruit_MPU6050 mpu;
bool mpu_ok = false;

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("\n===== BABY BAND START =====");

  Serial.print("MPU6050: ");
  if (mpu.begin()) {
    Serial.println("OK");
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu_ok = true;
  } else {
    Serial.println("NOT FOUND");
  }

  pinMode(MIC_PIN, INPUT);
  pinMode(PULSE_PIN, INPUT);

  Serial.println("All sensors initialized\n");
}

void loop() {

  // =====================================================
  // 🎤 SOUND SECTION
  // =====================================================
  long sum = 0;
  for (int i = 0; i < samples; i++) {
    sum += analogRead(MIC_PIN);
  }

  float avg = sum / (float)samples;
  if (avg < 1) avg = 1;

  float dB = -1*(20 * log10(avg / reference));
  

  String soundState = "Quiet";

  if (dB >= TALK_MIN && dB <= TALK_MAX) {
    soundState = "peacefull_enviro";
    cryCounter = 0;
  }

  if (dB > CRY_LEVEL) {
    cryCounter++;
    soundState = "Loud";

    if (cryCounter > CRY_DURATION) {
      soundState = "🚨 Crying";
    }
  }

  if (dB < TALK_MIN) cryCounter = 0;


  // =====================================================
  // 📦 MOTION SECTION
  // =====================================================
  String motionState = "NA";

  if (mpu_ok) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    float movement = sqrt(
      a.acceleration.x * a.acceleration.x +
      a.acceleration.y * a.acceleration.y +
      a.acceleration.z * a.acceleration.z
    );

    if ((movement - 9.8) > WAKE_THRESHOLD) 
        motionState = "Awake";
    else 
      motionState = "Sleeping";
  }


  // =====================================================
  // ❤️ HEART SECTION (MAPPED BPM)
  // =====================================================
  int heartSignal = analogRead(PULSE_PIN);

  String heartState = "";
  int bpm = 0;

  if (heartSignal > 3000) {
    heartState = "Ignore";
  }
  else if (heartSignal >= 2890 && heartSignal <= 2990) {
    heartState = "No Finger";
  }
  else if (heartSignal < 2550) {
    heartState = "⚠️ Danger";
  }
  else {
    // linear mapping
    bpm = 80 + (heartSignal - 2550) * 0.1515;
    heartState = "BPM: " + String(bpm);
  }


  // =====================================================
  // 🖨 PRINT SECTION
  // =====================================================
  Serial.print("Sound dB: ");
  Serial.print(dB);
  Serial.print(" (");
  Serial.print(soundState);
  Serial.print(")");

  Serial.print(" | Motion: ");
  Serial.print(motionState);

  Serial.print(" | Heart: ");
  Serial.print(heartState);

  Serial.println();

  delay(100);
}
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Screen dimensions
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

// Pin Definitions
#define VIBRATOR_PIN 12
#define OLED_SDA 19
#define OLED_SCL 18

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

 
  pinMode(VIBRATOR_PIN, OUTPUT); //initialize the vibrator pins

  // Initialize I2C with your specific pins
  Wire.begin(OLED_SDA, OLED_SCL);

  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is common I2C address
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // Clear the buffer
  display.clearDisplay();
}

void loop() {
  // 1. Turn Vibrator ON
  digitalWrite(VIBRATOR_PIN, HIGH);

  // 2. Display Message
  display.clearDisplay();
  display.setTextSize(2);      
  display.setTextColor(WHITE); 
  display.setCursor(10, 20);   
  display.println("BUZZING!");
  display.display(); 

  delay(2000); 

 
  digitalWrite(VIBRATOR_PIN, LOW);

 
  display.clearDisplay();
  display.setCursor(10, 20);
  display.println("QUIET...");
  display.display();

  delay(2000);  
}
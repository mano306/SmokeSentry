#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C  // Try 0x3D if OLED doesn't work

#define MQ2_PIN     34     // Analog input pin for MQ-2 sensor
#define LED_PIN     2      // Red LED pin
#define BUZZER_PIN  5      // Buzzer pin
#define THRESHOLD   400    // Smoke level threshold

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("⚠️ OLED initialization failed"));
    while (true);  // Stop here if OLED fails
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("🚨 SmokeSentry Booting...");
  display.display();
  delay(2000);
}

void loop() {
  int gasValue = analogRead(MQ2_PIN);
  Serial.print("Gas level: ");
  Serial.println(gasValue);

  bool smokeDetected = gasValue > THRESHOLD;

  // Display values on OLED
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Gas: ");
  display.println(gasValue);

  display.setTextSize(1);
  display.setCursor(0, 40);
  if (smokeDetected) {
    display.println("⚠️ Smoke Detected!");
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    display.println("✅ Air is Clean");
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  display.display();
  delay(1000);
}

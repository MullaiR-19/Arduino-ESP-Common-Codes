#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Set the screen dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create an instance of the display
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define FEEDER_PIN 3
#define TIMER_CONTROLLER_PIN A0

float intervalHours[9] = { 0.3, 0.5, 1, 2, 4, 6, 8, 12, 24 };  // Initializes the array with values.

int timerVal = 0;



void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(2);  // Normal text size
  display.setCursor(20, 0);
  display.print(F("Fish Feeder"));
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {

  timerVal = map(analogRead(TIMER_CONTROLLER_PIN), 0, 1023, 0, 9);

  display.clearDisplay();
  display.setTextSize(1);  // Normal text size
  display.setCursor(0, 0);
  display.print(F("Fish Feeder"));
  display.setCursor(0, 30);
  display.print(F("Feeding interval: "));
  display.setCursor(90, 30);
  display.display();


  delay(intervalHours[timer] * 60 * 60);
}

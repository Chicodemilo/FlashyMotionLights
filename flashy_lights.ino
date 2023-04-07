#include <Adafruit_NeoPixel.h>

// Pin assignments
#define MOTION_PIN 13
#define LED_STRIP_PIN 5
#define BUTTON_PIN 12
#define ONBOARD_LED_PIN 2

// LED strip configurations
#define NUM_LEDS 5
Adafruit_NeoPixel strip(NUM_LEDS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);

// Blink timings
unsigned long previousMillis = 0;
int blinkCount = 0;
bool blinking = false;
int ledMode = 1;

void setup() {
  // Initialize pins
  pinMode(MOTION_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(ONBOARD_LED_PIN, OUTPUT);

  // Initialize the LED strip
  strip.begin();
  strip.show();
}

void loop() {
  int motion_detected = digitalRead(MOTION_PIN);
  int button_pressed = digitalRead(BUTTON_PIN) == LOW;

  if (motion_detected && !blinking) {
    blinking = true;
    previousMillis = millis();
  }

  if (blinking) {
    digitalWrite(ONBOARD_LED_PIN, HIGH);
    delay(50);
    digitalWrite(ONBOARD_LED_PIN, LOW);
    blinking = false;

    switch (ledMode) {
      case 1:
        ledMode1();
        break;
      case 2:
        ledMode2();
        break;
      case 3:
        ledMode3();
        break;
      case 4:
        ledMode4();
        break;
    }
  }

  if (button_pressed) {
    ledMode = (ledMode % 4) + 1;
    for (int i = 0; i < ledMode; i++) {
      strip.fill(strip.Color(255, 0, 0));
      strip.show();
      delay(150);
      strip.clear();
      strip.show();
      delay(150);
    }
  }
}

void ledMode1() {
  // Blink the LED strip blue for 5 seconds
  strip.fill(strip.Color(0, 0, 255));
  strip.show();
  delay(5000);
  strip.clear();
  strip.show();
}

void ledMode2() {
  // Gold sparkles for 5 seconds
  unsigned long sparkleStart = millis();
  while (millis() - sparkleStart < 5000) {
    int led = random(NUM_LEDS);
    strip.setPixelColor(led, strip.Color(255, 215, 0));
    strip.show();
    delay(50);
    strip.setPixelColor(led, strip.Color(0, 0, 0));
    strip.show();
  }
  strip.clear();
  strip.show();
}

void ledMode3() {
  // Red back and forth like KITT in Knight Rider
  int dir = 1;
  int pos = 0;
  unsigned long kittStart = millis();
  while (millis() - kittStart < 5000) {
    strip.clear();
    strip.setPixelColor(pos, strip.Color(255, 0, 0));
    strip.show();
    delay(67); // Speed up by 1.5x
    pos += dir;
    if (pos == NUM_LEDS - 1 || pos == 0) {
      dir = -dir;
    }
  }
  strip.clear();
  strip.show();
}

void ledMode4() {
  // Smooth color transition from right to left for 5 seconds
  unsigned long transitionStart = millis();
  const uint32_t colors[] = {
    strip.Color(0, 0, 255),    // dark blue
    strip.Color(255, 0, 0),    // dark red
    strip.Color(255, 140, 0),  // dark orange
    strip.Color(255, 200, 0),  // dark yellow
    strip.Color(0, 255, 0),    // dark green
    strip.Color(100, 0, 200),  // dark purple
    strip.Color(139, 0, 139),  // dark magenta
    strip.Color(0, 200, 200),  // dark cyan
    strip.Color(128, 0, 128),  // dark mauve
    strip.Color(75, 0, 130)    // deep indigo
  };
  const int numColors = sizeof(colors) / sizeof(colors[0]);

  while (millis() - transitionStart < 5000) {
    uint32_t color = colors[random(numColors)];

    for (int i = NUM_LEDS - 1; i >= 0; i--) {
      for (int j = NUM_LEDS - 1; j >= i; j--) {
        strip.setPixelColor(j, color);
      }
      strip.show();
      delay(100);
    }
  }
  strip.clear();
  strip.show();
}


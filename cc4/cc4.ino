#include <Adafruit_NeoPixel.h>

#define LED_PIN1    6
#define LED_PIN2    7
#define LED_PIN3    8
#define LED_PIN4    9
#define NUM_LEDS    240
#define BREATHE_DELAY  15

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(NUM_LEDS, LED_PIN4, NEO_GRB + NEO_KHZ800);

int breatheBrightness = 0;
int breatheDirection = 1;
unsigned long lastBreatheMillis = 0;
char currentMode = '0';

void setup() {
  strip1.begin();
  strip1.show();
  strip2.begin();
  strip2.show();
  strip3.begin();
  strip3.show();
  strip4.begin();
  strip4.show();
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastBreatheMillis >= BREATHE_DELAY) {
    lastBreatheMillis = currentMillis;
    if (currentMode == 'W') {
      breatheEffect(strip1, 255, 255, 255);
      breatheEffect(strip2, 255, 255, 255);
      breatheEffect(strip3, 255, 255, 255);
      breatheEffect(strip4, 255, 255, 255);
    } else if (currentMode == 'O') {
      breatheEffect(strip1, 255, 80, 0); // 橙色
      breatheEffect(strip2, 255, 80, 0);
      breatheEffect(strip3, 255, 80, 0);
      breatheEffect(strip4, 255, 80, 0);
    }
  }

  if (Serial.available() > 0) {
    currentMode = Serial.read();
  }
}

void breatheEffect(Adafruit_NeoPixel &strip, int red, int green, int blue) {
  setAllLedsWithBrightness(strip, red, green, blue, breatheBrightness);
  breatheBrightness += breatheDirection;
  if (breatheBrightness <= 0 || breatheBrightness >= 255) {
    breatheDirection *= -1;
  }
}

void setAllLedsWithBrightness(Adafruit_NeoPixel &strip, int red, int green, int blue, int brightness) {
  strip.setBrightness(brightness);
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(red, green, blue));
  }
  strip.show();
}

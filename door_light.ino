#include <FastLED.h>

#define NUM_LEDS 38
#define PIN 7
#define LEN 8

CRGB leds[NUM_LEDS];
int brightness[NUM_LEDS];
int hue[NUM_LEDS];
boolean on = false;
int inc = 0;
int hueInc = 0;

int ledPin = 13;                // choose the pin for the LED
int inputPin = 3;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;
int timeLeft = 0;
int delayTime = 25;

void setup() {
  LEDS.addLeds<WS2812, PIN, RGB>(leds, NUM_LEDS);
  LEDS.setBrightness(255);
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);
}

void readMotion() {
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      pirState = HIGH;
      timeLeft = 1500;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH) {
      Serial.println("Motion ended!");
      pirState = LOW;
    }
  }
}

void loop() {
  readMotion();

  if (timeLeft > 0) {
    timeLeft = 0;

    //    for (int a = 0; a < 2; a++) {

    for (int x = 0; x < NUM_LEDS / 2; x++) {
      leds[x] = CHSV(220, 255, 255);
      leds[NUM_LEDS - x] = CHSV(220, 255, 255);
      delay(delayTime);
      FastLED.show();
    }

    for (int x = 0; x < NUM_LEDS / 2; x++) {
      leds[x] = CHSV(170, 255, 0);
      leds[NUM_LEDS - x] = CHSV(170, 255, 0);
      delay(delayTime);
      FastLED.show();
    }

    for (int x = NUM_LEDS / 2; x > 0; x--) {
      leds[x] = CHSV(220, 255, 255);
      leds[NUM_LEDS - x] = CHSV(220, 255, 255);
      delay(delayTime);
      FastLED.show();
    }

    for (int x = NUM_LEDS / 2; x > 0; x--) {
      leds[x] = CHSV(170, 255, 0);
      leds[NUM_LEDS - x] = CHSV(170, 255, 0);
      delay(delayTime);
      FastLED.show();
    }
    //    }
  }

  if (timeLeft == 0) {
    for (int x = 0; x < NUM_LEDS; x++) {
      leds[x] = CHSV(0, 0, 0);
      for (int a = NUM_LEDS - 1; a > 0; a--) {
        hue[a] = 0;
        brightness[a] = 0;
      }
      FastLED.show();
    }

  }
}

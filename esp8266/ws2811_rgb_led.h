#ifndef WS2811_RGB_LED_H
#define WS2811_RGB_LED_H

#include <FastLED.h>
#define NUM_LEDS 1
#define DATA_PIN 4

CRGB leds[NUM_LEDS];
CRGB& rgb_led = leds[0];
void setup_rgb_led() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(16);
    rgb_led.setHue(0);
    FastLED.show();
}

#endif

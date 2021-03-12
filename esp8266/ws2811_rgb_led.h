#ifndef WS2811_RGB_LED_H
#define WS2811_RGB_LED_H

#include <FastLED.h>
#define NUM_LEDS (1)
#define DATA_PIN (4)

CRGB __leds[NUM_LEDS];
CRGB& rgb_led = __leds[0];
void setup_rgb_led() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(__leds, NUM_LEDS);
    // FastLED.setBrightness(16); // AAAAAAA MY EYES
    FastLED.clear();
    FastLED.show();
}

#endif

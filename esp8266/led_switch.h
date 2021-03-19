#include "lib/ws2811_rgb_led.h"

boolean switchState = false;
double brightness = 0;

ICACHE_RAM_ATTR void toggle() {
    switchState = !switchState;
    brightness = switchState ? 8 : 0;
    Serial.println(switchState ? "on" : "off");
}

void setup() {
    Serial.begin(115200);
    setup_rgb_led();
    rgb_led = CRGB::White;
    FastLED.setBrightness(0);
    FastLED.show();

    pinMode(D8, INPUT);
    attachInterrupt(digitalPinToInterrupt(D8), toggle, RISING);

    Serial.println("ready");
}

void loop() {
    FastLED.setBrightness(brightness);
    FastLED.show();
    while (switchState && digitalRead(D8) == 1 && brightness < 255) {
        brightness += 0.5;
        if (brightness > 255) brightness = 255;
        FastLED.setBrightness(brightness);
        FastLED.show();
    }
}

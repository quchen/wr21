#include "util.h"
#include "bh1750_light.h"
#include "ws2811_rgb_led.h"
#include "bme280_temperature_humidity_pressure.h"

void setup_serial() {
    Serial.begin(115200);
    while (!Serial) {
        delay(10);
    }
    delay(100);
    Serial.println("");
    Serial.println("Serial set up");
}

#define LED2_BUILTIN (2)

void builtin_led_on(bool on) {
    digitalWrite(LED_BUILTIN, on ? LOW : HIGH);
}

void builtin_led2_on(bool on) {
    digitalWrite(LED2_BUILTIN, on ? LOW : HIGH);
}

void setup_builtin_leds() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED2_BUILTIN, OUTPUT);
    builtin_led_on(false);
    builtin_led2_on(false);
    pinMode(14, INPUT_PULLUP);
}

void setup() {
    setup_serial();
    setup_builtin_leds();
    setup_rgb_led();
    setup_bh1750_light_sensor();
    setup_bme280_temperature_humidity_pressure_sensor();
}

float lux, celsius;
int hue = 0;
int brightness = 0;
void loop() {
    lux = measure_light_level_lux();
    celsius = measure_temperature_celsius();

    brightness = ema(brightness, constrain(map(lux, 25., 50., 255, 0), 0, 255), 0.2);
    hue = ema(celsius, map(celsius, 20, 30, 0, 255), 0.5);
    rgb_led.setHSV(hue, 255, brightness);
    FastLED.show();
    delay(20);
}

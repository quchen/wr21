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

void setup_builtin_led() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void builtin_led_on(bool state) {
    digitalWrite(LED_BUILTIN, state ? LOW : HIGH);
}

void setup() {
    setup_serial();
    setup_builtin_led();
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

    brightness = exponential_moving_average(brightness, constrain(map(lux, 75., 100., 255, 0), 0, 255), 0.2);
    hue = exponential_moving_average(celsius, map(celsius, 20, 30, 0, 255), 0.5);
    rgb_led.setHSV(hue, 255, brightness);
    FastLED.show();
    delay(20);
}

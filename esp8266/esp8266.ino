#include "bh1750_light.h"
#include "si7021_temperature_humidity.h"
// #include "bme280_temperature_humidity_pressure.h"
#include "ws2811_rgb_led.h"



void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(10);
    }

    setup_light_sensor();
    setup_rgb_led();
    pinMode(LED_BUILTIN, OUTPUT);
}

void builtin_led_on(bool state) {
    digitalWrite(LED_BUILTIN, state ? LOW : HIGH);
}

int hue = 0;
void loop() {
    builtin_led_on(true);
    float lux = measure_light_level_lux();
    float celsius = measure_temperature_celsius();
    float humidity = measure_rel_humidity();
    Serial.printf("%f,%f,%f\n", lux, celsius, humidity);
    rgb_led.setHue(hue);
    hue = (hue + 20) % 256;
    FastLED.show();
    delay(50);
    builtin_led_on(false);
    delay(1000);
}

#include "bh1750_light.h"
// #include "si7021_temperature_humidity.h"
#include "ws2811_rgb_led.h"
#include "bme280_temperature_humidity_pressure.h"



void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(10);
    }

    setup_light_sensor();
    setup_rgb_led();
    setup_bme280_temperature_humidity_pressure();
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
    float hPa = measure_pressure_pascal() / 100;
    float altitude = measure_altitude_meters();
    Serial.printf("%f,%f,%f,%f,%f\n", lux, celsius, humidity, hPa, altitude);
    rgb_led.setHue(hue);
    hue = (hue + 20) % 256;
    FastLED.show();
    delay(50);
    builtin_led_on(false);
    delay(1000);
}

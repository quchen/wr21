#include "lib/util.h"
#include "lib/bh1750_light.h"
#include "lib/ws2811_rgb_led.h"
#include "lib/bme280_temperature_humidity_pressure.h"

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
}

void setup() {
    setup_serial();
    setup_builtin_leds();
    setup_rgb_led();
    setup_bh1750_light_sensor();
    setup_bme280_temperature_humidity_pressure_sensor();
}


unsigned long       last_measurement_ms = 0;
const unsigned long measure_interval_ms = 20;
unsigned long       now_ms;
unsigned long       since_last_measurement_ms;
bool                measurement_outstanding;

float lux, celsius;
int led_hue = 0;
int led_brightness = 0;
const float dark_lux = 50;
const float bright_lux = 150;
void loop() {
    now_ms = millis();
    since_last_measurement_ms = now_ms - last_measurement_ms;
    measurement_outstanding = since_last_measurement_ms > measure_interval_ms;
    if(measurement_outstanding) {
        last_measurement_ms = now_ms;
        lux = measure_light_level_lux();
        celsius = measure_temperature_celsius();
    }

    led_brightness = ema(led_brightness, constrain(map(lux, bright_lux, dark_lux, 0, 255), 0, 255), 0.1);
    led_hue = ema(led_hue, map(celsius, 20, 30, 0, 255), 0.1);
    rgb_led.setHSV(led_hue, 255, led_brightness);
    FastLED.show();
    delay(20);
}

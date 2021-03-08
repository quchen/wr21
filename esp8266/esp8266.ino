#include <Wire.h>
#include <BH1750.h> // Light sensor, Lib: BH1750 by Christopher Laws
#include "Adafruit_Si7021.h" // Library: Adafruit Si7021

BH1750 lightSensor;
Adafruit_Si7021 tempHumSensor = Adafruit_Si7021();
void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(10);
    }
    Wire.begin();
    lightSensor.begin();
    pinMode(LED_BUILTIN, OUTPUT);
}

void builtin_led_on(bool state) {
    digitalWrite(LED_BUILTIN, state ? LOW : HIGH);
}

float measure_light_level_lux() {
    return lightSensor.readLightLevel();
}

float measure_rel_humidity() {
    return tempHumSensor.readHumidity();
}

float measure_temperature_celsius() {
    return tempHumSensor.readTemperature();
}

void loop() {
    builtin_led_on(true);
    float lux = measure_light_level_lux();
    float celsius = measure_temperature_celsius();
    float humidity = measure_rel_humidity();
    Serial.printf("%f,%f,%f\n", lux, celsius, humidity);
    delay(100);
    builtin_led_on(false);
    delay(1000);
}

#include "bh1750_light.h"

#include "Adafruit_Si7021.h" // Library: Adafruit Si7021

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_Si7021 tempHumSensor = Adafruit_Si7021();
Adafruit_BME280 thpSensor;
void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(10);
    }
    setup_light_sensor();
    pinMode(LED_BUILTIN, OUTPUT);

    unsigned status = thpSensor.begin();
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(thpSensor.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(100);
    }
}

void builtin_led_on(bool state) {
    digitalWrite(LED_BUILTIN, state ? LOW : HIGH);
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

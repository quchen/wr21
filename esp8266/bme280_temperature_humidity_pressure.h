#ifndef BME280_TEMPERATURE_HUMIDITY_PRESSURE_H
#define BME280_TEMPERATURE_HUMIDITY_PRESSURE_H

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 __bme280;

void setup_bme280_temperature_humidity_pressure_sensor() {
    unsigned int status = __bme280.begin(0x76);
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1) delay(100);
    }
}

float measure_rel_humidity() {
    return __bme280.readHumidity();
}

float measure_temperature_celsius() {
    return __bme280.readTemperature();
}

float measure_pressure_pascal() {
    return __bme280.readPressure();
}

float measure_altitude_meters() {
    return __bme280.readAltitude(SEALEVELPRESSURE_HPA);
}

#endif

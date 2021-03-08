#ifndef BME280_TEMPERATURE_HUMIDITY_PRESSURE_H
#define BME280_TEMPERATURE_HUMIDITY_PRESSURE_H

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 __bme280;

void setup_bme280_temperature_humidity_pressure_sensor() {
    unsigned int status = __bme280.begin(0x76);
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(__bme280.sensorID(), 16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
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

#ifndef BME280_TEMPERATURE_HUMIDITY_PRESSURE_H
#define BME280_TEMPERATURE_HUMIDITY_PRESSURE_H

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme280;

void setup_bme280_temperature_humidity_pressure_sensor() {
    unsigned int status = bme280.begin(0x76);
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme280.sensorID(), 16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(100);
    }
}

float measure_rel_humidity() {
    return bme280.readHumidity();
}

float measure_temperature_celsius() {
    return bme280.readTemperature();
}

float measure_pressure_pascal() {
    return bme280.readPressure();
}

float measure_altitude_meters() {
    return bme280.readAltitude(SEALEVELPRESSURE_HPA);
}

#endif

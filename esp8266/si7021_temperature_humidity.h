#ifndef SI17021_TEMPERATURE_HUMIDITY_SENSOR_H
#define SI17021_TEMPERATURE_HUMIDITY_SENSOR_H

#include "Adafruit_Si7021.h" // Library: Adafruit Si7021


Adafruit_Si7021 tempHumSensor = Adafruit_Si7021();

float measure_rel_humidity() {
    return tempHumSensor.readHumidity();
}

float measure_temperature_celsius() {
    return tempHumSensor.readTemperature();
}

#endif

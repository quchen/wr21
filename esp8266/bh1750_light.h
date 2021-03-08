#ifndef BH1750_LIGHT_SENSOR_H
#define BH1750_LIGHT_SENSOR_H

#include <Wire.h>
#include <BH1750.h> // Light sensor, Lib: BH1750 by Christopher Laws

BH1750 bh1750_light_sensor;

void setup_light_sensor() {
    Wire.begin();
    bh1750_light_sensor.begin();
}

float measure_light_level_lux() {
    return bh1750_light_sensor.readLightLevel();
}

#endif

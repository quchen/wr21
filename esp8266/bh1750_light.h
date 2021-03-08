#ifndef BH1750_LIGHT_SENSOR_H
#define BH1750_LIGHT_SENSOR_H

#include <Wire.h>
#include <BH1750.h> // Light sensor, Lib: BH1750 by Christopher Laws

BH1750 bh1750_light_sensor;

// High res: 0.5 lux, 120ms measure time
// Low res: 4 lux, 16ms measure time
void setup_bh1750_light_sensor(bool highres = false) {
    Wire.begin();
    bh1750_light_sensor.begin(highres ? BH1750::CONTINUOUS_HIGH_RES_MODE_2 : BH1750::CONTINUOUS_LOW_RES_MODE);
}

float measure_light_level_lux() {
    return bh1750_light_sensor.readLightLevel();
}

#endif

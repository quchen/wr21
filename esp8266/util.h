#ifndef UTIL_H
#define UTIL_H

float exponential_moving_average(float old_value, float new_value, float alpha) {
    return alpha*new_value + (1 - alpha)*old_value;
}

#endif

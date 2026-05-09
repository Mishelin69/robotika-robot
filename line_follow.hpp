#pragma once

#define LEFT_SENSOR_PIN (35)
#define RIGHT_SENSOR_PIN (39)
#define BLACK_LINE (2000)

#include <vehicle.h>

void linetracking_init();

bool is_line_in_front_of_car();

bool does_any_sensor_see_black();

int linetracking_get_left_dist();

int linetracking_get_right_dist();
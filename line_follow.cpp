#include "line_follow.hpp"

#include <Arduino.h>

static bool has_linetracking_been_initialized = false;

void linetracking_init() {
  has_linetracking_been_initialized = true;
  pinMode(LEFT_SENSOR_PIN, INPUT);
  pinMode(RIGHT_SENSOR_PIN, INPUT);
}

bool is_line_in_front_of_car() {
  if (!has_linetracking_been_initialized) {
    return false;
  }

  int left_dst = linetracking_get_left_dist();
  int right_dst = linetracking_get_right_dist();

  return left_dst < BLACK_LINE && right_dst < BLACK_LINE;
}

bool does_any_sensor_see_black() {
    if (!has_linetracking_been_initialized) {
    return false;
  }

  int left_dst = linetracking_get_left_dist();
  int right_dst = linetracking_get_right_dist();

  return left_dst <= 300 || right_dst <= 1000;
}

int linetracking_get_left_dist() {
  return analogRead(LEFT_SENSOR_PIN);
}

int linetracking_get_right_dist() {
  return analogRead(RIGHT_SENSOR_PIN);
}
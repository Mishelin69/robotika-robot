#include "wait_for_starting_codintion.hpp"
#include "line_follow.hpp"

#include "led.hpp"
#include "ultrasound.hpp"

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

static bool obj_detected_in_range = false;
static bool line_tracking_active = false;

static int both_sensors_active = 0;
static int obj_off_screen = 0;

void wait_for_starting_condition() {
  led_turn_off_all();

  while (true) {
    if (both_sensors_active >= ACTIVE_IS_WIN_MIN*5) {
      break;
    }

    int both_locked = 0;

    if (is_object_detected_in_distance_range()) {
      led_turn_on_ultrasound_obj_detected();
      obj_detected_in_range = true;
      both_locked += 1;
    }
    else {
      led_turn_off_ultrasound_obj_detected();
      obj_detected_in_range = false;
    }

    if (is_line_in_front_of_car()) {
      led_turn_on_line_tracking_detected();
      line_tracking_active = true;
      both_locked += 1;
    }
    else {
      led_turn_off_line_tracking_detected();
      line_tracking_active = false;
    }

    if (both_locked == 2) {
      both_sensors_active += 1;
    }
    else {
      both_sensors_active = 0;
    }

    delay(100);
  }

  wait_for_object_to_be_pulled_away();
}

void wait_for_object_to_be_pulled_away() {
  while (true) {
    if (obj_off_screen >= ACTIVE_IS_WIN_MIN) {
      break;
    }

    if (!is_object_detected_in_distance_range()) {
      obj_off_screen += 1;
    }
    else {
      obj_off_screen = 0;
    }

    delay(1000);
  }

  led_turn_off_all();
}

bool is_object_detected_in_distance_range() {
  int current_sensor_read_distance = ultrasound_get_distance();
  return current_sensor_read_distance >= (ACTIVATE_DISTANCE_CM - ACTIVATE_DISTANCE_ERROR_CM) && 
         current_sensor_read_distance <= (ACTIVATE_DISTANCE_CM + ACTIVATE_DISTANCE_ERROR_CM);
}

#ifdef __cplusplus
}
#endif
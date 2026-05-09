#include "led.hpp"

#include "stdbool.h"

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

static bool LEFT_LIGHT_ON = false;

static bool RIGHT_LIGHT_ON = false;

void led_setup() {
  pinMode(LEFT_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
  led_turn_off_all();
}

void led_turn_on_line_tracking_detected() {
  LEFT_LIGHT_ON = true;
  digitalWrite(LEFT_LED, HIGH);
}

void led_turn_on_ultrasound_obj_detected() {
  RIGHT_LIGHT_ON = true;
  digitalWrite(RIGHT_LED, HIGH);
}

void led_turn_off_line_tracking_detected() {
  LEFT_LIGHT_ON = false;
  digitalWrite(LEFT_LED, LOW);
}

void led_turn_off_ultrasound_obj_detected() {
  RIGHT_LIGHT_ON = false;
  digitalWrite(RIGHT_LED, LOW);
}

void led_turn_off_all() {
  led_turn_off_line_tracking_detected();
  led_turn_off_ultrasound_obj_detected();
}

void led_signal_victory() {
  if (!(LEFT_LIGHT_ON | RIGHT_LIGHT_ON)) {
    LEFT_LIGHT_ON = true;
  }

  if (LEFT_LIGHT_ON) {
    led_turn_off_ultrasound_obj_detected();
    led_turn_on_line_tracking_detected();
    LEFT_LIGHT_ON = false;
    RIGHT_LIGHT_ON = true;
  }
  else {
    led_turn_off_line_tracking_detected();
    led_turn_on_ultrasound_obj_detected();
    LEFT_LIGHT_ON = true;
    RIGHT_LIGHT_ON = false;
  }
}

#ifdef __cplusplus
}
#endif
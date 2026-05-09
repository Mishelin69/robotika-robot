#pragma once

#define LEFT_LED (12)
#define RIGHT_LED (2)

#ifdef __cplusplus
extern "C" {
#endif

void led_setup();

void led_turn_on_line_tracking_detected();

void led_turn_on_ultrasound_obj_detected();

void led_turn_off_line_tracking_detected();

void led_turn_off_ultrasound_obj_detected();

void led_turn_off_all();

void led_signal_victory();

#ifdef __cplusplus
}
#endif
#pragma once

#define ULTRASOUND_TRIG_PIN (13)
#define ULTRASOUND_ECHO_PIN (14)
#define ULTRASOUND_SERVO_PIN (25)
#define ULTRASOUND_SERVO_STRAIGHT (98)
#define ULTRASOUND_SERVO_RIGHT (68)
#define ULTRASOUND_SERVO_LEFT (128)

#include <ultrasonic.h>

void ultrasound_init();

int ultrasound_get_distance();

void ultrasound_calibrate_position();

void ultrasound_look_angle(int angle);
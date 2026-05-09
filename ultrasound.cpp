#include "ultrasound.hpp"

#include <ESP32Servo.h>

static Servo servo;

static ultrasonic ultrasonic_device;
static bool has_device_been_initialized = false;

void ultrasound_init() {
  servo.attach(ULTRASOUND_SERVO_PIN);
  ultrasonic_device.Init(ULTRASOUND_TRIG_PIN, ULTRASOUND_ECHO_PIN);
  has_device_been_initialized = true;
  ultrasound_calibrate_position();
}

int ultrasound_get_distance() {
  if (!has_device_been_initialized) {
    return -1;
  }

  return ultrasonic_device.Ranging();
}

void ultrasound_calibrate_position() {
  servo.write(ULTRASOUND_SERVO_STRAIGHT);
  delay(1000);

  servo.detach();
}

void ultrasound_look_angle(int angle) {
  if (!servo.attached()) {
    servo.attach(ULTRASOUND_SERVO_PIN); 
  }
  
  servo.write(angle);
  delay(500); 
  servo.detach(); 
}
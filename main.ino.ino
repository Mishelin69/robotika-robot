#include "led.hpp"
#include "wait_for_starting_codintion.hpp"
#include "ultrasound.hpp"
#include "line_follow.hpp"
#include "foraging.hpp"

void setup() {
  Serial.begin(9600);
  linetracking_init();
  ultrasound_init();
  init_car();
  led_setup();
}

void loop() {
  wait_for_starting_condition();
  start_foraging();

  Serial.println("Victory!");
  while (true) {
    led_signal_victory();
    delay(500);
  }
}
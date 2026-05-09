#include "foraging.hpp"

#include "line_follow.hpp"
#include "ultrasound.hpp"

#include <vehicle.h>

#include <Arduino.h>

#include <esp_random.h>

static vehicle car;
static int consecutive_fails = 0;
static int found_target_count = 0;

void init_car() {
  car.Init();
}

void start_foraging() {
  jesus_take_the_wheel_go_forward();

  while (true) {
    if (check_for_victory()) {
      break; 
    }

    if (consecutive_fails >= NUM_OF_ALLOWED_FAILS) {
      car_panic_turn_after_stuck();
    }

    execute_weighted_turn();

    if (!check_safe_distance()) {
      delay(200);
      continue;
    }
    
    consecutive_fails = 0;

    if (move_forward_and_check()) {
      break;
    }

    delay(200);
  }

  car.Move(Stop, 0);
}

bool move_forward_and_check() {
  int move_for_ms = calculate_levy_time();
  int time_driven = 0;

  car.Move(Forward, CAR_SPEED-80);

  while (time_driven < move_for_ms) {

    if (check_for_victory()) {
      car.Move(Stop, 0);
      return true;
    }

    if (!check_safe_distance()) {
      break;
    }
    
    delay(50);
    time_driven += 50;
  }

  car.Move(Stop, 0);
  delay(300);
  return false;
}

void execute_weighted_turn() {
  int roll = esp_random() % 101; 
  int turn_time = 250 + (esp_random() % 200) - 99;

  if (roll <= 50) {
    return;
  } else if (roll <= 75) {
    car.Move(Clockwise, CAR_SPEED);
    delay(turn_time);
    car.Move(Stop, 0);
  } else {
    car.Move(Contrarotate, CAR_SPEED);
    delay(turn_time);
    car.Move(Stop, 0);
  }
}

//Levy flight approximated by Inverse Transform Sampling Pareto Distribution
int calculate_levy_time() {
  float u = ((esp_random() % 1000) + 1) / 1000.0;
  float calculated_time = MIN_STEP_TIME_MS * pow(u, -1.0 / LEVY_BETA);
  
  int final_time = (int)calculated_time;

  if (final_time > MAX_STEP_TIME_MS) {
    final_time = MAX_STEP_TIME_MS;
  }

  return final_time;
}

void jesus_take_the_wheel_go_forward() {
  car.Move(Forward, CAR_SPEED);
  delay(1250);
  car.Move(Stop, 0);
  delay(2000);
}

void car_panic_turn_after_stuck() {
  car.Move(Backward, CAR_SPEED/2);
  delay(300);
  car.Move(Stop, 0);

  ultrasound_look_angle(ULTRASOUND_SERVO_RIGHT);

  int dist_right = ultrasound_get_distance();
  if (dist_right <= 0) {
    dist_right = 0;
  }

  ultrasound_look_angle(ULTRASOUND_SERVO_LEFT);
  int dist_left = ultrasound_get_distance();
  if (dist_left <= 0) {
    dist_left = 0;
  }

  ultrasound_look_angle(ULTRASOUND_SERVO_STRAIGHT);

  if (dist_right > dist_left) {
    car.Move(Clockwise, CAR_SPEED/2); 
  } else {
    car.Move(Contrarotate, CAR_SPEED/2);
  }

  delay(350 + esp_random() % 200); 
  car.Move(Stop, 0);

  consecutive_fails = 0;
}

bool check_for_victory() {
  if (does_any_sensor_see_black()) {
    found_target_count += 1;
  } else {
    found_target_count = 0;
  }

  return found_target_count >= FOUND_TARGET_TIMES;
}

bool check_safe_distance() {
  int sensor_distance = ultrasound_get_distance();
  
  if (sensor_distance > 0 && sensor_distance > DANGEROUS_DISTANCE_CM) {
    return true;
  }

  consecutive_fails += 1;
  return false;
}
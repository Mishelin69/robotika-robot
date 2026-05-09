#pragma once

#define CAR_SPEED (255)
#define NUM_OF_ALLOWED_FAILS (1)
#define DANGEROUS_DISTANCE_CM (15)

#define LEVY_BETA (1.2)
#define MIN_STEP_TIME_MS (400)
#define MAX_STEP_TIME_MS (3000)
#define FOUND_TARGET_TIMES (5)

void init_car();

void car_panic_turn_after_stuck();

void start_foraging();

void execute_weighted_turn();

int calculate_levy_time();

void jesus_take_the_wheel_go_forward();

bool move_forward_and_check();

bool check_for_victory();

bool check_safe_distance();
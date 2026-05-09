#pragma once

#define ACTIVATE_DISTANCE_CM (17)
#define ACTIVATE_DISTANCE_ERROR_CM (3)
#define ACTIVE_IS_WIN_MIN (5)

#ifdef __cplusplus
extern "C" {
#endif

void wait_for_starting_condition();

void wait_for_object_to_be_pulled_away();

bool is_object_detected_in_distance_range();

#ifdef __cplusplus
}
#endif
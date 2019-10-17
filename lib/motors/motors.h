#ifndef WHEELIE_MOTORS
#define WHEELIE_MOTORS

#include "wheelie_config.h"

// Signed speed
void set_left_speed(int target_speed);
void set_right_speed(int target_speed);

void encoders_setup_interrupts();

Direction get_left_direction();
Direction get_right_direction();

int get_left_speed();
int get_right_speed();

#endif

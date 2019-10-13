#ifndef WHEELIE_ENCODERS
#define WHEELIE_ENCODERS

#include <Energia.h>
#include "wheelie_config.h"

enum Direction {
    FORWARD,
    REVERSE
};

volatile static bool _encoders_left_a_set;
volatile static bool _encoders_left_b_set;
volatile static bool _encoders_left_a_prev;
volatile static bool _encoders_left_b_prev;

volatile static bool _encoders_right_a_set;
volatile static bool _encoders_right_b_set;
volatile static bool _encoders_right_a_prev;
volatile static bool _encoders_right_b_prev;

volatile static unsigned long _encoders_last_left_mot;
volatile static unsigned long _encoders_last_right_mot;

volatile static Direction _left_direction;
volatile static unsigned long _left_interval;

volatile static Direction _right_direction;
volatile static unsigned long _right_interval;

void encoders_setup_interrupts();

Direction get_left_direction();
Direction get_right_direction();

int get_left_speed();
int get_right_speed();

#endif

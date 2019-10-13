#include <msp430f5529.h>

#include "encoders.h"
#include "wheelie_util.h"

Direction _parse_left_encoder() {
  if (_encoders_left_a_prev && _encoders_left_b_prev) {
    if (!_encoders_left_a_set && _encoders_left_b_set)
      return REVERSE;
    if (_encoders_left_a_set && !_encoders_left_b_set)
      return FORWARD;
  } else if (!_encoders_left_a_prev && _encoders_left_b_prev) {
    if (!_encoders_left_a_set && !_encoders_left_b_set)
      return REVERSE;
    if (_encoders_left_a_set && _encoders_left_b_set)
      return FORWARD;
  } else if (!_encoders_left_a_prev && !_encoders_left_b_prev) {
    if (_encoders_left_a_set && !_encoders_left_b_set)
      return REVERSE;
    if (!_encoders_left_a_set && _encoders_left_b_set)
      return FORWARD;
  } else if (_encoders_left_a_prev && !_encoders_left_b_prev) {
    if (_encoders_left_a_set && _encoders_left_b_set)
      return REVERSE;
    if (!_encoders_left_a_set && !_encoders_left_b_set)
      return FORWARD;
  }
}

Direction _parse_right_encoder() {
  if (_encoders_right_a_prev && _encoders_right_b_prev) {
    if (!_encoders_right_a_set && _encoders_right_b_set)
      return REVERSE;
    if (_encoders_right_a_set && !_encoders_right_b_set)
      return FORWARD;
  } else if (!_encoders_right_a_prev && _encoders_right_b_prev) {
    if (!_encoders_right_a_set && !_encoders_right_b_set)
      return REVERSE;
    if (_encoders_right_a_set && _encoders_right_b_set)
      return FORWARD;
  } else if (!_encoders_right_a_prev && !_encoders_right_b_prev) {
    if (_encoders_right_a_set && !_encoders_right_b_set)
      return REVERSE;
    if (!_encoders_right_a_set && _encoders_right_b_set)
      return FORWARD;
  } else if (_encoders_right_a_prev && !_encoders_right_b_prev) {
    if (_encoders_right_a_set && _encoders_right_b_set)
      return REVERSE;
    if (!_encoders_right_a_set && !_encoders_right_b_set)
      return FORWARD;
  }
}

static int _left_ticks = 0;
static int _right_ticks = 0;

void encoders_left_mot_handler_a() {
  _encoders_left_a_set = left_encoder_a();
  _encoders_left_b_set = left_encoder_b();

  unsigned long t = micros();

  _left_direction = _parse_left_encoder();
  _left_interval = t - _encoders_last_left_mot;

  _encoders_left_a_prev = _encoders_left_a_set;
  _encoders_left_b_prev = _encoders_left_b_set;
  _encoders_last_left_mot = t;
}

void encoders_left_mot_handler_b() {
  _encoders_left_a_set = left_encoder_a();
  _encoders_left_b_set = left_encoder_b();

  _encoders_left_a_prev = _encoders_left_a_set;
  _encoders_left_b_prev = _encoders_left_b_set;
}

void encoders_right_mot_handler_a() {
  _encoders_right_a_set = right_encoder_a();
  _encoders_right_b_set = right_encoder_b();

  _right_ticks += _parse_right_encoder();

  _encoders_right_a_prev = _encoders_right_a_set;
  _encoders_right_b_prev = _encoders_right_b_set;
}

void encoders_right_mot_handler_b() {
  _encoders_right_a_set = right_encoder_a();
  _encoders_right_b_set = right_encoder_b();

  _right_ticks += _parse_right_encoder();

  _encoders_right_a_prev = _encoders_right_a_set;
  _encoders_right_b_prev = _encoders_right_b_set;
}

static int _left_speed;
static int _right_speed;

#pragma vector = TIMER0_A0_VECTOR
__interrupt void CCR0_ISR(void) {
  // Timer A0 Interrupt service routine
  _right_speed += 1;
  return;
  _right_speed = 100000 / _right_ticks;
  _right_ticks = 0;
}

void encoders_setup_interrupts() {
  pinMode(LEFT_MOT_ENCODER_A, INPUT);
  pinMode(LEFT_MOT_ENCODER_B, INPUT);
  pinMode(RIGHT_MOT_ENCODER_A, INPUT);
  pinMode(RIGHT_MOT_ENCODER_B, INPUT);

  // (Re)set last interrupt times
  _encoders_last_left_mot = 0;
  _encoders_last_right_mot = 0;

  // Attach interrupts for left and right encoders
  attachInterrupt(LEFT_MOT_ENCODER_A, *encoders_left_mot_handler_a, CHANGE);
  attachInterrupt(LEFT_MOT_ENCODER_B, *encoders_left_mot_handler_b, CHANGE);
  attachInterrupt(RIGHT_MOT_ENCODER_A, *encoders_right_mot_handler_a, CHANGE);
  attachInterrupt(RIGHT_MOT_ENCODER_B, *encoders_right_mot_handler_b, CHANGE);

  // Attach timer interrupt
  TA0CCR0 = 10000;
  TA0CCTL0 |= CCIE;
  TA0CTL |= MC_1 + TASSEL_2 + TACLR;
}

Direction get_left_direction() {
  return _left_direction;
}

Direction get_right_direction() {
  return _right_direction;
}

int get_left_speed() {
  if (micros() - _encoders_last_left_mot > 10000)  // >10ms since last interrupt
    return 0;

  int sign = _left_direction ? -1 : 1;
  return sign * (1000000 / _left_interval);
}

int get_right_speed() {
  return _right_speed;
}

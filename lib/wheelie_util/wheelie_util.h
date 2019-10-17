#ifndef WHEELIE_UTIL_H
#define WHEELIE_UTIL_H

#include <msp430f5529.h>
#include "wheelie_config.h"
#include "wheelie_util.h"

static bool left_encoder_a() {
  return LEFT_MOT_EAP & LEFT_MOT_EAB;
}

static bool left_encoder_b() {
  return LEFT_MOT_EBP & LEFT_MOT_EBB;
}

static bool right_encoder_a() {
  return RIGHT_MOT_EAP & RIGHT_MOT_EAB;
}

static bool right_encoder_b() {
  return RIGHT_MOT_EBP & RIGHT_MOT_EBB;
}

#endif

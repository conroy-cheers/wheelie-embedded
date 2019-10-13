#include "wheelie_config.h"

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

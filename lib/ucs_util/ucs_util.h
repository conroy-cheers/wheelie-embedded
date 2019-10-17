#ifndef UCS_UTIL_H
#define UCS_UTIL_H

#include <inttypes.h>
#include "driverlib.h"

volatile uint32_t ACLK_value, MCLK_value, SMCLK_value;

void ucs_init_clocks() {
  PMM_setVCore(PMM_CORE_LEVEL_3);

  UCS_initClockSignal(UCS_ACLK, UCS_REFOCLK_SELECT, UCS_CLOCK_DIVIDER_1);
  UCS_initClockSignal(UCS_FLLREF, UCS_REFOCLK_SELECT, UCS_CLOCK_DIVIDER_1);
  UCS_initFLLSettle(25000, 763);

  ACLK_value = UCS_getACLK();
  MCLK_value = UCS_getMCLK();
  SMCLK_value = UCS_getSMCLK();
}

#endif

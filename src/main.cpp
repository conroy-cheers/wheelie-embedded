#include "encoders.h"
#include "ucs_util.h"
#include "wheelie_util.h"
#include <Energia.h>

bool ledVal = 0;

void setup() {
  ucs_init_clocks();

  Serial1.begin(9600);
  encoders_setup_interrupts();

  pinMode(GREEN_LED, OUTPUT);
}

char report[80];

void loop() {
  Serial1.print("right speed (ticks/s): ");
  Serial1.println(get_right_speed());

  ledVal |= 1;
  digitalWrite(GREEN_LED, ledVal);

  delay(100);
}
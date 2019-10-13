#include <Energia.h>
#include <msp430f5529.h>
#include "encoders.h"
#include "wheelie_util.h"

bool ledVal = 0;

void setup() {
  WDTCTL = WDTPW + WDTHOLD;  // Stop WDT
  
  Serial1.begin(9600);
  // encoders_setup_interrupts();

  pinMode(GREEN_LED, OUTPUT);
}

void loop() {
  Serial1.print("right speed (ticks/s): ");
  Serial1.println(get_right_speed());

  ledVal |= 1;
  digitalWrite(GREEN_LED, ledVal);

  delay(500);
}
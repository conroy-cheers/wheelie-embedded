#include <Energia.h>
#include <msp430f5529.h>
#include "LSM6.h"
#include "encoders.h"
#include "wheelie_util.h"

bool ledVal = 0;
LSM6 imu;

void setup() {
  Serial1.begin(9600);
  // encoders_setup_interrupts();

  Serial1.println("Init IMU...");
  if (!imu.init()) {
    Serial1.println("Failed to detect and initialize IMU!");
    while (1) {
    };
  }
  Serial1.println("Enable IMU...");
  imu.enableDefault();

  pinMode(GREEN_LED, OUTPUT);
}

char report[80];

void loop() {
  // Serial1.print("right speed (ticks/s): ");
  // Serial1.println(get_right_speed());

  Serial1.println("reading IMU");
  imu.read();
  snprintf(report, sizeof(report), "A: %6d %6d %6d    G: %6d %6d %6d", imu.a.x,
           imu.a.y, imu.a.z, imu.g.x, imu.g.y, imu.g.z);
  Serial1.println(report);

  ledVal |= 1;
  digitalWrite(GREEN_LED, ledVal);

  delay(100);
}
#include "Led.h"
#include "Ultrasonic.h"
#include "ServoConfig.h"

Led led(6, 5);
// Ultrasonic ultrasonic;
 ServoConfig servito;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servito.setPin(2);
}

void loop() {
  // led.redFade(10, 5);
  // servito.rotate(0, 90, 1500);
}

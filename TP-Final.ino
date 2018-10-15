#include "Led.h"

Led led(11, 10, 9);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  led.redOn(50);
}

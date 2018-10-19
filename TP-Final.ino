#include "Led.h"
#include "Ultrasonic.h"
#include "ServoConfig.h"

Led led;
ServoConfig servito;
Ultrasonic ultrasonic;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  led.set(6, 5);
  servito.setPin(2);
  ultrasonic.set(12, 13);
}

void loop() {
  // servito.rotate(0, 90, 1500);
  ultrasonic.on();
  if (ultrasonic.getDistance() < 15) {
    led.blueOff(5);
    led.redOn(10);
  } else if (ultrasonic.getDistance() > 15)
  {
    led.redOff(5);
    led.blueOn(10);
  }
}

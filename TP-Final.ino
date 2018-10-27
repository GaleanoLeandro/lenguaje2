#include "Led.h"
#include "Ultrasonic.h"
#include "ServoConfig.h"

Led led;
ServoConfig servito;
Ultrasonic ultrasonic;
NonBlockDelay del;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  led.set(6, 5);
  servito.setPin(2);
  ultrasonic.set(12, 13);
}

void loop() {
  ultrasonic.on();
  ultrasonic.select();

  if (ultrasonic.state == "standby") {
    led.redOff();
    led.blueOn();
    servito.restart();
  }
  if (ultrasonic.state == "start") {
    led.blueOff();
    led.redOn();
    servito.rotate(0, 90, 2000);
  }
  if (ultrasonic.state == "rejected") {
    servito.reject();
    // led.reject();
  }
}

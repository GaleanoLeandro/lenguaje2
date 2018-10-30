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
  // servito.start(3, 5);

  ultrasonic.on();
  ultrasonic.select();

  if (ultrasonic.state == "standby") {
    led.redOff();
    led.blueOn();
    servito.restart();
  }
  if (ultrasonic.state == "start") {
    servito.start(3, 15);
    led.blueOff();
    led.redOn();
  }
  if (ultrasonic.state == "rejected") {
    servito.reject(50);
    led.reject();
    led.blueOff();
  }
}

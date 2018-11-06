#include "Delay.h"
#include "Led.h"
#include "Ultrasonic.h"
#include "ServoConfig.h"

Led led;
ServoConfig servito1, servito2;
Ultrasonic ultrasonic;
int vel; // Velocidad del motor
int redLevel, blueLevel;

void setup() {
  Serial.begin(9600);
  led.set(6, 5);
  servito1.setPin(2);
  servito2.setPin(3);
  ultrasonic.set(12, 13);
}

void loop() {
  ultrasonic.on();
  ultrasonic.select();

  if (ultrasonic.state == "standby") {
    blueLevel = (ultrasonic.deciding) ? 255 : 30;
    led.redOff();
    led.blueOn(blueLevel);
    servito1.restart();
    servito2.restart();
  } else if (ultrasonic.state == "start") {
      if (ultrasonic.level == 1) {
        redLevel = 15;
        vel = 25;
      } else if (ultrasonic.level == 2) {
        redLevel = 40;
        vel = 18;
      } else if (ultrasonic.level == 3) {
        redLevel = 100;
        vel = 8;
      } else if (ultrasonic.level == 4) {
        redLevel = 255;
        vel = 4;
      }
      servito1.start(7, vel);
      servito2.start(7, vel);

      led.blueOff();
      led.redOn(redLevel);
  } else if (ultrasonic.state == "rejected") {
      servito1.reject();
      servito2.reject();
      led.reject();
      led.blueOff();
  }
}

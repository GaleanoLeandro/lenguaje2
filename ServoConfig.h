#include <Servo.h>

class ServoConfig
{
private:
  Servo servo;
  NonBlockDelay servoD, servoD1;
  int servoPin;
  unsigned int angle;
  int dir;
  int minAngle = 0;
  int maxAngle = 180;
  bool toggle = true;
  int minPulse = 650;
  int maxPulse = 2550;
  int count; // Variable usada en la funcion reject para generar el movimiento de ida y vuelta solo dos veces.

public:
  void setPin(int pin) {
    servoPin = pin;
    servo.attach(servoPin);
  }
  // void rotate (int ang1 = 0, int ang2 = 180, int delayTime = 3000) {
  //   if (d.Timeout()) {
  //     angle = (angle == ang2) ? ang1 : ang2;
  //     servo.write(angle);
  //     d.Delay(delayTime);
  //   }
  // }
  void reject (int ang = 20) {
    int oldAngle = angle - ang;

    if (servoD.Timeout() && count < 2) {
      angle = (toggle) ? angle + ang : oldAngle;
      toggle = !toggle;
      servo.write(angle);
      count++;
      servoD.Delay(80);
    }
  }
  void restart () {
    count = 0;
  }
  void start (int range = 3, int level = 50)  {
    int randomDir;
    if (servoD1.Timeout()) {
      randomDir = (random(0, 2) == 0) ? 1 : -1;
      servoD1.Delay(random(level * 6, level * 8));
    }
    if (servoD.Timeout())
    {
      range = range * randomDir;
      dir = range;
      angle += dir;
      if (angle < minAngle) {
        angle = range;
      }
      if (angle > maxAngle) {
        angle = angle - range;
      }
      servo.write(angle);
      // Serial.print("angle: ");
      // Serial.println(angle);
      servoD.Delay(random(level, level * 2));
    }
  }
  void off () {
    servo.detach();
  }
};

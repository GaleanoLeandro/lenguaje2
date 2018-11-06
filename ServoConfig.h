#include <Servo.h>

class ServoConfig
{
  Servo servo;
  NonBlockDelay d, servoD, servoD1;
  int servoPin;
  unsigned int angle;
  int dir;
  int minAngle = 0;
  int maxAngle = 180;
  bool toggle = true;
  int minPulse = 650;
  int maxPulse = 2550;
  int randomDir;
  int count; // Variable usada en la funcion reject para generar el movimiento de ida y vuelta solo dos veces.

  public:
    void setPin(int pin) {
      servoPin = pin;
      servo.attach(servoPin);
    }
    void reject (int ang = 60) {
      int oldAngle = angle - ang;

      if (servoD.Timeout() && count < 2) {
        angle = (toggle) ? angle + ang : oldAngle;
        toggle = !toggle;
        servo.write(angle);
        count++;
        servoD.Delay(250);
      }
    }
    void rotate (int ang1 = 0, int ang2 = 180, int delayTime = 3000) {
      if (d.Timeout()) {
        angle = (angle == ang2) ? ang1 : ang2;
        servo.write(angle);
        d.Delay(delayTime);
      }
    }
    void restart () {
      count = 0;
      angle = 0;
      servo.write(angle);
    }
    void start (int range = 3, int delayLevel = 20)  {
      if (servoD1.Timeout()) {
        randomDir = (random(0, 2) == 0) ? 1 : -1;
        servoD1.Delay(random(delayLevel * 8, delayLevel * 10));
      }
      if (servoD.Timeout())
      {
        range = range * randomDir;
        dir = range;
        angle += dir;
        if (angle <= minAngle) {
          angle = range;
        }
        if (angle >= maxAngle) {
          angle = angle - range;
        }
        servo.write(angle);
        // Serial.print("angle: ");
        // Serial.println(angle);
        servoD.Delay(random(delayLevel, delayLevel * 2));
      }
    }
    void off () {
      servo.detach();
    }
};

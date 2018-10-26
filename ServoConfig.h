#include <Servo.h>

class ServoConfig
{
private:
  Servo servo;
  NonBlockDelay d;
  int servoPin;
  int angle;
  bool toggle = true;
  int minPulse = 650;
  int maxPulse = 2550;
  int count;

public:
  void setPin(int pin) {
    servoPin = pin;
    servo.attach(servoPin);
  }
  void rotate (int ang1 = 0, int ang2 = 180, int delayTime = 3000) {
    if (d.Timeout()) {
      angle = (angle == ang2) ? ang1 : ang2;
      servo.write(angle);
      d.Delay(delayTime);
    }
  }
  void reject (int ang = 20) {
    int oldAngle = angle - ang;

    if (d.Timeout() && count < 2) {
      angle = (toggle) ? angle + ang : oldAngle;
      toggle = !toggle;
      servo.write(angle);
      count++;
      d.Delay(200);
    }
  }
  void restart () {
    count = 0;
  }
  void off () {
    servo.detach();
  }
};

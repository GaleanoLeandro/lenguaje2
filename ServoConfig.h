#include <Servo.h>

class ServoConfig
{
private:
  Servo servo;
  NonBlockDelay d;
  int servoPin;
  int angle;
  int minPulse = 650;
  int maxPulse = 2550;

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
  void off () {
    servo.detach();
  }
};

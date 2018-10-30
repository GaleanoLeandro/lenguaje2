#include "Delay.h"

class Led
{ 
  private:
    NonBlockDelay ledD;
    int redPin, red;
    int bluePin, blue;
    bool toggle;

  public:
    void set (int r, int b) {
      toggle = true;
      redPin = r;
      bluePin = b;

      pinMode(redPin, OUTPUT);
      pinMode(bluePin, OUTPUT);

      analogWrite(redPin, 0);
      analogWrite(bluePin, 0);
    }
    void redOn(int fadeSpeed = 100, int level = 256)
    {
      analogWrite(redPin, 255);
      // if (red < level && d.Timeout())
      // {
      //   analogWrite(redPin, red);
      //   // Serial.println(red);
      //   red++;
      //   d.Delay(fadeSpeed);
      // }
    }
    void redOff(int fadeSpeed = 100)
    {
      analogWrite(redPin, 0);
      // if (red > 0 && d.Timeout())
      // {
      //   analogWrite(redPin, red);
      //   // Serial.println(red);
      //   red--;
      //   d.Delay(fadeSpeed);
      // }
    }
    void blueOn(int fadeSpeed = 100, int level = 256)
    {
      analogWrite(bluePin, 255);
      // if (blue < level && d.Timeout())
      // {
      //   analogWrite(bluePin, blue);
      //   // Serial.println(blue);
      //   blue++;
      //   d.Delay(fadeSpeed);
      // }
    }
    void blueOff(int fadeSpeed = 100)
    {
      analogWrite(bluePin, 0);
      // if (blue > 0 && d.Timeout())
      // {
      //   analogWrite(bluePin, blue);
      //   // Serial.println(blue);
      //   blue--;
      //   d.Delay(fadeSpeed);
      // }
    }
    void reject() {
      if (ledD.Timeout()) {
        int level = toggle ? 220 : 0;
        toggle = !toggle;
        analogWrite(redPin, level);
        ledD.Delay(80);
      }
    }
};

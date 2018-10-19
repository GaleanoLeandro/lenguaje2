#include "Delay.h"

NonBlockDelay d;

class Led
{ 
  private:
    int redPin, red;
    int bluePin, blue;
    bool toggle;

  public:
    set (int r, int b) {
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
      if (red < level && d.Timeout())
      {
        analogWrite(redPin, red);
        // Serial.println(red);
        red++;
        d.Delay(fadeSpeed);
      }
    }
    void redOff(int fadeSpeed = 100)
    {
      if (red > 0 && d.Timeout())
      {
        analogWrite(redPin, red);
        // Serial.println(red);
        red--;
        d.Delay(fadeSpeed);
      }
    }
    void blueOn(int fadeSpeed = 100, int level = 256)
    {
      if (blue < level && d.Timeout())
      {
        analogWrite(bluePin, blue);
        // Serial.println(blue);
        blue++;
        d.Delay(fadeSpeed);
      }
    }
    void blueOff(int fadeSpeed = 100)
    {
      if (blue > 0 && d.Timeout())
      {
        analogWrite(bluePin, blue);
        // Serial.println(blue);
        blue--;
        d.Delay(fadeSpeed);
      }
    }
    void redFade(int fadeIn = 200, int fadeOut = 200) {
      if (toggle)
      {
        redOn(fadeIn);
      }
      else
      {
        redOff(fadeOut);
      }
      if (red > 253 || red < 1)
      {
        toggle = !toggle;
      }
    }
};

#include "Delay.h"

NonBlockDelay d;

int period = 1000;
unsigned long time_now = 0;

class Led
{ 
  private:
    int red;
    int green;
    int blue;
    int brightness;

  public:
    Led(int r, int g, int b);
    void on();
    void off();
    void redOn(int fadeSpeed = 200);
    void redOff(int fadeSpeed = 200);
    int getBrightness();
};

Led::Led (int r, int g, int b) {
  red = r;
  green = g;
  blue = b;

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void Led::on()
{
  analogWrite(red, 255);
  analogWrite(green, 255);
  analogWrite(blue, 255);

  Serial.println("Led on");
}

void Led::off()
{
  analogWrite(red, 0);
  analogWrite(green, 0);
  analogWrite(blue, 0);

  Serial.println("Led off");
}

void Led::redOn(int fadeSpeed)
{
  if (brightness < 256 && d.Timeout()) {
    analogWrite(red, brightness);
    // Serial.println(brightness);
    brightness++;
    d.Delay(fadeSpeed);
  }
}

void Led::redOff(int fadeSpeed)
{
  if (brightness > 0 && d.Timeout())
  {
    analogWrite(red, brightness);
    // Serial.println(brightness);
    brightness--;
    d.Delay(fadeSpeed);
  }
}

int Led::getBrightness() {
  return brightness;
}

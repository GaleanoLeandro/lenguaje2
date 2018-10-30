#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#endif

class NonBlockDelay
{
  unsigned long iTimeout;
  unsigned long microsTimeout;
  int count;
  bool timeoutState;

  public:
    void Delay(unsigned long);
    void DelayInMicros(unsigned long);
    bool Timeout(void);
    bool TimeoutInMicros(void);
    unsigned long Time(void);
    bool onceTimeout(unsigned long);
};

void NonBlockDelay::Delay(unsigned long t)
{
  iTimeout = millis() + t;
  return;
};
void NonBlockDelay::DelayInMicros(unsigned long t)
{
  microsTimeout = micros() + t;
  return;
};
bool NonBlockDelay::Timeout(void)
{
  return (iTimeout < millis());
}
bool NonBlockDelay::TimeoutInMicros(void)
{
  return (microsTimeout < micros());
}
unsigned long NonBlockDelay::Time(void)
{
  return iTimeout;
}
bool NonBlockDelay::onceTimeout(unsigned long timeout = 3000) {
  if (Timeout()) {
    if (count >= 1) {
      count = 0;
      timeoutState = true;
    } else {
      timeoutState = false;
      count++;
    }
    Delay(timeout);
  }

  return timeoutState;
}
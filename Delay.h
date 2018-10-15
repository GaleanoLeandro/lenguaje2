#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#endif

class NonBlockDelay
{
  unsigned long iTimeout;

  public:
    void Delay(unsigned long);
    bool Timeout(void);
    unsigned long Time(void);
};

void NonBlockDelay::Delay(unsigned long t)
{
  iTimeout = millis() + t;
  return;
};
bool NonBlockDelay::Timeout(void)
{
  return (iTimeout < millis());
}
unsigned long NonBlockDelay::Time(void)
{
  return iTimeout;
}
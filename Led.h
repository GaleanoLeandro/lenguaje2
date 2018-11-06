class Led
{ 
  private:
    NonBlockDelay ledD;
    int redPin;
    int bluePin;
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
    void redOn(int level = 255)
    {
      analogWrite(redPin, level);
    }
    void redOff()
    {
      analogWrite(redPin, 0);
    }
    void blueOn(int level = 255)
    {
      analogWrite(bluePin, level);
    }
    void blueOff()
    {
      analogWrite(bluePin, 0);
    }
    void reject() {
      if (ledD.Timeout()) {
        int level = toggle ? 220 : 0;
        toggle = !toggle;
        analogWrite(redPin, level);
        ledD.Delay(200);
      }
    }
};

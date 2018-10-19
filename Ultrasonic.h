class Ultrasonic {
private:
  NonBlockDelay d1;
  int trigPin;
  int echoPin;
  long duration;
  int distance; // dist, para evitar conflicto con la función llamada distance
  int trigState; // pseudoboolean LOW y HIGH
  int delayTime; // variar tiempo entre 2 ms y 10 ms (microsegundos)

public:
  set (int trig, int echo)
  { 
    trigState = LOW;
    delayTime = 0,010;
    trigPin = trig;
    echoPin = echo;

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }
  void on () {
    // if (d1.Timeout())
    // { 
      // trigState = (trigState == LOW) ? HIGH : LOW; //toggle state
      // delayTime = (delayTime == 0,010) ? 0,002 : 0,010; //toggle time
      // digitalWrite(trigPin, trigState);
      // d1.Delay(delayTime);
    // }
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29;  // función copiada de un tutorial
    // Serial.println(distance);
  }
  void off() {
    digitalWrite(trigPin, LOW);

    duration = 0;
    distance = 0;
  }
  int getDistance () {
    return distance;
  }

};

NonBlockDelay d1;

class Ultrasonic {
private:
  int trigPin;
  int echoPin;
  long duration;
  int dist; // dist, para evitar conflicto con la función llamada distance
  int trigState; // pseudoboolean LOW y HIGH
  int delayTime; // variar tiempo entre 2 ms y 10 ms (microsegundos)

public:
  Ultrasonic(int trig, int echo)
  { 
    trigState = LOW;
    delayTime = 0.010;
    trigPin = trig;
    echoPin = echo;

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }
  int distance () {
    if (d1.Timeout())
    { 
      digitalWrite(trigPin, trigState);
      trigState = (trigState == LOW) ? HIGH : LOW; //toggle state
      delayTime = (delayTime == 0.010) ? 0.002 : 0.010; //toggle time
      Serial.println(trigState);
      d1.Delay(delayTime);
    }

    duration = pulseIn(echoPin, HIGH);
    dist = duration*0.034/2;  // función copiada de un tutorial
    return dist;
  }

};

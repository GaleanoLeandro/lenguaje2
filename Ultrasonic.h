/*
Estados del sensor
standby = disponible para aceptar o rechazar a alguien.
start = aceptó a alguien.
rejected = rechazo a alguien.
*/
class Ultrasonic {
  private:
    NonBlockDelay d;
    int trigPin;
    int echoPin;
    int restartTime;
    long duration;
    int distance;
    bool isSelected;
    int count;

  public:
    String state;
    // restartT tiempo en el que se mantiene "bloqueado" y desp se reinicia
    void set (int trig, int echo, int restartT = 5000)
    {
      state = "standby";
      restartTime = restartT;
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

      if (count >= 10) {
        restart();
        // Serial.print("state ");
        // Serial.println(state);
      }

      if (state == "start") {
        if (d.Timeout()) {
          count++;
          // Serial.print("count ");
          // Serial.println(count);
          d.Delay(1000);
        }
      } else if (state == "nouser") {
        delay(restartTime); // Espera 5 segundos desp de rechazar para volver a evaluar si alguien se acerca
        restart();
        // Serial.println("Estado reiniciado");
      }
    }
    void restart () {
      state = "standby";
      count = 0;
    }
    void off() {
      digitalWrite(trigPin, LOW);
      duration = 0;
      distance = 0;
    }
    void select (int limit = 10) {
      // limit = limite de distancia en cm para la detección
      if (distance <= limit) {
        if (state == "standby") {
          delay(random(1500, 3500));
          isSelected = random(2);
          // Serial.print("isSelected ");
          // Serial.println(isSelected);
          if (isSelected) {
            state = "start";
          } else {
            state = "rejected";
          }
        }
        return isSelected;
      } else if (distance > limit && state != "standby") {
        state = "nouser";
      }
      return;
    }
    int getDistance () {
      return distance;
    }
};

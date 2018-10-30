/*
Estados del sensor
standby = disponible para aceptar o rechazar a alguien.
start = aceptó a alguien.
rejected = rechazo a alguien.
nouser = el usuario se alejó.
*/
class Ultrasonic {
  private:
    NonBlockDelay d, d1, d2;
    int trigPin;
    int echoPin;
    int restartTime;
    long duration;
    int distance;
    bool isSelected;
    int count;
    // variables timer para activar sensor
    unsigned long previousMillis = 0; //will store last time viewTime was updated
    unsigned long previousMicros = 0; // will sotre last time TRIGGER was updated
    unsigned long viewTime = 200;
    int delayTime;
    long OnTime = 10; //microseconds of on-time
    long OffTime = 2; //microseconds of off-time
    int triggerState;

  public:
    String state = "standby";
    void set (int trig, int echo)
    {
      delayTime = OnTime;
      triggerState = HIGH;
      trigPin = trig;
      echoPin = echo;

      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }
    void on () {
      if (d.TimeoutInMicros()) {
        triggerState = (triggerState == HIGH) ? LOW : HIGH;
        delayTime = (delayTime == OnTime) ? OffTime : OnTime;
        d.DelayInMicros(delayTime);
      }
      digitalWrite(trigPin, triggerState); // update the actual trigger

      duration = pulseIn(echoPin, HIGH);

      if (d2.Timeout()) {
        d2.Delay(viewTime);
      } else {
        distance = (duration / 2) / 29; // función copiada de un tutorial
      }

      Serial.print("distance: ");
      Serial.println(distance);

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
      }
      if (state == "nouser") {
        if (d1.onceTimeout(5000)) {
          restart();
          Serial.println("Estado reiniciado");
        }
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
        if (state == "standby" && d.onceTimeout(random(1500, 3500)))
        {
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
};

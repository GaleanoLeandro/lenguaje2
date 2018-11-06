/*
Estados del sensor
standby = disponible para aceptar o rechazar a alguien.
start = aceptó a alguien.
rejected = rechazo a alguien.
nouser = el usuario se alejó.
*/
class Ultrasonic {
  NonBlockDelay d, d1, d2, d3;
  int trigPin;
  int echoPin;
  int restartTime;
  long duration;
  int distance;
  bool isSelected;
  int count;
  // variables timer para activar sensor
  unsigned long viewTime = 200;
  int delayTime;
  long OnTime = 10; //microseconds of on-time
  long OffTime = 2; //microseconds of off-time
  int triggerState;

  public:
    String state = "standby";
    bool deciding = false;
    int level = 1;
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
      if (state == "standby") {
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

        // Serial.print("distance: ");
        // Serial.println(distance);
      }

      if (count >= 8 && count < 13) {
        level = 2;
      } else if (count >= 13 && count < 16) {
        level = 3;
      } else if (count >= 16 && count < 20) {
        level = 4;
      } else if (count >= 20) {
        state = "rejected";
      }

      // Serial.print("level: ");
      // Serial.println(level);

      if (state == "start") {
        if (d.Timeout()) {
          count++;
          // Serial.print("count ");
          // Serial.println(count);
          d.Delay(1000);
        }
      }
      if (state == "nouser" || state == "rejected")
      {
        if (d1.onceTimeout(5000)) {
          restart();
          Serial.println("Estado reiniciado");
        }
      }
    }
    void restart () {
      state = "standby";
      level = 1;
      count = 0;
      distance = 0;
      deciding = false;
    }
    void select (int limit = 10) {
      // limit = limite de distancia en cm para la detección
      if (distance <= limit && distance != 0 && state == "standby") {
        deciding = true;
        if (d3.onceTimeout(random(3600, 6500))) {
          isSelected = random(2);
          Serial.print("isSelected ");
          Serial.println(isSelected);
          if (isSelected)
          {
            state = "start";
          } else {
            state = "rejected";
          }
        }
      } else {
        deciding = false;
      }
      return;
    }
};

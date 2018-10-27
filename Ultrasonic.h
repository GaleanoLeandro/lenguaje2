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
    // variables timer para activar sensor
    unsigned long previousMillis = 0; //will store last time viewTime was updated
    unsigned long previousMicros = 0; // will sotre last time TRIGGER was updated
    unsigned long viewTime = 200;
    long OnTime = 10; //microseconds of on-time
    long OffTime = 2; //microseconds of off-time
    int triggerState = LOW;

  public:
    String state = "standby";
    void set (int trig, int echo)
    {
      trigPin = trig;
      echoPin = echo;

      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    }
    void on () {

      // check to see if it's time to change the state of the TRIGGER
      unsigned long currentMicros = micros();

      if ((triggerState == LOW) && (currentMicros - previousMicros >= OffTime))
      {
        triggerState = HIGH; // turn it on
        previousMicros = currentMicros; // remember the time
        digitalWrite(trigPin, triggerState); // update the actual trigger
      }
      else if ((triggerState == HIGH) && (currentMicros - previousMicros >= OnTime))
      {
        triggerState = LOW; // turn it off
        previousMicros = currentMicros; // remember the time
        digitalWrite(trigPin, triggerState); // update the actual trigger
      }

      duration = pulseIn(echoPin, HIGH);

      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= viewTime)
      {
        previousMillis = currentMillis; // remember the time
      } else {
        distance = (duration / 2) / 29; // función copiada de un tutorial
      }

      Serial.print("distance: ");
      Serial.println(distance);

      // if (count >= 10) {
        // restart();
        // Serial.print("state ");
        // Serial.println(state);
      // }

      // if (state == "start") {
        // if (d.Timeout()) {
          // count++;
          // Serial.print("count ");
          // Serial.println(count);
          // d.Delay(1000);
        // }
      // } else if (state == "nouser") {
        // delay(5000); // Espera 5 segundos desp de rechazar para volver a evaluar si alguien se acerca
        // restart();
        // Serial.println("Estado reiniciado");
      // }
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

#include <Arduino.h>

const int fanRelayPin = 9;

void initFan() {
  pinMode(fanRelayPin, OUTPUT);
}

void startFan() {
  digitalWrite(fanRelayPin, HIGH);  // Relay ON 
  delay(10000); //enough time for the perfect rpm
}

void stopFan() {
  delay(15000); //enough time to drop everything
  digitalWrite(fanRelayPin, LOW);  // Relay OFF
}
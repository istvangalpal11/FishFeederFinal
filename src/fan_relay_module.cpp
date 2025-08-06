#include <Arduino.h>

const int fanRelayPin = 9;

void initFan() {
  pinMode(fanRelayPin, OUTPUT);
}

void startFan() {
  digitalWrite(fanRelayPin, HIGH);  // Relay ON 
}

void stopFan() {
  digitalWrite(fanRelayPin, LOW);  // Relay OFF
}
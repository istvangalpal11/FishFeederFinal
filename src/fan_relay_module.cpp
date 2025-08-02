#include <Arduino.h>

const int fanRelayPin = 9;

void initFan() {
  pinMode(fanRelayPin, OUTPUT);
}

void testFan() {
  digitalWrite(fanRelayPin, LOW);  // Relay ON (may be LOW-active)
  delay(3000); // Fan runs 3 sec

  digitalWrite(fanRelayPin, HIGH); // Relay OFF
  delay(5000);
}
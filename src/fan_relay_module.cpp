#include <Arduino.h>

const int fanRelayPin = 9;

void initFan() {
  pinMode(fanRelayPin, OUTPUT);
}

void testFan() {
  digitalWrite(fanRelayPin, HIGH);  // Relay ON 
  delay(3000); // Fan runs 3 sec

  digitalWrite(fanRelayPin, LOW); // Relay OFF
  delay(10000);
}
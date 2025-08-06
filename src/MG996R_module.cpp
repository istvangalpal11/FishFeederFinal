#include "MG996R_module.h"

// Servo object definitions (global instances)
Servo gate1, gate2, gate3;

const int gate1PIN = 2, gate2PIN = 3, gate3PIN = 4;

void initServo() {
    gate1.attach(gate1PIN);
    gate2.attach(gate2PIN);
    gate3.attach(gate3PIN);
}

void openGate(Servo& gate, int reps, int rotAng) {
  for (int i = 0; i < reps; i++) {
    gate.write(rotAng);  // Open gate
    delay(5000);
    gate.write(0);        // Close gate
    delay(10000);
  }
}
#ifndef MG996R_MODULE_H
#define MG996R_MODULE_H

#include <Servo.h>
#include <Arduino.h>

extern Servo gate1, gate2, gate3;

void initServo();
void openGate(Servo& gate, int reps, int rotAng);

#endif
#include <Arduino.h>
#include "DS1302_module.h"
#include "fan_relay_module.h"
#include "MG996R_module.h"

//feeding repetitions(control the quantity of the food)
int feedReps1 = 5;
int feedReps2 = 15;
int feedReps3 = 2;
//rotation angles(controls the flow-rate)
int rotateAngle1 = 60;
int rotateAngle2 = 90;
int rotateAngle3 = 50;

Servo* gates[3] = {&gate1, &gate2, &gate3};
int reps[3] = {feedReps1, feedReps2, feedReps3};
int angles[3] = {rotateAngle1, rotateAngle2, rotateAngle3};

void feedingProcess();

void setup() {
  Serial.begin(9600);
  initTime();
  initFan();
  initServo();
}

void loop() {
  if (isFeedTime()) {
    feedingProcess();
  }

  digitalClockDisplay(); //for testing
}

void feedingProcess(){
  startFan();

  for (int i = 0; i < 3; i++) {
    openGate(*gates[i], reps[i], angles[i]);  // Note the * to dereference
  }

  stopFan();
}
#include "feeder_module.h"
#include "MG996R_module.h"
#include "fan_relay_module.h"
#include "DS1302_module.h"

struct PondConfig {
  Servo* gate;
  int reps;
  int angle;
};

PondConfig ponds[3] = {
  {&gate1, 4, 100},
  {&gate2, 0, 90},
  {&gate3, 0, 50}
};

void feedingProcess() {
  delay(1000);
  startFan();

  for (int i = 0; i < 3; i++) {
    openGate(*ponds[i].gate, ponds[i].reps, ponds[i].angle);
  }

  stopFan();
}
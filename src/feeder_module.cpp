#include "feeder_module.h"
#include "MG996R_module.h"
#include "fan_relay_module.h"

struct PondConfig {
  Servo* gate;
  int reps;
  int angle;
};

PondConfig ponds[3] = {
  {&gate1, 2, 60},
  {&gate2, 3, 90},
  {&gate3, 2, 50}
};

void feedingProcess() {
  startFan();

  for (int i = 0; i < 3; i++) {
    openGate(*ponds[i].gate, ponds[i].reps, ponds[i].angle);
  }

  stopFan();
}
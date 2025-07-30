#include <Arduino.h>
#include <Servo.h>

Servo myServo;

// test servo angle sweep

// this is the new modification

//lest go

void setup() {
  myServo.attach(9);  // Control pin
}

void loop() {
  myServo.write(0);     // Turn to 0°
  delay(1000);
  myServo.write(90);    // Turn to 90°
  delay(1000);
  myServo.write(180);   // Turn to 180°
  delay(1000);
}
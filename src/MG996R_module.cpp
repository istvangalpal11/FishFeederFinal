#include <MG996R_module.h>

Servo gateServo;

void initServo(){
    gateServo.attach(10);
}

void testServo(){
  gateServo.write(90);  // Open gate
  delay(2000);          // Wait 2 seconds
  gateServo.write(0);   // Close gate
  delay(5000);          // Wait before next cycle
}

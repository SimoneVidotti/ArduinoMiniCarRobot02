#include <G1LIBMiniCarRobot02.h>

int LedGiallo_pin = 8;
int LedVerde_pin = 7;

Led LedGiallo(LedGiallo_pin);
Led LedVerde(LedVerde_pin);

void setup() {
  LedGiallo.SetupLed();
  LedVerde.SetupLed();
}

void loop() {
  LedGiallo.LampeggioLed(true, 300);
  LedVerde.LampeggioLed(true, 300);
}

#include <G1LIBMiniCarRobot02.h>

// Phototransistors 
int pin_BPX45_Sx = A13;
int pin_BPX45_Ce = A11;
int pin_BPX45_Dx = A8;
int LightVar_Sx = 0;
int LightVar_Ce = 0;
int LightVar_Dx = 0;

Phototransistor BPX45_Sx(pin_BPX45_Sx);
Phototransistor BPX45_Ce(pin_BPX45_Ce);
Phototransistor BPX45_Dx(pin_BPX45_Dx);

void setup() {
  BPX45_Sx.Phototransistor_Setup();
  BPX45_Ce.Phototransistor_Setup();
  BPX45_Dx.Phototransistor_Setup();
  Serial.begin(9600);
}

void loop() {
  LightVar_Sx = BPX45_Sx.Lettura();
  LightVar_Ce = BPX45_Ce.Lettura();
  LightVar_Dx = BPX45_Dx.Lettura();
  Serial.print(LightVar_Sx);
  Serial.print(LightVar_Ce);
  Serial.print(LightVar_Dx);
  Serial.println(" ");
  delay(100);
}
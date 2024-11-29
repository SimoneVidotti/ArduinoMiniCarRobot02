#include <G1LIBMiniCarRobot02.h>

Ultrasuoni HCSR04_Dx(22, 23);
Ultrasuoni HCSR04_Ce(9, 10);
Ultrasuoni HCSR04_Sx(12, 13);

float Lettura_Sx = HCSR04_Sx.DistanzaOstacoli();
float Lettura_Ce = HCSR04_Ce.DistanzaOstacoli();
float Lettura_Dx = HCSR04_Dx.DistanzaOstacoli();

void setup() {
  HCSR04_Sx.HCSR04_Setup();
  HCSR04_Ce.HCSR04_Setup();
  HCSR04_Dx.HCSR04_Setup();
  Serial.begin(9600);
}

void loop() {
  Serial.print(Lettura_Sx);
  Serial.print(" "); 
  Serial.print(Lettura_Ce);
  Serial.print(" "); 
  Serial.println(Lettura_Dx); 
}
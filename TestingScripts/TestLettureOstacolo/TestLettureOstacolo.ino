#include <G1LIBMiniCarRobot02.h> // Libreria classi per robottino Gruppo 1

// HCSR04 
const float SogliaHCSR04 = 7.50;
int pin_Trig = 52;
int pin_Echo = 53;
int LetturaHCSR04 = 0;

// IR sensors 
int pin_IR_Sx = 51;
int pin_IR_Dx = 50;
int LetturaIR_Sx = 0;
int LetturaIR_Dx = 0;

Ultrasuoni HCSR04(pin_Trig, pin_Echo, SogliaHCSR04);

IR_sensor IR_sensor_Sx(pin_IR_Sx);
IR_sensor IR_sensor_Dx(pin_IR_Dx);

void LettureOstacolo() {
  // Lettura Ultrasuoni
  LetturaHCSR04 = HCSR04.LetturaOstacolo();
  LetturaIR_Sx = IR_sensor_Sx.Read_IR();
  LetturaIR_Dx = IR_sensor_Dx.Read_IR();
}

void setup() {
  HCSR04.HCSR04_Setup();
  IR_sensor_Sx.IR_Setup();
  IR_sensor_Dx.IR_Setup();
  Serial.begin(9600);
}

void loop() {
  LettureOstacolo();
  Serial.print(LetturaIR_Sx );
  Serial.print(LetturaHCSR04);
  Serial.print(LetturaIR_Dx);
  Serial.println(" ");
  delay(100);
}

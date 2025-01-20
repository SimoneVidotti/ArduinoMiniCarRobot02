#include <G1LIBMiniCarRobot02.h>

int LoopState = 0;

// Motori cc 
int pin_a = 3;
int pin_dir_a = 2;
int pin_b = 9;
int pin_dir_b = 8;

// HCSR04 
const float SogliaHCSR04 = 7.0;
int pin_Trig = 52;
int pin_Echo = 53;
int LetturaHCSR04 = 0;

// IR sensors 
int pin_IR_Sx = 51;
int pin_IR_Dx = 50;
int LetturaIR_Sx = 0;
int LetturaIR_Dx = 0;

// Phototransistors 
int pin_BPX45_Sx = 1;
int pin_BPX45_Ce = 1;
int pin_BPX45_Dx = 1;
int LightVar_Sx = 0;
int LightVar_Ce = 0;
int LightVar_Dx = 0;

// NFC 
int pin_SDA = 1;
int pin_SCL = 1;

// Bluetooth 
int pin_bt_Tx = 1;
int pin_bt_Rx = 1;

// Dichiarazione Oggetti
Motori_cc Motori(pin_a, pin_b, pin_dir_a, pin_dir_b);

Ultrasuoni HCSR04(pin_Trig, pin_Echo, SogliaHCSR04);

IR_sensor IR_sensor_Sx(pin_IR_Sx);
IR_sensor IR_sensor_Dx(pin_IR_Dx);

Phototransistor BPX45_Sx(pin_BPX45_Sx);
Phototransistor BPX45_Ce(pin_BPX45_Ce);
Phototransistor BPX45_Dx(pin_BPX45_Dx);

NFC nfc(pin_SDA, pin_SCL);

HC05 bt_HC05(pin_bt_Rx, pin_bt_Tx);

void LettureOstacolo() {
  // Lettura Ultrasuoni
  LetturaHCSR04 = HCSR04.LetturaOstacolo();
  LetturaIR_Sx = IR_sensor_Sx.Read_IR();
  LetturaIR_Dx = IR_sensor_Dx.Read_IR();
}

void LetturaLuce() {
  int LightVar_Sx = BPX45_Sx.Lettura();
  int LightVar_Ce = BPX45_Ce.Lettura();
  int LightVar_Dx = BPX45_Dx.Lettura();
}

void setup() {
  Motori.MotoriSetup();
  HCSR04.HCSR04_Setup();
  IR_sensor_Sx.IR_Setup();
  IR_sensor_Dx.IR_Setup();
  BPX45_Sx.Phototransistor_Setup();
  BPX45_Ce.Phototransistor_Setup();
  BPX45_Dx.Phototransistor_Setup();
  nfc.NFC_Setup();
  bt_HC05.bt_Setup();

  // Tre giri su se stesso
  Motori.Tre_Giri();
}

void loop() {
  // case 000
  Motori.ZigZag(LoopState);

  LettureOstacolo();

  // --- Superamento Ostacoli ---
  // case 001
  if (LetturaIR_Sx == 0 && LetturaHCSR04 == 0 && LetturaIR_Dx == 1) {
    Motori.Indietro();
    delay(100);
    Motori.Sinistra();
    delay(350);
    LettureOstacolo();
  }

  // case 100
  if (LetturaIR_Sx == 1 && LetturaHCSR04 == 0 && LetturaIR_Dx == 0) {
    Motori.Indietro();
    delay(100);
    Motori.Destra();
    delay(350);
    LettureOstacolo();
  }

  // case 011
  if (LetturaIR_Sx == 0 && LetturaHCSR04 == 1 && LetturaIR_Dx == 1) {
    Motori.Sinistra();
    delay(700);
    LettureOstacolo();
  }

  // case 110
  if (LetturaIR_Sx == 1 && LetturaHCSR04 == 1 && LetturaIR_Dx == 0) {
    Motori.Destra();
    delay(700);
    LettureOstacolo();
  }

  // case 010
  if (LetturaIR_Sx == 0 && LetturaHCSR04 == 1 && LetturaIR_Dx == 0) {
    Motori.Giro_180();
    LettureOstacolo();
  }

  // case 101
  if (LetturaIR_Sx == 1 && LetturaHCSR04 == 0 && LetturaIR_Dx == 1) {
    Motori.Giro_180();
    LettureOstacolo();
  }

  // case 111
  if (LetturaIR_Sx == 1 && LetturaHCSR04 == 1 && LetturaIR_Dx == 1) {
    Motori.Giro_180();
    LettureOstacolo();
  }

  LoopState++;
}

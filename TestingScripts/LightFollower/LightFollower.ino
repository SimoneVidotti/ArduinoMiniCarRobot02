// Light follower, codice sorgente robottino, Vidotti Zhou Grecu G1 5TELA
#include <G1LIBMiniCarRobot02.h> // Libreria classi per robottino Gruppo 1

// Motori cc 
int pin_a = 3;
int pin_dir_a = 2;
int pin_b = 9;
int pin_dir_b = 8;

// HCSR04 
const float SogliaHCSR04 = 7.50;
float d_HCSR04 = 0;
int pin_Trig = 52;
int pin_Echo = 53;
int LetturaHCSR04 = 0;

// Phototransistors 
int pin_BPX45_Sx = A13;
int pin_BPX45_Ce = A11;
int pin_BPX45_Dx = A8;
int LightVar_Sx = 0;
int LightVar_Ce = 0;
int LightVar_Dx = 0;

// --- Istanziazione Oggetti ---
Motori_cc Motori(pin_a, pin_b, pin_dir_a, pin_dir_b);

Ultrasuoni HCSR04(pin_Trig, pin_Echo, SogliaHCSR04);

Phototransistor BPX45_Sx(pin_BPX45_Sx);
Phototransistor BPX45_Ce(pin_BPX45_Ce);
Phototransistor BPX45_Dx(pin_BPX45_Dx);
// --- ---

void Distanza_HCSR04() {
  d_HCSR04 =  HCSR04.LetturaDistanza();
}

void LettureLuce() {
  LightVar_Sx = BPX45_Sx.Lettura();
  LightVar_Ce = BPX45_Ce.Lettura();
  LightVar_Dx = BPX45_Dx.Lettura();
}

void setup() {
  Motori.MotoriSetup();
  HCSR04.HCSR04_Setup();
  BPX45_Sx.Phototransistor_Setup();
  BPX45_Ce.Phototransistor_Setup();
  BPX45_Dx.Phototransistor_Setup();
}

void loop() {
  // Trovare e seguire la luce

    Distanza_HCSR04();

    if (d_HCSR04 < 5) {
      Motori.Indietro();
      delay(200);
      Distanza_HCSR04();
    }

    LettureLuce();

    if (LightVar_Sx == 0 && LightVar_Ce == 0 && LightVar_Dx == 1) { // case 001
      Motori.Destra();
      delay(100);
      Motori.Avanti();
      delay(100);
      LettureLuce();
    } 
      
    if (LightVar_Sx == 1 && LightVar_Ce == 0 && LightVar_Dx == 0) { // case 100
      Motori.Sinistra();
       delay(100);
      Motori.Avanti();
      delay(100);
      LettureLuce();
    } 
      
    if (LightVar_Sx == 0 && LightVar_Ce == 1 && LightVar_Dx == 1) { // case 011
      Motori.Destra();
      delay(100);
      Motori.Avanti();
      delay(100);
      LettureLuce();
    } 
      
    if (LightVar_Sx == 1 && LightVar_Ce == 1 && LightVar_Dx == 0) { // case 110
      Motori.Sinistra();
      delay(100);
      Motori.Avanti();
      delay(100);
      LettureLuce();
    } 

    if (LightVar_Sx == 0 && LightVar_Ce == 1 && LightVar_Dx == 0) { // case 010
      Motori.Avanti();
      delay(100);
      LettureLuce();
    }

    if (LightVar_Sx == 1 && LightVar_Ce == 0 && LightVar_Dx == 1) { // case 010
      Motori.Avanti();
      delay(100);
      LettureLuce();
    }
      
    if (LightVar_Sx == 1 && LightVar_Ce == 1 && LightVar_Dx == 1) { // case 111
      Motori.Avanti();
      delay(100);
      LettureLuce();
    }

    Motori.Fermo(1);
}

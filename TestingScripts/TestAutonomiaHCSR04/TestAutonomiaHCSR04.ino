#include <G1LIBMiniCarRobot02.h>

Motori_cc Motori(3, 9, 2, 8);

Ultrasuoni HCSR04_Dx(22, 23);
Ultrasuoni HCSR04_Ce(9, 10);
Ultrasuoni HCSR04_Sx(12, 13);

bool Start = true;

float Lettura_Sx = HCSR04_Sx.DistanzaOstacoli();
float Lettura_Ce = HCSR04_Ce.DistanzaOstacoli();
float Lettura_Dx = HCSR04_Dx.DistanzaOstacoli();

void LetturaHCSR04s() {
  Lettura_Sx = HCSR04_Sx.DistanzaOstacoli();
  Lettura_Ce = HCSR04_Ce.DistanzaOstacoli();
  Lettura_Dx = HCSR04_Dx.DistanzaOstacoli();
}

void setup() {
  Motori.MotoriSetup();
  HCSR04_Sx.HCSR04_Setup();
  HCSR04_Ce.HCSR04_Setup();
  HCSR04_Dx.HCSR04_Setup();
}

void loop() {
  while(Start) {
    //Start
    delay(3000);
    Motori.GiroSuSeStesso();
    Start = false;
  }

  LetturaHCSR04s();

  while(Lettura_Sx > 5.0 && Lettura_Ce <= 5.0 && Lettura_Dx > 5.0) {
    Motori.Indietro();
    delay(10);
    Motori.Sinistra();
    delay(10);

    LetturaHCSR04s();
  }

  while(Lettura_Sx > 5.0 && Lettura_Ce <= 5.0 && Lettura_Dx <= 5.0) {
    Motori.Indietro();
    delay(10);
    Motori.Sinistra();
    delay(10);

    LetturaHCSR04s();
  }

  while(Lettura_Sx <= 5.0 && Lettura_Ce <= 5.0 && Lettura_Dx > 5.0) {
    Motori.Indietro();
    delay(10);
    Motori.Destra();
    delay(10);

    LetturaHCSR04s();
  }

  while(Lettura_Sx <= 5.0 && Lettura_Ce <= 5.0 && Lettura_Dx <= 5.0) {
    Motori.Indietro();
    delay(1000);
    Motori.Destra();
    delay(2000);

    LetturaHCSR04s();
  }

  while(Lettura_Sx > 5.0 && Lettura_Ce > 5.0 && Lettura_Dx > 5.0) {
    Motori.Avanti();

    LetturaHCSR04s();
  }
}
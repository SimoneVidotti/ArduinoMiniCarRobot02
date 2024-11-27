#include <G1LIBMiniCarRobot02.h>

// setup
void setup() {

}

// ciclo 
void loop() {
    Motori_cc Motori(3, 9, 2, 8);

    Ultrasuoni HCSR04_Dx(22, 23);
    Ultrasuoni HCSR04_Ce(9, 10);
    Ultrasuoni HCSR04_Sx(12, 13);

    Phototransistor Ph_Dx(A0);
    Phototransistor Ph_Sx(A1);
}
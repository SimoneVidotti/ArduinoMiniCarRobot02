// Per far funzionare questa libreria bisogna spostarla nella cartella delle librerie del Arduino IDE.
#ifndef G1LIBMINICARROBOT02_H
#define G1LIBMINICARROBOT02_H

// dichiarazione librerie necessarie
#include <Wire.h>
#include <SoftwareSerial.h> // per il modulo bluetooth HC-05
#include <Adafruit_PN532.h> // per sensore NFC PN532

// --- programmazione oggetti per robottino ---
// Motore cc
class Motori_cc {
    private:
        int pwm_a;  //PWM control for motor outputs 
        int pwm_b;  //PWM control for motor outputs  
        int dir_a;  //direction control for motor outputs 
        int dir_b;  //direction control for motor outputs 

    public:
        // Costruttore per i motori 
        Motori_cc(int pwma, int pwmb, int dira, int dirb) {
            // Dichiarazione pins
            pwm_a = pwma;
            pwm_b = pwmb;
            dir_a = dira;
            dir_b = dirb;
        }

        // --- setup pins motori ---
        void MotoriSetup() {
            pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
            pinMode(pwm_b, OUTPUT);
            pinMode(dir_a, OUTPUT);
            pinMode(dir_b, OUTPUT);
        }

        // --- movimenti ---
        void Indietro() {
            digitalWrite(dir_a, LOW); 
            digitalWrite(dir_b, LOW);

            analogWrite(pwm_a, 100);  
            analogWrite(pwm_b, 100);
        }

        void Avanti() {
            digitalWrite(dir_a, HIGH); 
            digitalWrite(dir_b, HIGH);  
  
            analogWrite(pwm_a, 100);  
            analogWrite(pwm_b, 100);
        }

        void Destra90() {
            digitalWrite(dir_a, HIGH); 
            digitalWrite(dir_b, HIGH);  
  
            analogWrite(pwm_a, 0);  
            analogWrite(pwm_b, 100);
        }

        void Sinistra90() {
            digitalWrite(dir_a, HIGH); 
            digitalWrite(dir_b, HIGH);  
  
  
            analogWrite(pwm_a, 100);  
            analogWrite(pwm_b, 0);

            delay(1000);
        }

        void Fermo () {
            analogWrite(pwm_a, 0);  
            analogWrite(pwm_b, 0);
        }
};

// Sensore ultrasuoni
class Ultrasuoni {
    private:
        int TrigPin;
        int EchoPin;

    public:
        // Costruttore ultrasuoni
        Ultrasuoni(int trigPin, int echoPin) {
            TrigPin = trigPin;
            EchoPin = echoPin;
        }

        // --- setup ultrasuoni pins ---
        void HCSR04_Setup() {
            // HCSR04 trig echo pins set
            pinMode(TrigPin, OUTPUT);
            pinMode(EchoPin, INPUT);
        }

        float DistanzaOstacoli() {
            // Pulire TrigPin sensore 
            digitalWrite(TrigPin, LOW);
            delayMicroseconds(2);
  
            //impulso di 10 microsecondi 
            digitalWrite(TrigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(TrigPin, LOW);
  
            // Leggi il tempo di ritorno dell'eco 
            long durata = pulseIn(EchoPin, HIGH);
  
            return (durata * 0.0343) / 2;
        }
};

// Phototransistors
class Phototransistor {
    private:
        int phototransistorPin;

    public:
        // Costruttore phototransistor
        Phototransistor(int PhototransistorPin) {
            phototransistorPin = PhototransistorPin;
        }

        // --- Setup phototransistor ---
        void Phototransistor_Setup() {
            pinMode(phototransistorPin, INPUT);
        }

        // --- actions phototransistor ---
        int Lettura() {
            int reading = analogRead(phototransistorPin);
            float voltage = reading * 5.0 / 1023.0;

            if (voltage >= 1) {
                return 0;
            } 

            return 1;
        }
};

// NFC PN532

// Modulo Bluetooth HC-05

#endif
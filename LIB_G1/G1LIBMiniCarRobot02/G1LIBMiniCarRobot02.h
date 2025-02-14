// Per far funzionare questa libreria bisogna spostarla nella cartella librerie Arduino IDE.
#ifndef G1LIBMINICARROBOT02_H
#define G1LIBMINICARROBOT02_H

// dichiarazione librerie necessarie
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h> // per il modulo bluetooth HC-05
#include <Adafruit_PN532.h> // per sensore NFC PN532

// --- programmazione oggetti per robottino ---
class Motori_cc {
    private:
        int pwm_a;  //PWM control for motor outputs 
        int pwm_b;  //PWM control for motor outputs  
        int dir_a;  //direction control for motor outputs 
        int dir_b;  //direction control for motor outputs 

    public:
        // Costruttore per i motori 
        Motori_cc(int pwma, int pwmb, int dira, int dirb) : pwm_a(pwma), pwm_b(pwmb), dir_a(dira), dir_b(dirb) {
            
        }

        // --- setup pins motori ---
        void MotoriSetup() {
            pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
            pinMode(pwm_b, OUTPUT);
            pinMode(dir_a, OUTPUT);
            pinMode(dir_b, OUTPUT);
            digitalWrite(dir_a, LOW); 
            digitalWrite(dir_b, LOW);  
            analogWrite(pwm_a, 0);  
            analogWrite(pwm_b, 0);
        }

        // --- movimenti ---
        void Indietro() {
            digitalWrite(dir_a, LOW); 
            digitalWrite(dir_b, LOW);

            analogWrite(pwm_a, 80);  
            analogWrite(pwm_b, 80);
        }

        void Avanti() {
            digitalWrite(dir_a, HIGH); 
            digitalWrite(dir_b, HIGH);  
  
            analogWrite(pwm_a, 80);  
            analogWrite(pwm_b, 80);
        }

        void ZigZag(int State) {
            int v_a;
            int v_b;

            digitalWrite(dir_a, HIGH); 
            digitalWrite(dir_b, HIGH);  

            if(State%2 == 0) {
                v_a = 80;
                v_b = 70;
            } else  {
                v_a = 70;
                v_b = 80;
            }
  
            analogWrite(pwm_a, v_a);  
            analogWrite(pwm_b, v_b);
        }

        void Destra() {
            digitalWrite(dir_a, LOW); 
            digitalWrite(dir_b, HIGH);

            analogWrite(pwm_a, 100);  
            analogWrite(pwm_b, 100);
        }

        void Sinistra() {
            digitalWrite(dir_a, HIGH); 
            digitalWrite(dir_b, LOW);

            analogWrite(pwm_a, 100);  
            analogWrite(pwm_b, 100);
        } 

        void Tre_Giri() {
            digitalWrite(dir_a, HIGH); 
            digitalWrite(dir_b, LOW);

            analogWrite(pwm_a, 100);  
            analogWrite(pwm_b, 100);

            delay(7500);
        }

        void Giro_180() {
            digitalWrite(dir_a, HIGH); 
            digitalWrite(dir_b, LOW);

            analogWrite(pwm_a, 100);  
            analogWrite(pwm_b, 100);

            delay(1250);
        }

        void Fermo (int d) {
            digitalWrite(dir_a, HIGH); 
            digitalWrite(dir_b, HIGH);
            analogWrite(pwm_a, 0);  
            analogWrite(pwm_b, 0);

            delay(d);
        }

        void StopLoop() {
            while(true) {
                digitalWrite(dir_a, HIGH); 
                digitalWrite(dir_b, HIGH);
                analogWrite(pwm_a, 0);  
                analogWrite(pwm_b, 0);
            }
        }
};

// Sensore ultrasuoni
class Ultrasuoni {
    private:
        int TrigPin;
        int EchoPin;
        const float SogliaUltrasuoni;

    public:
        // Costruttore ultrasuoni
        Ultrasuoni(int trigPin, int echoPin, const float sogliaUltrasuoni) : TrigPin(trigPin), EchoPin(echoPin),  SogliaUltrasuoni(sogliaUltrasuoni) {
            
        }

        // --- setup ultrasuoni pins ---
        void HCSR04_Setup() {
            // HCSR04 trig echo pins set
            pinMode(TrigPin, OUTPUT);
            pinMode(EchoPin, INPUT);
        }

        float LetturaDistanza() {
            // Pulire TrigPin sensore 
            digitalWrite(TrigPin, LOW);
            delayMicroseconds(2);
  
            //impulso di 10 microsecondi 
            digitalWrite(TrigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(TrigPin, LOW);
  
            // Leggi il tempo di ritorno dell'eco 
            long durata = pulseIn(EchoPin, HIGH);
  
            float Distanza = (durata * 0.0343) / 2;

            return Distanza;
        }

        int LetturaOstacolo() {
            // Pulire TrigPin sensore 
            digitalWrite(TrigPin, LOW);
            delayMicroseconds(2);
  
            //impulso di 10 microsecondi 
            digitalWrite(TrigPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(TrigPin, LOW);
  
            // Leggi il tempo di ritorno dell'eco 
            long durata = pulseIn(EchoPin, HIGH);
  
            float Distanza = (durata * 0.0343) / 2;

            if (Distanza <= SogliaUltrasuoni) 
                return 1;
            else
                return 0;
        }
};

// Phototransistors
class Phototransistor {
    private:
        int phototransistorPin;

    public:
        // Costruttore phototransistor
        Phototransistor(int PhototransistorPin) : phototransistorPin(PhototransistorPin) {
            
        }

        // --- Setup phototransistor ---
        void Phototransistor_Setup() {
            pinMode(phototransistorPin, INPUT);
        }

        // --- actions phototransistor ---
        int Lettura() {
            int reading = analogRead(phototransistorPin);
            float voltage = reading * 5.0 / 1023.0;

            if (voltage >= 1) 
                return 0;
            else
                return 1;
        }
};

class NFC {
    private:
        uint8_t success;
        uint8_t uid[7]; // Maximum UID size (7 bytes for MIFARE)
        uint8_t uidLength;

        String uidString;

        int SDA_pin;
        int SCL_pin;
        Adafruit_PN532 _nfc_; // Create an Adafruit_PN532 object

    public:
        // Constructor to initialize SDA and SCL pins
        NFC(int SDA, int SCL) : SDA_pin(SDA), SCL_pin(SCL), _nfc_(SDA, SCL) {
            // Initialization
        }

        // Setup method to initialize NFC
        void NFC_Setup() {
            _nfc_.begin();
            _nfc_.SAMConfig(); // Configure the PN532 to read RFID tags
        }

        // Check if an NFC card is available
        String Check_NFC() {
            uidString = "Nothing";
            uidLength = 0; 

            // Read NFC card
            success = _nfc_.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

            if (success) {
                uidString = "";

                for (uint8_t i = 0; i < uidLength; i++) {
                    uidString += String(uid[i], HEX); // Value in hexadecimal format
                    if (i < uidLength - 1) {
                        uidString += ":";
                    }
                }     
            } 

            return uidString; // Return the UID string or "Nothing"
        }
};

// Sensore IR analog
class IR_sensor {
    private:
        int IR_Pin;
        int LetturaIR;

    public:
        IR_sensor(int IRpin) : IR_Pin(IRpin) {

        }

        void IR_Setup() {
            pinMode(IR_Pin, INPUT);
        }

        int Read_IR() {
            LetturaIR = digitalRead(IR_Pin);

            if (LetturaIR == 0) 
                return 1;
            else
                return 0;
        }
};

// Bluetooth HC-05
class HC05 {
    private:
        int RxPin;
        int TxPin;
        SoftwareSerial bt; // Create a SoftwareSerial object for Bluetooth communication

    public:
        // Constructor to initialize the Rx and Tx pins
        HC05(int Rx, int Tx) : RxPin(Rx), TxPin(Tx), bt(Rx, Tx) {
            // Initialize the SoftwareSerial object
        }

        // Setup method to begin Bluetooth communication
        void bt_Setup() {
            bt.begin(9600); // Ensure the baud rate is correct
        }

        // Method to send a string over Bluetooth
        void SendString(String message) {
            bt.println(message); // Send the string over Bluetooth
        }

        // Method to read a string from Bluetooth 
        String ReadString() {
            String received = "";
            while (bt.available()) {
                char c = bt.read(); // Read a character
                received += c; // Append the character to the string
            }
            return received; // Return the received string
        }
};

// leds
class Led {
    private:
        int Led_pin;

    public:
        Led(int LedPin) : Led_pin(LedPin) {
            
        }

        void SetupLed() {
            pinMode(Led_pin, OUTPUT);
        }

        void AccendiLed() {
            digitalWrite(Led_pin, HIGH);
        }

        void SpegniLed() {
            digitalWrite(Led_pin, LOW);
        }

        void LampeggioLed(bool state, int t) {
            if(state) {
                digitalWrite(Led_pin, HIGH);
                delay(t);
                digitalWrite(Led_pin, LOW);
                delay(t);
            } else {
                digitalWrite(Led_pin, LOW);
            }
        }
};

#endif

/* Piccolo sketch per programmare HC-05 tramite
 *  Arduino e terminale di Arduino.
 */
#include<SoftwareSerial.h>

byte const RXpin=3;   //Questo pin va collegato al TX dell'HC-05
byte const TXpin=2;   //Questo pin va collegato all'RX dell'HC-05

SoftwareSerial MyBT(RXpin, TXpin);

void setup() {
  Serial.begin(9600);  //Velocita' di comunicazione sulla porta seriale (arbitraria) 
  MyBT.begin(38400);  //Velocita' di comunicazione sulla porta BlueTooth (imposta dal modulo)
  Serial.println("Digita comandi AT ... ");
}

void loop() {
  if (Serial.available()){      //Se da PC giungono caratteri
    MyBT.write(Serial.read());  //allora inviali al BlueTooth
  }
  if (MyBT.available()){        //Se dal BlueTooth giungono caratteri
    Serial.write(MyBT.read());  //allora inviali al PC
  }
}

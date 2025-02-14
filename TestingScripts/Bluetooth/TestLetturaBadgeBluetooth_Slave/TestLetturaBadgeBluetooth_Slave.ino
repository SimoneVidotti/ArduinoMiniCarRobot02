// slave 
#include <G1LIBMiniCarRobot02.h>

// Define the I2C address of the PN532
#define SDA_PIN  20 // Change if necessary, 20 -> mega
#define SCL_PIN  21 // Change if necessary, 21 -> mega

// Bluetooth pin incrociati
int pin_bt_Tx = 48;
int pin_bt_Rx = 49;

// Motori cc 
int pin_a = 3;
int pin_dir_a = 2;
int pin_b = 9;
int pin_dir_b = 8;

String Lettura_bt = "";

Motori_cc Motori(pin_a, pin_b, pin_dir_a, pin_dir_b);

NFC nfc_G1(SDA_PIN, SCL_PIN);

HC05 bt_HC05(pin_bt_Rx, pin_bt_Tx);

void setup() {
  nfc_G1.NFC_Setup();
  bt_HC05.bt_Setup();
  Motori.MotoriSetup();
}

void loop() {
  // In caso di stampa, Mettere monitor su "Both NL & CR"
  String LetturaNFC = nfc_G1.Check_NFC();
  Lettura_bt = bt_HC05.ReadChar();

  if (LetturaNFC != "Nothing") {
    bt_HC05.SendString(LetturaNFC);
    Serial.println(LetturaNFC);
  } 
}
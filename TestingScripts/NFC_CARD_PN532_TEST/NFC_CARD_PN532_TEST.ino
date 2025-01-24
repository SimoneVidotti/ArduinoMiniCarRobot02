#include <G1LIBMiniCarRobot02.h>

// Define the I2C address of the PN532
#define SDA_PIN  20 // Change if necessary, 20 -> mega
#define SCL_PIN  21 // Change if necessary, 21 -> mega

NFC nfc_G1(SDA_PIN, SCL_PIN);

void setup(void) {
  Serial.begin(115200);
  Serial.println("Hello!");

  nfc_G1.NFC_Setup();
  
  Serial.println("Waiting for an NFC card...");
}

void loop(void) {
  String LetturaNFC = nfc_G1.Check_NFC();

  if (LetturaNFC != "Nothing") {
    Serial.println("Found an NFC card!");
    
    Serial.print(LetturaNFC);
    
    Serial.println("");
  } else {
    //Add a small delay to avoid flooding the serial output
    delay(100);
  }
}
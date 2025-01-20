#include <Wire.h>
#include <Adafruit_PN532.h>

// Define the I2C address of the PN532
#define SDA_PIN  20 // Change if necessary, 20 -> mega
#define SCL_PIN  21 // Change if necessary, 21 -> mega

Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

void setup(void) {
  Serial.begin(115200);
  Serial.println("Hello!");

  nfc.begin();
  nfc.SAMConfig(); // Configure the PN532 to read RFID tags
  Serial.println("Waiting for an NFC card...");
}

void loop(void) {
  // Check if an NFC card is available
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;

  // Read the NFC card
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    Serial.println("Found an NFC card!");

    // Print the UID of the card
    Serial.print("UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
    Serial.print("UID Value: ");
    for (uint8_t i=0; i < uidLength; i++) {
      Serial.print(" 0x"); Serial.print(uid[i], HEX);
    }
    Serial.println("");

    byte saldo[4]; // Array per memorizzare il saldo
    // Invia il comando per leggere il saldo (questo è un esempio)
    // Assicurati di avere il comando corretto per la tua carta
    if (nfc.ntag2xx_ReadPage(4, saldo)) {
      // Supponiamo che il saldo sia memorizzato in un formato specifico
      float saldoRimanente = (saldo[0] << 8) + saldo[1]; // Esempio di conversione
      Serial.print("Saldo rimanente: ");
      Serial.println(saldoRimanente);
    }
    // Wait for the card to be removed
    delay(1000);
  } else {
    // Optional: Add a small delay to avoid flooding the serial output
    delay(100);
  }
}
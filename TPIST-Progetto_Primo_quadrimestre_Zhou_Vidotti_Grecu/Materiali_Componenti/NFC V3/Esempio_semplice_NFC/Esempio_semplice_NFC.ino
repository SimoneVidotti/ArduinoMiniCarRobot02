#include <Wire.h>                // Libreria per la comunicazione I2C
#include <Adafruit_PN532.h>      // Libreria Adafruit per PN532

// Definisci i pin I2C
#define SDA_PIN A4
#define SCL_PIN A5

// Crea un'istanza dell'oggetto PN532 usando l'I2C
Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

void setup(void) {
  Serial.begin(115200);         // Inizializza la comunicazione seriale
  Serial.println("Inizializzazione del modulo NFC...");

  nfc.begin();                  // Avvia la comunicazione con il modulo NFC
  
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.println("Modulo NFC non trovato!");
    while (1);                  // Se non trova il modulo NFC, blocca l'esecuzione
  }

  // Mostra la versione del firmware del modulo NFC
  Serial.print("Firmware trovato: 0x"); 
  Serial.println(versiondata, HEX);
  
  // Configura il modulo NFC per la lettura di tag
  nfc.SAMConfig();
  Serial.println("Modulo NFC pronto per leggere tag.");
}

void loop(void) {
  Serial.println("Posiziona un tag NFC vicino al lettore...");

  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Array per memorizzare l'UID
  uint8_t uidLength;                        // Variabile per la lunghezza dell'UID

  // Prova a leggere un tag NFC (protocollo ISO14443A come MIFARE)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Se viene rilevato un tag, stampa l'UID del tag
    Serial.println("Tag NFC trovato!");
    Serial.print("UID del tag: ");
    
    for (uint8_t i = 0; i < uidLength; i++) {
      Serial.print(" 0x");
      Serial.print(uid[i], HEX);  // Stampa l'UID in formato esadecimale
    }
    Serial.println();
    delay(1000);  // Aspetta 1 secondo prima di cercare di nuovo
  }
  else {
    Serial.println("Nessun tag trovato.");
  }

  delay(1000);  // Aspetta un po' prima di riprovare
}

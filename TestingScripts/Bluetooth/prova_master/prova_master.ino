#include <SoftwareSerial.h>

SoftwareSerial BTSerial(8, 9); // RX, TX

void setup() {
  Serial.begin(9600); // Monitor seriale
  BTSerial.begin(9600); // Assicurati che il baud rate sia corretto
  delay(1000); // Attendi la connessione
  Serial.println("Master pronto e in attesa di inviare messaggi...");
}

void loop() {
  // Invia la stringa al dispositivo slave
  BTSerial.println("Hello from Master!");
  Serial.println("Stringa inviata: Hello from Master!");
  delay(2000); // Aspetta 2 secondi prima di inviare di nuovo

  // Controlla se ci sono messaggi in arrivo
  if (BTSerial.available()) {
    String response = BTSerial.readStringUntil('\n'); // Legge la risposta fino a newline
    Serial.print("Risposta dallo slave: ");
    Serial.println(response);
  }
}
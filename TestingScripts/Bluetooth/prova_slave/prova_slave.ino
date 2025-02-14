#include <SoftwareSerial.h>

#define RxPin 12
#define TxPin 11
SoftwareSerial bt(RxPin, TxPin);

void setup() {
  Serial.begin(9600);
  bt.begin(9600); // Assicurati che il baud rate sia corretto
}

void loop() {
  // Controlla se ci sono messaggi in arrivo
  if (bt.available()) {
    String receivedMessage = bt.readStringUntil('\n');
    Serial.println("Received: " + receivedMessage);
    
    // Invia una risposta
    String responseMessage = "Hello from Slave!";
    bt.println(responseMessage);
    Serial.println("Sent: " + responseMessage);
  }

  delay(1000); // Aspetta 1 secondo prima di controllare di nuovo
}
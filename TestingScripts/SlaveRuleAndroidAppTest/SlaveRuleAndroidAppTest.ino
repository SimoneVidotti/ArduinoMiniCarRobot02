// Invio messaggi da app android a bluetooth test slave mode
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(12, 11); // RX, TX (connect HC-05 TX to Arduino pin 10 and RX to pin 11)

void setup() {
  Serial.begin(9600);       // Start the Serial monitor at 9600 baud
  bluetooth.begin(38400);   // Start Bluetooth communication at 38400 baud (default for HC-05)
}

void loop() {
  // Receiving data from the Bluetooth device
  if (bluetooth.available()) {
    String message = bluetooth.readString(); // Read the incoming message
    Serial.println("Messaggio ricevuto: " + message); // Print the message to the Serial Monitor
  }
}
const int phototransistorPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(phototransistorPin);
  float voltage = reading * 5.0 / 1023.0;

  if (voltage >= 1) {
    Serial.print("Phototransistor reading: /");
  } else {
    Serial.print("Phototransistor reading: Luce");
  }
  
  Serial.println(" ");
  
  delay("100");
}
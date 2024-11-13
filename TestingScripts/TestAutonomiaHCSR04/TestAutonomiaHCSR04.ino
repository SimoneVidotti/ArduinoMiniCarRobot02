int pwm_a = 3;  //PWM control for motor outputs 1 and 2 
int pwm_b = 9;  //PWM control for motor outputs 3 and 4 
int dir_a = 2;  //direction control for motor outputs 1 and 2 
int dir_b = 8;  //direction control for motor outputs 3 and 4 

// Definizione dei pin HCSR04 x3
int trigPinDestra = 22;
int echoPinDestra = 23;
int trigPinCentrale = 9;
int echoPinCentrale = 10;
int trigPinSinistra = 12;
int echoPinSinistra = 13;

void Indietro() {
  digitalWrite(dir_a, LOW); 
  digitalWrite(dir_b, LOW);

  analogWrite(pwm_a, 100);  
  analogWrite(pwm_b, 100);
}

void Avanti() {
  digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, HIGH);  
  
  
  analogWrite(pwm_a, 100);  
  analogWrite(pwm_b, 100);
}

void Destra90() {
  digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, HIGH);  
  
  
  analogWrite(pwm_a, 0);  
  analogWrite(pwm_b, 100);

  delay(1000);
}

void Sinistra90() {
  digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, HIGH);  
  
  
  analogWrite(pwm_a, 100);  
  analogWrite(pwm_b, 0);

  delay(1000);
}

void Fermo (int t) {
  analogWrite(pwm_a, 0);  
  analogWrite(pwm_b, 0);
  delay(t);
}

float DistanzaOstacoli(int trigPin, int echoPin) {
  // Pulire trigPin sensore 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  //impulso di 10 microsecondi 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Leggi il tempo di ritorno dell'eco 
  long durata = pulseIn(echoPin, HIGH);
  
  return (durata * 0.0343) / 2;
}

void GestisciOstacoli() {

}

void setup()
{
  // Motori cc control pins outputs
  pinMode(pwm_a, OUTPUT);  
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);

  // HCSR04 trig echo pins set
  pinMode(trigPinDestra, OUTPUT);
  pinMode(echoPinDestra, INPUT);
  pinMode(trigPinCentrale, OUTPUT);
  pinMode(echoPinCentrale, INPUT);
  pinMode(trigPinSinistra, OUTPUT);
  pinMode(echoPinSinistra, INPUT);
}

void loop() {

}

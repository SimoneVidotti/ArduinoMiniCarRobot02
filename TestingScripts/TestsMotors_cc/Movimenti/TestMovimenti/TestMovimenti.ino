int pwm_a = 3;  //PWM control for motor outputs 1 and 2 
int pwm_b = 9;  //PWM control for motor outputs 3 and 4 
int dir_a = 2;  //direction control for motor outputs 1 and 2 
int dir_b = 8;  //direction control for motor outputs 3 and 4 

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

void Fermo () {
  analogWrite(pwm_a, 0);  
  analogWrite(pwm_b, 0);
  delay(6000);
}

void setup()
{
  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);
}

void loop() {
  // Devi aggiungere dei delay.
  // Testa varie tempistiche e velocità.
  // Velocità migliori: 100/150

  /*
  Avanti();
  delay(3000);

  Destra90();

  Avanti();
  delay(3000);

  Sinistra90();

  Avanti();
  delay(3000);

  Indietro();
  delay(2000);

  Fermo();
  */

  Avanti();
  delay(2000);

  Fermo();
}
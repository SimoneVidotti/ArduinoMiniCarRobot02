int pwm_a = 3;  //PWM control for motor outputs 1 and 2 
int pwm_b = 9;  //PWM control for motor outputs 3 and 4 
int dir_a = 2;  //direction control for motor outputs 1 and 2 
int dir_b = 8;  //direction control for motor outputs 3 and 4 

void setup()
{
  pinMode(pwm_a, OUTPUT);  //Set control pins to be outputs
  pinMode(pwm_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);
}

void Indietro() {
  analogWrite(pwm_a, 0);  
  analogWrite(pwm_b, 0);
  
  delay(1000);
  
  analogWrite(pwm_a, 100);  
  analogWrite(pwm_b, 100);
  
  delay(5000);
}

void Avanti() {
  analogWrite(pwm_a, 0);  
  analogWrite(pwm_b, 0);
  digitalWrite(dir_a, HIGH); 
  digitalWrite(dir_b, HIGH);  
  analogWrite(pwm_a, 50);  
  analogWrite(pwm_b, 50);
  analogWrite(pwm_a, 0);  
  analogWrite(pwm_b, 0);
  
  delay(1000);
  
  analogWrite(pwm_a, 150);  
  analogWrite(pwm_b, 150);
  
  delay(5000);
}

void loop()
{ 
  Indietro();
}



//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  // Print a message to the LCD.
  lcd.init();
  lcd.backlight();
  
}


void loop()
{
   
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
  lcd.setCursor(0,1);
  lcd.print("Arduino!");
  delay(1000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Funziona");
  lcd.setCursor(0,1);
  lcd.print("Evviva");
  delay(1000);
  lcd.clear();
}




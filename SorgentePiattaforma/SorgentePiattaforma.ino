// codice piattaforma G1
#include <G1LIBMiniCarRobot02.h>
#include <LiquidCrystal_I2C.h>

// Leds
int LedGiallo_pin = 8;
int LedVerde_pin = 7;

// Bluetooth pin incrociati
int pin_bt_Tx = 4;
int pin_bt_Rx = 2;

HC05 bt_HC05(pin_bt_Rx, pin_bt_Tx);

LiquidCrystal_I2C lcd(0x27,16,2);

Led LedGiallo(LedGiallo_pin);
Led LedVerde(LedVerde_pin);

void setup(void) {
  bt_HC05.bt_Setup();
  lcd.init();
  lcd.backlight();
  LedGiallo.AccendiLed();
  LedVerde.SpegniLed();
}

void loop(void) {
  String Badge_str = "79:56:b0:f";
  String Lettura_bt = bt_HC05.ReadString();

  bool cls = true;



  while (Lettura_bt == Badge_str) {
    LedGiallo.SpegniLed();
    LedVerde.AccendiLed();

    if (cls) {
      lcd.clear();
      cls = false;
    }
    
    lcd.setCursor(0,0);
    lcd.print("Trovato!");
    lcd.setCursor(0,1);
    lcd.print(Lettura_bt);
    Serial.print(Lettura_bt);
  } 

  lcd.setCursor(0,0);
  lcd.print("Waiting...");
}
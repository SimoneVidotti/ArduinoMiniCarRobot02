// Light follower, codice sorgente robottino, Vidotti Zhou Grecu G1 5TELA
#include <G1LIBMiniCarRobot02.h> // Libreria classi per robottino Gruppo 1

// Area globale
int LoopState = 0;
const int DIM = 9;
String Vet_Superamenti[DIM]; // Memoria 10 superamenti, 0---9
String SuperamentoAttuale;
bool stop = false;

// Motori cc 
int pin_a = 3;
int pin_dir_a = 2;
int pin_b = 9;
int pin_dir_b = 8;

// HCSR04 
const float SogliaHCSR04 = 7;
float d_HCSR04 = 0;
int pin_Trig = 52;
int pin_Echo = 53;
int LetturaHCSR04 = 0;

// IR sensors 
int pin_IR_Sx = 51;
int pin_IR_Dx = 50;
int LetturaIR_Sx = 0;
int LetturaIR_Dx = 0;

// Phototransistors 
int pin_BPX45_Sx = A13;
int pin_BPX45_Ce = A11;
int pin_BPX45_Dx = A8;
int LightVar_Sx = 0;
int LightVar_Ce = 0;
int LightVar_Dx = 0;

// NFC 
int pin_SDA = 20;
int pin_SCL = 21;

// Bluetooth pin incrociati
int pin_bt_Tx = 48;
int pin_bt_Rx = 49;

// --- Istanziazione Oggetti ---
Motori_cc Motori(pin_a, pin_b, pin_dir_a, pin_dir_b);
Ultrasuoni HCSR04(pin_Trig, pin_Echo, SogliaHCSR04);
IR_sensor IR_sensor_Sx(pin_IR_Sx);
IR_sensor IR_sensor_Dx(pin_IR_Dx);
Phototransistor BPX45_Sx(pin_BPX45_Sx);
Phototransistor BPX45_Ce(pin_BPX45_Ce);
Phototransistor BPX45_Dx(pin_BPX45_Dx);
NFC nfc_G1(pin_SDA, pin_SCL);
HC05 bt_HC05(pin_bt_Rx, pin_bt_Tx);

// --- Funzioni ---
void LettureOstacolo() {
  // Lettura Ultrasuoni e IR
  LetturaHCSR04 = HCSR04.LetturaOstacolo();
  LetturaIR_Sx = IR_sensor_Sx.Read_IR();
  LetturaIR_Dx = IR_sensor_Dx.Read_IR();
}

void LettureLuce() {
  LightVar_Sx = BPX45_Sx.Lettura();
  LightVar_Ce = BPX45_Ce.Lettura();
  LightVar_Dx = BPX45_Dx.Lettura();
}

void Distanza_HCSR04() {
  d_HCSR04 =  HCSR04.LetturaDistanza();
}

void AnalizzaSuperamenti() {
  // Controllo ripetizioni di "Destra" e "Sinistra"
  int destraCount = 0;
  int sinistraCount = 0;
  int consecutiveCount = 1; // Contatore per movimenti consecutivi
  String lastMovement = ""; // Ultimo movimento registrato

  for (int i = 0; i < DIM; i++) {
    if (Vet_Superamenti[i] == "Destra") {
      destraCount++;
      if (lastMovement == "Destra") {
        consecutiveCount++;
      } else {
        consecutiveCount = 1; // Reset del contatore
      }
      lastMovement = "Destra";
    } else if (Vet_Superamenti[i] == "Sinistra") {
      sinistraCount++;
      if (lastMovement == "Sinistra") {
        consecutiveCount++;
      } else {
        consecutiveCount = 1; // Reset del contatore
      }
      lastMovement = "Sinistra";
    }
  }

  // Controllo più di 3 movimenti consecutivi a destra o sinistra
  if (consecutiveCount > 3) {
    Motori.Indietro(); // Funzione per andare indietro
    delay(75);
  }

  // Controllo ripetizioni di movimenti alternati
  if (destraCount > 0 && sinistraCount > 0) {
    // Se ci sono movimenti alternati, controllo sequenza
    bool alternato = true;
    for (int i = 0; i < DIM - 1; i++) {
      if ((Vet_Superamenti[i] == "Destra" && Vet_Superamenti[i + 1] == "Destra") ||
          (Vet_Superamenti[i] == "Sinistra" && Vet_Superamenti[i + 1] == "Sinistra")) {
        alternato = false;
        break;
      }
    }

    if (alternato) {
      Motori.Giro_180(); // Gira di 180° se è bloccato
    }
  }
}

void setup() {
  Motori.MotoriSetup();
  HCSR04.HCSR04_Setup();
  IR_sensor_Sx.IR_Setup();
  IR_sensor_Dx.IR_Setup();
  BPX45_Sx.Phototransistor_Setup();
  BPX45_Ce.Phototransistor_Setup();
  BPX45_Dx.Phototransistor_Setup();
  nfc_G1.NFC_Setup();
  bt_HC05.bt_Setup();

  // Azzeramento memoria superamenti
  for (int i = 0; i < DIM; i++) {
    Vet_Superamenti[i] = ""; 
  }

  // Tre giri su se stesso
  Motori.Tre_Giri();
}

void loop() {
  Motori.ZigZag(LoopState);

  // Letture ostacolo
  LettureOstacolo();

  Distanza_HCSR04();
  
  LettureLuce();

  while (LightVar_Sx == 1 || LightVar_Ce == 1 || LightVar_Dx == 1) {
    Motori.Avanti();

    Distanza_HCSR04();

    stop = false;

    if (d_HCSR04 < 4) {
      Motori.Fermo(10);

      for (int i=0; i < 5; i++) {
        stop = false;
        String LetturaNFC = nfc_G1.Check_NFC();

        if (LetturaNFC != "Nothing") {
          bt_HC05.SendString(LetturaNFC);
          delay(100);
          stop = true;
        } 

        Motori.Destra();
        delay(25);
        LetturaNFC = nfc_G1.Check_NFC();
        if (LetturaNFC != "Nothing") {
          bt_HC05.SendString(LetturaNFC);
          delay(100);
          stop = true;
        } 
        Motori.Fermo(10);
        Motori.Sinistra();
        delay(25);
        LetturaNFC = nfc_G1.Check_NFC();
        if (LetturaNFC != "Nothing") {
          bt_HC05.SendString(LetturaNFC);
          delay(100);
          stop = true;
        } 
        Motori.Fermo(1);
      }

      if (stop) {
        Motori.Indietro();
        delay(1000);
        Motori.Tre_Giri();
        Motori.StopLoop();
      }
    }

    LettureLuce();
    
    if (LightVar_Sx == 0 && LightVar_Ce == 0 && LightVar_Dx == 1) { // case 001
      Motori.Destra();
      delay(100);
      LettureLuce();
    } 
      
    if (LightVar_Sx == 1 && LightVar_Ce == 0 && LightVar_Dx == 0) { // case 100
      Motori.Sinistra();
      delay(100);
      LettureLuce();
    } 
      
    if (LightVar_Sx == 0 && LightVar_Ce == 1 && LightVar_Dx == 1) { // case 011
      Motori.Destra();
      delay(100);
      LettureLuce();
    } 
      
    if (LightVar_Sx == 1 && LightVar_Ce == 1 && LightVar_Dx == 0) { // case 110
      Motori.Sinistra();
      delay(100);
      LettureLuce();
    } 

    if (LightVar_Sx == 0 && LightVar_Ce == 1 && LightVar_Dx == 0) { // case 010
      Motori.Avanti();
      delay(100);
      LettureLuce();
    }

    if (LightVar_Sx == 1 && LightVar_Ce == 0 && LightVar_Dx == 1) { // case 010
      Motori.Avanti();
      delay(100);
      LettureLuce();
    }
      
    if (LightVar_Sx == 1 && LightVar_Ce == 1 && LightVar_Dx == 1) { // case 111
      Motori.Avanti();
      delay(100);
      LettureLuce();
    }
  }

  // --- Superamento Ostacoli ---
  if (LetturaIR_Sx == 0 && LetturaHCSR04 == 0 && LetturaIR_Dx == 0) {
    SuperamentoAttuale = "/";
  }

  if (LetturaIR_Sx == 0 && LetturaHCSR04 == 0 && LetturaIR_Dx == 1) {
    Motori.Sinistra();
    delay(100);
    SuperamentoAttuale = "Sinistra";
  } 
  
  if (LetturaIR_Sx == 1 && LetturaHCSR04 == 0 && LetturaIR_Dx == 0) { // case 100
    Motori.Destra();
    delay(100);
    SuperamentoAttuale = "Destra";
  } 
  
  if (LetturaIR_Sx == 0 && LetturaHCSR04 == 1 && LetturaIR_Dx == 1) { // case 011
    Motori.Sinistra();
    delay(200);
    SuperamentoAttuale = "Sinistra+";
  }
  
   if (LetturaIR_Sx == 1 && LetturaHCSR04 == 1 && LetturaIR_Dx == 0) { // case 110
    Motori.Destra();
    delay(200);
    SuperamentoAttuale = "Destra+";
  }
  
  if (LetturaIR_Sx == 0 && LetturaHCSR04 == 1 && LetturaIR_Dx == 0) { // case 010
    Motori.Giro_180();
    SuperamentoAttuale = "180";
  } 
  
  if (LetturaIR_Sx == 1 && LetturaHCSR04 == 0 && LetturaIR_Dx == 1) { // case 101
    Motori.Giro_180();
    SuperamentoAttuale = "180";
  } 
  
  if (LetturaIR_Sx == 1 && LetturaHCSR04 == 1 && LetturaIR_Dx == 1) { // case 111
    Motori.Giro_180();
    SuperamentoAttuale = "180";
  } 

  while (d_HCSR04 < 4) {
      Motori.Fermo(1);

      stop = false;

      for (int i=0; i < 5; i++) {
        stop = false;

        String LetturaNFC = nfc_G1.Check_NFC();

        if (LetturaNFC != "Nothing") {
          bt_HC05.SendString(LetturaNFC);
          stop = true;
        } 

        Motori.Destra();
        delay(25);
        LetturaNFC = nfc_G1.Check_NFC();
        if (LetturaNFC != "Nothing") {
          bt_HC05.SendString(LetturaNFC);
          stop = true;
        } 
        Motori.Fermo(100);
        Motori.Sinistra();
        delay(25);
        LetturaNFC = nfc_G1.Check_NFC();
        if (LetturaNFC != "Nothing") {
          bt_HC05.SendString(LetturaNFC);
          stop = true;
        } 
        Motori.Fermo(100);
      }

      if (stop) {
        Motori.Indietro();
        delay(1000);
        Motori.Tre_Giri();
        Motori.StopLoop();
      }
    Distanza_HCSR04();
  }

  // Memorizza il superamento attuale
  Vet_Superamenti[LoopState] = SuperamentoAttuale;

  // Analizza i superamenti passati
  AnalizzaSuperamenti();

  // Incrementa LoopState
  LoopState++;
  if (LoopState >= DIM) {
    LoopState = 0;
  }
}
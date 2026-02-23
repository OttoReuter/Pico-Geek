#include <EEPROM.h>

// ================= EEPROM Layout =================
#define EEPROM_SIZE 512
#define EEPROM_PIN_START 0

int a = 0;
int valEE;

// Pin festlegen
int myPin[6] = {6,5,4,3,2,1};

void setup(){
  Serial.begin(9600);
  delay(5000);

  EEPROM.begin(EEPROM_SIZE);

  Serial.print("EEPROM schreiben\n");
  for (a = 0; a < 6; a++){
    // Adresse mit Adresswert beschreiben
    EEPROM.write(EEPROM_PIN_START + a, myPin[a]);
    Serial.print(a+1);
    Serial.print(" . Wert:  ");
    Serial.println(myPin[a]);
    delay(100);
  }
  EEPROM.commit();
}
void loop(){
}

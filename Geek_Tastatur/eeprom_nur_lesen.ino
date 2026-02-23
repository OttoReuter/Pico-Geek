#include <EEPROM.h>

// ================= EEPROM Layout =================
#define EEPROM_SIZE 512
#define EEPROM_PIN_START 0

int a = 0;
int valEE;

// leeren Pin definieren
int myPin[6] = {0,0,0,0,0,0};

void setup(){
  Serial.begin(9600);
  delay(5000);

  EEPROM.begin(EEPROM_SIZE);
  
  Serial.print("EEPROM lesen\n");
  for (int i = 0; i < 6; i++) {
    int val = EEPROM.read(EEPROM_PIN_START + i);
    Serial.print(val);
  }
}
void loop(){
}

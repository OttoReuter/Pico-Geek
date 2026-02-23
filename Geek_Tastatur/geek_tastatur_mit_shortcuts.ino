#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <EEPROM.h>
#include "Keyboard.h"

// ======== Display (Pins für Pico-Geek angepasst) ======
#define TFT_CS   9
#define TFT_RST  12
#define TFT_DC   8
#define TFT_BLK  13

// ================= Display & PinManager =================
Adafruit_ST7789 tft = Adafruit_ST7789(&SPI1, TFT_CS, TFT_DC, TFT_RST);

// ======== ADC Pin des Pico========
const int analogPin = 28;

// ================= EEPROM Layout =================
#define EEPROM_SIZE 512
#define EEPROM_PIN_START 0

// ======== Button Definition ========
enum Button {
  BTN_NONE,
  BTN_LEFT,
  BTN_UP,
  BTN_DOWN,
  BTN_RIGHT,
  BTN_OK
};

struct ButtonRange {
  int minVal;
  int maxVal;
  Button button;
};

ButtonRange buttons[] = {
  {0,     500,   BTN_LEFT},
  {1500,  4500,  BTN_UP},
  {5000,  7000,  BTN_DOWN},
  {10000, 15000, BTN_RIGHT},
  {20000, 30000, BTN_OK}
};

const int buttonCount = sizeof(buttons) / sizeof(buttons[0]);

// ======== PIN System ========
int pinDigits[6] = {0,0,0,0,0,0};
int correctPin[6] = {0,0,0,0,0,0};   // Beispiel-PIN
int cursorPos = 0;
bool pinActive = true; // true = Eingabe aktiv
bool locked = true;

// ======== Button State ========
Button lastButton = BTN_NONE;

// ======================================================
// Setup
// ======================================================
void setup() {
  Serial.begin(115200);
  delay(300);

  EEPROM.begin(EEPROM_SIZE);
  // ======== PIN einlesen ===========
  for (int i = 0; i < 6; i++) {
    int val = EEPROM.read(EEPROM_PIN_START + i);
    correctPin[i] = val;
  }

  SPI1.setSCK(10);
  SPI1.setTX(11);
  SPI1.begin();
  // Auflösung Analogbereich: 0-65535
  analogReadResolution(16);
  // Anzeige vorbereiten und starten
  tft.init(135,240);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setFont(&FreeSansBold12pt7b);
  tft.setCursor(50,30);
  tft.setTextColor(ST77XX_YELLOW);
  tft.print("Enter PIN");
  drawPin();
  Keyboard.begin();
}

// ======================================================
// Loop
// ======================================================
void loop() {
  Button current = getButton();
  // Flankenerkennung (nur bei neu gedrückter Taste reagieren)
  if (current != BTN_NONE && lastButton == BTN_NONE) {
    handleButton(current);
  }
  lastButton = current;
  delay(30);
}

// ======================================================
// ADC → Button
// ======================================================
Button getButton() {
  int value = analogRead(analogPin);
  for (int i = 0; i < buttonCount; i++) {
    if (value >= buttons[i].minVal &&
        value <= buttons[i].maxVal) {
      return buttons[i].button;
    }
  }
  return BTN_NONE;
}

// ======================================================
// Button Handling
// ======================================================
void handleButton(Button btn) {
  if (locked){
    switch (btn) {
      case BTN_UP:
        pinDigits[cursorPos]++;
        if (pinDigits[cursorPos] > 9)
          pinDigits[cursorPos] = 0;
        break;
      case BTN_DOWN:
        pinDigits[cursorPos]--;
        if (pinDigits[cursorPos] < 0)
          pinDigits[cursorPos] = 9;
        break;
      case BTN_LEFT:
        if (cursorPos > 0)
          cursorPos--;
        break;
      case BTN_RIGHT:
        if (cursorPos < 5)
          cursorPos++;
        break;
      case BTN_OK:
        checkPin();
        return;
      default:
        break;
    }
    drawPin();
  }
  if (!locked) {
    switch (btn) {
      case BTN_UP:
        Clear();
        tft.print("Desktop");
        Desktop();
        break;
      case BTN_DOWN:
        Clear();
        tft.print("Fenster zu");
        Fenster_zu();
        break;
      case BTN_LEFT:
        Clear();
        tft.print("Explorer");
        Explorer();
        break;
      case BTN_RIGHT:
        Clear();
        tft.print("Screenshot");
        Screenshot();
        break;
      case BTN_OK:
        Clear();
        tft.print("PC sperren");
        PC_sperren();
        break;
      default:
        break;
    }
    delay(5000);
    tft.fillRect(40,65,150,40,ST77XX_BLACK);
    tft.setCursor(50, 90);
    tft.setTextColor(ST77XX_WHITE);
    tft.print("bereit");
  }
}

void Clear() {
  tft.fillRect(40,65,150,40,ST77XX_RED);
  tft.setCursor(50, 90);
  tft.setTextColor(ST77XX_WHITE);
}

void Explorer() {
  // Datei-Explorer oeffnen
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('e');
  delay(100);
  Keyboard.releaseAll();
}

void Desktop() {
  // Desktop aufrufen
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('d');
  delay(100);
  Keyboard.releaseAll();
}

void Fenster_zu() {
  // aktuelles Fenster schliessen
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F4);
  delay(100);
  Keyboard.releaseAll();
}

void Screenshot() {
  // Screenshot aufnehmen
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('s');
  delay(100);
  Keyboard.releaseAll();
}

void PC_sperren() {
  // Desktop sperren 
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('l');
  delay(100);
  Keyboard.releaseAll();
}

// ======================================================
// PIN prüfen
// ======================================================
void checkPin() {
  bool correct = true;
  for (int i = 0; i < 6; i++) {
    if (pinDigits[i] != correctPin[i]) {
      correct = false;
      break;
    }
  }
  // keine Digits mehr anzeigen
  pinActive = false;
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(50, 90);
  if (correct) {
    tft.setTextColor(ST77XX_GREEN);
    tft.print("entsperrt");
    locked = false;
    // ab jetzt werden mit den Tasten Shortcuts gesenden
    tft.fillScreen(ST77XX_BLACK);
    tft.setCursor(50,30);
    tft.setTextColor(ST77XX_YELLOW);
    tft.print("USB-HID");
    tft.setCursor(50,90);
    tft.setTextColor(ST77XX_WHITE);
    tft.print("bereit");
  } else {
    tft.setTextColor(ST77XX_RED);
    tft.print("Pin falsch");
    delay(1500);
    resetPinEntry();
  }
}

void resetPinEntry() {
  pinActive = true;
  cursorPos = 0;
  for (int i = 0; i < 6; i++) {
    pinDigits[i] = 0;
  }
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(50,30);
  tft.setTextColor(ST77XX_YELLOW);
  tft.print("Enter PIN");
  drawPin();
}

// ======================================================
// Anzeige
// ======================================================
void drawPin() {
  if (!pinActive) return;
  int y = 90;
  int digitWidth = 16;   // Breite eines Digits
  int digitHeight = 20;  // Höhe des Digit-Bereichs
  int spacing = 20;      // Abstand zwischen Digits
  int xStart = 50;
  for (int i = 0; i < 6; i++) {
    int drawX = xStart + i * spacing;
    if (i == cursorPos) {
      // Aktives Digit: kompletten Bereich löschen
      tft.fillRect(drawX, y - 18, digitWidth, digitHeight + 6, ST77XX_BLACK);
      // Zahl zeichnen
      tft.setTextColor(ST77XX_YELLOW);
      tft.setCursor(drawX, y);
      tft.print(pinDigits[i]);    
    } else {
      // Abgeschlossenes Digit als Sternchen darstellen
      tft.fillRect(drawX, y - 16, digitWidth, digitHeight, ST77XX_BLACK);
      tft.setTextColor(ST77XX_WHITE);
      tft.setCursor(drawX, y);
      tft.print("*");
    }
  }
}

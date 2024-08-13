#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>


const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// Connections to Arduino
byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };

// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Create LCD object
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Setup LED
int Rpin = 11;
int Gpin = 12;
int Bpin = 13;

void setup() {
  // Setup LCD with backlight and initialize
  lcd.backlight();
  lcd.init();
  lcd.setCursor(3, 1);
  lcd.print("PC Controller");
  lcd.setCursor(2, 2);
  lcd.print("Please Enter Pin");
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  pinMode(Rpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  pinMode(Gpin, OUTPUT);

  statusColor(0,255,0);
  delay(50);
  statusColor(0,0,0);
}

// define vars
String pin = "";
String correctPin = "1234";
bool currentlyUnlocked = false;
bool onClearedScreen = false;

void loop() {
  // Get key value if pressed
  char customKey = customKeypad.getKey();

  if (customKey) {
    if (isdigit(customKey)) {
      pin += String(customKey);
      lcd.clear();
      if (pin.length() >= 19) {
        lcd.setCursor(0, 0);
        lcd.print("....................");
        lcd.setCursor(0, 1);
        lcd.print(pin.substring(pin.length() - 19)+"<");
        printCClear();
      } else {
        lcd.setCursor(0, 0);
        lcd.print("....................");
        lcd.setCursor(1, 1);
        lcd.print(pin+"<");
        printCClear();
      };
      
    } else {
      switch (customKey) {
        case 'C':
          if (!currentlyUnlocked) {
            clearPin();
          };
          break;
        case 'B':
          if (!currentlyUnlocked) {
            backspace();
          };
          break;
        case '*':
          validatePin(6500);
          break;
        case '#':
          validatePin(250);
          break;
        default:
          break;
      };
    };
  };
}

void printCClear() {
  lcd.setCursor(2, 2);
  lcd.print("Press C to clear");
  lcd.setCursor(0, 3);
  lcd.print("Press B to backspace");
};

void backspace(){
  pin.remove(pin.length()-1);
  lcd.clear();
      if (pin.length() >= 19) {
        lcd.setCursor(0, 0);
        lcd.print("....................");
        lcd.setCursor(0, 1);
        lcd.print(pin.substring(pin.length() - 19)+"<");
        printCClear();
      } else {
        lcd.setCursor(0, 0);
        lcd.print("....................");
        lcd.setCursor(1, 1);
        lcd.print(pin+"<");
        printCClear();
      };
  statusColor(100,100,100);
  delay(50);
  statusColor(0,0,0);
};
void statusColor(int R, int G, int B){
  analogWrite(Rpin, R);
  analogWrite(Bpin, B);
  analogWrite(Gpin, G);
};
void clearPin() {
  pin = "";
  lcd.clear();
  lcd.setCursor(6, 1);
  lcd.print("Cleared!");
  onClearedScreen = true;
  delay(2500);
  onClearedScreen=false;
  lcd.clear();
  
  lcd.setCursor(3, 1);
  lcd.print("PC Controller");
  lcd.setCursor(2, 2);
  lcd.print("Please Enter Pin");
};
void validatePin(int delayIfValid) {
  lcd.clear();
  if (pin == correctPin) {
    currentlyUnlocked = true;
    pin = "";
    lcd.setCursor(2, 1);
    statusColor(103, 237, 88);
    lcd.print("Toggling power...");
    
    digitalWrite(10, LOW);
    delay(delayIfValid);
    digitalWrite(10, LOW);
    statusColor(0,0,0);
    lock();

  } else {
    lcd.setCursor(1, 0);
    lcd.print("Incorrect Pin!");
    statusColor(255, 54, 54);
    delay(50);
    statusColor(0,0,0);
    lcd.setCursor(1, 1);
    lcd.print("Enter Pin");
    pin = "";
  };
};

void lock() {
  if (!currentlyUnlocked) { return; };
  digitalWrite(10, HIGH);
  lcd.clear();
  lcd.setCursor(3, 1);
  lcd.print("PC Controller");
  lcd.setCursor(2, 2);
  lcd.print("Please Enter Pin");
  currentlyUnlocked = false;
};
#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const byte ROWS = 4; 
const byte COLS = 4; 

const int RELAY_PIN = A3; //Solenoid Lock

char hexaKeys[ROWS][COLS] = {
  {'1', '4', '7', '*'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '#'},
  {'A', 'B', 'C', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char password[]= {'1', '4', '7', '*'};
char entered[4];
int pos = 0;

boolean passwordCheck(){
  for (int i = 0;  i < 4; i++){
    if( entered[i] != password[i] ){
      return false;
    }
  }
  return true;
}

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN,HIGH);
  
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    lcd.print(customKey);
    entered[pos] = customKey;
    pos++;
  }

  if (pos==4){
    if( passwordCheck()){
      lcd.clear();
      lcd.print("SUCCESS");
      digitalWrite(RELAY_PIN, LOW);  // Bounce out
      delay(2000);
      digitalWrite(RELAY_PIN, HIGH); // Lock in
    }
    else{
      lcd.clear();
      lcd.print("ERROR");
      delay(3000);  
    }
    lcd.clear();
    entered[4]={}; 
  }
}

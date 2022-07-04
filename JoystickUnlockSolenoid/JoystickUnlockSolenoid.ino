
/*
 * this is Arduino code to use Dual axis XY Joystick to read value of joystick position as X and Y and
 * also read the switch.
 * Other Arduino libarary and videos http://robojax.com/learn/arduino/
 
 * Watch the video for this code to learn it fully.
  * Watch the video here: https://youtu.be/6N8Iq353GM8
 * this code is offered "as is" without any warranty.
 * if you are sharing this code, you must keep this copyright note.
 */
 /*

 * Written for Robojax video on Jan 10, 2018
 * by Ahmad Shamshiri, in Ajax, Ontario, Canada
 * Copyright Robojax Inc. 
 */
 
/*
 * This is a dual axis joystick skitch for Arduino.
 * The position of joystick is read and displayed on serial monitor
 */
#define sw 6 
#define screenWidth 300
#define screenHeight 300

#include <LiquidCrystal_I2C.h> //LCD Screen
LiquidCrystal_I2C lcd(0x27,16,2);

const int RELAY_PIN = A3; //Solenoid Lock

char password[]= {'v', 'v', 'v', 'v'};
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

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(sw,INPUT_PULLUP);// setting pin sw as input
  pinMode(13,OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.print("");
  
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN,HIGH);
}

int isUp (int xP, int yP){
  return (yP>290 && xP>140 && xP<160)?1:0;}

int isDown (int xP, int yP){
  return (yP<10 && xP>140 && xP<160)?1:0;}

int isRight (int xP, int yP){
  return (xP>290 && yP>140 && yP<160)?1:0;}

int isLeft (int xP, int yP){
  return (xP<10 && yP>140 && yP<160)?1:0;}

void loop() {
  // Robojax Dual Axis joystick project
  int x = analogRead(A0);// read analog
  int y = analogRead(A1);
  int xPos = map(x, 0, 1023,0,screenWidth);
  int yPos = map(y, 0, 1023,0,screenHeight); 
  int sStat = digitalRead(sw);//
  // Robojax project

//  if(isUp(xPos,yPos)==1 || isDown(xPos,yPos)==1 || isRight(xPos,yPos)==1 || isLeft(xPos,yPos)==1){
//    Serial.print("X: ");
//  Serial.print(xPos);

//  Serial.print(" Y: ");
//  Serial.println(yPos);// Robojax prints y
//   }

if (isUp(xPos,yPos)==1){lcd.print("^");entered[pos]='^';pos++; digitalWrite(13,HIGH); delay(400);}
else if (isDown(xPos,yPos)==1){lcd.print("v");entered[pos]='v';pos++; digitalWrite(13,HIGH); delay(400);}
else if (isRight(xPos,yPos)==1){lcd.print(">");entered[pos]='>';pos++; digitalWrite(13,HIGH); delay(400);}
else if (isLeft(xPos,yPos)==1){lcd.print("<");entered[pos]='<';pos++; digitalWrite(13,HIGH); delay(400);}
else if (sStat == LOW){Serial.println("Switch pressed"); lcd.print("Switch");}
else digitalWrite(13,LOW); //Serial.println("UNKNOWN");

//BRANCH VERSION

//if(sStat == LOW){
//    Serial.println("Switch pressed");
    //lcd.setCursor(0,0);
//    lcd.print ("Switch");
//    digitalWrite(13,HIGH);// Turn LED ON
//  }else{
//    digitalWrite(13,LOW);// Turn LED OFF
//  }
//  delay(400);

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

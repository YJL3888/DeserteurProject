#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  // put your setup code here, to run once:
  // set up the LCD's number of columns and rows:
lcd.init();
lcd.backlight();
lcd.print("Hello World");
}

void loop() {
  // put your main code here, to run repeatedly:

}
